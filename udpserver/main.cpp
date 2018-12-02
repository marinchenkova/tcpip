#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <set>
#include "Command.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

static const char *ADDR = "127.0.0.1";
static const u_short PORT = 7500;
static const int EXIT = 'E';
static const int LIST = 'L';
static const int KICK = 'K';
static const int PING_PERIOD = 10000;
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
    cout << "Server "
         << addr << ":" << port
         << " on socket " << ss << " started" << endl;
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

bool send(Command cmd, sockaddr_in* addr, int socket) {
    WaitForSingleObject(hMutex, INFINITE);
    string response = cmd.response(clientSet, addr);
    ReleaseMutex(hMutex);

    sockaddr_in* notifyAddr = cmd.notify();
    if (notifyAddr != NULL) {
        string notifycmd = {cmd.getNum(), CMD_BALANCE};
        send(Command(Command::wrapData(
                notifycmd,
                CMD_DATA_SIZE,
                " ",
                false
        )), notifyAddr, socket);
    }

    const char* resparr;
    resparr = response.c_str();

    int rc = sendto(socket,
                    resparr,
                    strlen(resparr),
                    0,
                    (sockaddr*) addr,
                    sizeof(*addr)
    );


    return rc > 0;
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

void logoutClient(u_short port) {
    WaitForSingleObject(hMutex, INFINITE);

    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ADDR);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    Client* client = getClientByAddr(clientSet, &addr);
    if (client != NULL) {
        if (client->isRegistered()) {
            client->kick();
        }
        else clientSet.erase(*client);
        cout << "Client on port " << port << " exited" << endl;
    }
    else cout << "No such client" << endl;
    ReleaseMutex(hMutex);
}

void logoutAll() {
    WaitForSingleObject(hMutex, INFINITE);
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        Client* client = (Client *) &(*it);
        if (client->isRegistered()) {
            client->kick();
        }
        else clientSet.erase(*client);
    }
    ReleaseMutex(hMutex);
}

bool pingAll(int socket) {
    int rc = 0;
    const char* request;

    WaitForSingleObject(hMutex, INFINITE);
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        Client *client = (Client *) &(*it);
        if (client->online()) {
            cout << "PINGING " << *client << endl;
            client->logout();
            request = Command::requestPing(CMD_PING).c_str();
            rc = sendto(socket,
                        request,
                        strlen(request),
                        0,
                        (sockaddr*) client->getAddr(),
                        sizeof(*client->getAddr())
            );
            if (rc < 0) {
                ReleaseMutex(hMutex);
                perror("sendto PING");
                cerr << "Winsock error " << WSAGetLastError() << endl;
                return false;
            }
        }
    }
    ReleaseMutex(hMutex);

    return true;
}

DWORD WINAPI pingThread(CONST LPVOID lpParam) {
    int socket = ((PCDATA) lpParam)->socket;
    //while (pingAll(socket)) Sleep(PING_PERIOD);
    ExitThread(0);
}

DWORD WINAPI receiveThread(CONST LPVOID lpParam) {
    PCDATA threadData = (PCDATA) lpParam;
    int socket = threadData->socket;
    int e;
    char cn;
    char buf[BUFLEN];
    int rc = 0;
    sockaddr_in from;
    int fromlen = sizeof(from);
    Client *client;

    while (true) {
        rc = recvfrom(socket,
                      buf,
                      sizeof(buf) + 1,
                      0,
                      (sockaddr*) &from,
                      &fromlen
        );
        Command cmd = Command(buf);

        WaitForSingleObject(hMutex, INFINITE);
        client = getClientByAddr(clientSet, &from);
        if (client == NULL) clientSet.insert(Client(from, cmd.getNum()));
        ReleaseMutex(hMutex);

        cout << "MSG [" << buf << "]" << endl;

        if (rc <= 0) {
            if (0 != (e = WSAGetLastError())) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "WSA error: "<< e << endl;
                ReleaseMutex(hMutex);
                break;
            }

            WaitForSingleObject(hMutex, INFINITE);
            client->logout();
            cout << *client << " exited" << endl;
            ReleaseMutex(hMutex);
            continue;
        }

        WaitForSingleObject(hMutex, INFINITE);
        if (Command(buf).isPingResponse()) {
            if (client->isRegistered()) {
                client->relog_in();
            }
            else clientSet.erase(*client);
            ReleaseMutex(hMutex);
            continue;
        }
        ReleaseMutex(hMutex);
/*
        cn = client == NULL ? cmd.getNum() : client->nextNum();
        cout << "cmd num=" << cmd.getNum()
             << ", client num=" << cn << endl;
        if (cmd.getNum() == cn) */
            send(cmd, &from, socket);
    }

    cout << "BREAK" << endl;
    logoutAll();

    ExitThread(0);
}

int main() {
    struct sockaddr_in local;
    PCDATA receiveThreadData = new ClientData();
    int ss;

    initWinsock();
    ss = createSocket(&local, ADDR, PORT);
    checkBind(ss, &local);

    hMutex = CreateMutex(NULL, FALSE, NULL);

    receiveThreadData->socket = ss;

    HANDLE hPingThread = CreateThread(
            NULL,
            0,
            &pingThread,
            receiveThreadData,
            0,
            NULL
    );

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

            case KICK:
                WaitForSingleObject(hMutex, INFINITE);
                cout << "Enter client port to logout" << endl;
                cin >> ks;
                ReleaseMutex(hMutex);
                logoutClient(strtol(ks.c_str(), NULL, 0));
                break;

            case EXIT:
                shutdown(ss, 2);
                closesocket(ss);
                WaitForSingleObject(hReceiveThread, INFINITE);
                WaitForSingleObject(hPingThread, INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                CloseHandle(hReceiveThread);
                CloseHandle(hPingThread);
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

