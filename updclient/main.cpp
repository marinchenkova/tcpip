#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Command.h"
#include <thread>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

static const string EXIT_CMD = "exit";
static const string HELP_CMD = "help";

int iClient = 1;
HANDLE hMutex;


typedef struct ClientData {
    int socket;
    struct sockaddr_in *addr;
    int *addrlen;
} CDATA, *PCDATA;

bool send(string msg, int socket);


// Initialize Winsock
int initWinsock() {
    WSADATA wsaData;
    long iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return 1;
    }
    return 0;
}

int createSocket(struct sockaddr_in *peer, const char *addr, u_short port) {
    peer->sin_family = AF_INET;
    peer->sin_port = htons(port);
    peer->sin_addr.s_addr = inet_addr(addr);
    SOCKET ss = socket(AF_INET, SOCK_DGRAM, 0);
    if (ss < 0) {
        cerr << "Error calling SOCKET" << endl;
        exit(1);
    }
    return ss;
}

void printlnMsg(char *arr, int size) {
    for (int i = 2; i < size; i++) {
        printf( "%c", arr[i] );
    }
    printf("\n");
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool send(string msg, int socket, const sockaddr_in* dest) {
    const char* msgarr;
    msgarr = msg.c_str();
    int rc = 0;
    rc = sendto(socket, msgarr, strlen(msgarr), 0, (sockaddr*) dest, sizeof(*dest));
    return rc > 0;
}

bool readn(int n, int socket, const sockaddr_in* dest) {
    char buf[CMD_SIZE + 1];
    int rc = 0;
    int fill = 0;

    while (fill < n) {
        rc = recv(socket, buf + fill, n - fill, 0);
        if (rc <= 0) return false;
        if (buf[fill] == PREFIX) fill = 0;
        if (buf[0] == PREFIX) fill += rc;
    }

    WaitForSingleObject(hMutex, INFINITE);
    if (receivedClientListItem(buf, true)) {
        string cmd = CLIENT_NEXT_STR;
        stringstream ss;
        ss << cmd << " " << iClient++;
        send(Command(split(ss.str(), ' ')), socket, dest);
    }
    else iClient = 1;
    if (!receivedClientListItem(buf, false)) printlnMsg(buf, n);
    ReleaseMutex(hMutex);

    return true;
}

DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    CONST PCDATA data = (PCDATA) lpParam;
    while (readn(CMD_SIZE + 1, data->socket, data->addr));
    ExitThread(0);
}

void printHelp() {
    cout << "Commands:" << endl;
    cout << "id" << endl;
    cout << "balance" << endl;
    cout << "clients" << endl;
    cout << "get <int amount>" << endl;
    cout << "login <string login> <string password>" << endl;
    cout << "logout" << endl;
    cout << "payto <string id> <int amount>" << endl;
    cout << "put <int amount>" << endl;
    cout << "register <string login> <string password>" << endl;
    cout << endl;
}

void exitServer(int socket) {
    shutdown(socket, 2);
    closesocket(socket);
    cout << "Exit" << endl;
}

int main() {
    struct sockaddr_in peer;
    PCDATA receiveThreadData = new ClientData();
    int cs;
    string addr = "127.0.0.1";
    u_short port = 7500;

    initWinsock();
/*
    cout << "Enter IP address: ";
    cin >> addr;
    cout << endl;
    cout << "Enter port: ";
    cin >> port;
    cout << endl;
*/

    stringstream ss;
    ss << addr << ":" << port;
    string addrport = ss.str();

    cs = createSocket(&peer, addr.c_str(), port);

    cout << "Started at " << addrport << endl;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    receiveThreadData->socket = cs;
    receiveThreadData->addr = &peer;
    HANDLE hReceiveThread = CreateThread(
            NULL,
            0,
            &receiveThread,
            receiveThreadData,
            0,
            NULL
    );

    string cmd;
    vector<string> tokens;
    while (true) {
        getline(cin, cmd);
        cout << endl;
        tokens = split(cmd, ' ');

        if (tokens.size() == 0) continue;

        if (cmd == HELP_CMD) {
            printHelp();
            continue;
        }

        if (cmd == EXIT_CMD) {
            exitServer(cs);
            WaitForSingleObject(hReceiveThread, INFINITE);
            CloseHandle(hReceiveThread);
            CloseHandle(hMutex);
            break;
        }

        if (!send(Command(tokens), cs, &peer)) {
            cout << "Server not responding" << endl;
            exitServer(cs);
            return 0;
        }
    }

    return 0;
}

