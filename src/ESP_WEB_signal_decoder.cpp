// Sketch for Swiss Signal decoder on ESP32
// Version 1 (27-02-22)  Arjan Mooldijk

#include <Arduino.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <NmraDcc.h>
#include <Signale.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS TO BE ADAPTED  ///////////////////////////////////////////////////////////////////////////////////////////
// Decoder number. This value is stored in the decoder and displayed on the serial monitor.                         ///
// Only used for your own administration. Not functional use                                                        ///
const byte decoderNbr = 1; ///
                           ///
// DCC adresses:                                                                                                    ///
const unsigned int signalAdr[] = {400, 401, 402, 403, 404, 405}; /// Values just an Example
                                                                 ///
// Signal types per in line 18 listed address  (types can be found in /include/Settings.h)                          ///
const byte signalType[] = {VorAdr1, VorAdr2, VorAdr3Dkl};
/// Fade
const bool signalFade[16] = {1, 1, 1, 1,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0};
/// Dark between signal states (as many as nbr signalTypes)
const bool darkBetween[] = {1, 1, 1};
const long darkDelay = 350;            // Dark phase duration in mSec.                                              ///
///
// Brightness per led, per signal as listed above                                                                   ///
const int maxLight[16] = {200, 200, 200, 200,
                          8, 80, 180, 220,
                          100, 150, 0, 0,
                          0, 0, 0, 0}; // Brightness per led (max value 255 Every row a signal )                    ///
const long interval = 800;             // interval to blink in mSec.                                                ///
const double fadeDuration = 150;               // Fade in/decrease in mSec                                          ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Network credentials
/* const char *ssid = "Wifinetwerk van Jos";
const char *password = "suedRampe2020!";
IPAddress staticIP(192, 168, 0, 40); //fixed IP of booster monitor
IPAddress gateway(192, 168, 0, 1); */
const char* ssid = "CazMool";
const char* password = "steak74;Mlles";
IPAddress staticIP(192, 168, 178, 13); //fixed IP of booster monitor
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(8, 8, 8, 8);
const char *deviceName = "Signaldecoder";
//--------    DO NOT MAKE ANY CHANGES BELOW, UNLESS YOU WANT TO ALTER THE PROGRAM ;-)    ---------------------------///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const int anZahl = sizeof(signalType);
const int ledPin[16] = {23, 22, 21, 19, 18, 17, 16, 15, 32, 33, 25, 26, 27, 14, 12, 13}; // corresponds to GPIO's for LED's
const int freq = 5000;
const int resolution = 8;
const int fadeConst = fadeDuration / 10;

#include <Settings.h>
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
  for (byte index = 0; index < anZahl; index++)
  {
    if (Addr == signalAdr[index])
    { // ist eigene Adresse
      HandleCommand(index, OutputAddr);
    }
  }
}
///////////////////////////////////////////////////////////////

//Replaces placeholder with DHT values
String processor(const String &var)
{
  //Serial.println(var);
  return String();
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
  if (!LITTLEFS.begin())
  {
    Serial.println("An Error has occurred while mounting FS");
    return;
  }
  else
  {
    Serial.println("FS connect big success");
  }

  // Connect to Wi-Fi with fixed IP
  WiFi.disconnect();
  WiFi.config(staticIP, gateway, subnet);
  WiFi.hostname("booster-monitor");
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LITTLEFS, "/index.html", String(), false, processor);
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LITTLEFS, "/style.css", "text/css");
  });

  // Start servers
  AsyncElegantOTA.begin(&server);
  server.begin();

  for (int ledChannel = 0; ledChannel < 16; ledChannel++)
  {
    // configure and attach LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin[ledChannel], ledChannel);
    // Create the queue with 5 slots of 1 bytes
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

}