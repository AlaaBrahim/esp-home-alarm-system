#include "UserManager.h"
#include "ArduinoJson.h"
#include "FileManager.h"
#include "Printer.h"

UserManager::UserManager()
{
}

void UserManager::addUser(User user)
{
    String users = FileManager::readFromFile("users.json");
    JsonDocument doc;
    if (users != "")
    {
        deserializeJson(doc, users);
    }
    JsonObject newUser = doc["users"].add<JsonObject>();
    printDebug("Adding user: " + user.name);
    newUser["name"] = user.name;
    newUser["id"] = user.id;
    newUser["isAdmin"] = user.isAdmin;

    doc.shrinkToFit();
    String output;
    serializeJson(doc, output);
    FileManager::writeToFile("users.json", output);
}

void UserManager::removeUser(String id)
{
    String users = FileManager::readFromFile("users.json");
    JsonDocument doc;
    if (users != "")
    {
        deserializeJson(doc, users);
    }
    JsonArray usersArray = doc["users"].as<JsonArray>();
    for (int i = 0; i < usersArray.size(); i++)
    {
        JsonObject user = usersArray[i].as<JsonObject>();
        if (user["id"] == id)
        {
            usersArray.remove(i);
            break;
        }
    }
    doc.shrinkToFit();
    String output;
    serializeJson(doc, output);
    FileManager::writeToFile("users.json", output);
}

User UserManager::getUser(String id)
{
    String users = FileManager::readFromFile("users.json");
    JsonDocument doc;
    if (users != "")
    {
        deserializeJson(doc, users);
    }
    JsonArray usersArray = doc["users"].as<JsonArray>();
    for (int i = 0; i < usersArray.size(); i++)
    {
        JsonObject user = usersArray[i].as<JsonObject>();
        if (user["id"] == id)
        {
            User u;
            u.name = user["name"].as<String>();
            u.id = user["id"].as<String>();
            u.isAdmin = user["isAdmin"].as<bool>();
            return u;
        }
    }
    User u;
    u.name = "";
    u.id = "";
    u.isAdmin = false;
    return u;
}

bool UserManager::isUser(String id)
{
    return getUser(id).name != "";
}

bool UserManager::isAdmin(String id)
{
    return getUser(id).isAdmin;
}

String *UserManager::getUsers(int &count)
{
    String users = FileManager::readFromFile("users.json");
    JsonDocument doc;
    if (users != "")
    {
        deserializeJson(doc, users);
    }
    JsonArray usersArray = doc["users"].as<JsonArray>();
    String *userList = new String[usersArray.size()];
    count = usersArray.size();
    for (int i = 0; i < usersArray.size(); i++)
    {
        JsonObject user = usersArray[i].as<JsonObject>();
        userList[i] = user["id"].as<String>();
    }
    return userList;
}