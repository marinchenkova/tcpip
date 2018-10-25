#ifndef TCPIP_CLIENT_COMMAND_H
#define TCPIP_CLIENT_COMMAND_H

#include <stdio.h>
#include <array>
#include <set>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;


static const unsigned int MIN_WORD_SIZE = 4;
static const unsigned int MAX_WORD_SIZE = 20;
static const unsigned int CMD_DATA_SIZE = 40;
static const unsigned int CMD_SIZE = CMD_DATA_SIZE + 1;

static const char PREFIX = '[';

static const char CMD_ACCOUNT_ID  = '0';
static const char CMD_BALANCE     = '1';
static const char CMD_CLIENTS     = '2';
static const char CMD_GET         = '3';
static const char CMD_LOGIN       = '4';
static const char CMD_LOGOUT      = '5';
static const char CMD_PAY_TO      = '6';
static const char CMD_PUT         = '7';
static const char CMD_REGISTER    = '8';

static const string CMD_ACCOUNT_ID_STR  = "id";
static const string CMD_BALANCE_STR     = "balance";
static const string CMD_CLIENTS_STR     = "clients";
static const string CMD_GET_STR         = "get";
static const string CMD_LOGIN_STR       = "login";
static const string CMD_LOGOUT_STR      = "logout";
static const string CMD_PAY_TO_STR      = "payto";
static const string CMD_PUT_STR         = "put";
static const string CMD_REGISTER_STR    = "register";

static const string EMPTY_STR           = "                                        ";

static const string START_ITER_C_STR = "START";
static const string FINISH_ITER_C_STR = "FINISH";

class Command {
private:
    char code;
    string data;
public:
    Command(string cmd);
    static string wrapData(string data, int size, string wrap, bool start);
    operator string() const;
    friend ostream& operator<<(ostream& os, const Command& command);
};

#endif //TCPIP_CLIENT_COMMAND_H
