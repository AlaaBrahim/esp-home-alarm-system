#include "HomeCCTV.h"
#include "config.h"
#include "secrets.h"
#include "printer.h"

HomeCCTV::HomeCCTV() {}

void HomeCCTV::enable()
{
    printDebug("Enabling Home CCTV motion detection");
    String url = "http://" + String(HOME_CCTV_IP) + "/set_alarm.cgi?next_url=alarm.htm&motion_armed=1&input_armed=0&motion_sensitivity=3&motion_compensation=1&http=0&http_url=&preset=0&iolinkage=1&mail=0&upload_interval=0&ioin_level=1&ioout_level=0&schedule_enable=0&schedule_sun_0=0&schedule_sun_1=0&schedule_sun_2=0&schedule_mon_0=0&schedule_mon_1=0&schedule_mon_2=0&schedule_tue_0=0&schedule_tue_1=0&schedule_tue_2=0&schedule_wed_0=0&schedule_wed_1=0&schedule_wed_2=0&schedule_thu_0=0&schedule_thu_1=0&schedule_thu_2=0&schedule_fri_0=0&schedule_fri_1=0&schedule_fri_2=0&schedule_sat_0=0&schedule_sat_1=0&schedule_sat_2=0";
    printDebug("Sending request to " + url);
    sendRequest(url);
}

void HomeCCTV::disable()
{
    printDebug("Disabling Home CCTV motion detection");
    String url = "http://" + String(HOME_CCTV_IP) + "/set_alarm.cgi?next_url=alarm.htm&motion_armed=0&input_armed=0&motion_sensitivity=5&motion_compensation=0&iolinkage=0&mail=0&upload_interval=0&preset=0&http=0&http_url=&schedule_enable=0&schedule_sun_0=0&schedule_sun_1=0&schedule_sun_2=0&schedule_mon_0=0&schedule_mon_1=0&schedule_mon_2=0&schedule_tue_0=0&schedule_tue_1=0&schedule_tue_2=0&schedule_wed_0=0&schedule_wed_1=0&schedule_wed_2=0&schedule_thu_0=0&schedule_thu_1=0&schedule_thu_2=0&schedule_fri_0=0&schedule_fri_1=0&schedule_fri_2=0&schedule_sat_0=0&schedule_sat_1=0&schedule_sat_2=0";
    printDebug("Sending request to " + url);
    sendRequest(url);
}

void HomeCCTV::sendRequest(const String &url)
{
    HTTPClient http;
    WiFiClient wifiClient;
    http.begin(wifiClient, url);
    http.addHeader("Authorization", "Basic " + String(HOME_CCTV_AUTH));
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        Serial.printf("HTTP request sent, response code: %d\n", httpCode);
    }
    else
    {
        Serial.printf("HTTP request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}
