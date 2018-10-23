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

static const string EMPTY_DATA = "****************************************";

static const char RESPONSE_BAD_DATA = 'b';
static const char RESPONSE_CLIENTS = 'c';
static const char RESPONSE_INPUT_INCORRECT = 'i';
static const char RESPONSE_LOGIN_BUSY = 'l';
static const char RESPONSE_NEED_LOGIN = 'n';
static const char RESPONSE_OK = 'o';
static const char RESPONSE_UNKNOWN_CMD = 'u';


class Command {
private:
    char code;
    string data;
    Command(char response);
    void checkData();
public:
    Command(string cmd);
    char getCode() { return code; }
    string getData() { return data; }
    string response(set<Client>* clientSet);
    string to_string(Command command);
    friend ostream& operator<<(ostream& os, const Command& command);
};

bool isWord(string str);
bool isNumber(string str);

#endif //TCPIP_COMMAND_H
