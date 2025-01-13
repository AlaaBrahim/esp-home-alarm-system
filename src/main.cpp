#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "printer.h"
#include "config.h"
#include "wifi.h"
#include "secrets.h"
#include "Io.h"
#include "CommandManager.h"
#include "FileManager.h"
#include "AlarmManager.h"
#include "HumanDetector.h"

Io io = Io();
CommandManager commandManager = CommandManager();
HumanDetector humanDetector = HumanDetector();

void setupOTA()
{
  ArduinoOTA.setHostname("esp8266-ota-alarm");
  ArduinoOTA.setPassword("ota_password"); // Set your OTA password here

  ArduinoOTA.onStart([]()
                     {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    printDebug("Start updating " + type); });

  ArduinoOTA.onEnd([]()
                   { printDebug("\nEnd"); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { printDebug("Progress: " + String((progress / (total / 100))) + "%"); });

  ArduinoOTA.onError([](ota_error_t error)
                     {
    printDebug("Error[" + String(error) + "]: ");
    if (error == OTA_AUTH_ERROR) {
      printDebug("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      printDebug("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      printDebug("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      printDebug("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      printDebug("End Failed");
    } });

  ArduinoOTA.begin();
  printDebug("OTA Initialized");
}

void setup()
{
  io.setup();
  AlarmManager::setup();
  printDebug("\n");
  printDebug("Setup Printer");

  printDebug("Setup Wifi");
  setupWifi();

  printDebug("Setup OTA");
  setupOTA();

  FileManager::setup();
}

void loop()
{
  ArduinoOTA.handle();

  AlarmManager::thiefDetection(io);
  if (humanDetector.checkForHuman())
  {
    AlarmManager::trigger();
  }
  if (io.newCommandRecieved())
  {
    String message = io.recieveCommand();
    String reply = commandManager.executeCommand(message);
    io.replyCommand(reply);
  }
  else
  {
    printDebug("No New Messages");
    delay(1000);
  }
}
