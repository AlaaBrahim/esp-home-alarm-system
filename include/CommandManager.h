#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "Arduino.h"
#include "TelegramHandler.h"

class CommandManager
{
public:
    CommandManager();
    String executeCommand(String command);
};

#endif