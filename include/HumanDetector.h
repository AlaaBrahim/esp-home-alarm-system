#ifndef HUMANDETECTOR_H
#define HUMANDETECTOR_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

class HumanDetector
{
public:
    HumanDetector();
    bool checkForHuman();
    bool checkHeartbeat();

private:
    WiFiServer server;
    WiFiClient client;
    unsigned long lastHeartbeat;
    const unsigned long heartbeatTimeout = 30000; // 30 seconds
    bool processClient();
    void resetHeartbeat();
};

#endif // HUMANDETECTOR_H
