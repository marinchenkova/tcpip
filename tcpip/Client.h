#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sstream>
#include <string>
#include <iostream>
#include <set>

using namespace std;


static const int MAX_WORD_SIZE = 20;


class Client {
private:
    bool _registered = false;
    bool _logged = false;
    string _login;
    string _password;
    int _balance = 0;
    string _id;
    int _socket;

public:
    Client(int socket);
    bool loggedIn() { return _logged > 0; }
    void registerMe(string login, string password, string id);
    void log_in(int socket);
    void detach();
    void logout();
    string getLogin() { return _login; }
    string getPassword() { return _password; }
    int getBalance() { return _balance; }
    string getId() { return _id; }
    int getSocket() { return _socket; }
    bool isRegistered() { return _registered; }
    bool operator< (const Client &client) const;
    operator string() const;
    friend ostream& operator<<(ostream& os, const Client& client);
};

Client* getClient(set<Client>& clientSet, int socket);
Client* getClient(set<Client>& clientSet, string login);
int numRegistered(set<Client> &clientSet);
bool loginBusy(set<Client>& clientSet, string login);

#endif //TCPIP_CLIENT_H
