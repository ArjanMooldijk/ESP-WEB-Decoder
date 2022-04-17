#ifndef GetFromFlash_h
#define GetFromFlash_h

#include <Arduino.h>
#include <Initialisatie.h>

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

void printDecoder()
{

    Serial.println("en de nieuwe waardes zijn: ");
    Serial.print("decName ");
    Serial.println(this_dec.dekName);
    Serial.print("Aantal seinen: ");
    Serial.println(this_dec.nbrofsig);
    for (uint8_t i = 0; i < this_dec.nbrofsig; i++)
    {
        Serial.print("ID: ");
        Serial.println(this_dec.sigConnected[i].sigId);
        Serial.print("Type: ");
        Serial.println(this_dec.sigConnected[i].sigType);
        Serial.print("Draden: ");
        Serial.println(this_dec.sigConnected[i].sigDraden);
        Serial.print("#Adressen: ");
        Serial.println(this_dec.sigConnected[i].sigNbrAdr);
        Serial.print("Fade: ");
        Serial.println(this_dec.sigConnected[i].sigFade);
        Serial.print("Dark: ");
        Serial.println(this_dec.sigConnected[i].sigDark);
        Serial.print("Adr1: ");
        Serial.println(this_dec.sigConnected[i].sigAdressen[0]);
        Serial.print("Adr2: ");
        Serial.println(this_dec.sigConnected[i].sigAdressen[1]);
        Serial.print("Adr3: ");
        Serial.println(this_dec.sigConnected[i].sigAdressen[2]);
        Serial.print("Lamp1: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[0]);
        Serial.print("Lamp2: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[1]);
        Serial.print("Lamp3: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[2]);
        Serial.print("Lamp4: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[3]);
        Serial.print("Lamp5: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[4]);
        Serial.print("Lamp6: ");
        Serial.println(this_dec.sigConnected[i].sigLamp[5]);
    };
}

void initDecJson()
{
    // Serial.println("initDecJson");
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

void putDecoderValuesToFile(String inputJson)
{
    Serial.println("putDecoderValuesToFile");
    // StaticJsonDocument<2048> dekoder;

    // dekoder["dekName"] = hostName;
    // dekoder["nbrofsig"] = this_dec.nbrofsig;

    // JsonArray sigConnected = dekoder.createNestedArray("sigConnected");

    // for(uint8_t i=0;i<this_dec.nbrofsig;i++){

    //     sigConnected[i]["sigId"] = this_dec.sigConnected[i].sigId;
    //     sigConnected[i]["sigType"] = this_dec.sigConnected[i].sigType;
    //     sigConnected[i]["sigDraden"] = this_dec.sigConnected[i].sigDraden;
    //     sigConnected[i]["sigChannel"] = this_dec.sigConnected[i].sigChannel;
    //     sigConnected[i]["sigNbrAdr"] = this_dec.sigConnected[i].sigNbrAdr;
    //     JsonArray sigAdressen = sigConnected[i].createNestedArray("sigAdressen");
    //     for(uint8_t ai=0;ai<this_dec.sigConnected[i].sigNbrAdr;ai++){
    //         sigConnected[i]["sigAdressen"].add(this_dec.sigConnected[i].sigAdressen[ai]);
    //     };
    //     sigConnected[i]["sigFade"] = this_dec.sigConnected[i].sigFade;
    //     sigConnected[i]["sigDark"] = this_dec.sigConnected[i].sigDark;
    //     JsonArray sigLamp = sigConnected[i].createNestedArray("sigLamp");
    //     for(uint8_t li=0;li<this_dec.sigConnected[i].sigDraden;li++){
    //         sigConnected[i]["sigLamp"].add(this_dec.sigConnected[i].sigLamp[li]);
    //     };
    // };

    // serializeJson(dekoder, Serial);
    File decFile = SPIFFS.open(DECODER_JSON, "w");
    if (!decFile)
    {
        Serial.println("failed to open decoder file for writing");
    };
    int bytesWritten = decFile.print(inputJson);

    if (bytesWritten > 0)
    {
        Serial.println("File was written");
        Serial.println(bytesWritten);
    }
    else
    {
        Serial.println("File write failed");
    };
    // if (serializeJson(dekoder, decFile) == 0)
    // {
    //     Serial.println(F("Failed to write to file"));
    // };
    decFile.close();
}

void makeDekoderFromJson(String inputJson)
{
    // Serial.println("makeDekoderFromJson");
    Serial.println("ontvangen Json string : ");
    Serial.println(inputJson);
    Serial.println();

    StaticJsonDocument<2048> dekoder;
    DeserializationError error = deserializeJson(dekoder, inputJson);

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

        signale[sCc]=this_dec.sigConnected[sCc];
        setSignalType();

        sCc++;
    };
    // Serial.println("nieuwe decoder waarden gevuld ");
    // printDecoder();
}

void processJsonFromClient(String clientJson)
{
    // Serial.println("processJsonFromClient");
    makeDekoderFromJson(clientJson);
    setDimSteps();
    Initialiseer_decoder();
    putDecoderValuesToFile(clientJson);
};

String getDecoderValues()
{
    // Serial.println("getDecoderValues");
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
    // Serial.println("getDekoderJson");
    if (SPIFFS.exists(DECODER_JSON))
    {
        // The file exists, reading and loading
        File decFile = SPIFFS.open(DECODER_JSON, "r");
        if (decFile)
        {
            Serial.println("Opened configuration file");

            String decDataS;
            while (decFile.available())
            {
                decDataS += char(decFile.read());
            }
            makeDekoderFromJson(decDataS);
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