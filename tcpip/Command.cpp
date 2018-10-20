#include "Command.h"


Command::Command(char *cmd) {
    code = cmd[0];
    copy(cmd, cmd + CMD_DATA_SIZE, data);
}


char* response(Command cmd, set<Client>* clientSet) {
    switch(cmd.getCode()) {
        case CMD_REGISTER:

            break;
    }
}