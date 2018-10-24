#include "Command.h"


Command::Command(string cmd) {
    code = cmd[0];
    data = cmd.substr(1, CMD_SIZE);
    checkData();
}

Command::Command(char response) {
    code = response;
    switch (response) {
        case RESPONSE_BAD_DATA:
            data = BAD_DATA_STR;
            break;

        case RESPONSE_CLIENTS:

            break;

        case RESPONSE_INPUT_INCORRECT:
            data = INPUT_INCORRECT_STR;
            break;

        case RESPONSE_LOGIN_BUSY:
            data = LOGIN_BUSY_STR;
            break;

        case RESPONSE_NEED_LOGIN:
            data = NEED_LOGIN_STR;
            break;

        case RESPONSE_OK:
            data = EMPTY_STR;
            break;

        default:
            data = UNKNOWN_CMD_STR;
            break;
    }
}


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

string Command::response(set<Client>& clientSet, int socket) {
    char response_code;
    if (data.empty()) response_code = RESPONSE_BAD_DATA;
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
            response_code = RESPONSE_UNKNOWN_CMD;
            break;
    }
    return Command(response_code);
}

string Command::getAccountId() {

}

Command::operator string() const { return code + data; }

ostream &operator<<(ostream &os, const Command &command) {
    string s = command;
    return os << s;
}



