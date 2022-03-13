#ifndef ControlLeds_h
#define ControlLeds_h

#include <Arduino.h>

void LED_on_fade(int channelNr)
{
  // Check if led is already on
  if (ledcRead(channelNr) == 0)
  {
    // increase the LED brightness
    for (int dutyCycle = 1; dutyCycle < fadeConst-1; dutyCycle++)
    {
      // changing the LED brightness with PWM
      ledcWrite(channelNr, dimStep[channelNr][dutyCycle]);
      delay(10);
    }
    ledcWrite(channelNr, dimStep[channelNr][fadeConst-1]);
  }
}
void LED_on_nofade(int channelNr)
{
  // Check if led is already on
  if (ledcRead(channelNr) == 0)
  {
    ledcWrite(channelNr, maxLight[channelNr]);
  }
}

void LED_off_fade(int channelNr)
{
  // Check if led is already off
  if (ledcRead(channelNr) > 0)
  {
    // decrease the LED brightness
    for (int dutyCycle = fadeConst-1; dutyCycle > 0; dutyCycle--)
    {
      // changing the LED brightness with PWM
      ledcWrite(channelNr, dimStep[channelNr][dutyCycle]);
      delay(10);
    }
    ledcWrite(channelNr, 0);
    
  }
}

void LED_off_nofade(int channelNr)
{
  // Check if led is already on
  if (ledcRead(channelNr) > 0)
  {
    ledcWrite(channelNr, 0);
  }
}

#endif