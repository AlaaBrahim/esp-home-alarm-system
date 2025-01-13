#include <ESP8266WiFi.h>
#include "secrets.h"
#include "printer.h"
#include "wifi.h"

void setupWifi()
{
    WiFi.begin(ssid1, password1);
    printDebug("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        printDebug(".");
    }
    printDebug("connected " + WiFi.localIP().toString());
}