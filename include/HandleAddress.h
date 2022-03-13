#ifndef HandleAddress_h
#define HandleAddress_h

void HandleCommand(byte index, uint8_t OutputAddr)
{

    switch (signalType[index])
    {

    // Vorsignal Addr 1 Fb1 & Fb0
    case VorAdr1:
        if (darkBetween[index])
        {
            dunkelVorsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Vorsignal(index);
            break;
        }
        else
        {
            setFb0Vorsignal(index);
            break;
        }

    // Vorsignal 1 Addr Fb1 & Fb0
    case Vor1Adr:
        if (darkBetween[index])
        {
            dunkelVorsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Vorsignal(index);
            break;
        }
        else
        {
            setFb0Vorsignal(index);
            break;
        }

    // Vorsignal Addr 2 Fb3 & Fb2
    case VorAdr2:
        if (darkBetween[index])
        {
            dunkelVorsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Vorsignal(index);
            break;
        }
        else
        {
            setFb2Vorsignal(index);
            break;
        }

    // Vorsignal Addr 2 Dunkel
    case VorAdr2Dkl:
        dunkelVorsignal(index);
        break;

    // Vorsignal Addr 3 Dunkel
    case VorAdr3Dkl:
        dunkelVorsignal(index);
        break;

    // Vorsignal Addr 3 Fb5
    case VorAdr3:
        if (darkBetween[index])
        {
            dunkelVorsignal(index);
        }
        setFb5Vorsignal(index);
        break;

    // Zwergsignal Addr 1 Fahrt & Halt
    case ZwergAdr1:
        if (darkBetween[index])
        {
            dunkelZwergsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setZwergsignal(index, 1);
            break;
        }
        else
        {
            setZwergsignal(index, 0);
            break;
        }

    // Zwergsignal Addr 2 Fahrt mit Vorsicht
    case ZwergAdr2:
        if (darkBetween[index])
        {
            dunkelZwergsignal(index);
        }
        setZwergsignal(index, 2);
        break;

    // SIMhauptsignal An & Aus
    case SIMHaupt:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(index, 2);
            break;
        }
        else
        {
            setHilfsignal(index, 0);
            break;
        }

    // SIMvorsignal An & Aus
    case SIMVor:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(index, 1);
            break;
        }
        else
        {
            setHilfsignal(index, 0);
            break;
        }

    // HbBsignal An & Aus
    case HbB:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(index, 1); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
            break;
        }
        else
        {
            setHilfsignal(index, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
            break;
        }

        // Fahrtstellungsmelder An & Aus
    case FSM:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(index, 2); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            break;
        }
        else
        {
            setHilfsignal(index, 0); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            break;
        }

    // Hauptsignal Addr 1 Fb1 & Fb0
    case HptAdr1:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Hauptsignal(index);
            break;
        }
        else
        {
            setFb0Hauptsignal(index);
            break;
        }

    // Hauptsignal Addr 2 Fb2
    case HptAdr2O:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        setFb2Hauptsignalog(index);
        break;

    // Hauptsignal Addr 2 Fb3
    case HptAdr2G:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        setFb3Hauptsignalgo(index);
        break;

    // Hauptsignal Addr 2 Fb3 & Fb2 Oranje, Groen
    case HptAdr2OG:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Hauptsignalog(index);
            break;
        }
        else
        {
            setFb2Hauptsignalog(index);
            break;
        }

    // Hauptsignal Addr 2 Fb3 & Fb2  Groen, Oranje
    case HptAdr2GO:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Hauptsignalgo(index);
            break;
        }
        else
        {
            setFb2Hauptsignalgo(index);
            break;
        }

    // Hauptsignal 5L Addr 3 Fb5
    case HptAdr3G:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        setFb5Hauptsignal5(index);
        break;

    // Hauptsignal 5L Addr 3 Fb6
    case HptAdr3O:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        setFb6Hauptsignal5(index);
        break;

    // Hauptsignal Addr 3 Fb6 & Fb5
    case HptAdr3OG:
        if (darkBetween[index])
        {
            dunkelHauptsignal(index);
        }
        if (OutputAddr & 0x1)
        {
            setFb6Hauptsignal7(index);
            break;
        }
        else
        {
            setFb5Hauptsignal7(index);
            break;
        }
    default:
        break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void handle_blink()
{
    unsigned long currentMillis = millis();
    for (byte blindex = 0; blindex < 16; blindex++)
    {
        if (Blink[blindex] == 1)
        { // Blinkt deze pin/led?
            if (currentMillis - previousMillis[blindex] >= interval)
            { // Is de wachtperiode al voorbij?
                previousMillis[blindex] = currentMillis;
                if (blinkState[blindex] == 1)
                { // Led is aan, zet uit
                    xQueueSend(queueCh[blindex], &uit, portMAX_DELAY);
                    blinkState[blindex] = 0;
                }
                else
                { // Led is uit, zet aan
                    xQueueSend(queueCh[blindex], &aan, portMAX_DELAY);
                    blinkState[blindex] = 1;
                }
            }
        }
    }
}
#endif