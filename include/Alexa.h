#ifndef ALEXA_H
#define ALEXA_H

#include "Arduino.h"
#include <Espalexa.h>
#include "Io.h"

class Alexa
{
public:
    Alexa();
    void setup(Io *io);
    void loop();
    static void alarmCallback(EspalexaDevice *d);

private:
    Espalexa espalexa;
    static Io *io;
};

#endif