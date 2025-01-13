#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include "Arduino.h"
#include "Io.h"

enum AlarmState
{
    ARMED,
    DISARMED,
    ARMING
};

class AlarmManager
{
public:
    AlarmManager();
    static void setup();
    static void arm();
    static void disarm();
    static void scream();
    static void mute();
    static void trigger();
    static int readAnalog();
    static AlarmState getState();
    static void thiefDetection(Io &io);

private:
    // GPIO pins
    static const int analogPin = A0; // Analog pin to detect alarm state
    static const int armPin = D1;    // Pin to arm the alarm
    static const int disarmPin = D2; // Pin to disarm the alarm
    static const int screamPin = D3; // Pin to panic the alarm
    static const int mutePin = D5;   // Pin to mute the alarm
    static const int doorPin = D6;   // Pin to detect thief
    static const int sirenPin = D7;  // Pin to control siren
};

#endif