#ifndef InitServerRequests_h
#define InitServerRequests_h

#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Replaces placeholder with DHT values
String processor(const String &var)
{
    // Serial.println(var);
    return String();
}

void init_Servers()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false, processor); });
    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });
    // Route to load gauge.min.js file
    server.on("/gauge.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/gauge.min.js", "text/plain"); });

    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        { 
        //Handling function implementation
        for (size_t i = 0; i < len; i++) 
        {
            Serial.write(data[i]);
        } 
        Serial.println();
        
        request->send(200);
        });



    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        //   request->send_P(200, "text/plain", readINA219Current(1).c_str()); 
        });

}

#endif