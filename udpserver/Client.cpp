#include "Client.h"


Client::Client(sockaddr_in addr) {
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

void Client::log_in(sockaddr_in addr) {
    _addr = addr;
    _logged = true;
}

void Client::relog_in() {
    _logged = true;
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
    return client._addr.sin_port < _addr.sin_port;
}

Client::operator string() const {
    stringstream ss;
    ss << "[" << inet_ntoa(_addr.sin_addr) << ":" << _addr.sin_port << "]";
    return ss.str() + "<" +
           (_registered
            ? ("LOGIN[" + _login + "] ID[" + _id + "]" + (_logged ? " ONLINE" : " OFFLINE"))
            : "NOT REGISTERED") + ">";
}

ostream &operator<<(ostream &os, const Client &client) {
    string s = client;
    return os << s;
}

Client* getClientByAddr(set<Client> &clientSet, sockaddr_in* addr) {
    for (set<Client>::iterator it = clientSet.begin(); it != clientSet.end(); ++it) {
        if (addrEqual(((Client) (*it)).getAddr(), addr)) return (Client *) &(*it);
    }
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

bool addrEqual(sockaddr_in *addr1, sockaddr_in *addr2) {
    return inet_ntoa(addr1->sin_addr) == inet_ntoa(addr2->sin_addr)
            && addr1->sin_port == addr2->sin_port;
}

