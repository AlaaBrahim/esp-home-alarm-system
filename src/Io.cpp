#include "Io.h"
#include "config.h"
#include "SerialReciever.h"
#include "printer.h"
#include "UserManager.h"
#include <WebSerial.h>

Io::Io() {}

void Io::setup()
{
    if (TELEGRAM)
        telegramHandler.setupTelegram();
    if (SERIAL || DEBUG)
        Serial.begin(BAUD_RATE);
}

String Io::recieveCommand()
{
    if (SERIAL && serialRecieved)
        return recieveSerial();
    if (TELEGRAM && telegramRecieved)
        return telegramHandler.getNewMessage();
    return "";
}

bool Io::newCommandRecieved()
{
    if (SERIAL && newSerialRecieved())
    {
        serialRecieved = true;
        telegramRecieved = false;
        return true;
    }

    if (TELEGRAM && telegramHandler.newMessageExists())
    {
        telegramRecieved = true;
        serialRecieved = false;
        return true;
    }
    return false;
}

void Io::replyCommand(String message)
{
    if (SERIAL && serialRecieved)
    {
        print(message);
        serialRecieved = false;
    }
    if (TELEGRAM && telegramRecieved)
    {
        telegramHandler.replyToMessage(message);
        telegramRecieved = false;
    }
}

void Io::broadcastMessage(String message)
{
    printDebug("Broadcasting Message : " + message);
    if (SERIAL)
    {
        print(message);
    }
    if (TELEGRAM)
    {
        int count;
        String *users = UserManager::getUsers(count);
        telegramHandler.broadcastTelegramMessage(message, users, count);
    }
}