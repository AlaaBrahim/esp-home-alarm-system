#include "CommandManager.h"
#include "printer.h"
#include "TelegramHandler.h"
#include "SerialReciever.h"
#include "FileManager.h"
#include "UserManager.h"
#include "AlarmManager.h"
#include "HomeCCTV.h"

CommandManager::CommandManager() {}

String CommandManager::executeCommand(String command)
{
    command.toLowerCase();
    command.trim();
    if (command.startsWith("print"))
    {
        command.remove(0, 6);
        return (command);
    }
    else if (command.startsWith("debug"))
    {
        command.remove(0, 6);
        return ("debugging " + command);
    }
    else if (command.startsWith("cat"))
    {
        command.remove(0, 4);
        return FileManager::readFromFile(command);
    }
    else if (command.startsWith("write"))
    {
        // write filename file contents
        command.remove(0, 6);
        int spaceIndex = command.indexOf(" ");
        String filename = command.substring(0, spaceIndex);
        command.remove(0, spaceIndex + 1);
        FileManager::writeToFile(filename, command);
        return ("Data written to file");
    }
    else if (command.startsWith("append"))
    {
        command.remove(0, 7);
        int spaceIndex = command.indexOf(" ");
        String filename = command.substring(0, spaceIndex);
        command.remove(0, spaceIndex + 1);
        FileManager::appendToFile(filename, command);
        return ("Data appended to file");
    }
    else if (command.startsWith("rm"))
    {
        command.remove(0, 3);
        FileManager::removeFile(command);
        return ("File removed");
    }
    else if (command.startsWith("ls"))
    {
        command.remove(0, 3);
        return FileManager::listFiles(command);
    }
    else if (command.startsWith("adduser"))
    {
        // adduser username id isAdmin: true/false
        command.remove(0, 8);
        User user;
        user.name = command.substring(0, command.indexOf(" "));
        command.remove(0, user.name.length() + 1);
        user.id = command.substring(0, command.indexOf(" "));
        command.remove(0, user.id.length() + 1);
        user.isAdmin = command == "true";

        UserManager::addUser(user);
        return ("User added");
    }
    else if (command.startsWith("deleteuser"))
    {
        command.remove(0, 11);
        UserManager::removeUser(command);
        return ("User deleted");
    }

    else if (command.startsWith("isuser"))
    {
        command.remove(0, 7);
        return (UserManager::isUser(command) ? "User exists" : "User does not exist");
    }
    else if (command.startsWith("isadmin"))
    {
        command.remove(0, 8);
        return (UserManager::isAdmin(command) ? "User is admin" : "User is not admin");
    }
    else if (command.startsWith("getuser"))
    {
        command.remove(0, 8);
        return UserManager::getUser(command).name;
    }
    else if (command.startsWith("listusers"))
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
    else if (command.startsWith("arm"))
    {
        AlarmManager::arm();
        return ("Alarm armed");
    }
    else if (command.startsWith("disarm"))
    {
        AlarmManager::disarm();
        return ("Alarm disarmed");
    }
    else if (command.startsWith("scream"))
    {
        AlarmManager::scream();
        return ("Alarm screaming");
    }
    else if (command.startsWith("mute"))
    {
        AlarmManager::mute();
        return ("Alarm muted");
    }
    else if (command.startsWith("trigger"))
    {
        AlarmManager::trigger();
        return ("Alarm triggered");
    }
    else if (command.startsWith("getstate"))
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
    else if (command.startsWith("enablecctvhome"))
    {
        HomeCCTV::enable();
        return ("Home CCTV enabled");
    }
    else if (command.startsWith("disablecctvhome"))
    {
        HomeCCTV::disable();
        return ("Home CCTV disabled");
    }
    else
    {
        return ("Unknown command");
    }
}
