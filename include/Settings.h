#ifndef Settings_h
#define Settings_h

#include <Arduino.h>

TaskHandle_t Task_Ch[16];
QueueHandle_t queueCh[16];

const bool uit = false;
const bool aan = true;

class Sein
{
public:
  uint8_t sigId;
  const char *sigType;
  uint8_t sigDraden;
  uint8_t sigChannel;
  uint8_t sigNbrAdr;
  int sigAdressen[3];
  int sigFade;
  int sigDark;
  uint8_t sigLamp[6];
};

class Decoder
{
    public:
    const char *dekName; // Name of the decoder
    uint8_t nbrofsig;
    Sein sigConnected[8];
};

Decoder this_dec;
Sein signale[8];
uint8_t typeArray[8];
bool signalFade[16] = {false};
int fadeConst[8];
int maxLight[16] = {0};
uint8_t Blink[16] = {0};                // Flag to blink pin (for SIM)
uint8_t blinkState[16] = {0};           // Blink on/off
unsigned long previousMillis[16] = {0}; // will store last time LED was updated
unsigned long busyWait[8] = {0};
int dimStep[16][20] = {0};
int darkDelay[16];
int interval;
#define DECODER_JSON "/deKoder.json"
#define JSON_CONFIG_FILE "/hostname.json"
StaticJsonDocument<512> jsonHostNameFile;

char hostName[] = "Ausserberg";
// char hostName[20];
bool shouldSaveConfig = false;

#endif