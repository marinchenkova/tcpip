#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sstream>
#include <string>
#include <iostream>

using namespace std;


static const int LOGIN_SIZE = 20;


class Client {
private:
    bool _registered = false;
    string _login;
    string _password;
    int _balance = 0;
    int _id = -1;
    int _socket;

public:
    Client(int socket);
    void registerMe(string login, string password, int id);
    void logout();
    string getLogin() { return _login; }
    string getPassword() { return _password; }
    int getBalance() { return _balance; }
    int getId() { return _id; }
    int getSocket() { return _socket; }
    bool isRegistered() { return _registered; }
    bool operator< (const Client &client) const;
    operator string() const;
    friend ostream& operator<<(ostream& os, const Client& client);
};


#endif //TCPIP_CLIENT_H
