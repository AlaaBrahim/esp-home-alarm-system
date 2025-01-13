#include "CommandManager.h"
#include "printer.h"
#include "TelegramHandler.h"
#include "SerialReciever.h"
#include "FileManager.h"
#include "UserManager.h"
#include "AlarmManager.h"
#include "HomeCCTV.h"
#include "ConfigManager.h"

CommandManager::CommandManager() {}

String CommandManager::executeCommand(Command command)
{

    if (!command.isCommandIssuerRegisteredUser())
    {
        return ("You are not authorized to perform this action");
    }

    String commandMessage = command.getCommand();

    if (command.isCommandIssuerAdmin())
    {
        if (commandMessage.startsWith("print"))
        {
            commandMessage.remove(0, 6);
            return (commandMessage);
        }
        else if (commandMessage.startsWith("debug"))
        {
            commandMessage.remove(0, 6);
            if (commandMessage == "readAnalog")
            {
                return String(AlarmManager::readAnalog());
            }
            return ("debugging " + commandMessage);
        }
        else if (commandMessage.startsWith("cat"))
        {
            commandMessage.remove(0, 4);
            return FileManager::readFromFile(commandMessage);
        }
        else if (commandMessage.startsWith("config"))
        {
            commandMessage.remove(0, 7);
            int spaceIndex = commandMessage.indexOf(" ");
            String key = commandMessage.substring(0, spaceIndex);
            commandMessage.remove(0, spaceIndex + 1);
            String value = commandMessage;
            ConfigManager::setConfig(key, value);
            return ("Config set");
        }
        else if (commandMessage.startsWith("getconfig"))
        {
            commandMessage.remove(0, 10);
            return ConfigManager::getConfig(commandMessage);
        }
        else if (commandMessage.startsWith("removeconfig"))
        {
            commandMessage.remove(0, 13);
            ConfigManager::removeConfig(commandMessage);
            return ("Config removed");
        }
        else if (commandMessage.startsWith("getconfigs"))
        {
            return ConfigManager::getConfigs();
        }
        else if (commandMessage.startsWith("write"))
        {
            // write filename file contents
            commandMessage.remove(0, 6);
            int spaceIndex = commandMessage.indexOf(" ");
            String filename = commandMessage.substring(0, spaceIndex);
            commandMessage.remove(0, spaceIndex + 1);
            FileManager::writeToFile(filename, commandMessage);
            return ("Data written to file");
        }
        else if (commandMessage.startsWith("append"))
        {
            commandMessage.remove(0, 7);
            int spaceIndex = commandMessage.indexOf(" ");
            String filename = commandMessage.substring(0, spaceIndex);
            commandMessage.remove(0, spaceIndex + 1);
            FileManager::appendToFile(filename, commandMessage);
            return ("Data appended to file");
        }
        else if (commandMessage.startsWith("rm"))
        {
            commandMessage.remove(0, 3);
            FileManager::removeFile(commandMessage);
            return ("File removed");
        }
        else if (commandMessage.startsWith("ls"))
        {
            commandMessage.remove(0, 3);
            return FileManager::listFiles(commandMessage);
        }
        else if (commandMessage.startsWith("adduser"))
        {
            // adduser username id isAdmin: true/false
            commandMessage.remove(0, 8);
            User user;
            user.name = commandMessage.substring(0, commandMessage.indexOf(" "));
            commandMessage.remove(0, user.name.length() + 1);
            user.id = commandMessage.substring(0, commandMessage.indexOf(" "));
            commandMessage.remove(0, user.id.length() + 1);
            user.isAdmin = commandMessage == "true";

            UserManager::addUser(user);
            return ("User added");
        }
        else if (commandMessage.startsWith("deleteuser"))
        {
            commandMessage.remove(0, 11);
            UserManager::removeUser(commandMessage);
            return ("User deleted");
        }

        else if (commandMessage.startsWith("isuser"))
        {
            commandMessage.remove(0, 7);
            return (UserManager::isUser(commandMessage) ? "User exists" : "User does not exist");
        }
        else if (commandMessage.startsWith("isadmin"))
        {
            commandMessage.remove(0, 8);
            return (UserManager::isAdmin(commandMessage) ? "User is admin" : "User is not admin");
        }
        else if (commandMessage.startsWith("getuser"))
        {
            commandMessage.remove(0, 8);
            return UserManager::getUser(commandMessage).name;
        }
        else if (commandMessage.startsWith("listusers"))
        {
            printDebug("Getting users");
            int count;
            String *users = UserManager::getUsers(count);
            String output = "Users count: " + String(count) + ": [";
            for (int i = 0; i < count; i++)
            {
                output += users[i] + ", ";
            }
            output += "]";
            return output;
        }
    }

    if (commandMessage.startsWith("arm"))
    {
        AlarmManager::arm();
        return ("Alarm armed");
    }
    else if (commandMessage.startsWith("disarm"))
    {
        AlarmManager::disarm();
        return ("Alarm disarmed");
    }
    else if (commandMessage.startsWith("scream"))
    {
        AlarmManager::scream();
        return ("Alarm screaming");
    }
    else if (commandMessage.startsWith("mute"))
    {
        AlarmManager::mute();
        return ("Alarm muted");
    }
    else if (commandMessage.startsWith("trigger"))
    {
        AlarmManager::trigger();
        return ("Alarm triggered");
    }
    else if (commandMessage.startsWith("getstate"))
    {
        AlarmState state = AlarmManager::getState();
        if (state == ARMED)
            return ("Alarm is armed");
        if (state == DISARMED)
            return ("Alarm is disarmed");
        if (state == ARMING)
            return ("Alarm is arming");
        return ("Unknown state");
    }
    else if (commandMessage.startsWith("enablecctvhome"))
    {
        HomeCCTV::enable();
        return ("Home CCTV enabled");
    }
    else if (commandMessage.startsWith("disablecctvhome"))
    {
        HomeCCTV::disable();
        return ("Home CCTV disabled");
    }
    else
    {
        return ("Unknown command");
    }
}
