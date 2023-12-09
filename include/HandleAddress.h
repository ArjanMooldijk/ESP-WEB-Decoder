#ifndef HandleAddress_h
#define HandleAddress_h
#include <string>
using namespace std;

#include <Vorsignalbilder.h>
#include <Hauptsignalbilder.h>
#include <Hilfsignalbilder.h>
#include <Zwergsignalbilder.h>
#include <ChannelTasks.h>

void HandleCommand(uint8_t signr, uint8_t index, uint8_t OutputAddr)
{
    switch (index)
    {
    case 0:
        switch (typeArray[signr])
        {
        case Vor2:
        case Vor4:
        case Vor5:
            if (signale[signr].sigDark > 0)
            {
                dunkelVorsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb1Vorsignal(signr);
            }
            else
            {
                setFb0Vorsignal(signr);
            }
            break;
        case H2gr:
        case H3gro:
        case H3grg:
        case H4goro:
        case H4grog:
        case H5grogo:
        case H5grgog:
        case H7ggogr:
        case H7gogor:
        case H7gogogr:
            // Fb0 & Fb1
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb1Hauptsignal(signr);
            }
            else
            {
                setFb0Hauptsignal(signr);
            }
            break;

        case Zwerg:
            if (signale[signr].sigDark > 0)
            {
                dunkelZwergsignal(index);
            }
            if (OutputAddr & 0x1)
            {
                setZwergsignal(index, 1);
            }
            else
            {
                setZwergsignal(index, 0);
            }
            break;

        case SIMH:
            if (OutputAddr & 0x1)
            {
                setHilfsignal(signr, 2); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            else
            {
                setHilfsignal(signr, 0); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            break;
        case SIMV:
            if (OutputAddr & 0x1)
            {
                setHilfsignal(signr, 1);
            }
            else
            {
                setHilfsignal(signr, 0);
            }

            break;
        case Lmp:
            if (OutputAddr & 0x1)
            {
                setVerlichting(signr, 1);
            }
            else
            {
                setVerlichting(signr, 0);
            }

            break;
        case HbB:
            if (OutputAddr & 0x1)
            {
                setHilfsignal(signr, 2); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            else
            {
                setHilfsignal(signr, 0); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            if (OutputAddr & 0x1)
            {
                setHilfsignal(signr, 2); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            else
            {
                setHilfsignal(signr, 0); // Hetzelfde als SIM Hauptsignal; gebruik dezelfde routines voor aansturing
            }
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (typeArray[signr])
        {
        case Vor2:
            dunkelVorsignal(signr);
            break;

        case Vor4:
        case Vor5:
            if (signale[signr].sigDark > 0)
            {
                dunkelVorsignal(signr);
            };
            if (OutputAddr & 0x1)
            {
                setFb3Vorsignal(signr);
            }
            else
            {
                setFb2Vorsignal(signr);
            };
            break;

        case H3gro: // Fb2
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            setFb2Hauptsignalog(signr);
            break;

        case H3grg: // Fb3
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            setFb3Hauptsignalgo(signr);
            break;

        case H4goro: // Fb2 & Fb6
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb6Hauptsignaloo(signr);
            }
            else
            {
                setFb2Hauptsignalog(signr);
            }
        case H4grog:
        case H5grogo: // Fb2 & Fb3
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb3Hauptsignalog(signr);
            }
            else
            {
                setFb2Hauptsignalog(signr);
            }
            break;
        case H5grgog:
        case H7ggogr: // Fb2 & Fb3
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb3Hauptsignalgo(signr);
            }
            else
            {
                setFb2Hauptsignalgo(signr);
            }
            break;
        case H7gogor:
        case H7gogogr: // Fb2 & Fb3
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb3Hauptsignalgo(signr);
            }
            else
            {
                setFb2Hauptsignalgo(signr);
            }
            break;

        case Zwerg: // Zwergsignal Addr 2 Fahrt mit Vorsicht
            if (signale[signr].sigDark > 0)
            {
                dunkelZwergsignal(signr);
            }
            setZwergsignal(signr, 2);
            break;

        default:
            break;
        }
        break;
    case 2:
        switch (typeArray[signr])
        {
        case Vor4:
            dunkelVorsignal(signr);
            break;
        case Vor5:
            if (OutputAddr & 0x1)
            {
                setFb5Vorsignal(signr);
            }
            else
            {
                dunkelVorsignal(signr);
            }
            break;
        case H5grogo: // Fb6
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            setFb6Hauptsignal5(signr);
            break;
        case H5grgog:
        case H7ggogr: // Fb5
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            setFb5Hauptsignal5(signr);
            break;
        case H7gogor: // Fb6
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            setFb6Hauptsignal5(signr);
            break;
        case H7gogogr: // Fb5 & Fb6
            if (signale[signr].sigDark > 0)
            {
                dunkelHauptsignal(signr);
            }
            if (OutputAddr & 0x1)
            {
                setFb5Hauptsignal7(signr);
            }
            else
            {
                setFb6Hauptsignal7(signr);
            }
            break;
        default:
            break;
        }
        break;
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

void sockEventHandler(byte num, WStype_t typeWs, uint8_t *payload, size_t length)
{
    switch (typeWs)
    {
    case WStype_DISCONNECTED:
        Serial.println("disconnected");
        break;
    case WStype_CONNECTED:
        Serial.println("Client connected");
        break;
    case WStype_TEXT:
        testData testSein;
        uint8_t maxLight;
        StaticJsonDocument<256> subject;
        DeserializationError error = deserializeJson(subject, payload);

        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
        }
        else
        {
            testSein.Id = subject["sigId"];
            bool idFound = false;
            for (uint8_t i = 0; i < this_dec.nbrofsig; i++)
            {
                if (testSein.Id == this_dec.sigConnected[i].sigId)
                {
                    idFound = true;
                    maxLight = this_dec.sigConnected[i].sigDraden;
                }
            };
            if (idFound)
            {
                testSein.fade = subject["sigFade"];
                testSein.dark = subject["sigDark"];
                uint8_t sCc = 0;
                JsonArray lamp_item = subject["sigLamp"];
                for (sCc = 0; sCc < maxLight; sCc++)
                {
                    testSein.Lamp[sCc] = lamp_item[sCc];
                }
                testSein.Action = aan;
                xQueueSend(testLightsQueue, &testSein, portMAX_DELAY);
            };
        };
        break;
    };
};

postResponse endTestLights(String JsonData)
{
    // send message to stop test
    // wait 100 msec

    Serial.println("processing end test request");
    testData testSein;
    postResponse resultaat;
    Serial.println(JsonData);
    StaticJsonDocument<32> subject;
    DeserializationError error = deserializeJson(subject, JsonData);

    if (error)
    {
        resultaat.message = "deserialize failed";
        resultaat.succes = false;
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
    }
    else
    {
        testSein.Id = subject["sigId"];
        testSein.Action = uit;
        xQueueSend(testLightsQueue, &testSein, portMAX_DELAY);
        resultaat.message = "";
        resultaat.succes = true;
    }
    return resultaat;
}
#endif