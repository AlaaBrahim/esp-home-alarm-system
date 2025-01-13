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

Command Io::recieveCommand()
{
    Command command = commandQueue.pop();
    this->lastProcessedCommand = command;
    return command;
}

bool Io::newCommandRecieved()
{
    if (SERIAL && newSerialRecieved())
    {
        Command command = Command(recieveSerial(), CommandSource::SERIAL_COMMAND);
        commandQueue.unshift(command);
    }

    if (TELEGRAM && telegramHandler.newMessageExists())
    {
        Command command = Command(telegramHandler.getNewMessage(), CommandSource::TELEGRAM_COMMAND, telegramHandler.getNewMessageChatID());
        commandQueue.unshift(command);
    }
    return !commandQueue.isEmpty();
}

void Io::replyCommand(String message)
{
    if (lastProcessedCommand.getSource() == CommandSource::SERIAL_COMMAND)
    {
        print(message);
    }

    if (lastProcessedCommand.getSource() == CommandSource::TELEGRAM_COMMAND)
    {
        telegramHandler.replyToMessage(message);
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

void Io::addCommand(String message, CommandSource source)
{
    Command command(message, source);
    commandQueue.unshift(command);
}