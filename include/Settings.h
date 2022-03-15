#ifndef Settings_h
#define Settings_h

#include <Arduino.h>

TaskHandle_t Task_Ch[16];
QueueHandle_t queueCh[16];

const bool uit = false;
const bool aan = true;
struct Sein
{
    char* name;
    uint8_t stype[3];
    int adress[3];
    int fadetime;
    int darktime;
    uint8_t firstCH;
    uint8_t pins;
    uint8_t ChBright[6];
};

struct Decoder
{
    char* name;                         //Name of the decoder
    uint8_t nbrofsig;                     //Number of signals served
};

Decoder this_dec[1];
Sein signale [5];
byte signalLeds[16];                    // # leds per signal
byte signalChannel[16];                 // Eerste pin per het sein
byte Blink[16] = {0};                   // Flag to blink pin (for SIM)
byte blinkState[16] = {0};              // Blink on/off
unsigned long previousMillis[16] = {0}; // will store last time LED was updated
byte pinCounter = 0;                    // Variable to address the right pin
unsigned long busyWait[16] = {0};
int dimStep[16][20] = {0};

#endif