#ifndef Settings_h
#define Settings_h

#include <Arduino.h>


TaskHandle_t Task_Ch[16];
QueueHandle_t queueCh[16];

const bool uit = false;
const bool aan = true;

byte signalLeds[16];                          // # leds per signal
byte signalChannel[16];                       // Eerste pin per het sein
byte Blink [16] = {0};                      // Flag to blink pin (for SIM)
byte blinkState [16] = {0};                 // Blink on/off
unsigned long previousMillis[16]= {0};      // will store last time LED was updated
byte pinCounter = 0;                            // Variable to address the right pin 
unsigned long busyWait[16] = {0};
int dimStep[16][fadeConst] = {0};

#endif