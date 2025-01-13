#include <FileManager.h>
#include "printer.h"
#include "LittleFS.h"

FileManager::FileManager() {}

void FileManager::setup()
{
    printDebug("Setting up LittleFS");
    if (!LittleFS.begin())
    {
        printDebug("An Error has occurred while mounting LittleFS");
        return;
    }
    printDebug("LittleFS mounted successfully");
}

void FileManager::writeToFile(String fileName, String data)
{
    printDebug("Writing to file: " + fileName);
    File file = LittleFS.open(fileName, "w");
    if (!file)
    {
        printDebug("An Error has occurred while opening the file");
        return;
    }
    file.print(data);
    file.close();
    printDebug("Data written to file: " + fileName);
}

String FileManager::readFromFile(String fileName)
{
    printDebug("Reading from file: " + fileName);
    File file = LittleFS.open(fileName, "r");
    if (!file)
    {
        printDebug("An Error has occurred while opening the file");
        return "";
    }
    String data = file.readString();
    file.close();
    printDebug("Data read from file: " + fileName);
    return data;
}

void FileManager::appendToFile(String fileName, String data)
{
    printDebug("Appending to file: " + fileName);
    File file = LittleFS.open(fileName, "a");
    if (!file)
    {
        printDebug("An Error has occurred while opening the file");
        return;
    }
    file.print(data);
    file.close();
    printDebug("Data appended to file: " + fileName);
}

void FileManager::removeFile(String fileName)
{
    printDebug("Removing file: " + fileName);
    if (!LittleFS.exists(fileName))
    {
        printDebug("File does not exist");
        return;
    }
    LittleFS.remove(fileName);
    printDebug("File removed: " + fileName);
}

String FileManager::listFiles(String path)
{
    printDebug("Listing files");
    String files = "";
    Dir dir = LittleFS.openDir(path);
    while (dir.next())
    {
        if (dir.isFile())
            files += "F: ";
        else
            files += "D: ";

        files += path;
        files += dir.fileName();
        files += "\n";
    }
    printDebug("Files listed");
    return files;
}