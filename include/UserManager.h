#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "Arduino.h"

struct User
{
    String name;
    String id;
    bool isAdmin;
};

class UserManager
{
public:
    UserManager();
    static void addUser(User user);
    static void removeUser(String id);
    static User getUser(String id);
    static bool isUser(String id);
    static bool isAdmin(String id);
    static String *getUsers(int &count);

private:
};

#endif