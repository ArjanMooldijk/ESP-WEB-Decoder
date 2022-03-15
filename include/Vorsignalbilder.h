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
void dunkelVorsignal(uint8_t signr)
{
  for (uint8_t x = 0; x < signale[signr].pins; x++)
  { // Set wait time for darkDelay
    if (signale[signr].fadetime >0)
    {
      busyWait[signale[signr].firstCH + x] = millis() + signale[signr].fadetime;
    }
    else
    {
      busyWait[signale[signr].firstCH + x] = millis();
    }
    xQueueSend(queueCh[signale[signr].firstCH + x], &uit, portMAX_DELAY);
  }
}
/////////////
void setFb0Vorsignal(uint8_t signr)
{
  // led 1&2 aan, de rest uit
  xQueueSend(queueCh[signale[signr].firstCH + 0], &aan, portMAX_DELAY);
  if (signale[signr].stype[0] == VorAdr1)
  { // led 2 ook aan en 3&4 uit
    xQueueSend(queueCh[signale[signr].firstCH + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 2], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 3], &uit, portMAX_DELAY);
  }
  else
  { // anders uit
    xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
  }
}

/////////////
void setFb1Vorsignal(uint8_t signr)
{
  if (signale[signr].stype[0] == VorAdr1)
  {
    // led 3&4 aan, de rest uit
    xQueueSend(queueCh[signale[signr].firstCH + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 3], &aan, portMAX_DELAY);
  }
  else
  {
    // led 2 aan, de rest uit
    xQueueSend(queueCh[signale[signr].firstCH + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 1], &aan, portMAX_DELAY);
  }
}
/////////////
void setFb2Vorsignal(uint8_t signr)
{ // led 1&3 aan, de rest uit
  xQueueSend(queueCh[signale[signr].firstCH + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 3], &uit, portMAX_DELAY);
}
/////////////
void setFb3Vorsignal(uint8_t signr)
{ // led 1&3&4 aan, de rest uit
  xQueueSend(queueCh[signale[signr].firstCH + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 3], &aan, portMAX_DELAY);
}
/////////////
void setFb5Vorsignal(uint8_t signr)
{ // led 3&4&5 aan, de rest uit
  xQueueSend(queueCh[signale[signr].firstCH + 0], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 4], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 3], &aan, portMAX_DELAY);
}

#endif