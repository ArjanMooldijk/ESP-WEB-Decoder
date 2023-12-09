#ifndef Initialisatie_h
#define Initialisatie_h

#include <Signale.h>
#include <ChannelTasks.h>
#include <Vorsignalbilder.h>
#include <Hauptsignalbilder.h>
#include <Hilfsignalbilder.h>
#include <Zwergsignalbilder.h>

//////////////////////////
void setDimSteps()
{
  double dimFactor;
  uint8_t maxStep;
  Serial.print("aantal signalen: ");
  Serial.println(this_dec.nbrofsig);

  for (uint8_t scount = 0; scount < this_dec.nbrofsig; scount++) // voor ieder signaal
  {
    for (int x = 0; x < signale[scount].sigDraden; x++) // voor ieder kanaal
    {
      fadeConst[signale[scount].sigChannel + x] = signale[scount].sigFade / 10;
      darkDelay[signale[scount].sigChannel + x] = signale[scount].sigDark;
      maxLight[signale[scount].sigChannel + x] = signale[scount].sigLamp[x];
      if (signale[scount].sigFade > 0)
      {
        signalFade[signale[scount].sigChannel + x] = true;
      }
      else
      {
        signalFade[signale[scount].sigChannel + x] = false;
      }

      float dimExp = 1.0 / (fadeConst[signale[scount].sigChannel] - 1);
      dimStep[signale[scount].sigChannel + x][0] = 0;            // [0] is altijd 0
      dimFactor = pow(1.0 * signale[scount].sigLamp[x], dimExp); // grondgetal voor exponent
      maxStep = signale[scount].sigFade / 10;
      for (int y = maxStep - 1; y > 0; y--) //
      {
        double b = 1.0 * y;
        dimStep[signale[scount].sigChannel +x][y] = pow(dimFactor, b);
      }
    }
  }
}

void init_leds_andQueues()
{
  for (int ledChannel = 0; ledChannel < 16; ledChannel++)
  {
    // configure and attach LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(ledPin[ledChannel], ledChannel);
    // Create the queue with 5 slots of 1 byte
    queueCh[ledChannel] = xQueueCreate(5, sizeof(bool));
  }

  // Create message queue for light tests with 2 slots of 11 bytes
  // (start/stop, id, lamp[6])
  testLightsQueue = xQueueCreate(2, 11);
}

void init_tasks()
{
  // Create a separate task for each led channel (16 total)
  xTaskCreatePinnedToCore(ch0Loop, "CH0Task", 1000, NULL, 1, &Task_Ch[0], 1);
  xTaskCreatePinnedToCore(ch1Loop, "CH1Task", 1000, NULL, 1, &Task_Ch[1], 1);
  xTaskCreatePinnedToCore(ch2Loop, "CH2Task", 1000, NULL, 1, &Task_Ch[2], 1);
  xTaskCreatePinnedToCore(ch3Loop, "CH3Task", 1000, NULL, 1, &Task_Ch[3], 1);
  xTaskCreatePinnedToCore(ch4Loop, "CH4Task", 1000, NULL, 1, &Task_Ch[4], 1);
  xTaskCreatePinnedToCore(ch5Loop, "CH5Task", 1000, NULL, 1, &Task_Ch[5], 1);
  xTaskCreatePinnedToCore(ch6Loop, "CH6Task", 1000, NULL, 1, &Task_Ch[6], 1);
  xTaskCreatePinnedToCore(ch7Loop, "CH7Task", 1000, NULL, 1, &Task_Ch[7], 1);
  xTaskCreatePinnedToCore(ch8Loop, "CH8Task", 1000, NULL, 1, &Task_Ch[8], 1);
  xTaskCreatePinnedToCore(ch9Loop, "CH9Task", 1000, NULL, 1, &Task_Ch[9], 1);
  xTaskCreatePinnedToCore(ch10Loop, "CH10Task", 1000, NULL, 1, &Task_Ch[10], 1);
  xTaskCreatePinnedToCore(ch11Loop, "CH11Task", 1000, NULL, 1, &Task_Ch[11], 1);
  xTaskCreatePinnedToCore(ch12Loop, "CH12Task", 1000, NULL, 1, &Task_Ch[12], 1);
  xTaskCreatePinnedToCore(ch13Loop, "CH13Task", 1000, NULL, 1, &Task_Ch[13], 1);
  xTaskCreatePinnedToCore(ch14Loop, "CH14Task", 1000, NULL, 1, &Task_Ch[14], 1);
  xTaskCreatePinnedToCore(ch15Loop, "CH15Task", 1000, NULL, 1, &Task_Ch[15], 1);

  xTaskCreate(testLights, "testLights", 1000, NULL, 1, &testTask);
}

