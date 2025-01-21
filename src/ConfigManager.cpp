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
    for (unsigned int i = 0; i < doc["configs"].size(); i++)
    {
        JsonObject config = doc["configs"][i].as<JsonObject>();
        if (config.containsKey(key))
        {
            printDebug("Updating config: " + key + " to " + value);
            config[key] = value;
            doc.shrinkToFit();
            String output;
            serializeJson(doc, output);
            FileManager::writeToFile(CONFIG_FILE, output);
            return;
        }
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
    JsonArray configsArray = doc["configs"].as<JsonArray>();
    for (unsigned int i = 0; i < configsArray.size(); i++)
    {
        JsonObject config = configsArray[i].as<JsonObject>();
        if (config.containsKey(key))
        {
            return config[key];
        }
    }
    return "";
}

void ConfigManager::removeConfig(String key)
{
    String configs = FileManager::readFromFile(CONFIG_FILE);
    JsonDocument doc;
    if (configs != "")
    {
        deserializeJson(doc, configs);
    }
    JsonArray configsArray = doc["configs"].as<JsonArray>();
    for (unsigned int i = 0; i < configsArray.size(); i++)
    {
        JsonObject config = configsArray[i].as<JsonObject>();
        if (config.containsKey(key))
        {
            configsArray.remove(i);
            break;
        }
    }
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