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
