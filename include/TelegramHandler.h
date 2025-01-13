#ifndef TELEGRAM_HANDLER_H
#define TELEGRAM_HANDLER_H

#include "config.h"
#include <Arduino.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

class TelegramHandler
{
public:
    TelegramHandler();
    void setupTelegram();
    void sendTelegramMessage(String chat_id, String message);
    void broadcastTelegramMessage(String message, String *users, int usersCount);
    bool newMessageExists();
    String getNewMessage();
    String getNewMessageChatID();
    void replyToMessage(String message);

private:
    UniversalTelegramBot bot;
    telegramMessage *messages;
    WiFiClientSecure client;
    int unreadMessagesCount = -1;
    int lastReadMessageCounter = -1;
};

#endif