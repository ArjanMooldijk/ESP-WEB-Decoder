#ifndef Hilfsignalbilder_h
#define Hilfsignalbilder_h

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Hilfsignale:
//    SIM : 1 pin
//    Haltbeibedarf : 1 pin
//    Fahrtstellungsmelder : 1 pin
///////////////////////////////////////
void setHilfsignal(byte pntr, byte Fb)
{
   switch (Fb)
   {
   case 0: // zet ch1 uit
      Blink[signalChannel[pntr]] = 0;
      xQueueSend(queueCh[signalChannel[pntr] + 0], &uit, portMAX_DELAY);
      break;
   case 1: // zet ch1 blink aan
      Blink[signalChannel[pntr]] = 1;
      xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
      break;
   case 2: // zet ch1 aan
      xQueueSend(queueCh[signalChannel[pntr] + 0], &aan, portMAX_DELAY);
      break;
   default:
      break;
   }
}

#endif