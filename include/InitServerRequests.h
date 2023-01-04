#ifndef InitServerRequests_h
#define InitServerRequests_h

#include <Arduino.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <string>
using namespace std;
#include <cctype>
#include <HandleAddress.h>

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

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/plain"); });

    server.on("/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/jquery-3.6.0.min.js", "text/plain"); });

    server.on("/mustache.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/mustache.min.js", "text/plain"); });

    server.on("/signale.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/signale.js", "text/plain"); });

    server.on("/snippets.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/snippets.js", "text/plain"); });

    server.on("/Vor2", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor2.gif", "image/gif"); });

    server.on("/Vor4", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor4.gif", "image/gif"); });

    server.on("/Vor5", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Vor5.gif", "image/gif"); });

    server.on("/H2gr", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H2gr.gif", "image/gif"); });

    server.on("/H3gro", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H3gro.gif", "image/gif"); });

    server.on("/H3grg", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H3grg.gif", "image/gif"); });

    server.on("/H4grog", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H4grog.gif", "image/gif"); });

    server.on("/H4goro", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H4goro.gif", "image/gif"); });

    server.on("/H5grogo", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H5grogo.gif", "image/gif"); });

    server.on("/H5grgog", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H5grgog.gif", "image/gif"); });

    server.on("/H7ggogr", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7ggogr.gif", "image/gif"); });

    server.on("/H7gogor", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7gogor.gif", "image/gif"); });

    server.on("/H7gogogr", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/H7gogogr.gif", "image/gif"); });

    server.on("/SIMV", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/SIMV.gif", "image/gif"); });

    server.on("/SIMH", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/SIMH.png", "image/png"); });

    server.on("/Fsm", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Fsm.jpg", "image/jpg"); });

    server.on("/HbB", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/HbB.gif", "image/gif"); });

    server.on("/Zwerg", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/Zwerg.gif", "image/gif"); });

    server.on("/GetDecVal", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "application/json", getDecoderValues()); });

    server.on(
        "/PostDecVal", HTTP_POST, [](AsyncWebServerRequest *request) {},
        NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
        String newJsonDec;
        size_t i;
        for (i = 0; i < len; i++) {
                newJsonDec += char(data[i]);
        }
        processJsonFromClient(newJsonDec);
        request->send(200); });

    server.on(
        "/EndTest", HTTP_POST, [](AsyncWebServerRequest *request) {},
        NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
        String newJsonDec;
        size_t i;
        for (i = 0; i < len; i++) {
                newJsonDec += char(data[i]);
        }
        postResponse res = endTestLights(newJsonDec);
        Serial.println("endTest completed");
        if (res.succes) {
            request->send(200); }
        else {
            request->send(500, "text/plain", res.message);
        } });
}

#endif