#include "Client.h"


Client::Client(int socket) {
    _socket = socket;
}

void Client::registerMe(string login, string password, string id) {
    _login = login;
    _password = password;
    _id = id;
    _balance = 0;
    _logged = true;
    _registered = true;
}

void Client::log_in(int socket) {
    _socket = socket;
    _logged = true;
}

void Client::detach() {
    _socket = -1;
}

void Client::logout() {
    _logged = false;
}

void Client::moneyPut(unsigned long amount) {
    _balance += amount;
}

void Client::moneyGet(unsigned long amount) {
    _balance -= amount;
}

bool Client::operator<(const Client &client) const {
    return client._id < _id;
}

Client::operator string() const {
    stringstream ss;
    ss << _socket;
    return "Socket " + ss.str() + ": " +
            (_registered
             ? ("LOGIN " + _login + " ID " + _id  + (_logged
                                                     ? " online"
                                                     : " offline"))
             : "(NOT REGISTERED)");
}

ostream &operator<<(ostream &os, const Client &client) {
    string s = client;
    return os << s;
}

Client* getClient(set<Client> &clientSet, int socket) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) (*it)).getSocket() == socket) return (Client *) &(*it);
    }
    return NULL;
}

Client* getClient(set<Client> &clientSet, string login) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) *it).isRegistered() && (login == ((Client) *it).getLogin()))
            return (Client *) &(*it);
    }
    return NULL;
}

int numRegistered(set<Client> &clientSet) {
    int size = 0;
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) (*it)).isRegistered()) size++;
    }
    return size;
}

bool loginBusy(set<Client> &clientSet, string login) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) (*it)).getLogin() == login) return true;
    }
    return false;
}


