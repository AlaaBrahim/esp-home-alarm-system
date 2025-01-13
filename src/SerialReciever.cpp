#include <SerialReciever.h>

String recieveSerial()
{
    String command = "";
    if (Serial.available() > 0)
    {
        command = Serial.readString();
        // Read the incoming byte
        String command = Serial.readStringUntil('\n'); // Read the command until a newline character

        // Trim any whitespace characters from the command
        command.trim();
    }
    return command;
}

bool newSerialRecieved()
{
    return Serial.available() > 0;
}