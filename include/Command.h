#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"

enum CommandSource
{
    SERIAL_COMMAND,
    TELEGRAM_COMMAND,
    ALEXA_COMMAND
};

class Command
{
public:
    Command();
    Command(String command, CommandSource source, String issuer);
    Command(String command, CommandSource source);
    bool isCommandIssuerAdmin();
    bool isCommandIssuerRegisteredUser();
    String getCommand() { return command; }
    String getIssuer() { return issuer; }
    CommandSource getSource() { return source; }
    void setCommand(String command);
    void setSource(CommandSource CommandSource);
    void setIssuer(String issuer);

private:
    String command = "";
    String issuer = "";
    CommandSource source;
    String cleanString(String str);
};

#endif