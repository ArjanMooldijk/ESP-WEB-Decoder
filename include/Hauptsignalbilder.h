#ifndef Hauptsignalbilder_h
#define Hauptsignalbilder_h

/////////////////////////////////////// Hauptsignal Fade ////////////////////////////////////////////////////////////////
// lamp 1 = grun (hoch)
// lamp 2 = rot
//////////////
void dunkelHauptsignal(uint8_t signr)
{
  for (uint8_t x = 0; x < signale[signr].sigDraden; x++)
  {
    // Set wait time for darkDelay
    if (signale[signr].sigFade > 0)
    {
      busyWait[signale[signr].sigChannel + x] = millis() + signale[signr].sigFade;
    }
    else
    {
      busyWait[signale[signr].sigChannel + x] = millis();
    }
    xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
  }
}
/////////////////
void setFb0Hauptsignal(uint8_t signr)
{ // led 2 (x=1) aan, de rest uit
  for (byte x = 0; x < signale[signr].sigDraden; x++)
  {
    if (x == 1)
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
void setFb1Hauptsignal(uint8_t signr)
{ // led 1 (x=0) aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
  }
}
// lamp 3 = oranje
// lamp 4 = groen (of mist)
/////////////
void setFb2Hauptsignalog(uint8_t signr)
{ // led 1&3 (x=0&2) aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if (x == 2)
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
void setFb3Hauptsignalog(uint8_t signr)
{ // led 1&4 (x=0&3) aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if (x == 3)
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
// lamp 3 = groen
// lamp 4 = oranje (of mist)
/////////////
void setFb2Hauptsignalgo(uint8_t signr)
{ // led 1&4 (x=0&3) aan
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if (x == 3)
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
void setFb3Hauptsignalgo(uint8_t signr)
{ // led 1&3 (x=0&2) aan
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if (x == 2)
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}

/////////////
// lamp 5 = groen
/////////////
void setFb5Hauptsignal5(uint8_t signr)
{ // led 1&3&5 (x=0&2&4) aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}

/////////////
// lamp 5 = oranje
/////////////
void setFb6Hauptsignal5(uint8_t signr)
{ // led 3&5 (x=2&4) aan, de rest uit
  for (byte x = 0; x < signale[signr].sigDraden; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
// lamp 5 = oranje
// lamp 6 = groen
/////////////
void setFb5Hauptsignal7(uint8_t signr)
{ // led 1&4&6 (x=0&3&5) aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  for (byte x = 1; x < signale[signr].sigDraden; x++)
  {
    if ((x == 3) | (x == 5))
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
/////////////
void setFb6Hauptsignal7(uint8_t signr)
{ // led 3&5 (x=2&4) aan, de rest uit
  for (byte x = 0; x < signale[signr].sigDraden; x++)
  {
    if ((x == 2) | (x == 4))
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &aan, portMAX_DELAY);
    }
    else
    {
      xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
    }
  }
}
#endif