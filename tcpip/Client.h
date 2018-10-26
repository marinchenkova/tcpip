#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sstream>
#include <string>
#include <iostream>
#include <set>
#include <windows.h>
#include <winsock2.h>

using namespace std;


class Client {
private:
    bool _registered = false;
    bool _logged = false;
    string _login;
    string _password;
    unsigned long _balance = 0;
    string _id;
    int _socket;

public:
    Client(int socket);
    bool online() { return _logged; }
    void registerMe(string login, string password, string id);
    void log_in(int socket);
    void detach();
    void logout();
    void moneyPut(unsigned long amount);
    void moneyGet(unsigned long amount);
    string getLogin() { return _login; }
    string getPassword() { return _password; }
    unsigned long getBalance() { return _balance; }
    string getId() { return _id; }
    int getSocket() { return _socket; }
    bool isRegistered() { return _registered; }
    bool operator< (const Client &client) const;
    operator string() const;
    friend ostream& operator<<(ostream& os, const Client& client);
};

Client* getClient(set<Client>& clientSet, int socket);
Client* getClientById(set<Client> &clientSet, string id);
Client* getClientByLogin(set<Client> &clientSet, string login);
Client* getClientByIndex(set<Client> &clientSet, int index);
int numRegistered(set<Client> &clientSet);
bool loginBusy(set<Client>& clientSet, string login);

#endif //TCPIP_CLIENT_H
