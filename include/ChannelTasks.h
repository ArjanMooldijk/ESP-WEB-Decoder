#ifndef ChannelTasks_h
#define ChannelTasks_h

#include <Arduino.h>
#include <ControlLeds.h>

void HandleQueMsg(int pin)
{
  bool click;
  xQueueReceive(queueCh[pin], &click, portMAX_DELAY);
  /*   Serial.print("Msg received channel: ");
    Serial.println(pin); */

  if (click)
  {
    if (signalFade[pin])
    {
      LED_on_fade(pin);
    }
    else
    {
      LED_on_nofade(pin);
    }
  }
  else
  {
    if (signalFade[pin])
    {
      LED_off_fade(pin);
    }
    else
    {
      LED_off_nofade(pin);
    }
  }
  // Wait in case of a darkDelay. Time is set in dunkelZwergsignal, dunkelVorsignal & dunkelHauptsignal

  if (darkDelay[pin] > (millis() - busyWait[pin]))
  {
    delay(darkDelay[pin] - (millis() - busyWait[pin]));
  }
}
////////////////////////////////////////////////////////
void ch0Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(0);
  }
}
////////////////////////////////////////////////////////
void ch1Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(1);
  }
}
////////////////////////////////////////////////////////
void ch2Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(2);
  }
}
////////////////////////////////////////////////////////
void ch3Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(3);
  }
}
////////////////////////////////////////////////////////
void ch4Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(4);
  }
}
////////////////////////////////////////////////////////
void ch5Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(5);
  }
}
////////////////////////////////////////////////////////
void ch6Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(6);
  }
}
////////////////////////////////////////////////////////
void ch7Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(7);
  }
}
////////////////////////////////////////////////////////
void ch8Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(8);
  }
}
////////////////////////////////////////////////////////
void ch9Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(9);
  }
}
////////////////////////////////////////////////////////
void ch10Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(10);
  }
}
////////////////////////////////////////////////////////
void ch11Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(11);
  }
}
////////////////////////////////////////////////////////
void ch12Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(12);
  }
}
////////////////////////////////////////////////////////
void ch13Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(13);
  }
}
////////////////////////////////////////////////////////
void ch14Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(14);
  }
}
////////////////////////////////////////////////////////
void ch15Loop(void *parameter)
{
  for (;;)
  {
    HandleQueMsg(15);
  }
}
////////////////////////////////////////////////////////
void testLights(void *parameter)
{
  for (;;)
  {

    testData testSein;
    xQueueReceive(testLightsQueue, &testSein, portMAX_DELAY);

    Serial.println("message to start test received");
    if (testSein.Action)
    {
      Serial.println("parameter.id");
      Serial.println(testSein.Id);
    }
    else
    {
      Serial.println("ending test");
    }
    /*
   Bepaal wat voor sein het is
   save huidige lamp waardes
   schrijf tijdelijke lampwaardes voor iedere lamp

         fadeConst[sigChannel + chNr] = sigFade / 10;
         darkDelay[sigChannel + chNr] = sigDark;
         maxLight[sigChannel + chNr] = sigLamp[chNr];
         if (sigFade > 0)
         {
           signalFade[sigChannel + chNr] = true;
         }
     afhankelijk van het type sein, roep één voor één de seinbeelden Fb0, Fb1, Fb2, Fb3, Fb5, Fb6
     delay van 1500 msec (actieve loop)
     check message queue voor stop
     als stop,
       zet waardes terug
       zet sein op Fb0
       (geef semafoor vrij?)

    */
  }
}
#endif