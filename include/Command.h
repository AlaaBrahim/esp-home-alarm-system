#ifndef COMMAND_H
#define COMMAND_H

#include "Arduino.h"

class Command
{
public:
    Command();
    Command(String command, String issuer);
    bool isCommandIssuerAdmin();
    bool isCommandIssuerNormalUser();
    String getCommand() { return command; }
    String getIssuer() { return issuer; }
    void setCommand(String command);
    void setIssuer(String issuer);

private:
    String command = "";
    String issuer = "";
};

#endif