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


void PutDecoderValues()
{
    Serial.println("begin vullen");
    this_dec.sigConnected[0].sigId = 0;
    this_dec.sigConnected[0].sigType = "Vor4";
    this_dec.sigConnected[0].sigDraden = 4;
    this_dec.sigConnected[0].sigChannel = 0;
    this_dec.sigConnected[0].sigAdressen[0] = 511;
    this_dec.sigConnected[0].sigAdressen[1] = 512;
    this_dec.sigConnected[0].sigAdressen[2] = 513;
    this_dec.sigConnected[0].sigFade = 150;
    this_dec.sigConnected[0].sigDark = 300;
    this_dec.sigConnected[0].sigLamp[0] = 200;
    this_dec.sigConnected[0].sigLamp[1] = 200;
    this_dec.sigConnected[0].sigLamp[2] = 200;
    this_dec.sigConnected[0].sigLamp[3] = 200;

    this_dec.sigConnected[1].sigId = 1;
    this_dec.sigConnected[1].sigType = "H3gro";
    this_dec.sigConnected[1].sigDraden = 3;
    this_dec.sigConnected[1].sigChannel = 4;
    this_dec.sigConnected[1].sigAdressen[0] = 514;
    this_dec.sigConnected[1].sigAdressen[1] = 515;
    this_dec.sigConnected[1].sigFade = 150;
    this_dec.sigConnected[1].sigDark = 300;
    this_dec.sigConnected[1].sigLamp[0] = 110;
    this_dec.sigConnected[1].sigLamp[1] = 200;
    this_dec.sigConnected[1].sigLamp[2] = 150;

    this_dec.dekName = hostName;
    this_dec.nbrofsig = 2;
    StaticJsonDocument<768> dekoder;

    dekoder["dekName"] = this_dec.dekName;
    dekoder["nbrofsig"] = this_dec.nbrofsig;

    JsonArray sigConnected = dekoder.createNestedArray("sigConnected");
    uint8_t index = 0;
    while (index < this_dec.nbrofsig)
    {
        sigConnected[index]["sigId"] = this_dec.sigConnected[index].sigId;
        sigConnected[index]["sigType"] = this_dec.sigConnected[index].sigType;
        sigConnected[index]["sigDraden"] = this_dec.sigConnected[index].sigDraden;
        sigConnected[index]["sigAdressen"][0] = this_dec.sigConnected[index].sigAdressen[0];
        sigConnected[index]["sigAdressen"][1] = this_dec.sigConnected[index].sigAdressen[1];
        sigConnected[index]["sigAdressen"][2] = this_dec.sigConnected[index].sigAdressen[2];
        sigConnected[index]["sigFade"] = this_dec.sigConnected[index].sigType;
        sigConnected[index]["sigDark"] = this_dec.sigConnected[index].sigDark;
        sigConnected[index]["sigLamp"][0] = this_dec.sigConnected[index].sigLamp[0];
        sigConnected[index]["sigLamp"][1] = this_dec.sigConnected[index].sigLamp[1];
        sigConnected[index]["sigLamp"][2] = this_dec.sigConnected[index].sigLamp[2];
        sigConnected[index]["sigLamp"][3] = this_dec.sigConnected[index].sigLamp[3];
        sigConnected[index]["sigLamp"][4] = this_dec.sigConnected[index].sigLamp[4];
        sigConnected[index]["sigLamp"][5] = this_dec.sigConnected[index].sigLamp[5];
        index++;
    };
    // Open config file
    File decFile = SPIFFS.open(SIGNALE_JSON, "w");
    if (!decFile)
    {
        // Error, file did not open
        Serial.println("failed to open decoder file for writing");
    }

    // Serialize JSON data to write to file
    // serializeJsonPretty(dekoder, Serial);
    if (serializeJson(dekoder, decFile) == 0)
    {
        // Error writing file
        Serial.println(F("Failed to write to file"));
    }
    // Close file
    decFile.close();
}

void getDekoderJson()
{
    StaticJsonDocument<1024> dekoder;
    if (SPIFFS.exists(SIGNALE_JSON))
    {
        // The file exists, reading and loading
        Serial.println("reading Signale.json");
        File decFile = SPIFFS.open(SIGNALE_JSON, "r");
        if (decFile)
        {
            Serial.println("Opened configuration file");

            DeserializationError error = deserializeJson(dekoder, decFile);

            if (error)
            {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                return;
            };

            uint8_t count = 0;
            while (dekoder["dekName"][count] != NULL && count<20)
            {
                this_dec.dekName[count] = dekoder["dekName"][count];
                count++;
            }
            Serial.print("dekname : ");
            Serial.println(this_dec.dekName);
            Serial.print("count : ");
            Serial.print(count);
            this_dec.nbrofsig = dekoder["nbrofsig"];
            JsonArray sigConn = dekoder["sigConnected"];
            uint8_t index = 0;
            while (index < this_dec.nbrofsig)
            {
                this_dec.sigConnected[index].sigId = sigConn[index]["sigId"];
                count = 0;
                while (sigConn[index]["sigType"][count] != NULL && count < 9)
                {
                    this_dec.sigConnected[index].sigType[count] = sigConn[index]["sigType"][count];
                    count++;
                }
                this_dec.sigConnected[index].sigDraden = sigConn[index]["sigDraden"];
                this_dec.sigConnected[index].sigAdressen[0] = sigConn[index]["sigAdressen"][0];
                this_dec.sigConnected[index].sigAdressen[1] = sigConn[index]["sigAdressen"][1];
                this_dec.sigConnected[index].sigAdressen[2] = sigConn[index]["sigAdressen"][2];
                this_dec.sigConnected[index].sigFade = sigConn[index]["sigFade"];
                this_dec.sigConnected[index].sigDark = sigConn[index]["sigDark"];
                this_dec.sigConnected[index].sigLamp[0] = sigConn[index]["sigLamp"][0];
                this_dec.sigConnected[index].sigLamp[1] = sigConn[index]["sigLamp"][1];
                this_dec.sigConnected[index].sigLamp[2] = sigConn[index]["sigLamp"][2];
                this_dec.sigConnected[index].sigLamp[3] = sigConn[index]["sigLamp"][3];
                this_dec.sigConnected[index].sigLamp[4] = sigConn[index]["sigLamp"][4];
                this_dec.sigConnected[index].sigLamp[5] = sigConn[index]["sigLamp"][5];
                index++;
            };

            // Close file
            decFile.close();
        }
    }
}

#endif