#ifndef ConnectWiFi_h
#define ConnectWiFi_h

#include <Arduino.h>
#include <WiFi.h>

// Network credentials
/* const char *ssid = "Wifinetwerk van Jos";
const char *password = "suedRampe2020!";
IPAddress staticIP(192, 168, 0, 40); //fixed IP of booster monitor
IPAddress gateway(192, 168, 0, 1); */
/*
const char *ssid = "CazMool";
const char *password = "steak74;Mlles";
const char *deviceName = "Seindecoder"; */
IPAddress staticIP(192, 168, 178, 13); // fixed IP of booster monitor
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(8, 8, 8, 8);

void MakeOwnNetwork()
{
    const char *ssid = "Signal_Decoder";
    const char *password = "super_strong_password";
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());
}

void MakeWiFiConnection(String ssid, String password)
{
    // Connect to Wi-Fi with fixed IP
    WiFi.disconnect();
    WiFi.config(staticIP, gateway, subnet);
    // WiFi.hostname(this_dec[0].name);
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());
}

void ArrangeConnection()
{
    GetWiFiCredentials();
    if (ssid == "")
    {
        MakeOwnNetwork();
        // RegisterWifiCredentials(ssid, password);
    }
    MakeWiFiConnection(ssid, password);
}
#endif