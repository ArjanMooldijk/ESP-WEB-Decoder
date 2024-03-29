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
  for (uint8_t x = 0; x < signale[signr].sigDraden; x++)
  { 
    xQueueSend(queueCh[signale[signr].sigChannel + x], &uit, portMAX_DELAY);
  };
      // Wait in case of a darkDelay. Time is set in dunkelZwergsignal, dunkelVorsignal & dunkelHauptsignal
  if (signale[signr].sigDark > 0 || signale[signr].sigFade > 0)
  {
    delay(signale[signr].sigDark + signale[signr].sigFade);
  }
}
/////////////
void setFb0Vorsignal(uint8_t signr)
{
  // led 1&2 aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  if (typeArray[signr] == Vor4 || typeArray[signr] == Vor5)
  { // led 2 ook aan en 3&4 uit
    xQueueSend(queueCh[signale[signr].sigChannel + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 2], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 3], &uit, portMAX_DELAY);
    if (typeArray[signr] == Vor5)
    { // led 5  uit
      xQueueSend(queueCh[signale[signr].sigChannel + 4], &uit, portMAX_DELAY);
    }
  }
  else
  { // anders uit
    xQueueSend(queueCh[signale[signr].sigChannel + 1], &uit, portMAX_DELAY);
  }

}

/////////////
void setFb1Vorsignal(uint8_t signr)
{
  if (typeArray[signr] == Vor4 || typeArray[signr] == Vor5)
  {
    // led 3&4 aan, de rest uit
    xQueueSend(queueCh[signale[signr].sigChannel + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 1], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 2], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 3], &aan, portMAX_DELAY);
    if (typeArray[signr] == Vor5)
    { // led 5  uit
      xQueueSend(queueCh[signale[signr].sigChannel + 4], &uit, portMAX_DELAY);
    }
  }
  else
  {
    // led 2 aan, de rest uit
    xQueueSend(queueCh[signale[signr].sigChannel + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].sigChannel + 1], &aan, portMAX_DELAY);
  }
}
/////////////
void setFb2Vorsignal(uint8_t signr)
{ // led 1&3 aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 3], &uit, portMAX_DELAY);
  if (typeArray[signr] == Vor5)
  { // led 5  uit
    xQueueSend(queueCh[signale[signr].sigChannel + 4], &uit, portMAX_DELAY);
  }
}
/////////////
void setFb3Vorsignal(uint8_t signr)
{ // led 1&3&4 aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 3], &aan, portMAX_DELAY);
  if (typeArray[signr] == Vor5)
  { // led 5  uit
    xQueueSend(queueCh[signale[signr].sigChannel + 4], &uit, portMAX_DELAY);
  }
}
/////////////
void setFb5Vorsignal(uint8_t signr)
{ // led 3&4&5 aan, de rest uit
  xQueueSend(queueCh[signale[signr].sigChannel + 0], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 4], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 2], &aan, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].sigChannel + 3], &aan, portMAX_DELAY);
}

#endif