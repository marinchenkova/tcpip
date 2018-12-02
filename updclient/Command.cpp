#include "Command.h"

Command::Command(vector<string> tokens, char number) {
    num = number;
    code = '?';
    data = EMPTY_STR;
    if (tokens[0] == CMD_ACCOUNT_ID_STR) {
        code = CMD_ACCOUNT_ID;
        return;
    }

    if (tokens[0] == PING_STR) {
        code = RESPONSE_PING;
        return;
    }

    if (tokens[0] == CMD_BALANCE_STR) {
        code = CMD_BALANCE;
        return;
    }

    if (tokens[0] == CMD_CLIENTS_STR) {
        code = CMD_CLIENTS;
        data = wrapData("0", CMD_DATA_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CLIENT_NEXT_STR) {
        string i = "";
        if (tokens.size() >= 2) {
            i = tokens[1];
        }
        code = CMD_CLIENTS;
        data = wrapData(i, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CMD_GET_STR) {
        string amount = "";
        if (tokens.size() >= 2) {
            amount = tokens[1];
        }

        code = CMD_GET;
        data = wrapData(amount, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CMD_LOGIN_STR) {
        string login = "";
        string password = "";
        if (tokens.size() >= 3) {
            login = tokens[1];
            password = tokens[2];
        }

        code = CMD_LOGIN;
        data = wrapData(login, MAX_WORD_SIZE, " ", false) +
               wrapData(password, MAX_WORD_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CMD_LOGOUT_STR) {
        code = CMD_LOGOUT;
        return;
    }

    if (tokens[0] == CMD_PAY_TO_STR) {
        string id = "";
        string amount = "";
        if (tokens.size() >= 3) {
            id = tokens[1];
            amount = tokens[2];
        }

        code = CMD_PAY_TO;
        data = wrapData(id, MAX_WORD_SIZE, " ", false) +
               wrapData(amount, MAX_WORD_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CMD_PUT_STR) {
        string amount = "";
        if (tokens.size() >= 2) {
            amount = tokens[1];
        }

        code = CMD_PUT;
        data = wrapData(amount, CMD_DATA_SIZE, " ", false);
        return;
    }

    if (tokens[0] == CMD_REGISTER_STR) {
        string login = "";
        string password = "";
        if (tokens.size() >= 3) {
            login = tokens[1];
            password = tokens[2];
        }

        code = CMD_REGISTER;
        data = wrapData(login, MAX_WORD_SIZE, " ", false) +
               wrapData(password, MAX_WORD_SIZE, " ", false);
        return;
    }
}

Command::operator string() const {
    stringstream ss;
    ss << num << code;
    return ss.str() + data;
}

ostream &operator<<(ostream &os, const Command &command) {
    string s = command;
    return os << s;
}

bool receivedClientListItem(char *buf, bool next) {
    return buf[1] == RESPONSE_CLIENTS && (next ? buf[3] != ' ' : buf[3] == ' ');
}

Command responsePing(char number) {
    vector<string> tokens(1);
    tokens[0] = PING_STR;
    return Command(tokens, number);
}

bool requestedPing(char *buf) {
    return buf[1] == CMD_PING;
}

string Command::wrapData(string data, int size, string wrap, bool start) {
    string rest = "";
    for (int i = 0; i < size - data.length(); i++) rest.append(wrap);
    return start ? rest + data : data + rest;
}