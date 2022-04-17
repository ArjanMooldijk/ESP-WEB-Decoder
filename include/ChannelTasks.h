#ifndef ChannelTasks_h
#define ChannelTasks_h

#include <Arduino.h>
#include <ControlLeds.h>
#include <Hauptsignalbilder.h>
#include <Vorsignalbilder.h>
#include <Zwergsignalbilder.h>
#include <Hilfsignalbilder.h>

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
    // vTaskDelay(250 / portTICK_PERIOD_MS
    xQueueReceive(testLightsQueue, &testSein, portMAX_DELAY);

    if (testSein.Action)
    {
      Serial.println("parameter.id");
      Serial.println(testSein.Id);
      for (uint8_t i = 0; i < signale[testSein.Id].sigDraden; i++)
      {
        ledcWrite(signale[testSein.Id].sigChannel + i, testSein.Lamp[i]);
      }
    }
    else
    {
      Serial.println("ending test");
      switch (typeArray[testSein.Id])
      {
        case Vor2:
        case Vor4:
        case Vor5:
          setFb0Vorsignal(testSein.Id);
          break;

        case H2gr:
        case H3gro:
        case H3grg:
        case H4goro:
        case H4grog:
        case H5grogo:
        case H5grgog:
        case H7ggogr:
        case H7gogor:
        case H7gogogr:
          setFb0Hauptsignal(testSein.Id);
          break;

        case Zwerg:
          setZwergsignal(testSein.Id, 0);
          break;

        case SIMH:
        case SIMV:
        case HbB:
        case Fsm:
          setHilfsignal(testSein.Id, 0);
          break;

        default:
          break;
      }
    }
  }
}
#endif