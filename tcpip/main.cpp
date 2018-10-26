#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <set>
#include <map>
#include "Command.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

static const char *ADDR = "127.0.0.1";
static const u_short PORT = 7500;
static const int MAX_THREADS = 10;
static const int EXIT = 'E';
static const int LIST = 'L';
static const int KICK = 'K';

set<Client> clientSet;
HANDLE hMutex;


typedef struct ClientData {
    int socket;
    struct sockaddr *addr;
    int *addrlen;
} CDATA, *PCDATA;

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

bool send(Command cmd, int socket) {
    WaitForSingleObject(hMutex, INFINITE);
    string response = cmd.response(clientSet, socket);
    ReleaseMutex(hMutex);

    int notifySocket = cmd.notify();
    if (notifySocket > 0) {
        string notifycmd = {PREFIX, CMD_BALANCE};
        send(Command(Command::wrapData(
                notifycmd,
                CMD_DATA_SIZE,
                " ",
                false
        )), notifySocket);
    }

    const char* resparr;
    resparr = response.c_str();

    int rc = 0;
    int l = response.length();
    int i = 0;

    while (i < l) {
        rc = send(socket, resparr + i, l - i, 0);
        if (rc <= 0) return false;
        i += rc;
    }

    return true;
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

    while (!send(Command(buf), socket));

    return true;
}

int checkBind(int ss, struct sockaddr_in local) {
    int b = bind(ss, (struct sockaddr *) &local, sizeof(local));
    if (b < 0) {
        cerr << "Error calling BIND" << endl;
        exit(1);
    }
    return b;
}

int checkListen(int ss, int backlog) {
    int l = listen(ss, backlog);
    if (l) {
        cerr << "Error calling LISTEN" << endl;
        return 0;
    }
    cout << "Server on socket " << ss << " started" << endl;
    return l;
}


void listClients() {
    WaitForSingleObject(hMutex, INFINITE);
    cout << "Current clients:" << endl;
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        cout << (*it) << endl;
    }
    if (clientSet.size() == 0) cout << "No clients" << endl;
    ReleaseMutex(hMutex);
}

void kick(int socket) {
    WaitForSingleObject(hMutex, INFINITE);
    cout << "Kicking " << socket << endl;
    Client* client = getClient(clientSet, socket);
    if (client != NULL) {
        shutdown(socket, 2);
        closesocket(socket);
        if (client->isRegistered()) {
            client->logout();
            client->detach();
        }
        else clientSet.erase(*client);
        cout << "Client on socket " << socket << " exited" << endl;
    }
    else cout << "No such client" << endl;
    ReleaseMutex(hMutex);
}

void kickAll(map<int, HANDLE> clientThreadMap) {
    WaitForSingleObject(hMutex, INFINITE);
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        Client* client = (Client *) &(*it);
        int socket = client->getSocket();

        if (client->isRegistered()) {
            client->logout();
            client->detach();
        }
        else clientSet.erase(*client);

        shutdown(socket, 2);
        closesocket(socket);
        WaitForSingleObject(clientThreadMap[socket], INFINITE);
        CloseHandle(clientThreadMap[socket]);
    }
    ReleaseMutex(hMutex);
}

DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    CONST PCDATA data = (PCDATA) lpParam;

    WaitForSingleObject(hMutex, INFINITE);
    cout << endl << "Client on socket " << data->socket << " joined" << endl;
    ReleaseMutex(hMutex);

    while (readn(CMD_SIZE + 1, data->socket));
    cout << endl;

    kick(data->socket);
    ExitThread(0);
}

DWORD WINAPI acceptThread(CONST LPVOID lpParam) {
    PCDATA threadData = (PCDATA) lpParam;
    map<int, HANDLE> clientThreadMap;
    PCDATA data;
    int cs;

    while (true) {
        if (clientThreadMap.size() <= MAX_THREADS) {
            cs = accept(threadData->socket, threadData->addr, threadData->addrlen);
            if (cs < 0) break;

            WaitForSingleObject(hMutex, INFINITE);
            clientSet.insert(Client(cs));
            ReleaseMutex(hMutex);

            data = (PCDATA) HeapAlloc(
                    GetProcessHeap(),
                    HEAP_ZERO_MEMORY,
                    sizeof(CDATA)
            );
            data->socket = cs;

            clientThreadMap[cs] = CreateThread(
                    NULL,
                    0,
                    &receiveThread,
                    data,
                    0,
                    NULL
            );
        }
    }

    kickAll(clientThreadMap);

    ExitThread(0);
}

int main() {
    struct sockaddr_in local;
    PCDATA acceptThreadData = new ClientData();
    int ss;

    initWinsock();
    ss = createSocket(&local, ADDR, PORT);
    checkBind(ss, local);
    checkListen(ss, 5);

    hMutex = CreateMutex(NULL, FALSE, NULL);

    acceptThreadData->socket = ss;
    HANDLE hAcceptThread = CreateThread(
            NULL,
            0,
            &acceptThread,
            acceptThreadData,
            0,
            NULL
    );

    char cmd;
    bool cont = true;
    string ks;
    while (cont) {
        cin >> cmd;
        switch (cmd) {
            case LIST:
                listClients();
                break;

            case KICK:
                WaitForSingleObject(hMutex, INFINITE);
                cout << "Enter client socket to kick: ";
                cin >> ks;
                ReleaseMutex(hMutex);
                kick(strtol(ks.c_str(), NULL, 0));
                break;

            case EXIT:
                shutdown(ss, 2);
                closesocket(ss);
                WaitForSingleObject(hAcceptThread, INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                CloseHandle(hAcceptThread);
                CloseHandle(hMutex);
                cont = false;
                cout << "Exit" << endl;
                break;

            default:
                WaitForSingleObject(hMutex, INFINITE);
                cout << cmd << ": unknown command" << endl;
                ReleaseMutex(hMutex);
                break;
        }
    }

    ExitProcess(0);
}

