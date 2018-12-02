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
char dgramNum = '0';
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

int checkBind(int ss, sockaddr_in* local) {
    local->sin_family = AF_INET;
    local->sin_port = htons((u_short) rand());
    local->sin_addr.s_addr = inet_addr("127.0.0.1");
    int b = bind(ss, (sockaddr *) local, sizeof(*local));
    if (b < 0) {
        perror("bind");
        cerr << "Winsock error " << WSAGetLastError() << endl;
        exit(1);
    }
    cout << "Client "
         << inet_ntoa(local->sin_addr) << ":" << local->sin_port
         << " on socket " << ss << " started" << endl;
    return b;
}

char nextDgram() {
    if (dgramNum == '8') {
        dgramNum = '0';
        return '8';
    }
    return dgramNum++;
}

void printlnMsg(char *arr, int size) {
    for (int i = 2; i < size; i++) {
        printf( "%c", arr[i] );
    }
    if (arr[0] != '\0') printf("\n");
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
    cout << "[" << msg << "]" << endl;
    int rc = 0;
    rc = sendto(socket,
                msgarr,
                strlen(msgarr),
                0,
                (sockaddr*) dest,
                sizeof(*dest)
    );
    return rc > 0;
}

bool receive(int socket) {
    char buf[CMD_SIZE];
    sockaddr_in from;
    int fromlen = sizeof(from);
    int rc = recvfrom(socket,
                      buf,
                      sizeof(buf) + 1,
                      0,
                      (sockaddr*) &from,
                      &fromlen
    );
    if (rc <= 0) {
        cout << "Server not responding" << endl;
        return false;
    }
    cout << "MSG:" << buf << endl;

    WaitForSingleObject(hMutex, INFINITE);
    if (receivedClientListItem(buf, true)) {
        string cmd = CLIENT_NEXT_STR;
        stringstream ss;
        ss << cmd << " " << iClient++;
        send(Command(split(ss.str(), ' '), nextDgram()), socket, &from);
    }
    else iClient = 1;
    if (!receivedClientListItem(buf, false)) printlnMsg(buf, CMD_SIZE);

    if (requestedPing(buf)) send(responsePing(CMD_PING), socket, &from);

    ReleaseMutex(hMutex);

    return true;
}

DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    CONST PCDATA data = (PCDATA) lpParam;
    while (receive(data->socket));
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
    struct sockaddr_in local;
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
    checkBind(cs, &local);

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

        WaitForSingleObject(hMutex, INFINITE);
        if (!send(Command(tokens, nextDgram()), cs, &peer)) {
            cout << "Server not responding" << endl;
            exitServer(cs);
            return 0;
        }
        ReleaseMutex(hMutex);
    }

    return 0;
}

