#ifndef Initialisatie_h
#define Initialisatie_h

//////////////////////////
void setDimSteps()
{
  double dimFactor;
  uint8_t chCount = 0;
  uint8_t maxStep;

  for (uint8_t scount = 0; scount < this_dec[0].nbrofsig; scount++) // voor ieder signaal
  {
    for (int x = 0; x < signale[scount].pins; x++) // voor ieder kanaal
    {
      float dimExp = 1.0 / (fadeConst[signale[scount].firstCH] - 1);
      dimStep[signale[scount].firstCH + x][0] = 0;          // [0] is altijd 0
      dimFactor = pow(signale[scount].ChBright[x], dimExp); // grondgetal voor exponent
      if (signale[scount].fadetime > 200)
      {
        maxStep = 20; // nooit meer dan 20 stappen dimmen
      }
      else
      {
        maxStep = signale[scount].fadetime / 10;
      }
      for (int y = maxStep - 1; y > 0; y--) //
      {
        dimStep[x][y] = pow(dimFactor, y);
      }
    }
  }
}

//////////////////////////
void Initialiseer_decoder()
{
  for (uint8_t signr = 0; signr < this_dec[0].nbrofsig; signr++)

  { // set nbr of fade steps and darkdelay for each channel
    for (uint8_t chNr = 0; chNr < signale[signr].pins; chNr++)
    {
      fadeConst[signale[signr].firstCH + chNr] = signale[signr].fadetime / 10;
      darkDelay[signale[signr].firstCH + chNr] = signale[signr].darktime;
      maxLight[signale[signr].firstCH + chNr] = signale[signr].ChBright[chNr];
      if (signale[signr].fadetime > 0)
      {
        signalFade[signale[signr].firstCH + chNr] = true;
      }
    }
    // set all default Halt and register starting pin per signal
    switch (signale[signr].stype[0])
    {
    case VorAdr1:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.print(" Vorsignal ");
      Serial.print(signale[signr].pins);
      Serial.println(" Leds");
      setFb0Vorsignal(signr);
      break;

    case Vor1Adr:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.print(" Vorsignal ");
      Serial.print(signale[signr].pins);
      Serial.println(" Leds");
      setFb0Vorsignal(signr);
      break;

    case ZwergAdr1:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.print(" Zwergsignal ");
      Serial.print(signale[signr].pins);
      Serial.println(" Leds");
      setZwergsignal(signr, 0);
      break;

    case SIMHaupt:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.println(" SIM Hauptsignal");
      setHilfsignal(signr, 0);
      break;

    case SIMVor:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.println(" SIM Vorsignal");
      setHilfsignal(signr, 0);
      break;

    case HbB:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.println(" Halt bei Bedarf Signal");
      setHilfsignal(signr, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
      break;

    case FSM:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.println(" Halt bei Bedarf Signal");
      setHilfsignal(signr, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
      break;

    case HptAdr1:
      Serial.print("Channel: ");
      Serial.print(signale[signr].firstCH);
      Serial.print(" Adres: ");
      Serial.print(signale[signr].adress[0]);
      Serial.print(" Hauptsignal ");
      Serial.print(signale[signr].pins);
      Serial.println(" Leds");
      setFb0Hauptsignal(signr);
      break;

    default:
      break;
    }
  }
}

#endif