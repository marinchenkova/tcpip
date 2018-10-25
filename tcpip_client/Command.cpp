#include <iostream>
#include <vector>
#include "Command.h"


Command::Command(string cmd) {
    code = 'z';
    data = EMPTY_STR;
    if (cmd == CMD_ACCOUNT_ID_STR) {
        code = CMD_ACCOUNT_ID;
        return;
    }

    if (cmd == CMD_BALANCE_STR) {
        code = CMD_BALANCE;
        return;
    }

    if (cmd == CMD_CLIENTS_STR) {
        code = CMD_CLIENTS;
        data = wrapData(START_ITER_C_STR, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (cmd == CMD_GET_STR) {
        string amount;
        cin >> amount;
        code = CMD_GET;
        data = wrapData(amount, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (cmd == CMD_LOGIN_STR) {
        string login;
        string password;
        cin >> login;
        cin >> password;
        code = CMD_LOGIN;
        data = wrapData(login, MAX_WORD_SIZE, " ", false) +
               wrapData(password, MAX_WORD_SIZE, " ", false);
        return;
    }

    if (cmd == CMD_LOGOUT_STR) {
        code = CMD_LOGOUT;
        return;
    }

    if (cmd == CMD_PAY_TO_STR) {
        string id;
        string amount;
        cin >> id;
        cin >> amount;
        code = CMD_PAY_TO;
        data = wrapData(id, MAX_WORD_SIZE, " ", false) +
               wrapData(amount, MAX_WORD_SIZE, " ", false);
        return;
    }

    if (cmd == CMD_PUT_STR) {
        string amount;
        cin >> amount;
        code = CMD_PUT;
        data = wrapData(amount, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (cmd == CMD_REGISTER_STR) {
        string login;
        string password;
        cin >> login;
        cin >> password;
        code = CMD_REGISTER;
        data = wrapData(login, MAX_WORD_SIZE, " ", false) +
               wrapData(password, MAX_WORD_SIZE, " ", false);
        return;
    }
}

Command::operator string() const {
    stringstream ss;
    ss << '[' << code;
    return ss.str() + data;
}

ostream &operator<<(ostream &os, const Command &command) {
    string s = command;
    return os << s;
}

string Command::wrapData(string data, int size, string wrap, bool start) {
    string rest = "";
    for (int i = 0; i < size - data.length(); i++) rest.append(wrap);
    return start ? rest + data : data + rest;
}