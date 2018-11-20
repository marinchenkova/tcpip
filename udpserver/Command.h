#ifndef UDPSERVER_COMMAND_H
#define UDPSERVER_COMMAND_H


#include <stdio.h>
#include <array>
#include <set>
#include <string>
#include <sstream>
#include "Client.h"
#include <cstdlib>

using namespace std;


static const unsigned int MIN_WORD_SIZE = 4;
static const unsigned int MAX_WORD_SIZE = 20;
static const unsigned int CMD_DATA_SIZE = 40;
static const unsigned int CMD_SIZE = CMD_DATA_SIZE + 1;

static const char PREFIX = '[';

static const char CMD_ACCOUNT_ID = '0';
static const char CMD_BALANCE    = '1';
static const char CMD_CLIENTS    = '2';
static const char CMD_GET        = '3';
static const char CMD_LOGIN      = '4';
static const char CMD_LOGOUT     = '5';
static const char CMD_PAY_TO     = '6';
static const char CMD_PUT        = '7';
static const char CMD_REGISTER   = '8';
static const char CMD_PING       = '9';

static const char RESPONSE_BAD_DATA          = 'b';
static const char RESPONSE_CLIENTS           = 'c';
static const char RESPONSE_INPUT_INCORRECT   = 'i';
static const char RESPONSE_LOGIN_BUSY        = 'l';
static const char RESPONSE_NEED_LOGIN        = 'm';
static const char RESPONSE_NEED_LOGOUT       = 'n';
static const char RESPONSE_CLIENT_ONLINE_NOW = 'w';
static const char RESPONSE_OK                = 'o';
static const char RESPONSE_UNKNOWN_CMD       = 'u';
static const char RESPONSE_PING              = 'p';

static const string BAD_DATA_STR        = "ERROR Broken data  please retry sending ";
static const string CLIENT_ONLINE_STR   = "Client is online now                    ";
static const string LOGIN_INCORRECT_STR = "ERROR Login incorrect input             ";
static const string ID_INCORRECT_STR    = "ERROR ID incorrect input                ";
static const string PASS_INCORRECT_STR  = "ERROR Password incorrect input          ";
static const string LOGIN_BUSY_STR      = "Login is busy                           ";
static const string INSUF_FUNDS_STR     = "Insufficient funds                      ";
static const string NEED_LOGIN_STR      = "You need to log in                      ";
static const string NEED_LOGOUT_STR     = "You are already logged in               ";
static const string NEED_NUMBER_STR     = "ERROR Need number                       ";
static const string UNKNOWN_CMD_STR     = "ERROR Unknown command                   ";

static const string FINISH_ITER_C_STR = "F";


class Command {
private:
    char code;
    string data;
    sockaddr notifySocket;
    void checkData();
public:
    Command(string cmd);
    static string wrapData(string data, int size, string wrap, bool start);
    static string wrapData(unsigned long data, int size, string wrap, bool start);
    static string wrapBalance(unsigned long balance);
    static string wrapWelcome(string login);
    static string wrapBye(string login);
    static string requestPing();
    sockaddr notify() { return notifySocket; }
    string extractWord(unsigned int start, unsigned int end);
    unsigned long extractULong(unsigned int start, unsigned int end);
    string response(set<Client>& clientSet, sockaddr* addr);
    operator string() const;
    friend ostream& operator<<(ostream& os, const Command& command);
};

bool isValidData(string str);
bool isNumber(string str);
string trim(const std::string &s);


#endif //UDPSERVER_COMMAND_H
