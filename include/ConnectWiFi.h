#ifndef ConnectWiFi_h
#define ConnectWiFi_h

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

void saveConfigCallback()
// Callback notifying us of the need to save configuration
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
 
void configModeCallback(WiFiManager *myWiFiManager)
// Called when config mode launched
{
  Serial.println("Entered Configuration Mode");
 
  Serial.print("Config SSID: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
 
  Serial.print("Config IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void MakeWiFiConnection()
{
    WiFiManager wm;
    bool forceConfig = false;
    bool hostNameFileExist = loadHostNameFile();
    if (!hostNameFileExist)
    {
        Serial.println(F("Forcing config mode as there is no saved config"));
        forceConfig = true;
    }

    WiFi.mode(WIFI_STA);
    delay(200); // do not remove, give time for STA_START

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    WiFi.setHostname(hostName);
#ifdef ESP32MDNS_H
    if (MDNS.begin(_hostname))
    {
        MDNS.addService("http", "tcp", 80);
    }
#endif

    // Set config save notify callback
     wm.setSaveConfigCallback(saveConfigCallback);

     // Set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
     wm.setAPCallback(configModeCallback);
    
    // Text box (String) - 20 characters maximum
    WiFiManagerParameter custom_text_box("hostName", "Network name", hostName, 20);
    wm.addParameter(&custom_text_box);

    if (forceConfig)
    // Run in case of missing hostname file (first time)
    {
        if (!wm.startConfigPortal("NeueDekoder", "Ausserberg"))
        {
            Serial.println("failed to connect and hit timeout");
            delay(3000);
            // reset and try again, or maybe put it to deep sleep
            ESP.restart();
            delay(5000);
        }
    }
    else
    {
        if (!wm.autoConnect("NeueDekoder", "Ausserberg"))
        {
            Serial.println("failed to connect and hit timeout");
            delay(3000);
            // if we still have not connected restart and try all over again
            ESP.restart();
            delay(5000);
        }
    }
    // Copy the string value
    strncpy(hostName, custom_text_box.getValue(), sizeof(hostName));
    Serial.print("hostName: ");
    Serial.println(hostName);

    // Save the custom parameters to FS
    if (shouldSaveConfig)
    {
        saveHostNameFile();
    }
}
#endif