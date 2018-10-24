#ifndef TCPIP_COMMAND_H
#define TCPIP_COMMAND_H

#include <stdio.h>
#include <array>
#include <set>
#include <string>
#include <sstream>
#include "Client.h"

using namespace std;


static const unsigned int MIN_WORD_SIZE = 4;
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
static const char RESPONSE_NEED_LOGIN = 'm';
static const char RESPONSE_NEED_LOGOUT = 'n';
static const char RESPONSE_OK = 'o';
static const char RESPONSE_UNKNOWN_CMD = 'u';

static const string BAD_DATA_STR        = "ERROR  broken data  please retry sending";
static const string INPUT_INCORRECT_STR = "ERROR  incorrect input                  ";
static const string LOGIN_BUSY_STR      = "ERROR  log_in is busy  try another one  ";
static const string NEED_LOGIN_STR      = "ERROR  you need to log in               ";
static const string NEED_LOGOUT_STR     = "ERROR  you are already logged in        ";
static const string UNKNOWN_CMD_STR     = "ERROR  unknown command                  ";

class Command {
private:
    char code;
    string data;
    void checkData();
public:
    Command(string cmd);
    static string wrapData(string data, int size, string wrap, bool start);
    static string wrapData(int data, int size, string wrap, bool start);
    string extractWord(unsigned int start, unsigned int end);
    char getCode() { return code; }
    string getData() { return data; }
    string response(set<Client>& clientSet, int socket);
    operator string() const;
    friend ostream& operator<<(ostream& os, const Command& command);
};

bool isValidData(string str);
bool isWord(string str);
bool isNumber(string str);
string trim(const std::string &s);

#endif //TCPIP_COMMAND_H
