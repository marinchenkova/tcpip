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
    sockaddr* _addr;

public:
    Client(sockaddr *addr);
    bool online() { return _logged; }
    void registerMe(string login, string password, string id);
    void log_in(sockaddr *addr);
    void detach();
    void logout();
    void moneyPut(unsigned long amount);
    void moneyGet(unsigned long amount);
    string getLogin() { return _login; }
    string getPassword() { return _password; }
    unsigned long getBalance() { return _balance; }
    string getId() { return _id; }
    sockaddr* getAddr() { return _addr; }
    bool isRegistered() { return _registered; }
    bool operator< (const Client &client) const;
    operator string() const;
    friend ostream& operator<<(ostream& os, const Client& client);
};

Client* getClientByAddr(set<Client> &clientSet, sockaddr* addr);
Client* getClientById(set<Client> &clientSet, string id);
Client* getClientByLogin(set<Client> &clientSet, string login);
Client* getClientByIndex(set<Client> &clientSet, int index);
int numRegistered(set<Client> &clientSet);
bool loginBusy(set<Client>& clientSet, string login);
bool addrEqual(sockaddr* addr1, sockaddr* addr2);


#endif //UDPSERVER_CLIENT_H
