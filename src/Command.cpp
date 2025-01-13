#include "Command.h"
#include "UserManager.h"

Command::Command() {}

Command::Command(String command, String issuer)
{
    command.toLowerCase();
    command.trim();

    issuer.toLowerCase();
    issuer.trim();

    this->command = command;
    this->issuer = issuer;
}

bool Command::isAdmin()
{
    if (this->issuer == "serial" || UserManager::isAdmin(this->issuer))
        return true;

    return false;
}

bool Command::isUser()
{
    if (this->issuer == "alexa" || UserManager::isUser(this->issuer))
        return true;

    return false;
}

void Command::setCommand(String command)
{
    command.toLowerCase();
    command.trim();
    this->command = command;
}

void Command::setIssuer(String issuer)
{
    issuer.toLowerCase();
    issuer.trim();
    this->issuer = issuer;
}