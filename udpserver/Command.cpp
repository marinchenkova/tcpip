#include "Command.h"


Command::Command(string cmd) {
    num = cmd[0];
    code = cmd[1];
    data = cmd.substr(2, CMD_DATA_SIZE);
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

bool isNumber(string str) {
    for (char &c : str) if (!isdigit(c)) return false;
    return true;
}

string Command::response(set<Client>& clientSet, sockaddr_in* addr) {
    if (data.empty()) {
        stringstream ss;
        ss << num << RESPONSE_BAD_DATA;
        return ss.str() + BAD_DATA_STR;
    }

    Client* client = getClientByAddr(clientSet, addr);
    char responseCode;
    string responseData;

    string word1 = extractWord(0, MAX_WORD_SIZE);
    string word2 = extractWord(MAX_WORD_SIZE, CMD_DATA_SIZE);

    cout << *client << " requests ";
    switch(code) {
        case CMD_ACCOUNT_ID:
        {
            cout << "ACCOUNT ID" << endl;
            if (!client->isRegistered() || !client->online()) {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
                break;
            }

            responseCode = RESPONSE_OK;
            responseData = wrapData(client->getId(), CMD_DATA_SIZE, " ", false);
            break;
        }

        case CMD_BALANCE:
        {
            cout << "BALANCE" << endl;
            if (!client->isRegistered() || !client->online()) {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
                break;
            }

            responseCode = RESPONSE_OK;
            responseData = wrapBalance(client->getBalance());
            break;
        }

        case CMD_CLIENTS:
        {
            cout << "CLIENT LIST";
            if (!isNumber(word1)) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = NEED_NUMBER_STR;
                cout << endl;
                break;
            }

            unsigned long index = extractULong(0, CMD_DATA_SIZE);
            Client* need = getClientByIndex(clientSet, (int) index);
            string id;
            if (need == NULL) id = FINISH_ITER_C_STR;
            else id = need->getId();

            responseCode = RESPONSE_CLIENTS;
            responseData = wrapData(id, CMD_DATA_SIZE, " ", false);
            cout << " NEXT" << endl;
            break;
        }

        case CMD_GET:
        {
            cout << "MONEY GET " << trim(data) << endl;
            if (!client->isRegistered() || !client->online()) {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
                break;
            }

            if (!isNumber(trim(data))) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = NEED_NUMBER_STR;
                break;
            }

            unsigned long amount = extractULong(0, CMD_DATA_SIZE);
            if (client->getBalance() < amount) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INSUF_FUNDS_STR;
                break;
            }

            client->moneyGet(amount);
            responseCode = RESPONSE_OK;
            responseData = wrapBalance(client->getBalance());
            break;
        }

        case CMD_LOGIN:
        {
            cout << "LOG IN LOGIN[" << word1 << "] PASSWORD[" << word2 << "]" << endl;

            if (client->online()) {
                responseCode = RESPONSE_NEED_LOGOUT;
                responseData = NEED_LOGOUT_STR;
                break;
            }

            // Find out if such client exists
            Client* registered = getClientByLogin(clientSet, word1);

            // If client not exists
            if (registered == NULL) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = LOGIN_INCORRECT_STR;
                break;
            }

            // Client exists (also log_in was correct), check if password is incorrect
            if (registered->getPassword() != word2) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = PASS_INCORRECT_STR;
                break;
            }

            if (registered->online()) {
                responseCode = RESPONSE_CLIENT_ONLINE_NOW;
                responseData = CLIENT_ONLINE_STR;
                break;
            }

            if (!client->isRegistered()) {
                clientSet.erase(*client);
                delete(client);
            }

            // Found client socket is not passed socket
            registered->log_in(*addr);
            responseCode = RESPONSE_OK;
            responseData = wrapWelcome(registered->getLogin());
            cout << *registered << " logged in" << endl;
            break;
        }

        case CMD_LOGOUT:
        {
            cout << "LOG OUT" << endl;
            if (client->online()) {
                responseCode = RESPONSE_OK;
                responseData = wrapBye(client->getLogin());
                client->logout();
                cout << *client << " logged out" << endl;
                break;
            }

            responseCode = RESPONSE_NEED_LOGIN;
            responseData = NEED_LOGIN_STR;
            break;
        }

        case CMD_PAY_TO:
        {
            cout << "PAY " << word2 << " TO " << word1 << endl;
            if (!client->isRegistered() || !client->online()) {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
                break;
            }

            Client* to = getClientById(clientSet, word1);
            if (to == NULL) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = ID_INCORRECT_STR;
                break;
            }

            if (!isNumber(trim(word2))) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = NEED_NUMBER_STR;
                break;
            }

            unsigned long amount = extractULong(MAX_WORD_SIZE, CMD_DATA_SIZE);
            if (client->getBalance() < amount) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = INSUF_FUNDS_STR;
                break;
            }

            notifyAddr = to->getAddr();
            client->moneyGet(amount);
            to->moneyPut(amount);
            responseCode = RESPONSE_OK;
            responseData = wrapBalance(client->getBalance());
            break;
        }

        case CMD_PUT:
        {
            cout << "MONEY PUT " << trim(data) << endl;
            if (!client->isRegistered() || !client->online()) {
                responseCode = RESPONSE_NEED_LOGIN;
                responseData = NEED_LOGIN_STR;
                break;
            }

            if (!isNumber(trim(data))) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = NEED_NUMBER_STR;
                break;
            }

            unsigned long amount = extractULong(0, CMD_DATA_SIZE);

            client->moneyPut(amount);
            responseCode = RESPONSE_OK;
            responseData = wrapBalance(client->getBalance());
            break;
        }

        case CMD_REGISTER:
        {
            cout << "REGISTRATION LOGIN[" << word1 << "] PASSWORD[" << word2 << "]" << endl;
            // If client is already logged in
            if (client->online()) {
                responseCode = RESPONSE_NEED_LOGOUT;
                responseData = NEED_LOGOUT_STR;
                break;
            }

            // If login is incorrect
            if (word1.empty()) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = LOGIN_INCORRECT_STR;
                break;
            }

            // If password is incorrect
            if (word2.empty()) {
                responseCode = RESPONSE_INPUT_INCORRECT;
                responseData = PASS_INCORRECT_STR;
                break;
            }

            // If log_in already exists
            if (loginBusy(clientSet, word1)) {
                responseCode = RESPONSE_LOGIN_BUSY;
                responseData = LOGIN_BUSY_STR;
                break;
            }

            if (client->isRegistered() && !client->online()) {
                client->logout();
                Client another = Client(*addr);
                // Login and password are correct, complete registration
                another.registerMe(
                        word1,
                        word2,
                        wrapData((unsigned long) numRegistered(clientSet), MAX_WORD_SIZE, "0", true)
                );
                clientSet.insert(another);
                responseCode = RESPONSE_OK;
                responseData = wrapWelcome(another.getLogin());
                cout << another << " registered" << endl;
                break;
            }

            // Login and password are correct, complete registration
            client->registerMe(
                    word1,
                    word2,
                    wrapData((unsigned long) numRegistered(clientSet), MAX_WORD_SIZE, "0", true)
            );
            responseCode = RESPONSE_OK;
            responseData = wrapWelcome(client->getLogin());
            cout << *client << " registered" << endl;
            break;
        }

        default:
        {
            cout << "UNKNOWN COMMAND" << endl;
            responseCode = RESPONSE_UNKNOWN_CMD;
            responseData = UNKNOWN_CMD_STR;
            break;
        }
    }
    cout << "Responding: " << responseData << endl << endl;
    stringstream ss;
    ss << num << responseCode;
    return ss.str() + responseData;
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

