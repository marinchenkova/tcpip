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
static const int PING_PERIOD = 30000;
static const int BUFLEN = CMD_SIZE;

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
    SOCKET ss = socket(AF_INET, SOCK_DGRAM, 0);
    if (ss < 0) {
        cerr << "Error calling SOCKET" << endl;
        exit(1);
    }
    return ss;
}

int checkBind(int ss, struct sockaddr_in *local) {
    int b = bind(ss, (sockaddr *) local, sizeof(*local));
    if (b < 0) {
        cerr << "Error calling BIND" << endl;
        exit(1);
    }
    return b;
}

bool send(Command cmd, int socket) {/*
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
        rc = sendto(
                socket,
                resparr + i,
                l - i,
                0,
                const sockaddr *to,
                int            tolen
        );
        if (rc <= 0) return false;
        i += rc;
    }
*/
    return true;
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

void kick(int socket) {/*
    WaitForSingleObject(hMutex, INFINITE);
    cout << "Kicking " << socket << endl;
    Client* client = getClientByAddr(clientSet, socket);
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
*/}

void kickAll(map<int, HANDLE> clientThreadMap) {
    WaitForSingleObject(hMutex, INFINITE);
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        Client* client = (Client *) &(*it);
        int socket = 0;//client->getAddr();

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

void pingAll() {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        Client *client = (Client *) &(*it);

    }
}

DWORD WINAPI pingThread(CONST LPVOID lpParam) {
    int socket = ((PCDATA) lpParam)->socket;

    while (true) {
        Sleep(PING_PERIOD);
        pingAll();
    }
    WaitForSingleObject(hMutex, INFINITE);



    ReleaseMutex(hMutex);

    ExitThread(0);
}


DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    PCDATA threadData = (PCDATA) lpParam;
    int socket = threadData->socket;
    char buf[BUFLEN];
    int rc = 0;
    sockaddr_in from;
    int fromlen = sizeof(from);
    Client *client;

    while (true) {
        rc = recvfrom(socket, buf, sizeof(buf) + 1, 0, (sockaddr*) &from, &fromlen);
        if (rc <= 0) {
            /*client = getClientByAddr(clientSet, from);
            if (client != NULL)  {
                client->detach();
                client->logout();
            }*/
            perror("recvfrom");
            cerr << "Winsock error " << WSAGetLastError() << endl;
            break;
        }
        cout << inet_ntoa(from.sin_addr) << ":" << ntohs(from.sin_port) << buf << "]" << endl;
    }

    ExitThread(0);
}

int main() {
    struct sockaddr_in local;
    PCDATA receiveThreadData = new ClientData();
    int ss;

    initWinsock();
    ss = createSocket(&local, ADDR, PORT);
    checkBind(ss, &local);

    cout << "Server on socket " << ss << " started" << endl;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    receiveThreadData->socket = ss;
    /*
    HANDLE hPingThread = CreateThread(
            NULL,
            0,
            &pingThread,
            receiveThreadData,
            0,
            NULL
    );
*/
    HANDLE hReceiveThread = CreateThread(
            NULL,
            0,
            &receiveThread,
            receiveThreadData,
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
/*
            case KICK:
                WaitForSingleObject(hMutex, INFINITE);
                cout << "Enter client socket to kick: ";
                cin >> ks;
                ReleaseMutex(hMutex);
                kick(strtol(ks.c_str(), NULL, 0));
                break;
*/
            case EXIT:
                shutdown(ss, 2);
                closesocket(ss);
                WaitForSingleObject(hReceiveThread, INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                CloseHandle(hReceiveThread);
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

