#include "Command.h"
#include "UserManager.h"

Command::Command() {}

Command::Command(String command, CommandSource source, String issuer)
{
    command = cleanString(command);
    issuer = cleanString(issuer);

    this->command = command;
    this->source = source;
    this->issuer = issuer;
}

Command::Command(String command, CommandSource source)
{
    command = cleanString(command);

    this->command = command;
    this->source = source;
}

bool Command::isCommandIssuerAdmin()
{
    if (this->source == CommandSource::SERIAL_COMMAND)
        return true;

    if (this->source == CommandSource::TELEGRAM_COMMAND && UserManager::isAdmin(this->issuer))
        return true;

    return false;
}

bool Command::isCommandIssuerRegisteredUser()
{
    if (this->source == CommandSource::ALEXA_COMMAND)
        return true;

    if (this->source == CommandSource::TELEGRAM_COMMAND && UserManager::isUser(this->issuer))
        return true;

    return false;
}

void Command::setCommand(String command)
{
    this->command = cleanString(command);
}

void Command::setSource(CommandSource source)
{
    this->source = source;
}

void Command::setIssuer(String issuer)
{
    this->issuer = cleanString(issuer);
}

String Command::cleanString(String str)
{
    str.toLowerCase();
    str.trim();
    return str;
}