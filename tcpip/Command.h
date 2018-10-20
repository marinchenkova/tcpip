#ifndef TCPIP_COMMAND_H
#define TCPIP_COMMAND_H

#include <stdio.h>
#include <array>
#include <set>
#include "Client.h"

using namespace std;

static const int CMD_SIZE = 41;
static const int CMD_DATA_SIZE = 40;

static const char CMD_REGISTER = '0';
static const char CMD_LOGIN = '1';
static const char CMD_ACCOUNT_ID = '2';
static const char CMD_BALANCE = '3';
static const char CMD_PAY_TO = '4';
static const char CMD_CLIENTS = '5';
static const char CMD_LOGOUT = '6';

static const char RESPONSE_LOGIN_BUSY = 'a';
static const char RESPONSE_INPUT_INCORRECT = 'b';
static const char RESPONSE_OK = 'c';
static const char RESPONSE_NEED_LOGIN = 'd';
static const char RESPONSE_CLIENTS = 'e';


class Command {
private:
    char code;
    char data[CMD_DATA_SIZE];
public:
    Command(char cmd[CMD_SIZE]);
    char getCode() { return code; }
    char* getData() { return data; }
};

char* response(Command cmd);

#endif //TCPIP_COMMAND_H
