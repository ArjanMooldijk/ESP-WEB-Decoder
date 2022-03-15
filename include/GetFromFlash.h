#ifndef GetFromFlash_h
#define GetFromFlash_h

#include <Arduino.h>
#include <Preferences.h>

Preferences SigDec_pref;
unsigned int signalAdr[16];
byte signalType[16];
bool signalFade[16];
bool darkBetween[16];
int darkDelay;
int maxLight[16];
int interval;
int fadeDuration;

void GetDecoderValues()
{
    SigDec_pref.begin("parameters", true);

    size_t decLen = SigDec_pref.getBytesLength("Decoder");
    char d_buffer[decLen]; // prepare a buffer for the data
    SigDec_pref.getBytes("Decoder", d_buffer, decLen);
    memcpy(this_dec, d_buffer, decLen);

    size_t sigLen = SigDec_pref.getBytesLength("Signale");
    char s_buffer[sigLen]; // prepare a buffer for the data
    SigDec_pref.getBytes("Signale", s_buffer, sigLen);
    memcpy(signale, s_buffer, sigLen);

    /*
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

    signalFade[0] = SigDec_pref.getBool("Dec_fade_flag0", 0);
    signalFade[1] = SigDec_pref.getBool("Dec_fade_flag1", 0);
    signalFade[2] = SigDec_pref.getBool("Dec_fade_flag2", 0);
    signalFade[3] = SigDec_pref.getBool("Dec_fade_flag3", 0);
    signalFade[4] = SigDec_pref.getBool("Dec_fade_flag4", 0);
    signalFade[5] = SigDec_pref.getBool("Dec_fade_flag5", 0);
    signalFade[6] = SigDec_pref.getBool("Dec_fade_flag6", 0);
    signalFade[7] = SigDec_pref.getBool("Dec_fade_flag7", 0);
    signalFade[8] = SigDec_pref.getBool("Dec_fade_flag8", 0);
    signalFade[9] = SigDec_pref.getBool("Dec_fade_flag9", 0);
    signalFade[10] = SigDec_pref.getBool("Dec_fade_flag10", 0);
    signalFade[11] = SigDec_pref.getBool("Dec_fade_flag11", 0);
    signalFade[12] = SigDec_pref.getBool("Dec_fade_flag12", 0);
    signalFade[13] = SigDec_pref.getBool("Dec_fade_flag13", 0);
    signalFade[14] = SigDec_pref.getBool("Dec_fade_flag14", 0);
    signalFade[15] = SigDec_pref.getBool("Dec_fade_flag15", 0);

    darkBetween[0] = SigDec_pref.getBool("Dec_Between_flag0", 0);
    darkBetween[1] = SigDec_pref.getBool("Dec_Between_flag1", 0);
    darkBetween[2] = SigDec_pref.getBool("Dec_Between_flag2", 0);
    darkBetween[3] = SigDec_pref.getBool("Dec_Between_flag3", 0);
    darkBetween[4] = SigDec_pref.getBool("Dec_Between_flag4", 0);
    darkBetween[5] = SigDec_pref.getBool("Dec_Between_flag5", 0);
    darkBetween[6] = SigDec_pref.getBool("Dec_Between_flag6", 0);
    darkBetween[7] = SigDec_pref.getBool("Dec_Between_flag7", 0);
    darkBetween[8] = SigDec_pref.getBool("Dec_Between_flag8", 0);
    darkBetween[9] = SigDec_pref.getBool("Dec_Between_flag9", 0);
    darkBetween[10] = SigDec_pref.getBool("Dec_Between_flag10", 0);
    darkBetween[11] = SigDec_pref.getBool("Dec_Between_flag11", 0);
    darkBetween[12] = SigDec_pref.getBool("Dec_Between_flag12", 0);
    darkBetween[13] = SigDec_pref.getBool("Dec_Between_flag13", 0);
    darkBetween[14] = SigDec_pref.getBool("Dec_Between_flag14", 0);
    darkBetween[15] = SigDec_pref.getBool("Dec_Between_flag15", 0);

    maxLight[0] = SigDec_pref.getInt("Dec_Bright0", 0);
    maxLight[1] = SigDec_pref.getInt("Dec_Bright1", 0);
    maxLight[2] = SigDec_pref.getInt("Dec_Bright2", 0);
    maxLight[3] = SigDec_pref.getInt("Dec_Bright3", 0);
    maxLight[4] = SigDec_pref.getInt("Dec_Bright4", 0);
    maxLight[5] = SigDec_pref.getInt("Dec_Bright5", 0);
    maxLight[6] = SigDec_pref.getInt("Dec_Bright6", 0);
    maxLight[7] = SigDec_pref.getInt("Dec_Bright7", 0);
    maxLight[8] = SigDec_pref.getInt("Dec_Bright8", 0);
    maxLight[9] = SigDec_pref.getInt("Dec_Bright9", 0);
    maxLight[10] = SigDec_pref.getInt("Dec_Bright10", 0);
    maxLight[11] = SigDec_pref.getInt("Dec_Bright11", 0);
    maxLight[12] = SigDec_pref.getInt("Dec_Bright12", 0);
    maxLight[13] = SigDec_pref.getInt("Dec_Bright13", 0);
    maxLight[14] = SigDec_pref.getInt("Dec_Bright14", 0);
    maxLight[15] = SigDec_pref.getInt("Dec_Bright15", 0);
 */
    SigDec_pref.end();
}

