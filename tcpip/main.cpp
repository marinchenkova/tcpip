#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <set>
#include <map>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

static const char *ADDR = "127.0.0.1";
static const u_short PORT = 7500;
static const int MAX_THREADS = 10;
static const int EXIT = 'E';
static const int LIST = 'L';
static const int KICK = 'K';

set<int> csSet;
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


void printlnMsg(int socket, char *arr, int size) {
    printf("Client%d/>", socket);
    for (int i = 0; i < size; i++) {
        printf( "%c", arr[i] );
    }
    printf("\n");
}


bool readn(int n, int socket) {
    char buf[10];
    int rc = 0;
    int fill = 0;

    while (fill < n) {
        rc = recv(socket, buf + fill, n - fill, 0);
        if (rc <= 0) return false;
        fill += rc;
    }

    printlnMsg(socket, buf, n);
    return true;
}


int checkBind(int *ss, struct sockaddr_in local) {
    int b = bind(*ss, (struct sockaddr *) &local, sizeof(local));
    if (b < 0) {
        cerr << "Error calling BIND" << endl;
        exit(1);
    }
    return b;
}


int checkListen(int *ss, int backlog) {
    int l = listen(*ss, backlog);
    if (l) {
        cerr << "Error calling LISTEN" << endl;
    }
    return l;
}

DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    CONST PCDATA data = (PCDATA) lpParam;
    WaitForSingleObject(hMutex, INFINITE);
    cout << endl << "Client" << data->socket << " joined" << endl;
    ReleaseMutex(hMutex);
    while (readn(10, (SOCKET) data->socket)) {}
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
            if (cs < 0) {
                WaitForSingleObject(hMutex, INFINITE);
                for (int socket : csSet) {
                    shutdown(socket, 2);
                    closesocket(socket);
                    WaitForSingleObject(clientThreadMap[socket], INFINITE);
                    CloseHandle(clientThreadMap[socket]);
                }
                ReleaseMutex(hMutex);
                break;
            }

            WaitForSingleObject(hMutex, INFINITE);
            csSet.insert(cs);
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

    ExitThread(0);
}


int main() {
    struct sockaddr_in local;
    PCDATA acceptThreadData = new ClientData();
    int ss;

    initWinsock();
    ss = createSocket(&local, ADDR, PORT);
    checkBind(&ss, local);
    checkListen(&ss, 5);

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
    bool found;
    int id;
    while (cont) {
        cin >> cmd;
        switch (cmd) {
            case LIST:
                cout << "Current clients:" << endl;
                WaitForSingleObject(hMutex, INFINITE);

                for (int socket : csSet) cout << socket << endl;
                if (csSet.size() == 0) cout << "No clients" << endl;
                ReleaseMutex(hMutex);
                break;

            case KICK:
                cout << "Enter client id to kick: ";
                cin >> id;
                found = false;
                WaitForSingleObject(hMutex, INFINITE);
                for (int socket : csSet) {
                    if (socket == id) {
                        shutdown(socket, 2);
                        closesocket(socket);
                        csSet.erase(socket);
                        cout << "Client " << socket << " was kicked" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "No such client" << endl;
                ReleaseMutex(hMutex);
                break;

            case EXIT:
                shutdown(ss, 2);
                closesocket(ss);
                WaitForSingleObject(hAcceptThread, INFINITE);
                CloseHandle(hAcceptThread);
                cont = false;
                break;

            default:
                cout << cmd << ": unknown command" << endl;
                break;
        }
    }

    ExitProcess(0);
}

