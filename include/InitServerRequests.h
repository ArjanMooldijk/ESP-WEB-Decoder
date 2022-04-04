#ifndef InitServerRequests_h
#define InitServerRequests_h

#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
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
    server.on("/cleanstyle.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/cleanstyle.css", "text/css"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/base.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/base.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/jquery-3.6.0.min.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/mustache.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/mustache.min.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/deKoder.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/deKoder.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/signale.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/signale.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/snippets.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/snippets.js", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/image/Vor2.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/image/Vor2.gif", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/image/Vor4.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/image/Vor4.gif", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/image/Vor5.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/image/Vor5.gif", "text/plain"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/image/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/image/H3gro.gif", "text/plain"); });

    // server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
    //     { 
    //     //Handling function implementation
    //     for (size_t i = 0; i < len; i++) 
    //     {
    //         Serial.write(data[i]);
    //     } 
    //     Serial.println();
        
    //     request->send(200);
    //     });



    // server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
        //       {
        //   request->send_P(200, "text/plain", readINA219Current(1).c_str()); 
        // });

}

#endif