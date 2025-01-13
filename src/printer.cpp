#include "printer.h"

void print(String message)
{
    if (DEBUG)
    {
        Serial.println("DEBUG " + message);
    }

    if (TELEGRAM)
    {
        // send message to telegram
    }
}

void printDebug(String message)
{
    if (DEBUG)
    {
        Serial.println("DEBUG " + message);
    }
}