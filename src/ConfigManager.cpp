#include "ConfigManager.h"
#include "ArduinoJson.h"
#include "FileManager.h"
#include "Printer.h"
#include "config.h"

ConfigManager::ConfigManager()
{
}

void ConfigManager::setConfig(String key, String value)
{
    String configs = FileManager::readFromFile(CONFIG_FILE);
    JsonDocument doc;
    if (configs != "")
    {
        deserializeJson(doc, configs);
    }
    JsonObject newConfig = doc["configs"].add<JsonObject>();

    printDebug("Setting config: " + key + " to " + value);

    newConfig[key] = value;

    doc.shrinkToFit();
    String output;
    serializeJson(doc, output);
    FileManager::writeToFile(CONFIG_FILE, output);
}

String ConfigManager::getConfig(String key)
{
    String configs = FileManager::readFromFile(CONFIG_FILE);
    JsonDocument doc;
    if (configs != "")
    {
        deserializeJson(doc, configs);
    }
    if (!doc["configs"].containsKey(key))
    {
        return "";
    }
    JsonObject config = doc["configs"].as<JsonObject>();
    return config[key];
}

void ConfigManager::removeConfig(String key)
{
    String configs = FileManager::readFromFile(CONFIG_FILE);
    JsonDocument doc;
    if (configs != "")
    {
        deserializeJson(doc, configs);
    }
    doc["configs"].remove(key);
    doc.shrinkToFit();
    String output;
    serializeJson(doc, output);
    FileManager::writeToFile(CONFIG_FILE, output);
}

String ConfigManager::getConfigs()
{
    String configs = FileManager::readFromFile(CONFIG_FILE);
    return configs;
}