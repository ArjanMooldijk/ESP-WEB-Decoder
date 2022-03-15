#ifndef HandleAddress_h
#define HandleAddress_h

void HandleCommand(uint8_t signr; uint8_t index, uint8_t OutputAddr)
{

    switch (signale[signr].stype[index])
    {
    // Vorsignal Addr 1 Fb1 & Fb0
    case VorAdr1:
        if (signale[signr].darktime>0)
        {
            dunkelVorsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Vorsignal(signr);
            break;
        }
        else
        {
            setFb0Vorsignal(signr);
            break;
        }

    // Vorsignal 1 Addr Fb1 & Fb0
    case Vor1Adr:
        if (signale[signr].darktime>0)
        {
            dunkelVorsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Vorsignal(signr);
            break;
        }
        else
        {
            setFb0Vorsignal(signr);
            break;
        }

    // Vorsignal Addr 2 Fb3 & Fb2
    case VorAdr2:
        if (signale[signr].darktime>0)
        {
            dunkelVorsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Vorsignal(signr);
            break;
        }
        else
        {
            setFb2Vorsignal(signr);
            break;
        }

    // Vorsignal Addr 2 Dunkel
    case VorAdr2Dkl:
        dunkelVorsignal(signr);
        break;

    // Vorsignal Addr 3 Dunkel
    case VorAdr3Dkl:
        dunkelVorsignal(signr);
        break;

    // Vorsignal Addr 3 Fb5
    case VorAdr3:
        if (signale[signr].darktime>0)
        {
            dunkelVorsignal(signr);
        }
        setFb5Vorsignal(signr);
        break;

    // Zwergsignal Addr 1 Fahrt & Halt
    case ZwergAdr1:
        if (signale[signr].darktime>0)
        {
            dunkelZwergsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setZwergsignal(signr, 1);
            break;
        }
        else
        {
            setZwergsignal(signr, 0);
            break;
        }

    // Zwergsignal Addr 2 Fahrt mit Vorsicht
    case ZwergAdr2:
        if (signale[signr].darktime>0)
        {
            dunkelZwergsignal(signr);
        }
        setZwergsignal(signr, 2);
        break;

    // SIMhauptsignal An & Aus
    case SIMHaupt:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(signr, 2);
            break;
        }
        else
        {
            setHilfsignal(signr, 0);
            break;
        }

    // SIMvorsignal An & Aus
    case SIMVor:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(signr, 1);
            break;
        }
        else
        {
            setHilfsignal(signr, 0);
            break;
        }

    // HbBsignal An & Aus
    case HbB:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(signr, 1); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
            break;
        }
        else
        {
            setHilfsignal(signr, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
            break;
        }

        // Fahrtstellungsmelder An & Aus
    case FSM:
        if (OutputAddr & 0x1)
        {
            setHilfsignal(signr, 2); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            break;
        }
        else
        {
            setHilfsignal(signr, 0); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            break;
        }

    // Hauptsignal Addr 1 Fb1 & Fb0
    case HptAdr1:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb1Hauptsignal(signr);
            break;
        }
        else
        {
            setFb0Hauptsignal(signr);
            break;
        }

    // Hauptsignal Addr 2 Fb2
    case HptAdr2O:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        setFb2Hauptsignalog(signr);
        break;

    // Hauptsignal Addr 2 Fb3
    case HptAdr2G:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        setFb3Hauptsignalgo(signr);
        break;

    // Hauptsignal Addr 2 Fb3 & Fb2 Oranje, Groen
    case HptAdr2OG:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Hauptsignalog(signr);
            break;
        }
        else
        {
            setFb2Hauptsignalog(signr);
            break;
        }

    // Hauptsignal Addr 2 Fb3 & Fb2  Groen, Oranje
    case HptAdr2GO:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb3Hauptsignalgo(signr);
            break;
        }
        else
        {
            setFb2Hauptsignalgo(signr);
            break;
        }

    // Hauptsignal 5L Addr 3 Fb5
    case HptAdr3G:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        setFb5Hauptsignal5(signr);
        break;

    // Hauptsignal 5L Addr 3 Fb6
    case HptAdr3O:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        setFb6Hauptsignal5(signr);
        break;

    // Hauptsignal Addr 3 Fb6 & Fb5
    case HptAdr3OG:
        if (signale[signr].darktime>0)
        {
            dunkelHauptsignal(signr);
        }
        if (OutputAddr & 0x1)
        {
            setFb6Hauptsignal7(signr);
            break;
        }
        else
        {
            setFb5Hauptsignal7(signr);
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