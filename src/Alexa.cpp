#include "Alexa.h"
#include "config.h"
#include "printer.h"

Io *Alexa::io = nullptr;

Alexa::Alexa() {}

void Alexa::setup(Io *io)
{
    Alexa::io = io;
    espalexa.addDevice(ALEXA_ALARM_DEVICE_NAME, alarmCallback, EspalexaDeviceType::onoff);
    espalexa.begin();
}

void Alexa::loop()
{
    espalexa.loop();
}

void Alexa::alarmCallback(EspalexaDevice *d)
{
    if (d == nullptr)
        return; // this is good practice, but not required

    if (d->getValue())
    {
        // ON: Arm
        printDebug("Alexa ON " + (String)ALEXA_ALARM_DEVICE_NAME);
        if (Alexa::io != nullptr)
        {
            Alexa::io->addCommand("arm", CommandSource::ALEXA_COMMAND);
        }
    }
    else
    {
        // OFF: Disarm
        printDebug("Alexa OFF " + (String)ALEXA_ALARM_DEVICE_NAME);
        if (Alexa::io != nullptr)
        {
            Alexa::io->addCommand("disarm", CommandSource::ALEXA_COMMAND);
        }
    }
}