void setSignalType()
{ // in geval van kernal panic, is de vergelijking van een char* met een fixed string mogelijk de oorzaak.
  for (uint8_t signr = 0; signr < this_dec.nbrofsig; signr++)
  {
    if (signale[signr].sigType[3] == '2') // Vor2
    {
      typeArray[signr] = Vor2;
    };
    if (signale[signr].sigType[3] == '4') // Vor4
    {
      typeArray[signr] = Vor4;
    };
    if (signale[signr].sigType[3] == '5') // Vor5
    {
      typeArray[signr] = Vor5;
    };
    if (signale[signr].sigType[1] == '2') // H2gr
    {
      typeArray[signr] = H2gr;
    };
    if (signale[signr].sigType[1] == '3' && signale[signr].sigType[4] == 'o') // H3gro
    {
      typeArray[signr] = H3gro;
    };
    if (signale[signr].sigType[1] == '3' && signale[signr].sigType[4] == 'g') // H3grg
    {
      typeArray[signr] = H3grg;
    };
    if (signale[signr].sigType[1] == '4' && signale[signr].sigType[3] == 'r') // H4grog
    {
      typeArray[signr] = H4grog;
    };
    if (signale[signr].sigType[1] == '4' && signale[signr].sigType[3] == 'o') // H4goro
    {
      typeArray[signr] = H4goro;
    };
    if (signale[signr].sigType[1] == '5' && signale[signr].sigType[4] == 'g') // H5grgog
    {
      typeArray[signr] = H5grgog;
    };
    if (signale[signr].sigType[1] == '5' && signale[signr].sigType[4] == 'o') // H5grogo
    {
      typeArray[signr] = H5grogo;
    };
    if (signale[signr].sigType[1] == '7' && signale[signr].sigType[3] == 'g') // H7ggogr
    {
      typeArray[signr] = H7ggogr;
    };
    if (signale[signr].sigType[1] == '7' && signale[signr].sigType[6] == 'r') // H7gogor
    {
      typeArray[signr] = H7gogor;
    };
    if (signale[signr].sigType[1] == '7' && signale[signr].sigType[6] == 'g') // H7gogogr
    {
      typeArray[signr] = H7gogogr;
    };
    if (signale[signr].sigType[0] == 'Z') // Zwerg
    {
      typeArray[signr] = Zwerg;
    };
    if (signale[signr].sigType[3] == 'V') // SIMV
    {
      typeArray[signr] = SIMV;
    };
    if (signale[signr].sigType[3] == 'H') // SIMH
    {
      typeArray[signr] = SIMH;
    };
    if (signale[signr].sigType[1] == 'b') // HbB
    {
      typeArray[signr] = HbB;
    };
    if (signale[signr].sigType[0] == 'F') // Fsm
    {
      typeArray[signr] = Fsm;
    };
    if (signale[signr].sigType[0] == 'L') // Lamp
    {
      typeArray[signr] = Lmp;
    };
  };
}

//////////////////////////
void Initialiseer_decoder()
{
  if (this_dec.nbrofsig == 0)
  {
    Serial.println("geen seinen aangesloten");
  }
  else
  {
    for (uint8_t signr = 0; signr < this_dec.nbrofsig; signr++)
    {
      switch (typeArray[signr])
      {
      case Vor2:
      case Vor4:
      case Vor5:
        Serial.print("Voorsignaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.print(" Vorsignal ");
        Serial.print(signale[signr].sigDraden);
        Serial.println(" Leds");
        setFb0Vorsignal(signr);
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
        Serial.print("Hoofdsignaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.print(" Hauptsignal ");
        Serial.print(signale[signr].sigDraden);
        Serial.println(" Leds");
        setFb0Hauptsignal(signr);
        break;

      case Zwerg:
        Serial.print("Dwergsignaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.print(" Zwergsignal ");
        Serial.print(signale[signr].sigDraden);
        Serial.println(" Leds");
        setZwergsignal(signr, 0);
        break;

      case SIMH:
        Serial.print("SIM signaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.println(" SIM Hauptsignal");
        setHilfsignal(signr, 0);
        break;

      case SIMV:
        Serial.print("Sim Signaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.println(" SIM Vorsignal");
        setHilfsignal(signr, 0);
        break;

      case HbB:
        Serial.print("Hulpsignaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.println(" Halt bei Bedarf Signal");
        setHilfsignal(signr, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
        break;

      case Fsm:
        Serial.print("Hulpsignaal Type: ");
        Serial.print(signale[signr].sigType);
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.println(" Fahrtstellungsmelder");
        setHilfsignal(signr, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
        break;

      case Lmp:
        Serial.print("Verlichting");
        Serial.print(" Channel: ");
        Serial.print(signale[signr].sigChannel);
        Serial.print(" Adres: ");
        Serial.print(signale[signr].sigAdressen[0]);
        Serial.print(" Aantal lampen: ");
        Serial.print(signale[signr].sigDraden);
        //setVerlichting(signr,0);
        break;

      default:
        break;
      }
    }
  }
}

#endif