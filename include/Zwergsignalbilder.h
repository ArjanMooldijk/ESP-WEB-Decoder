#ifndef Zwergsignalbilder_h
#define Zwergsignalbilder_h

//////////////////////////////// Zwergsignal Fade ///////////////////////////////////////////////////////////////////////
void dunkelZwergsignal(byte pntr)
{
  // Set wait time for darkDelay
  if (signalFade[signalChannel[pntr]])
  {
    busyWait[signalChannel[pntr] + 0] = millis() + fadeDuration; // Set wait time for darkDelay
    busyWait[signalChannel[pntr] + 1] = millis() + fadeDuration; // Set wait time for darkDelay
    busyWait[signalChannel[pntr] + 2] = millis() + fadeDuration; // Set wait time for darkDelay
  }
  else
  {
    busyWait[signalChannel[pntr] + 0] = millis(); // Set wait time for darkDelay
    busyWait[signalChannel[pntr] + 1] = millis(); // Set wait time for darkDelay
    busyWait[signalChannel[pntr] + 2] = millis(); // Set wait time for darkDelay
  }
  xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
  xQueueSend(queueCh[signalChannel[pntr] + 2], &uit, portMAX_DELAY);
}
//////////////
void setZwergsignal(byte pntr, byte Fb)
{
  // ch1 links unter
  // ch2 rechts unter
  // ch3 oben
  switch (Fb)
  {
  case 0: // zet ch1 en ch2 aan en ch3 uit
    xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 2], &uit, portMAX_DELAY);
    break;
  case 1: // zet ch1 en ch3 aan, ch2 uit
    xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 1], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
    break;
  case 2: // zet ch1 uit en ch2, ch3 aan
    xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 1], &aan, portMAX_DELAY);
    xQueueSend(queueCh[signalChannel[pntr] + 2], &aan, portMAX_DELAY);
    break;
  default:
    break;
  }
}

#endif