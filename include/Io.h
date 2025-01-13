#ifndef IO_H
#define IO_H

#include "Arduino.h"
#include "TelegramHandler.h"
#include <CircularBuffer.hpp>
#include "Command.h"

class Io
{
public:
    Io(const Io &) = delete;
    Io &operator=(const Io &) = delete;
    Io();
    void setup();
    bool newCommandRecieved();
    Command recieveCommand();
    void replyCommand(String message);
    void broadcastMessage(String message);
    void addCommand(String message, CommandSource source);

private:
    TelegramHandler telegramHandler = TelegramHandler();
    bool serialRecieved = false;
    bool telegramRecieved = false;
    bool manualCommandsRecieved = false;
    CircularBuffer<Command, 10> commandQueue;
    Command lastProcessedCommand;
};

#endif