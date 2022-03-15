#ifndef Hilfsignalbilder_h
#define Hilfsignalbilder_h

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Hilfsignale:
//    SIM : 1 pin
//    Haltbeibedarf : 1 pin
//    Fahrtstellungsmelder : 1 pin
///////////////////////////////////////
void setHilfsignal(uint8_t signr, uint8_t Fb)
{
   switch (Fb)
   {
   case 0: // zet channel uit
      Blink[signr] = 0;
      xQueueSend(queueCh[signale[signr].firstCH], &uit, portMAX_DELAY);
      break;
   case 1: // zet channel blink aan
      Blink[signr] = 1;
      xQueueSend(queueCh[signale[signr].firstCH], &aan, portMAX_DELAY);
      break;
   case 2: // zet channel aan
      xQueueSend(queueCh[signale[signr].firstCH], &aan, portMAX_DELAY);
      break;
   default:
      break;
   }
}

#endif