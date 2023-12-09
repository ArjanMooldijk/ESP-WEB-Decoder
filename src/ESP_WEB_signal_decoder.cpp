// Sketch for Swiss Signal decoder on ESP32
// Version 2 (with web interface, 16-03-22)  Arjan Mooldijk

#include <Arduino.h>
#include <SPIFFS.h>
#include <string>
using namespace std;
#include <WiFi.h>
#include <WiFiManager.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include "ArduinoJson.h"
#include <NmraDcc.h>
#include <Settings.h>
#include <GetFromFlash.h>
#include <Signale.h>
//--------    DO NOT MAKE ANY CHANGES BELOW, UNLESS YOU WANT TO ALTER THE PROGRAM ;-)    ---------------------------///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// const char *ssid = "CazMool";
// const char *password = "stMlleseak74;";
// IPAddress staticIP(192, 168, 178, 30); // fixed IP of booster monitor
// IPAddress gateway(192, 168, 178, 1);
// IPAddress subnet(255, 255, 255, 0);
// IPAddress DNS(8, 8, 8, 8);
// const char *deviceName = "Stadel";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create AsyncWebSocketServer object on port 81
WebSocketsServer webSock = WebSocketsServer(81);

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
// void notifyDccAccState( uint16_t Addr, uint16_t BoardAddr, uint8_t OutputAddr, uint8_t State ){
void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t OutputAddr, uint8_t OutputPower)
{
  Serial.print("DCC command received. Address: ");
  Serial.println(Addr);
  for (uint8_t signr = 0; signr < this_dec.nbrofsig; signr++)
  {
    for (uint8_t index = 0; index < signale[signr].sigNbrAdr; index++)
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
  Dcc.pin(digitalPinToInterrupt(2), 2, 1); // Dcc-Signal an Pin2 ( = Int0 );
  Dcc.init(MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0);
  // Dcc.init( MAN_ID_DIY, 15, FLAGS_OUTPUT_ADDRESS_MODE | FLAGS_DCC_ACCESSORY_DECODER, 0 );

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
  webSock.begin();
  webSock.onEvent(sockEventHandler);

  init_leds_andQueues();
  init_tasks();
  setDimSteps();
  Initialiseer_decoder();
}
////////////////////////////////////////////////////////////////
void loop()
{
  Dcc.process(); // Hier werden die empfangenen Telegramme analysiert
  webSock.loop();
  // delay(1);
  handle_blink();
  
  /*
// hoofd rood, Voor donker
  HandleCommand(1, 0, 0);
  HandleCommand(0, 2, 0);
  delay(3500);

// hoofd Fb1, Voor Halt
  HandleCommand(1, 0, 1);
  HandleCommand(0, 0, 0);
  delay(1100);

// hoofd Fb1, Voor FB1
  HandleCommand(0, 1, 1);
  HandleCommand(0, 0, 1);
  delay(4000); */
}