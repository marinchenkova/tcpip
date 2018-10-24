#ifndef TCPIP_COMMAND_H
#define TCPIP_COMMAND_H

#include <stdio.h>
#include <array>
#include <set>
#include <string>
#include "Client.h"
#include <sstream>

using namespace std;


static const unsigned int CMD_DATA_SIZE = 40;
static const unsigned int CMD_SIZE = CMD_DATA_SIZE + 1;

static const char CMD_ACCOUNT_ID = '0';
static const char CMD_BALANCE = '1';
static const char CMD_CLIENTS = '2';
static const char CMD_LOGIN = '3';
static const char CMD_LOGOUT = '4';
static const char CMD_PAY_TO = '5';
static const char CMD_REGISTER = '6';

static const char RESPONSE_BAD_DATA = 'b';
static const char RESPONSE_CLIENTS = 'c';
static const char RESPONSE_INPUT_INCORRECT = 'i';
static const char RESPONSE_LOGIN_BUSY = 'l';
static const char RESPONSE_NEED_LOGIN = 'n';
static const char RESPONSE_OK = 'o';
static const char RESPONSE_UNKNOWN_CMD = 'u';

static const string EMPTY_STR           = "                                        ";
static const string BAD_DATA_STR        = "ERROR: broken data, please retry sending";
static const string INPUT_INCORRECT_STR = "ERROR: bad input, only A-Z, a-z, 0-9, _ ";
static const string LOGIN_BUSY_STR      = "ERROR: login is busy, try another one   ";
static const string NEED_LOGIN_STR      = "ERROR: you need to log in               ";
static const string UNKNOWN_CMD_STR     = "ERROR: unknown command                  ";

class Command {
private:
    char code;
    string data;
    string account_id;
    int balance;
    string login;
    string password;
    Command(char response);
    void checkData();
    string getAccountId();
    string getBalance();
    string getLogin();
    string getPassword();
public:
    Command(string cmd);
    char getCode() { return code; }
    string getData() { return data; }
    string response(set<Client>& clientSet, int socket);
    operator string() const;
    friend ostream& operator<<(ostream& os, const Command& command);
};

bool isWord(string str);
bool isNumber(string str);

#endif //TCPIP_COMMAND_H
