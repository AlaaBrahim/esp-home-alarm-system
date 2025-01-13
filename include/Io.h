#ifndef IO_H
#define IO_H

#include "Arduino.h"
#include "TelegramHandler.h"
#include <ESPAsyncWebServer.h>

class Io
{
public:
    Io();
    void setup();
    bool newCommandRecieved();
    String recieveCommand();
    String getCommandIssuer();
    void replyCommand(String message);
    void broadcastMessage(String message);

private:
    TelegramHandler telegramHandler = TelegramHandler();
    bool serialRecieved = false;
    bool telegramRecieved = false;
    // AsyncWebServer server(80);
};

#endif