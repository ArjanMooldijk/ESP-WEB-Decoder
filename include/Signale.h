
#ifndef Signale_h
#define Signale_h

#include <Arduino.h>

enum SignalTypes {
     VorAdr1       , // Vorsignal addr 1,  Fade    Voorsignaal, eerste adres  beelden Warnung & Fb1
     Vor1Adr       , // Vorsignal 1 addr,  Fade    Voorsignaal, één adres (2 pins)  beelden Warnung & Fb1
     VorAdr2       , // Vorsignal addr 2,  Fade    Voorsignaal, tweede adres  beelden Fb2 & Fb3
     VorAdr3       , // Vorsignal addr 3,  Fade    Voorsignaal, derde adres  beeld Fb5
     VorAdr2Dkl     , // Vorsignal addr 2,  Fade    Voorsignaal, tweede adres donker schakelen
     VorAdr3Dkl     , // Vorsignal addr 3,  Fade    Voorsignaal, derde adres donker schakelen
//
     HptAdr1       , // Haupt addr 1,     Fade    Hoofdsignaal eerste adres beelden Fb0 & Fb1                         G,R
     HptAdr2O      , // Haupt addr 2,     Fade    Hoofdsignaal tweede adres beeld Fb2 (3e licht oranje)               g,r,O
     HptAdr2G      , // Haupt addr 2,     Fade    Hoofdsignaal tweede adres beeld Fb3 (3e licht groen)                g,r,G
     HptAdr2OG     , // Haupt addr 2,     Fade    Hoofdsignaal tweede adres beeld Fb2 & Fb3 (3e oranje, 4e groen)     g,r,O,G,..
     HptAdr2GO     , // Haupt addr 2,     Fade    Hoofdsignaal tweede adres beeld Fb2 & Fb3 (3e groen, 4e oranje)     g,r,G,O,..
     HptAdr3O      , // Haupt addr 3,     Fade    Hoofdsignaal derde adres beeld Fb6 (5e licht oranje)                g,r,o,g,O
     HptAdr3G      , // Haupt addr 3,     Fade    Hoofdsignaal derde adres beeld Fb5 (5e licht groen)                 g,r,g,o,G
     HptAdr3OG     , // Haupt addr 3,     Fade    Hoofdsignaal derde adres beeld Fb5 & Fb6 (5e oranje, 6e groen)      g,r,o,g,O,G,r (niet aangesloten)

     ZwergAdr1     , // Zwerg addr 1,      Fade    Dwersignaal, eerste adres  beelden Halt & Fahrt
     ZwergAdr2     , // Zwerg addr 2,      Fade    Dwersignaal, tweede adres  beeld Fahrt mit Vorsicht
//
     SIMHaupt       , // SIM Haupt,         SIM hoofdsein
     SIMVor         , // SIM Vor,           SIM voorsein
     HbB            , // HbB addr 1,        Halt bei Bedarf sein
     FSM            , // FSM addr 1,        Fahrtstellungsmelder 
};
#endif