// Sketch for Swiss Signal decoder on ESP32
// Version 1 (27-02-22)  Arjan Mooldijk

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncElegantOTA.h>
#include <NmraDcc.h>
#include <Settings.h>
#include <GetFromFlash.h>
#include <Signale.h>
//--------    DO NOT MAKE ANY CHANGES BELOW, UNLESS YOU WANT TO ALTER THE PROGRAM ;-)    ---------------------------///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const int anZahl = 16;
const int ledPin[16] = {23, 22, 21, 19, 18, 17, 16, 15, 32, 33, 25, 26, 27, 14, 12, 13}; // corresponds to GPIO's for LED's
const int freq = 5000;
const int resolution = 8;
const bool runMode = true;

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
  for (uint8_t signr = 0; signr < this_dec[0].nbrofsig; signr++)
  {
    for (uint8_t index = 0; index < 3; index++)
    {
      if (Addr == signale[signr].adress[index])
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
    Serial.println("FS connect big success");
  }

  GetDecoderValues();

  // connect to WiFi

  init_Servers();
  // Start servers
  AsyncElegantOTA.begin(&server);
  server.begin();

  for (int ledChannel = 0; ledChannel < 16; ledChannel++)
  {
    // configure and attach LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin[ledChannel], ledChannel);
    // Create the queue with 5 slots of 1 byte
    queueCh[ledChannel] = xQueueCreate(5, sizeof(bool));
  }
  // Create a separate task for each led channel (16 total)
  xTaskCreatePinnedToCore(ch0Loop, "CH0Task", 1000, NULL, 1, &Task_Ch[0], 1);
  xTaskCreatePinnedToCore(ch1Loop, "CH1Task", 1000, NULL, 1, &Task_Ch[1], 1);
  xTaskCreatePinnedToCore(ch2Loop, "CH2Task", 1000, NULL, 1, &Task_Ch[2], 1);
  xTaskCreatePinnedToCore(ch3Loop, "CH3Task", 1000, NULL, 1, &Task_Ch[3], 1);
  xTaskCreatePinnedToCore(ch4Loop, "CH4Task", 1000, NULL, 1, &Task_Ch[4], 1);
  xTaskCreatePinnedToCore(ch5Loop, "CH5Task", 1000, NULL, 1, &Task_Ch[5], 1);
  xTaskCreatePinnedToCore(ch6Loop, "CH6Task", 1000, NULL, 1, &Task_Ch[6], 1);
  xTaskCreatePinnedToCore(ch7Loop, "CH7Task", 1000, NULL, 1, &Task_Ch[7], 1);
  xTaskCreatePinnedToCore(ch8Loop, "CH8Task", 1000, NULL, 1, &Task_Ch[8], 1);
  xTaskCreatePinnedToCore(ch9Loop, "CH9Task", 1000, NULL, 1, &Task_Ch[9], 1);
  xTaskCreatePinnedToCore(ch10Loop, "CH10Task", 1000, NULL, 1, &Task_Ch[10], 1);
  xTaskCreatePinnedToCore(ch11Loop, "CH11Task", 1000, NULL, 1, &Task_Ch[11], 1);
  xTaskCreatePinnedToCore(ch12Loop, "CH12Task", 1000, NULL, 1, &Task_Ch[12], 1);
  xTaskCreatePinnedToCore(ch13Loop, "CH13Task", 1000, NULL, 1, &Task_Ch[13], 1);
  xTaskCreatePinnedToCore(ch14Loop, "CH14Task", 1000, NULL, 1, &Task_Ch[14], 1);
  xTaskCreatePinnedToCore(ch15Loop, "CH15Task", 1000, NULL, 1, &Task_Ch[15], 1);

  setDimSteps();
  Initialiseer_decoder();
}
////////////////////////////////////////////////////////////////
void loop()
{ /*
   if (runMode)
   {
     Dcc.process(); // Hier werden die empfangenen Telegramme analysiert
     delay(1);
     handle_blink();

     dunkelVorsignal(0);
     setFb1Vorsignal(0);
     delay(5000);
     dunkelVorsignal(0);
     setFb0Vorsignal(0);
     delay(5000);
   } */
}