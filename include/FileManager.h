#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Arduino.h"

class FileManager
{
public:
    FileManager();
    static void setup();
    static void writeToFile(String fileName, String data);
    static String readFromFile(String fileName);
    static void appendToFile(String fileName, String data);
    static void removeFile(String fileName);
    static String listFiles(String path);
};

#endif