#ifndef Settings_h
#define Settings_h

#include <Arduino.h>

TaskHandle_t Task_Ch[16];
QueueHandle_t queueCh[16];

const bool uit = false;
const bool aan = true;
struct Sein
{
    uint8_t sigId;
    char* sigType;
    uint8_t sigDraden;
    uint8_t sigChannel;
    int sigAdressen[3];
    int sigFade;
    int sigDark;
    uint8_t sigLamp[6];
};

struct Decoder
{
    char *dekName;       // Name of the decoder
    uint8_t nbrofsig;
    Sein sigConnected [8];
};

Decoder this_dec;
Sein signale[8];
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
#define SIGNALE_JSON "/deKoder.json"
#define JSON_CONFIG_FILE "/hostname.json"
StaticJsonDocument<512> jsonHostNameFile;
char hostName[20];
bool shouldSaveConfig = false;

#endif