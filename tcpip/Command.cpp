#include "Command.h"


Command::Command(string cmd) {
    code = cmd[0];
    data = cmd.substr(1, CMD_DATA_SIZE);
    checkData();
}

void Command::checkData() {
    if (!isValidData(data)) data.clear();
}

bool isValidData(string str) {
    for (char &c : str) {
        if (!isalpha(c) && !isdigit(c) && c != ' ' && c != '_' ) return false;
    }
    return true;
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
    if (data.empty()) return Command(RESPONSE_BAD_DATA + BAD_DATA_STR);

    Client* client = getClient(clientSet, socket);
    char responseCode;
    string responseData;

    string word1 = extractWord(0, MAX_WORD_SIZE);
    string word2 = extractWord(MAX_WORD_SIZE, CMD_DATA_SIZE);

    switch(code) {
        case CMD_ACCOUNT_ID:
        {
            if (client->isRegistered() && client->loggedIn()) {
                responseCode = RESPONSE_OK;
                responseData = wrapData(client->getId(), CMD_DATA_SIZE, "0", true);
            }
            else {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
            }
            break;
        }

        case CMD_BALANCE:
        {
            if (client->isRegistered() && client->loggedIn()) {
                responseCode = RESPONSE_OK;
                responseData = wrapData(client->getBalance(), CMD_DATA_SIZE, " ", false);
            }
            else {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
            }
            break;
        }

        case CMD_CLIENTS:

            break;

        case CMD_LOGIN:
        {
            // Find out if such client exists
            Client* registered = getClient(clientSet, word1);

            // If client not exists
            if (registered == NULL) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INPUT_INCORRECT_STR;
                break;
            }

            // Client exists (also log_in was correct), check if password is incorrect
            if (registered->getPassword() != word2) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INPUT_INCORRECT_STR;
                break;
            }

            // Found client socket is passed socket
            if (registered == client) {
                if (registered->loggedIn()) {
                    responseCode = RESPONSE_NEED_LOGOUT;
                    responseData = NEED_LOGOUT_STR;
                    break;
                }
            }
            else {
                clientSet.erase(*client);
                clientSet.insert(*registered);
                delete(client);
            }

            // Found client socket is not passed socket
            registered->log_in(socket);
            responseCode = RESPONSE_OK;
            responseData = wrapData("Welcome " + registered->getLogin(), CMD_DATA_SIZE, " ", false);
            break;
        }

        case CMD_LOGOUT:
        {
            if (client->loggedIn()) {
                responseCode = RESPONSE_OK;
                responseData = wrapData("Good bye " + client->getLogin(), CMD_DATA_SIZE, " ", false);
                client->logout();
                break;
            }

            responseCode = RESPONSE_NEED_LOGIN;
            responseData = NEED_LOGIN_STR;
            break;
        }

        case CMD_PAY_TO:

            break;

        case CMD_REGISTER:
        {
            // If client is already logged in
            if (client->loggedIn()) {
                responseCode = RESPONSE_NEED_LOGOUT;
                responseData = NEED_LOGOUT_STR;
                break;
            }

            // If login is incorrect
            if (word1.empty()) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INPUT_INCORRECT_STR;
                break;
            }

            // If password is incorrect
            if (word2.empty()) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INPUT_INCORRECT_STR;
                break;
            }

            // If log_in already exists
            if (loginBusy(clientSet, word1)) {
                responseCode = RESPONSE_LOGIN_BUSY;
                responseData = LOGIN_BUSY_STR;
                break;
            }

            // Login and password are correct, complete registration
            client->registerMe(
                    word1,
                    word2,
                    wrapData(numRegistered(clientSet), MAX_WORD_SIZE, "0", true)
            );
            responseCode = RESPONSE_OK;
            responseData = wrapData("Welcome " + client->getLogin(), CMD_DATA_SIZE, " ", false);
            break;
        }

        default:
        {
            responseCode = RESPONSE_UNKNOWN_CMD;
            responseData = UNKNOWN_CMD_STR;
            break;
        }
    }

    return Command(responseCode + responseData);
}

Command::operator string() const { return code + data; }

ostream &operator<<(ostream &os, const Command &command) {
    string s = command;
    return os << s;
}

string Command::extractWord(unsigned int start, unsigned int end) {
    string word = trim(data.substr(start, end));
    if (word.length() < MIN_WORD_SIZE) return "";
    return word;
}

string Command::wrapData(string data, int size, string wrap, bool start) {
    string rest = "";
    for (int i = 0; i < size - data.length(); i++) rest.append(wrap);
    return start ? rest + data : data + rest;
}

string Command::wrapData(int data, int size, string wrap, bool start) {
    stringstream ss;
    ss << data;
    return wrapData(ss.str(), size, wrap, start);
}

string trim(const std::string &s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it)) it++;
    string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit)) rit++;
    return std::string(it, rit.base());
}
