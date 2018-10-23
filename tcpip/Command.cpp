#include "Command.h"


Command::Command(string cmd) {
    code = cmd[0];
    data = cmd.substr(1, CMD_SIZE);
    checkData();
}
/*
Command::Command(char response) {
    code = response;
    switch (response) {
        case RESPONSE_BAD_DATA:
            data = "ERROR: broken data, please retry sending";
            break;

        case RESPONSE_CLIENTS:

            break;

        case RESPONSE_INPUT_INCORRECT:
            data = "ERROR: bad input, only A-Z, a-z, 0-9, _ ";
            break;

        case RESPONSE_LOGIN_BUSY:
            data = "ERROR: login is busy, try another one   ";
            break;

        case RESPONSE_NEED_LOGIN:
            data = "ERROR: you need to log in               ";
            break;

        case RESPONSE_OK:
            data = EMPTY_DATA;
            break;

        default:
            data = "ERROR: broken command                   ";
            break;
    }
}
*/

void Command::checkData() {
    if (!isWord(data) && !isNumber(data)) data.clear();
}

bool isWord(string str) {
    for (char &c : str) if (!isalpha(c) && c != '_') return false;
    return true;
}

bool isNumber(string str) {
    for (char &c : str) if (!isdigit(c)) return false;
    return true;
}

const char* Command::response(set<Client>* clientSet) {
//    if (data.empty()) return Command(RESPONSE_BAD_DATA).to_string().c_str();
    switch(code) {
        case CMD_ACCOUNT_ID:

            break;

        case CMD_BALANCE:

            break;

        case CMD_CLIENTS:

            break;

        case CMD_LOGIN:

            break;

        case CMD_LOGOUT:

            break;

        case CMD_PAY_TO:

            break;

        case CMD_REGISTER:

            break;

        default:

            break;
    }
}


string Command::to_string() {
    ostringstream ss;
    ss << this;
    return ss.str();
}

ostream &operator<<(ostream &os, const Command &command) {
    return os << command.code << command.data;
}

