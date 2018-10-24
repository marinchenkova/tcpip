#include "Client.h"


Client::Client(int socket) {
    _socket = socket;
}

void Client::registerMe(string login, string password, int id) {
    _login = login;
    _password = password;
    _id = id;
    _balance = 0;
}

void Client::logout() {
    _socket = -1;
}

bool Client::operator<(const Client &client) const {
    return client._id < _id;
}

Client::operator string() const {
    stringstream ss;
    ss << _socket;
    return "Socket " + ss.str() + ": " + (_registered ? "LOGIN " + _login : "(NOT REGISTERED)");
}

ostream &operator<<(ostream &os, const Client &client) {
    string s = client;
    return os << s;
}

Client* getClient(set<Client> &clientSet, int socket) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        int s = ((Client) (*it)).getSocket();
        if (s == socket) return (Client *) &(*it);
    }
    return NULL;
}


