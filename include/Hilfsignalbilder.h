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
      xQueueSend(queueCh[signale[signr].sigChannel], &uit, portMAX_DELAY);
      break;
   case 1: // zet channel blink aan
      Blink[signr] = 1;
      xQueueSend(queueCh[signale[signr].sigChannel], &aan, portMAX_DELAY);
      break;
   case 2: // zet channel aan
      xQueueSend(queueCh[signale[signr].sigChannel], &aan, portMAX_DELAY);
      break;
   default:
      break;
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// verlichting
//    aantal draden is aantal pins
///////////////////////////////////////
void setVerlichting(uint8_t signr, uint8_t Fb)
{
   switch (Fb)
   {
   case 0: // zet verlichting uit
         for (uint8_t index = 0; index < signale[signr].sigDraden; index++){
            xQueueSend(queueCh[signale[signr].sigChannel + index], &uit, portMAX_DELAY);
         }
      break;
   case 1: // zet verlichting aan
         for (uint8_t index = 0; index < signale[signr].sigDraden; index++){
            xQueueSend(queueCh[signale[signr].sigChannel + index], &aan, portMAX_DELAY);
         }
         break;
   default:
      break;
   }
}

#endif