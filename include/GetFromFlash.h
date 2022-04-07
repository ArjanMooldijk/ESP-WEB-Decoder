#ifndef GetFromFlash_h
#define GetFromFlash_h

#include <Arduino.h>

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

void initDecJson()
{
    StaticJsonDocument<512> dekoder;

    dekoder["dekName"] = hostName;
    dekoder["nbrofsig"] = 0;

    JsonArray sigConnected = dekoder.createNestedArray("sigConnected");
    File decFile = SPIFFS.open(DECODER_JSON, "w");
    if (!decFile)
    {
        Serial.println("failed to open decoder file for writing");
    };
    if (serializeJson(dekoder, decFile) == 0)
    {
        Serial.println(F("Failed to write to file"));
    };
    decFile.close();
}


void PutDecoderValues()
{
    this_dec.sigConnected[0].sigId = 0;
    this_dec.sigConnected[0].sigType = "Vor4";
    this_dec.sigConnected[0].sigDraden = 4;
    this_dec.sigConnected[0].sigChannel = 0;
    this_dec.sigConnected[0].sigNbrAdr = 3;
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
    this_dec.sigConnected[1].sigNbrAdr = 2;
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
        sigConnected[index]["sigNbrAdr"] = this_dec.sigConnected[index].sigNbrAdr;
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
    File decFile = SPIFFS.open(DECODER_JSON, "w");
    if (!decFile)
    {
        // Error, file did not open
        Serial.println("failed to open decoder file for writing");
    };
    // Serialize JSON data to write to file
    // serializeJsonPretty(dekoder, Serial);
    if (serializeJson(dekoder, decFile) == 0)
    {
        // Error writing file
        Serial.println(F("Failed to write to file"));
    }
    else
    {
        Serial.println("weggeschreven naar SPIFFS :");
        serializeJson(dekoder, Serial);
        Serial.println();
    };
    // Close file
    decFile.close();
}


 String getDecoderValues()
{
    String decDataS;
    if (SPIFFS.exists(DECODER_JSON))
    {
        File decFile = SPIFFS.open(DECODER_JSON, "r");
        if (decFile)
        {
            while (decFile.available())
            {
                decDataS += char(decFile.read());
            }
            decFile.close();
        }
    }
    return decDataS;
}


void getDekoderJson()
{
    StaticJsonDocument<2048> dekoder;
    if (SPIFFS.exists(DECODER_JSON))
    {
        // The file exists, reading and loading
        File decFile = SPIFFS.open(DECODER_JSON, "r");
        if (decFile)
        {
            // Serial.println("Opened configuration file");

            String decDataS;
            uint16_t nbrOfChars = 0;
            while (decFile.available())
            {
                decDataS += char(decFile.read());
            }
            nbrOfChars = decDataS.length() + 1;
            char decData[nbrOfChars];
            decDataS.toCharArray(decData, nbrOfChars);
            // Serial.print("Gelezen uit deKoder.json : ");
            // Serial.println(decData);

            DeserializationError error = deserializeJson(dekoder, decData);

            if (error)
            {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                return;
            };

            this_dec.dekName = dekoder["dekName"];
            this_dec.nbrofsig = dekoder["nbrofsig"];

            uint8_t sCc = 0;
            for (JsonObject sigConnected_item : dekoder["sigConnected"].as<JsonArray>())
            {
                this_dec.sigConnected[sCc].sigId = sigConnected_item["sigId"];
                this_dec.sigConnected[sCc].sigType = sigConnected_item["sigType"];
                this_dec.sigConnected[sCc].sigDraden = sigConnected_item["sigDraden"];
                this_dec.sigConnected[sCc].sigNbrAdr = sigConnected_item["sigNbrAdr"];
                this_dec.sigConnected[sCc].sigFade = sigConnected_item["sigFade"];
                this_dec.sigConnected[sCc].sigDark = sigConnected_item["sigDark"];
                JsonArray sigConnected_item_sigAdressen = sigConnected_item["sigAdressen"];
                this_dec.sigConnected[sCc].sigAdressen[0] = sigConnected_item_sigAdressen[0];
                this_dec.sigConnected[sCc].sigAdressen[1] = sigConnected_item_sigAdressen[1];
                this_dec.sigConnected[sCc].sigAdressen[2] = sigConnected_item_sigAdressen[2];
                JsonArray sigConnected_item_sigLamp = sigConnected_item["sigLamp"];
                this_dec.sigConnected[sCc].sigLamp[0] = sigConnected_item_sigLamp[0];
                this_dec.sigConnected[sCc].sigLamp[1] = sigConnected_item_sigLamp[1];
                this_dec.sigConnected[sCc].sigLamp[2] = sigConnected_item_sigLamp[2];
                this_dec.sigConnected[sCc].sigLamp[3] = sigConnected_item_sigLamp[3];
                this_dec.sigConnected[sCc].sigLamp[4] = sigConnected_item_sigLamp[4];
                this_dec.sigConnected[sCc].sigLamp[5] = sigConnected_item_sigLamp[5];

                sCc++;
            }
            // Close file
            decFile.close();
        }
    }
    else
    {
        Serial.println("file not found, creating decoder");
        initDecJson();
    };
}

#endif