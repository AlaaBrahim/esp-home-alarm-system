#ifndef HOMECCTV_H
#define HOMECCTV_H

#include <ESP8266HTTPClient.h>

class HomeCCTV
{
public:
    HomeCCTV();
    static void enable();
    static void disable();

private:
    static String getIp();
    static void sendRequest(const String &url);
};

#endif // HOMECCTV_H
