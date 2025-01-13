#include "AlarmManager.h"
#include "Printer.h"
#include "Io.h"

AlarmManager::AlarmManager() {}

void AlarmManager::setup()
{
    printDebug("Setting up AlarmManager");
    pinMode(armPin, OUTPUT);
    digitalWrite(armPin, LOW);

    pinMode(disarmPin, OUTPUT);
    digitalWrite(disarmPin, LOW);

    pinMode(screamPin, OUTPUT);
    digitalWrite(screamPin, LOW);

    pinMode(mutePin, OUTPUT);
    digitalWrite(mutePin, LOW);

    pinMode(doorPin, OUTPUT);
    pinMode(sirenPin, INPUT);
    printDebug("AlarmManager setup complete");
}

void AlarmManager::arm()
{
    printDebug("Arming the alarm");
    digitalWrite(armPin, HIGH);
    delay(1000);
    digitalWrite(armPin, LOW);
}

void AlarmManager::disarm()
{
    printDebug("Disarming the alarm");
    digitalWrite(disarmPin, HIGH);
    delay(1000);
    digitalWrite(disarmPin, LOW);
}

void AlarmManager::scream()
{
    printDebug("Screaming the alarm");
    digitalWrite(screamPin, HIGH);
    delay(1000);
    digitalWrite(screamPin, LOW);
}

void AlarmManager::mute()
{
    printDebug("Muting the alarm");
    digitalWrite(mutePin, HIGH);
    delay(1000);
    digitalWrite(mutePin, LOW);
}

void AlarmManager::trigger()
{
    printDebug("Triggering the alarm");
    digitalWrite(doorPin, HIGH);
    delay(1000);
    digitalWrite(doorPin, LOW);
}

int AlarmManager::readAnalog()
{
    printDebug("Reading analog pin" + String(analogPin) + "value");
    int analogValue = analogRead(analogPin);
    printDebug("Analog value: " + String(analogValue));
    return analogValue;
}

AlarmState AlarmManager::getState()
{
    printDebug("Getting the alarm state");
    const unsigned long measureInterval = 300; // Time between measurements in milliseconds
    const int measureCount = 10;               // Number of measurements to take
    const int threshold = 1024 * 1.5 / 3.3;    // Threshold for determining if the LED is on

    int onCount = 0;
    int offCount = 0;

    for (int i = 0; i < measureCount; i++)
    {
        int analogValue = analogRead(analogPin);
        if (analogValue > threshold)
        {
            onCount++;
        }
        else
        {
            offCount++;
        }
        delay(measureInterval);
    }

    if (onCount == measureCount)
    {
        printDebug("Alarm is armed");
        return ARMED;
    }
    else if (offCount == measureCount)
    {
        printDebug("Alarm is disarmed");
        return DISARMED;
    }
    else
    {
        printDebug("Alarm is arming");
        return ARMING;
    }
}

void AlarmManager::thiefDetection(Io io)
{
    printDebug("Detecting thief");
    if (digitalRead(sirenPin) == HIGH)
    {
        io.broadcastMessage("Thief detected");
    }
}
