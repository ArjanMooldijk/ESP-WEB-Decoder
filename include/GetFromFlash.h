#ifndef GetFromFlash_h
#define GetFromFlash_h

#include <Arduino.h>
#include <Preferences.h>
using namespace std;

void GetDecoderValues()
{
/*     parameters
    {
        char *Dec_name;            // Max 12 bytes
        unsigned int Dec_Addr[16]; // 32 bytes
        byte Dec_Sig_Type[16];     // 16 bytes
        bool Dec_fade_flag[16];    // 16 bytes
        bool Dec_Between_flag[16]; // 16 bytes
        long Dec_Delay;            // 2 bytes
        int Dec_Bright[16];        // 32 bytes
        int Dec_Int;               // 2 bytes
        int Dec_Fade_Dur;          // 2 bytes
                                   // Total 130 bytes
    } */
    char* decoderName;
    unsigned int signalAdr[16];
    byte signalType[16];
    bool signalFade[16];
    bool darkBetween[16];
    int darkDelay;
    int maxLight[16];
    int interval;
    int fadeDuration;
    int index = 0;

    Preferences SigDec_pref;

    SigDec_pref.begin("parameters", false);

    decoderName = &SigDec_pref.getString("Dec_name", "")[0];
    darkDelay = SigDec_pref.getInt("Dec_Delay", 0);
    interval = SigDec_pref.getInt("Dec_Int", 0);
    fadeDuration = SigDec_pref.getInt("Dec_Fade_Dur", 0);
    
    signalAdr[0] = SigDec_pref.getUInt("Dec_Addr0", 0);
    signalAdr[1] = SigDec_pref.getUInt("Dec_Addr1", 0);
    signalAdr[2] = SigDec_pref.getUInt("Dec_Addr2", 0);
    signalAdr[3] = SigDec_pref.getUInt("Dec_Addr3", 0);
    signalAdr[4] = SigDec_pref.getUInt("Dec_Addr4", 0);
    signalAdr[5] = SigDec_pref.getUInt("Dec_Addr5", 0);
    signalAdr[6] = SigDec_pref.getUInt("Dec_Addr6", 0);
    signalAdr[7] = SigDec_pref.getUInt("Dec_Addr7", 0);
    signalAdr[8] = SigDec_pref.getUInt("Dec_Addr8", 0);
    signalAdr[9] = SigDec_pref.getUInt("Dec_Addr9", 0);
    signalAdr[10] = SigDec_pref.getUInt("Dec_Addr10", 0);
    signalAdr[11] = SigDec_pref.getUInt("Dec_Addr11", 0);
    signalAdr[12] = SigDec_pref.getUInt("Dec_Addr12", 0);
    signalAdr[13] = SigDec_pref.getUInt("Dec_Addr13", 0);
    signalAdr[14] = SigDec_pref.getUInt("Dec_Addr14", 0);
    signalAdr[15] = SigDec_pref.getUInt("Dec_Addr15", 0);

    signalType[0] = SigDec_pref.getUChar("Dec_Sig_Type0", 0);
    signalType[1] = SigDec_pref.getUChar("Dec_Sig_Type1", 0);
    signalType[2] = SigDec_pref.getUChar("Dec_Sig_Type2", 0);
    signalType[3] = SigDec_pref.getUChar("Dec_Sig_Type3", 0);
    signalType[4] = SigDec_pref.getUChar("Dec_Sig_Type4", 0);
    signalType[5] = SigDec_pref.getUChar("Dec_Sig_Type5", 0);
    signalType[6] = SigDec_pref.getUChar("Dec_Sig_Type6", 0);
    signalType[7] = SigDec_pref.getUChar("Dec_Sig_Type7", 0);
    signalType[8] = SigDec_pref.getUChar("Dec_Sig_Type8", 0);
    signalType[9] = SigDec_pref.getUChar("Dec_Sig_Type9", 0);
    signalType[10] = SigDec_pref.getUChar("Dec_Sig_Type10", 0);
    signalType[11] = SigDec_pref.getUChar("Dec_Sig_Type11", 0);
    signalType[12] = SigDec_pref.getUChar("Dec_Sig_Type12", 0);
    signalType[13] = SigDec_pref.getUChar("Dec_Sig_Type13", 0);
    signalType[14] = SigDec_pref.getUChar("Dec_Sig_Type14", 0);
    signalType[15] = SigDec_pref.getUChar("Dec_Sig_Type15", 0);
    
    
    Dec_key = "Dec_fade_flag" + to_string(index);
    signalFade[index] = SigDec_pref.getBool(Dec_key, 0);
    While(index < 15)
    {
        index++;
        Dec_key = "Dec_fade_flag" + to_string(index);
        signalFade[index] = SigDec_pref.getBool(Dec_key, 0);
    }
    index = 0;

    Dec_key = "Dec_Between_flag" + to_string(index);
    signalFade[index] = SigDec_pref.getBool(Dec_key, 0);
    While(index < 15)
    {
        index++;
        Dec_key = "Dec_Between_flag" + to_string(index);
        signalFade[index] = SigDec_pref.getBool(Dec_key, 0);
    }
    index = 0;

    Dec_key = "Dec_Bright" + to_string(index);
    signalFade[index] = SigDec_pref.getInt(Dec_key, 0);
    While ((signalFade[index]>0))&(index<15))
    {
        index++;
        Dec_key = "Dec_Bright" + to_string(index);
        signalFade[index] = SigDec_pref.getInt(Dec_key, 0);
    }
    index = 0;

    SigDec_pref.end();
}

#endif