void PutDecoderValues()
{
    SigDec_pref.begin("parameters", false);

    SigDec_pref.putBytes("Decoder", this_dec, sizeof(this_dec));
    SigDec_pref.putBytes("Signale", signale, sizeof(signale));

    /*
        SigDec_pref.putString("Dec_name", decoderName);
        SigDec_pref.putInt("Dec_Delay", darkDelay);
        SigDec_pref.putInt("Dec_Int", interval);
        SigDec_pref.putInt("Dec_Fade_Dur", fadeDuration);

        SigDec_pref.putUInt("Dec_Addr0", signalAdr[0]);
        SigDec_pref.putUInt("Dec_Addr1", signalAdr[1]);
        SigDec_pref.putUInt("Dec_Addr2", signalAdr[2]);
        SigDec_pref.putUInt("Dec_Addr3", signalAdr[3]);
        SigDec_pref.putUInt("Dec_Addr4", signalAdr[4]);
        SigDec_pref.putUInt("Dec_Addr5", signalAdr[5]);
        SigDec_pref.putUInt("Dec_Addr6", signalAdr[6]);
        SigDec_pref.putUInt("Dec_Addr7", signalAdr[7]);
        SigDec_pref.putUInt("Dec_Addr8", signalAdr[8]);
        SigDec_pref.putUInt("Dec_Addr9", signalAdr[9]);
        SigDec_pref.putUInt("Dec_Addr10", signalAdr[10]);
        SigDec_pref.putUInt("Dec_Addr11", signalAdr[11]);
        SigDec_pref.putUInt("Dec_Addr12", signalAdr[12]);
        SigDec_pref.putUInt("Dec_Addr13", signalAdr[13]);
        SigDec_pref.putUInt("Dec_Addr14", signalAdr[14]);
        SigDec_pref.putUInt("Dec_Addr15", signalAdr[15]);

        SigDec_pref.putUChar("Dec_Sig_Type0", signalType[0]);
        SigDec_pref.putUChar("Dec_Sig_Type1", signalType[1]);
        SigDec_pref.putUChar("Dec_Sig_Type2", signalType[2]);
        SigDec_pref.putUChar("Dec_Sig_Type3", signalType[3]);
        SigDec_pref.putUChar("Dec_Sig_Type4", signalType[4]);
        SigDec_pref.putUChar("Dec_Sig_Type5", signalType[5]);
        SigDec_pref.putUChar("Dec_Sig_Type6", signalType[6]);
        SigDec_pref.putUChar("Dec_Sig_Type7", signalType[7]);
        SigDec_pref.putUChar("Dec_Sig_Type8", signalType[8]);
        SigDec_pref.putUChar("Dec_Sig_Type9", signalType[9]);
        SigDec_pref.putUChar("Dec_Sig_Type10", signalType[10]);
        SigDec_pref.putUChar("Dec_Sig_Type11", signalType[11]);
        SigDec_pref.putUChar("Dec_Sig_Type12", signalType[12]);
        SigDec_pref.putUChar("Dec_Sig_Type13", signalType[13]);
        SigDec_pref.putUChar("Dec_Sig_Type14", signalType[14]);
        SigDec_pref.putUChar("Dec_Sig_Type15", signalType[15]);

        SigDec_pref.putBool("Dec_fade_flag0", signalFade[0]);
        SigDec_pref.putBool("Dec_fade_flag1", signalFade[1]);
        SigDec_pref.putBool("Dec_fade_flag2", signalFade[2]);
        SigDec_pref.putBool("Dec_fade_flag3", signalFade[3]);
        SigDec_pref.putBool("Dec_fade_flag4", signalFade[4]);
        SigDec_pref.putBool("Dec_fade_flag5", signalFade[5]);
        SigDec_pref.putBool("Dec_fade_flag6", signalFade[6]);
        SigDec_pref.putBool("Dec_fade_flag7", signalFade[7]);
        SigDec_pref.putBool("Dec_fade_flag8", signalFade[8]);
        SigDec_pref.putBool("Dec_fade_flag9", signalFade[9]);
        SigDec_pref.putBool("Dec_fade_flag10", signalFade[10]);
        SigDec_pref.putBool("Dec_fade_flag11", signalFade[11]);
        SigDec_pref.putBool("Dec_fade_flag12", signalFade[12]);
        SigDec_pref.putBool("Dec_fade_flag13", signalFade[13]);
        SigDec_pref.putBool("Dec_fade_flag14", signalFade[14]);
        SigDec_pref.putBool("Dec_fade_flag15", signalFade[15]);

        SigDec_pref.putBool("Dec_Between_flag0", darkBetween[0]);
        SigDec_pref.putBool("Dec_Between_flag1", darkBetween[1]);
        SigDec_pref.putBool("Dec_Between_flag2", darkBetween[2]);
        SigDec_pref.putBool("Dec_Between_flag3", darkBetween[3]);
        SigDec_pref.putBool("Dec_Between_flag4", darkBetween[4]);
        SigDec_pref.putBool("Dec_Between_flag5", darkBetween[5]);
        SigDec_pref.putBool("Dec_Between_flag6", darkBetween[6]);
        SigDec_pref.putBool("Dec_Between_flag7", darkBetween[7]);
        SigDec_pref.putBool("Dec_Between_flag8", darkBetween[8]);
        SigDec_pref.putBool("Dec_Between_flag9", darkBetween[9]);
        SigDec_pref.putBool("Dec_Between_flag10", darkBetween[10]);
        SigDec_pref.putBool("Dec_Between_flag11", darkBetween[11]);
        SigDec_pref.putBool("Dec_Between_flag12", darkBetween[12]);
        SigDec_pref.putBool("Dec_Between_flag13", darkBetween[13]);
        SigDec_pref.putBool("Dec_Between_flag14", darkBetween[14]);
        SigDec_pref.putBool("Dec_Between_flag15", darkBetween[15]);

        SigDec_pref.putInt("Dec_Bright0", maxLight[0]);
        SigDec_pref.putInt("Dec_Bright1", maxLight[1]);
        SigDec_pref.putInt("Dec_Bright2", maxLight[2]);
        SigDec_pref.putInt("Dec_Bright3", maxLight[3]);
        SigDec_pref.putInt("Dec_Bright4", maxLight[4]);
        SigDec_pref.putInt("Dec_Bright5", maxLight[5]);
        SigDec_pref.putInt("Dec_Bright6", maxLight[6]);
        SigDec_pref.putInt("Dec_Bright7", maxLight[7]);
        SigDec_pref.putInt("Dec_Bright8", maxLight[8]);
        SigDec_pref.putInt("Dec_Bright9", maxLight[9]);
        SigDec_pref.putInt("Dec_Bright10", maxLight[10]);
        SigDec_pref.putInt("Dec_Bright11", maxLight[11]);
        SigDec_pref.putInt("Dec_Bright12", maxLight[12]);
        SigDec_pref.putInt("Dec_Bright13", maxLight[13]);
        SigDec_pref.putInt("Dec_Bright14", maxLight[14]);
        SigDec_pref.putInt("Dec_Bright15", maxLight[15]);
     */
    SigDec_pref.end();
}

#endif