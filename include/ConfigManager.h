#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Arduino.h"

class ConfigManager
{
public:
    ConfigManager();
    static void setConfig(String key, String value);
    static String getConfig(String key);
    static void removeConfig(String key);
    static String getConfigs();

private:
};

#endif