#ifndef ChannelTasks_h
#define ChannelTasks_h

#include <Arduino.h>

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
  //Wait in case of a darkDelay. Time is set in dunkelZwergsignal, dunkelVorsignal & dunkelHauptsignal

  if (darkDelay > (millis() - busyWait[pin]))
  {
    delay(darkDelay -((millis() - busyWait[pin])));
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

#endif