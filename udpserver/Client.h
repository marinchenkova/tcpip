#ifndef UDPSERVER_CLIENT_H
#define UDPSERVER_CLIENT_H


#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

using namespace std;


class Client {
private:
    bool _registered = false;
    bool _logged = false;
    string _login;
    string _password;
    unsigned long _balance = 0;
    string _id;
    sockaddr_in _addr;

public:
    Client(sockaddr_in addr);
    bool online() { return _logged; }
    void registerMe(string login, string password, string id);
    void log_in(sockaddr_in addr);
    void relog_in();
    void logout();
    void moneyPut(unsigned long amount);
    void moneyGet(unsigned long amount);
    string getLogin() { return _login; }
    string getPassword() { return _password; }
    unsigned long getBalance() { return _balance; }
    string getId() { return _id; }
    sockaddr_in* getAddr() { return &_addr; }
    bool isRegistered() { return _registered; }
    bool operator< (const Client &client) const;
    operator string() const;
    friend ostream& operator<<(ostream& os, const Client& client);
};

Client* getClientByAddr(set<Client> &clientSet, sockaddr_in* addr);
Client* getClientById(set<Client> &clientSet, string id);
Client* getClientByLogin(set<Client> &clientSet, string login);
Client* getClientByIndex(set<Client> &clientSet, int index);
int numRegistered(set<Client> &clientSet);
bool loginBusy(set<Client>& clientSet, string login);
bool addrEqual(sockaddr_in* addr1, sockaddr_in* addr2);


#endif //UDPSERVER_CLIENT_H
