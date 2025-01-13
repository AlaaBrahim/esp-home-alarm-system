#include "TelegramHandler.h"
#include "secrets.h"
#include "printer.h"

TelegramHandler::TelegramHandler() : bot(TELEGRAM_BOT_TOKEN, client) {}

void TelegramHandler::setupTelegram()
{
    printDebug("Setting up Telegram");
    client = WiFiClientSecure();
    client.setInsecure();
    UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);
    this->bot = bot;
    printDebug("Telegram setup complete");
}

void TelegramHandler::sendTelegramMessage(String chat_id, String message)
{
    printDebug("Sending message to " + chat_id + ": " + message);
    bot.sendMessage(chat_id, message, "");
}

void TelegramHandler::broadcastTelegramMessage(String message, String *users, int usersCount)
{
    printDebug("Broadcasting message: " + message);
    for (int i = 0; i < usersCount; i++)
    {
        bot.sendMessage(users[i], message, "");
    }
}

bool TelegramHandler::newMessageExists()
{
    if (lastReadMessageCounter < unreadMessagesCount)
        return true;

    unreadMessagesCount = bot.getUpdates(bot.last_message_received + 1);
    lastReadMessageCounter = 0;
    return unreadMessagesCount > 0;
}

String TelegramHandler::getNewMessage()
{
    return bot.messages[lastReadMessageCounter].text;
}

String TelegramHandler::getNewMessageChatID()
{
    return bot.messages[lastReadMessageCounter].chat_id;
}

void TelegramHandler::replyToMessage(String message)
{
    String chat_id = bot.messages[lastReadMessageCounter].chat_id;
    lastReadMessageCounter++;
    TelegramHandler::sendTelegramMessage(chat_id, message);
}