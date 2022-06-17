// Sketch for Swiss Signal decoder on ESP32
// Version 2 (with web interface, 16-03-22)  Arjan Mooldijk

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <string>
using namespace std;
#include <WiFi.h>
#include <WiFiManager.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ArduinoJson.h"
#include <AsyncElegantOTA.h>
#include <NmraDcc.h>
#include <Settings.h>
#include <GetFromFlash.h>
#include <Signale.h>
//--------    DO NOT MAKE ANY CHANGES BELOW, UNLESS YOU WANT TO ALTER THE PROGRAM ;-)    ---------------------------///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// const char *ssid = "CazMool";
// const char *password = "steak74;Mlles";
// IPAddress staticIP(192, 168, 178, 30); // fixed IP of booster monitor
// IPAddress gateway(192, 168, 178, 1);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress DNS(8, 8, 8, 8);
// const char *deviceName = "Stadel";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const int anZahl = 16;

#include <ConnectWiFi.h>
#include <InitServerRequests.h>
#include <ControlLeds.h>
#include <Vorsignalbilder.h>
#include <Hauptsignalbilder.h>
#include <Zwergsignalbilder.h>
#include <Hilfsignalbilder.h>
#include <Initialisatie.h>
#include <HandleAddress.h>
#include <ChannelTasks.h>

NmraDcc Dcc;
//////////////////////////////////////////////////////////////
// Unterprogramme, die von der DCC Library aufgerufen werden:
// Die folgende Funktion wird von Dcc.process() aufgerufen, wenn ein Weichentelegramm empfangen wurde
void notifyDccAccState(uint16_t Addr, uint16_t BoardAddr, uint8_t OutputAddr, uint8_t State)
{
  for (uint8_t signr = 0; signr < this_dec.nbrofsig; signr++)
  {
    for (uint8_t index = 0; index < 3; index++)
    {
      if (Addr == signale[signr].sigAdressen[index])
      {
        HandleCommand(signr, index, OutputAddr);
      }
    }
  }
}
///////////////////////////////////////////////////////////////
void setup()
{
  Dcc.init(MAN_ID_DIY, 15, FLAGS_OUTPUT_ADDRESS_MODE | FLAGS_DCC_ACCESSORY_DECODER, 0);
  Dcc.pin(0, 2, 1); // Dcc-Signal an Pin2 ( = Int0 );

  Serial.begin(115200);
  while (!Serial)
  {
  } // wait for serial port to connect

  Serial.println("Initialising");
  // Initialize MYFS
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting FS");
    return;
  }
  else
  {
    // SPIFFS.format();
    // Serial.println("Spiffs formatted");
    Serial.println("FS connect big success");
  }

  // connect to WiFi
  MakeWiFiConnection();

  //////////////////////////////////////////////////////////// temp

  // Connect to Wi-Fi with fixed IP
  // WiFi.disconnect();
  // WiFi.config(staticIP, gateway, subnet);
  // WiFi.hostname(hostName);
  // WiFi.begin(ssid, password);
  // Serial.println("Connecting to WiFi");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println();
  //////////////////////////////////////////////////////////// temp

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  getDekoderJson();

  init_Servers();
  // Start servers
  AsyncElegantOTA.begin(&server);
  server.begin();

  init_leds_andQueues();
  init_tasks();
  setDimSteps();
  Initialiseer_decoder();
}
////////////////////////////////////////////////////////////////
void loop()
{
  if (processingDCC)
  {
    Dcc.process(); // Hier werden die empfangenen Telegramme analysiert
    delay(1);
    handle_blink();

    HandleCommand(0, 0, 0);
    delay(5000);
    HandleCommand(0, 0, 1);
    delay(5000);
    HandleCommand(0, 1, 0);
    delay(5000);
    HandleCommand(0, 1, 1);
    delay(5000);
    HandleCommand(0, 2, 0);
    delay(1000);
    HandleCommand(0, 2, 1);
    delay(1000);
  }
}