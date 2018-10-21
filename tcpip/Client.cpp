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

ostream &operator<<(ostream &os, const Client &client) {
    string str;
    if (client._registered) str = ": LOGIN " + client._login;
    else str = ": (NOT REGISTERED)";
    return os << "Client "
              << client._socket
              << str;
}