#ifndef Vorsignalbilder_h
#define Vorsignalbilder_h


////////////////////////////////////// Vorsignal /////////////////////////////////////////////////////////////////
// Signalbilder : Warnung (Gelb1, Gelb2), Fb1 (Grün1, Grün2), Fb2 (Gelb1, Grün1), Fb3 (Gelb1, Grün1, Grün2), Fb5 (Grün1, Grün2, Gelb3)
// lamp1 = gelb (links)
// lamp2 = gelb (rechts oben)
// lamp3 = grun (rechts)
// lamp4 = grun (links)
// lamp5 = gelb (rechts unter)
//
//  oder (Vor1AdrF):
// lamp1 = gelb (2 x oben)
// lamp2 = grun (2 x unter)
//////////////
void dunkelVorsignal(byte pntr)
{
  for (byte x = 0; x < signalLeds[pntr]; x++)
  { // Set wait time for darkDelay
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
/////////////
void setFb0Vorsignal(byte pntr)
{
  // led 1&2 aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  if (signalType[pntr] == VorAdr1)
  { // led 2 ook aan en 3&4 uit
    xQueueSend(queueCh[signalChannel[pntr] + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 2], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 3], &uit, portMAX_DELAY);
  }
  else
  { // anders uit
    xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
  }
}

/////////////
void setFb1Vorsignal(byte pntr)
{
  if (signalType[pntr] == VorAdr1)
  {
    // led 3&4 aan, de rest uit
    xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 3], &aan, portMAX_DELAY);
  }
  else
  {
    // led 2 aan, de rest uit
    xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 1], &aan, portMAX_DELAY);
  }
}
/////////////
void setFb2Vorsignal(byte pntr)
{ // led 1&3 aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 3], &uit, portMAX_DELAY);
}
/////////////
void setFb3Vorsignal(byte pntr)
{ // led 1&3&4 aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 3], &aan, portMAX_DELAY);
}
/////////////
void setFb5Vorsignal(byte pntr)
{ // led 3&4&5 aan, de rest uit
  xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 4], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 3], &aan, portMAX_DELAY);
}

#endif