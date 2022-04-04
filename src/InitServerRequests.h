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
    server.on("/Vor2.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor2.gif", "image/gif"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/Vor4.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor4.gif", "image/gif"); });
    // Route to load jquery-3.6.0.min.js file
    server.on("/Vor5.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor5.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H2gr.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H3gro.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H3grg.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H4grog.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H4goro.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H5grogo.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H5grgog.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7ggogr.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7gogor.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7gogogr.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/SIM Vor.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/sim.png", "image/png"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/fsm.jpg", "image/jpg"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Bedraf-Halt.gif", "image/gif"); });
              
    server.on("/H3gro.gif", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Zwerg", "image/gif"); });

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