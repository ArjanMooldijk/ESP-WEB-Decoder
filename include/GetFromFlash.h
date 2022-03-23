#ifndef GetFromFlash_h
#define GetFromFlash_h

#include <Arduino.h>
#include <Preferences.h>

Preferences SigDec_pref;

void saveHostNameFile()
// Save Config in JSON format
{
    Serial.println(F("Saving configuration..."));

    jsonHostNameFile["hostName"] = hostName;

    // Open config file
    File configFile = SPIFFS.open(JSON_CONFIG_FILE, "w");
    if (!configFile)
    {
        // Error, file did not open
        Serial.println("failed to open config file for writing");
    }

    // Serialize JSON data to write to file
    serializeJsonPretty(jsonHostNameFile, Serial);
    if (serializeJson(jsonHostNameFile, configFile) == 0)
    {
        // Error writing file
        Serial.println(F("Failed to write to file"));
    }
    // Close file
    configFile.close();
}

bool loadHostNameFile()
// Load existing configuration file
{
    // Uncomment if we need to format filesystem (debug)
    // SPIFFS.format();

    // Read configuration from FS json
    if (SPIFFS.exists(JSON_CONFIG_FILE))
    {
        // The file exists, reading and loading
        Serial.println("reading config file");
        File configFile = SPIFFS.open(JSON_CONFIG_FILE, "r");
        if (configFile)
        {
            Serial.println("Opened configuration file");
            DeserializationError error = deserializeJson(jsonHostNameFile, configFile);
            // serializeJsonPretty(jsonHostNameFile, Serial);
            if (!error)
            {
                Serial.println("Parsing JSON");

                strcpy(hostName, jsonHostNameFile["hostName"]);

                return true;
            }
            else
            {
                // Error loading JSON data
                Serial.println("Failed to load json config");
            }
        }
    }
    return false;
}

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

    SigDec_pref.end();
}

void PutDecoderValues()
{
    SigDec_pref.begin("parameters", false);

    SigDec_pref.putBytes("Decoder", this_dec, sizeof(this_dec));
    SigDec_pref.putBytes("Signale", signale, sizeof(signale));

    SigDec_pref.end();
    /*
        this_dec[0].name = "Seindecoder";
        this_dec[0].nbrofsig = 1;

        signale[0].name = "Stadel";
        signale[0].stype[0] = VorAdr1;
        signale[0].stype[1] = VorAdr2;
        signale[0].stype[2] = VorAdr3Dkl;

        signale[0].adress[0] = 401;
        signale[0].adress[1] = 402;
        signale[0].adress[2] = NULL;

        signale[0].fadetime = 150;
        signale[0].darktime = 300;
        signale[0].firstCH = 0;
        signale[0].pins = 4;

        signale[0].ChBright[0] = 200;
        signale[0].ChBright[1] = 200;
        signale[0].ChBright[2] = 200;
        signale[0].ChBright[3] = 200;
        signale[0].ChBright[4] = NULL;
        signale[0].ChBright[5] = NULL; */
}

#endif