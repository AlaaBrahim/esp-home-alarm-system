#include "HumanDetector.h"
#include "printer.h"

HumanDetector::HumanDetector() : server(9999), lastHeartbeat(0)
{
    server.begin();
}

bool HumanDetector::checkForHuman()
{
    if (processClient())
    {
        String request = client.readStringUntil('}');
        printDebug("Received data : " + request);
        request.toLowerCase();
        if (request.indexOf("human") != -1)
        {
            return true;
        }
    }
    return false;
}

bool HumanDetector::checkHeartbeat()
{
    if (millis() - lastHeartbeat > heartbeatTimeout)
    {
        return true;
    }
    return false;
}

bool HumanDetector::processClient()
{
    if (!client || !client.connected())
    {
        client = server.available();
    }
    if (client)
    {
        if (client.available())
        {
            String line = client.readStringUntil('\n');
            line.trim();
            if (line.length() > 0)
            {
                lastHeartbeat = millis(); // Reset heartbeat timer
                return true;
            }
        }
    }
    return false;
}

void HumanDetector::resetHeartbeat()
{
    lastHeartbeat = millis();
}
