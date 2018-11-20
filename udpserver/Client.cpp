#include "Client.h"


Client::Client(sockaddr *addr) {
    _addr = addr;
}

void Client::registerMe(string login, string password, string id) {
    _login = login;
    _password = password;
    _id = id;
    _balance = 0;
    _logged = true;
    _registered = true;
}

void Client::log_in(sockaddr *addr) {
    _addr = addr;
    _logged = true;
}

void Client::detach() {
    _addr = NULL;
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
    return client._addr->sa_data < _addr->sa_data;
}

Client::operator string() const {
    stringstream ss;
    ss << "[" << _addr->sa_data << "]";
    return ss.str() + "<" +
           (_registered
            ? ("LOGIN[" + _login + "] ID[" + _id + "]" + (_logged ? " ONLINE" : " OFFLINE"))
            : "NOT REGISTERED") + ">";
}

ostream &operator<<(ostream &os, const Client &client) {
    string s = client;
    return os << s;
}

Client* getClientByAddr(set<Client> &clientSet, sockaddr* addr) {
    /*for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (addrEqual(((Client) (*it)).getAddr(), addr)) return (Client *) &(*it);
    }*/
    return NULL;
}

Client* getClientByIndex(set<Client> &clientSet, int index) {
    int count = 0;
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) *it).isRegistered() && count++ == index) {
            return (Client *) &(*it);
        }
    }
    return NULL;
}

Client* getClientByLogin(set<Client> &clientSet, string login) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) *it).isRegistered() && (login == ((Client) *it).getLogin()))
            return (Client *) &(*it);
    }
    return NULL;
}

Client* getClientById(set<Client> &clientSet, string id) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (((Client) *it).isRegistered() && (id == ((Client) *it).getId()))
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

bool addrEqual(sockaddr *addr1, sockaddr *addr2) {
    return addr1->sa_family == addr2->sa_family && addr1->sa_data == addr2->sa_data;
}


