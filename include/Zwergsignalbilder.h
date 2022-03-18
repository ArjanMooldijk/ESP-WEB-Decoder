#ifndef Zwergsignalbilder_h
#define Zwergsignalbilder_h

//////////////////////////////// Zwergsignal Fade ///////////////////////////////////////////////////////////////////////
void dunkelZwergsignal(uint8_t signr)
{
  // Set wait time for darkDelay
  if (signale[signr].fadetime >0)
  {
    busyWait[signale[signr].firstCH + 0] = millis() + signale[signr].fadetime; // Set wait time for darkDelay
    busyWait[signale[signr].firstCH + 1] = millis() + signale[signr].fadetime; // Set wait time for darkDelay
    busyWait[signale[signr].firstCH + 2] = millis() + signale[signr].fadetime; // Set wait time for darkDelay
  }
  else
  {
    busyWait[signale[signr].firstCH + 0] = millis(); // Set wait time for darkDelay
    busyWait[signale[signr].firstCH + 1] = millis(); // Set wait time for darkDelay
    busyWait[signale[signr].firstCH + 2] = millis(); // Set wait time for darkDelay
  }
  xQueueSend(queueCh[signale[signr].firstCH + 0], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signale[signr].firstCH + 2], &uit, portMAX_DELAY);
}
//////////////
void setZwergsignal(uint8_t signr, uint8_t Fb)
{
  // ch1 links unter
  // ch2 rechts unter
  // ch3 oben
  switch (Fb)
  {
  case 0: // zet ch1 en ch2 aan en ch3 uit
    xQueueSend(queueCh[signale[signr].firstCH + 0], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 2], &uit, portMAX_DELAY);
    break;
  case 1: // zet ch1 en ch3 aan, ch2 uit
    xQueueSend(queueCh[signale[signr].firstCH + 0], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 1], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
    break;
  case 2: // zet ch1 uit en ch2, ch3 aan
    xQueueSend(queueCh[signale[signr].firstCH + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signale[signr].firstCH + 2], &aan, portMAX_DELAY);
    break;
  default:
    break;
  }
}

#endif