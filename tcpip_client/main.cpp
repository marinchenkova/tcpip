#include <sys/types.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include <vector>
#include "Command.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

static const string EXIT = "exit";
static const string HELP = "help";

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

int createSocket(struct sockaddr_in *local, const char *addr, u_short port) {
    local -> sin_family = AF_INET;
    local -> sin_port = htons (port);
    local -> sin_addr.s_addr = inet_addr (addr);
    SOCKET ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss < 0) {
        cerr << "Error calling SOCKET" << endl;
        exit(1);
    }
    return ss;
}

int checkConnect(int ss, struct sockaddr_in local, string addr) {
    int b = connect(ss, (struct sockaddr *) &local, sizeof(local));
    if (b) {
        cerr << "Error calling CONNECT" << endl;
        ExitThread(1);
    }
    cout << "Connected to " << addr << endl;
    return b;
}

void printlnMsg(char *arr, int size) {
    for (int i = 2; i < size; i++) {
        printf( "%c", arr[i] );
    }
    printf("\n");
}

bool readn(int n, int socket) {
    char buf[CMD_SIZE + 1];
    int rc = 0;
    int fill = 0;

    while (fill < n) {
        rc = recv(socket, buf + fill, n - fill, 0);
        if (rc <= 0) return false;
        if (buf[fill] == PREFIX) fill = 0;
        if (buf[0] == PREFIX) fill += rc;
    }

    printlnMsg(buf, n);

    return true;
}

bool send(string msg, int socket) {
    const char* msgarr;
    msgarr = msg.c_str();

    int rc = 0;
    int l = msg.length();
    int i = 0;

    while (i < l) {
        rc = send(socket, msgarr + i, l - i, 0);
        if (rc <= 0) return false;
        i += rc;
    }

    return readn(CMD_SIZE + 1, socket);
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
    checkConnect(cs, peer, addrport);

    string cmd;
    while (true) {
        cout << addrport << ">";
        cin >> cmd;
        cout << endl;

        if (cmd == HELP) {
            printHelp();
            continue;
        }

        if (cmd == EXIT) {
            exitServer(cs);
            break;
        }

        if (!send(Command(cmd), cs)) {
            cout << "Server not responding" << endl;
            exitServer(cs);
            return 0;
        }
    }

    return 0;
}

