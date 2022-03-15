#ifndef Initialisatie_h
#define Initialisatie_h

//////////////////////////
void setDimSteps()
{
  double dimFactor;
  float dimExp = 1.0 / float(fadeConst - 1);
  uint8_t chCount = 0;
  uint8_t maxStep;

  for (uint8_t scount = 0; scount < this_dec[0].nbrofsig; scount++)     // voor ieder signaal
  {
    for (int x = signale[scount].firstCH; x < (signale[scount].firstCH + signale[scount].pins); x++) //voor ieder kanaal
    {
      dimStep[x][0] = 0;                                         // [0] is altijd 0
      dimFactor = pow(signale[scount].ChBright[x-signale[scount].firstCH], dimExp);           // grondgetal voor exponent
      if (signale[scount].fadetime>200){
        maxStep = 20;                                                 // nooit meer dan 20 stappen dimmen
      }
      else{
        maxStep = signale[scount].fadetime / 10;
      }
      for (int y = maxStep-1; y > 0; y--)                             // 
      {
        dimStep[x][y] = pow(dimFactor, y);
      }
    }
  }
}

//////////////////////////
void Initialiseer_decoder()
{
  for (byte x = 0; x < anZahl; x++)
  { // set all default Halt and register starting pin per signal
    switch (signalType[x])
    {
    case VorAdr1:
      if (signalType[x + 1] == VorAdr2 || signalType[x + 1] == VorAdr2Dkl)
      {
        if (signalType[x + 2] == VorAdr3)
        {
          signalLeds[x] = 5;
          signalLeds[x + 1] = 5;
          signalLeds[x + 2] = 5;
          signalChannel[x] = pinCounter;
          signalChannel[x + 1] = pinCounter;
          signalChannel[x + 2] = pinCounter;
          pinCounter = pinCounter + 5;
        }
        else
        {
          signalLeds[x] = 4;
          signalLeds[x + 1] = 4;
          signalChannel[x] = pinCounter;
          signalChannel[x + 1] = pinCounter;
          if (signalType[x + 2] == VorAdr3Dkl)
          {
            signalLeds[x + 2] = 4;
            signalChannel[x + 2] = pinCounter;
          }
          pinCounter = pinCounter + 4;
        }
      }
      else
      {
        signalLeds[x] = 4;
        signalChannel[x] = pinCounter;
        pinCounter = pinCounter + 4;
      }
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.print(" Vorsignal ");
      Serial.print(signalLeds[x]);
      Serial.println(" Leds");
      setFb0Vorsignal(x);
      break;

    case Vor1Adr:
      signalLeds[x] = 2;
      signalChannel[x] = pinCounter;
      if (signalType[x + 1] == VorAdr2Dkl)
      {
        signalChannel[x + 1] = pinCounter;
      }
      pinCounter = pinCounter + 2;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.print(" Vorsignal ");
      Serial.print(signalLeds[x]);
      Serial.println(" Leds");
      setFb0Vorsignal(x);
      break;

    case ZwergAdr1:
      signalLeds[x] = 3;
      signalLeds[x + 1] = 3;
      signalChannel[x] = pinCounter;
      signalChannel[x + 1] = pinCounter;
      pinCounter = pinCounter + 3;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.print(" Zwergsignal Fade ");
      Serial.print(signalLeds[x]);
      Serial.println(" Leds");
      setZwergsignal(x, 0);
      break;

    case SIMHaupt:
      signalLeds[x] = 1;
      signalChannel[x] = pinCounter;
      pinCounter = pinCounter + 1;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.println(" SIM Hauptsignal");
      setHilfsignal(x, 0);
      break;

    case SIMVor:
      signalLeds[x] = 1;
      signalChannel[x] = pinCounter;
      pinCounter = pinCounter + 1;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.println(" SIM Vorsignal");
      setHilfsignal(x, 0);
      break;

    case HbB:
      signalLeds[x] = 1;
      signalChannel[x] = pinCounter;
      pinCounter = pinCounter + 1;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.println(" Halt bei Bedarf Signal");
      setHilfsignal(x, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
      break;

    case FSM:
      signalLeds[x] = 1;
      signalChannel[x] = pinCounter;
      pinCounter = pinCounter + 1;
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.println(" Halt bei Bedarf Signal");
      setHilfsignal(x, 0); // Hetzelfde als SIM Vorsignal; gebruik dezelfde routines voor aansturing
      break;

    case HptAdr1:
      if (signalType[x + 1] == HptAdr2O || signalType[x + 1] == HptAdr2G)
      {
        signalLeds[x] = 3;
        signalLeds[x + 1] = 3;
        signalChannel[x] = pinCounter;
        signalChannel[x + 1] = pinCounter;
        pinCounter = pinCounter + 3;
      }
      else
      {
        if (signalType[x + 1] == HptAdr2OG || signalType[x + 1] == HptAdr2GO)
        {
          if (signalType[x + 2] == HptAdr3O || signalType[x + 1] == HptAdr3G)
          {
            signalLeds[x] = 5;
            signalLeds[x + 1] = 5;
            signalLeds[x + 2] = 5;
            signalChannel[x] = pinCounter;
            signalChannel[x + 1] = pinCounter;
            signalChannel[x + 2] = pinCounter;
            pinCounter = pinCounter + 5;
          }
          else
          {
            if (signalType[x + 2] == HptAdr3OG)
            {
              signalLeds[x] = 6;
              signalLeds[x + 1] = 6;
              signalLeds[x + 2] = 6;
              signalChannel[x] = pinCounter;
              signalChannel[x + 1] = pinCounter;
              signalChannel[x + 2] = pinCounter;
              pinCounter = pinCounter + 6;
            }
            else
            {
              signalLeds[x] = 4;
              signalLeds[x + 1] = 4;
              signalChannel[x] = pinCounter;
              signalChannel[x + 1] = pinCounter;
              pinCounter = pinCounter + 4;
            }
          }
        }
        else
        {
          signalLeds[x] = 2;
          signalChannel[x] = pinCounter;
          pinCounter = pinCounter + 2;
        }
      }
      Serial.print("Pin: ");
      Serial.print(signalChannel[x]);
      Serial.print(" Adres: ");
      Serial.print(signalAdr[x]);
      Serial.print(" Hauptsignal ");
      Serial.print(signalLeds[x]);
      Serial.println(" Leds");
      setFb0Hauptsignal(x);
      break;

    default:
      break;
    }
  }
}

#endif