unsigned long Command::extractULong(unsigned int start, unsigned int end) {
    string word = trim(data.substr(start, end));
    if (word.length() > MAX_WORD_SIZE - 10) word = word.substr(0, MAX_WORD_SIZE - 10);
    return strtoul(word.c_str(), NULL, 0);
}

string Command::wrapData(string data, int size, string wrap, bool start) {
    string rest = "";
    for (int i = 0; i < size - data.length(); i++) rest.append(wrap);
    return start ? rest + data : data + rest;
}

string Command::wrapData(unsigned long data, int size, string wrap, bool start) {
    stringstream ss;
    ss << data;
    return wrapData(ss.str(), size, wrap, start);
}

string Command::wrapBalance(unsigned long balance) {
    string remained = "Remained " + wrapData(balance, MAX_WORD_SIZE, "", false);
    return wrapData(remained, CMD_DATA_SIZE, " ", false);
}

string Command::wrapWelcome(string login) {
    return wrapData("Welcome " + login, CMD_DATA_SIZE, " ", false);
}

string Command::wrapBye(string login) {
    return wrapData("Good bye " + login, CMD_DATA_SIZE, " ", false);
}

string trim(const std::string &s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it)) it++;
    string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit)) rit++;
    return std::string(it, rit.base());
}

bool Command::isPingResponse() {
    return code == RESPONSE_PING;
}

string Command::requestPing(char num) {
    return wrapData({num, CMD_PING}, CMD_DATA_SIZE + 1, " ", false);
}

