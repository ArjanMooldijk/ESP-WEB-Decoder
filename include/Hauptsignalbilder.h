#ifndef Hauptsignalbilder_h
#define Hauptsignalbilder_h

/////////////////////////////////////// Hauptsignal Fade ////////////////////////////////////////////////////////////////
// lamp 1 = grun (hoch)
// lamp 2 = rot
//////////////
void dunkelHauptsignal(byte pntr)
{
  for (byte x = 0; x < signalLeds[pntr]; x++)
  {
    // Set wait time for darkDelay
    if (signalFade[signalChannel[pntr] + x])
    {
      busyWait[signalChannel[pntr] + x] = millis() + fadeDuration;
    }
    else
    {
      busyWait[signalChannel[pntr] + x] = millis();
    }
    xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
  }
}
/////////////////
void setFb0Hauptsignal(byte pntr)
{ // led 2 (x=1) aan, de rest uit
  for (byte x = 0; x < signalLeds[pntr]; x++)
  {
    if (x == 1)
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
void setFb1Hauptsignal(byte pntr)
{ // led 1 (x=0) aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
  }
}
/////////////
// lamp 3 = oranje
// lamp 4 = groen (of mist)
/////////////
void setFb2Hauptsignalog(byte pntr)
{ // led 1&3 (x=0&2) aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if (x == 2)
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
void setFb3Hauptsignalog(byte pntr)
{ // led 1&4 (x=0&3) aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if (x == 3)
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
// lamp 3 = groen
// lamp 4 = oranje (of mist)
/////////////
void setFb2Hauptsignalgo(byte pntr)
{ // led 1&4 (x=0&3) aan
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if (x == 3)
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
void setFb3Hauptsignalgo(byte pntr)
{ // led 1&3 (x=0&2) aan
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if (x == 2)
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}

/////////////
// lamp 5 = groen
/////////////
void setFb5Hauptsignal5(byte pntr)
{ // led 1&3&5 (x=0&2&4) aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}

/////////////
// lamp 5 = oranje
/////////////
void setFb6Hauptsignal5(byte pntr)
{ // led 3&5 (x=2&4) aan, de rest uit
  for (byte x = 0; x < signalLeds[pntr]; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
// lamp 5 = oranje
// lamp 6 = groen
/////////////
void setFb5Hauptsignal7(byte pntr)
{ // led 1&4&6 (x=0&3&5) aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signalLeds[pntr]; x++)
  {
    if ((x == 3) | (x == 5))
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
void setFb6Hauptsignal7(byte pntr)
{ // led 3&5 (x=2&4) aan, de rest uit
  for (byte x = 0; x < signalLeds[pntr]; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signalChannel[pntr] + x], &uit, portMAX_DELAY);
    }
  }
}
#endif