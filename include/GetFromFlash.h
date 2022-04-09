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

void putDecoderValuesToFile()
{
    Serial.println("putDecoderValuesToFile");
    StaticJsonDocument<2048> dekoder;

    dekoder["dekName"] = hostName;
    dekoder["nbrofsig"] = this_dec.nbrofsig;

    JsonArray sigConnected = dekoder.createNestedArray("sigConnected");

    for(uint8_t i=0;i<this_dec.nbrofsig;i++){

        sigConnected[i]["sigId"] = this_dec.sigConnected[i].sigId;
        sigConnected[i]["sigType"] = this_dec.sigConnected[i].sigType;
        sigConnected[i]["sigDraden"] = this_dec.sigConnected[i].sigDraden;
        sigConnected[i]["sigChannel"] = this_dec.sigConnected[i].sigChannel;
        sigConnected[i]["sigNbrAdr"] = this_dec.sigConnected[i].sigNbrAdr;
        JsonArray sigAdressen = sigConnected[i].createNestedArray("sigAdressen");
        for(uint8_t ai=0;ai<this_dec.sigConnected[i].sigNbrAdr;ai++){
            sigConnected[i]["sigAdressen"].add(this_dec.sigConnected[i].sigAdressen[ai]);
        };
        sigConnected[i]["sigFade"] = this_dec.sigConnected[i].sigFade;
        sigConnected[i]["sigDark"] = this_dec.sigConnected[i].sigDark;
        JsonArray sigLamp = sigConnected[i].createNestedArray("sigLamp");
        for(uint8_t li=0;li<this_dec.sigConnected[i].sigDraden;li++){
            sigConnected[i]["sigLamp"].add(this_dec.sigConnected[i].sigLamp[li]);
        };
    };


///////////////////////////////////////////////////////////////////////////////////////////
    // StaticJsonDocument<2048> dekoder;

    // dekoder["dekName"] = hostName;
    // dekoder["nbrofsig"] = this_dec.nbrofsig;

    // JsonArray sigConnected = dekoder.createNestedArray("sigConnected");
    // if (this_dec.nbrofsig > 0)
    // {
    //     JsonObject sigConnected_0 = sigConnected.createNestedObject();
    //     sigConnected_0["sigId"] = this_dec.sigConnected[0].sigId;
    //     sigConnected_0["sigType"] = this_dec.sigConnected[0].sigType;
    //     sigConnected_0["sigDraden"] = this_dec.sigConnected[0].sigDraden;
    //     sigConnected_0["sigChannel"] = this_dec.sigConnected[0].sigChannel;
    //     sigConnected_0["sigNbrAdr"] = this_dec.sigConnected[0].sigNbrAdr;

    //     JsonArray sigConnected_0_sigAdressen = sigConnected_0.createNestedArray("sigAdressen");
    //     sigConnected_0_sigAdressen.add(this_dec.sigConnected[0].sigAdressen[0]);
    //     if (this_dec.sigConnected[0].sigAdressen[1] > 0)
    //     {
    //         sigConnected_0_sigAdressen.add(this_dec.sigConnected[0].sigAdressen[1]);

    //         if (this_dec.sigConnected[0].sigAdressen[2] > 0)
    //         {
    //             sigConnected_0_sigAdressen.add(this_dec.sigConnected[0].sigAdressen[2]);
    //         };
    //     };
    //     sigConnected_0["sigFade"] = this_dec.sigConnected[0].sigFade;
    //     sigConnected_0["sigDark"] = this_dec.sigConnected[0].sigDark;

    //     JsonArray sigConnected_0_sigLamp = sigConnected_0.createNestedArray("sigLamp");
    //     sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[0]);
    //     if (this_dec.sigConnected[0].sigAdressen[1] > 0)
    //     {
    //         sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[1]);
    //         if (this_dec.sigConnected[0].sigAdressen[2] > 0)
    //         {
    //             sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[2]);
    //             if (this_dec.sigConnected[0].sigAdressen[3] > 0)
    //             {
    //                 sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[3]);
    //                 if (this_dec.sigConnected[0].sigAdressen[4] > 0)
    //                 {
    //                     sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[4]);
    //                     if (this_dec.sigConnected[0].sigAdressen[5] > 0)
    //                     {
    //                         sigConnected_0_sigLamp.add(this_dec.sigConnected[0].sigLamp[5]);
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     if (this_dec.nbrofsig > 1)
    //     {
    //         JsonObject sigConnected_1 = sigConnected.createNestedObject();
    //         sigConnected_1["sigId"] = this_dec.sigConnected[1].sigId;
    //         sigConnected_1["sigType"] = this_dec.sigConnected[1].sigType;
    //         sigConnected_1["sigDraden"] = this_dec.sigConnected[1].sigDraden;
    //         sigConnected_1["sigChannel"] = this_dec.sigConnected[1].sigChannel;
    //         sigConnected_1["sigNbrAdr"] = this_dec.sigConnected[1].sigNbrAdr;

    //         JsonArray sigConnected_1_sigAdressen = sigConnected_1.createNestedArray("sigAdressen");
    //         sigConnected_1_sigAdressen.add(this_dec.sigConnected[1].sigAdressen[0]);
    //         if (this_dec.sigConnected[1].sigAdressen[1] > 0)
    //         {
    //             sigConnected_1_sigAdressen.add(this_dec.sigConnected[1].sigAdressen[1]);

    //             if (this_dec.sigConnected[1].sigAdressen[2] > 0)
    //             {
    //                 sigConnected_1_sigAdressen.add(this_dec.sigConnected[1].sigAdressen[2]);
    //             };
    //         };
    //         sigConnected_1["sigFade"] = this_dec.sigConnected[1].sigFade;
    //         sigConnected_1["sigDark"] = this_dec.sigConnected[1].sigDark;

    //         JsonArray sigConnected_1_sigLamp = sigConnected_1.createNestedArray("sigLamp");
    //         sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[0]);
    //         if (this_dec.sigConnected[1].sigAdressen[1] > 0)
    //         {
    //             sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[1]);
    //             if (this_dec.sigConnected[1].sigAdressen[2] > 0)
    //             {
    //                 sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[2]);
    //                 if (this_dec.sigConnected[1].sigAdressen[3] > 0)
    //                 {
    //                     sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[3]);
    //                     if (this_dec.sigConnected[1].sigAdressen[4] > 0)
    //                     {
    //                         sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[4]);
    //                         if (this_dec.sigConnected[1].sigAdressen[5] > 0)
    //                         {
    //                             sigConnected_1_sigLamp.add(this_dec.sigConnected[1].sigLamp[5]);
    //                         }
    //                     }
    //                 }
    //             }
    //         }

    //         if (this_dec.nbrofsig > 2)
    //         {
    //             JsonObject sigConnected_2 = sigConnected.createNestedObject();
    //             sigConnected_2["sigId"] = this_dec.sigConnected[2].sigId;
    //             sigConnected_2["sigType"] = this_dec.sigConnected[2].sigType;
    //             sigConnected_2["sigDraden"] = this_dec.sigConnected[2].sigDraden;
    //             sigConnected_2["sigChannel"] = this_dec.sigConnected[2].sigChannel;
    //             sigConnected_2["sigNbrAdr"] = this_dec.sigConnected[2].sigNbrAdr;

    //             JsonArray sigConnected_2_sigAdressen = sigConnected_2.createNestedArray("sigAdressen");
    //             sigConnected_2_sigAdressen.add(this_dec.sigConnected[2].sigAdressen[0]);
    //             if (this_dec.sigConnected[2].sigAdressen[1] > 0)
    //             {
    //                 sigConnected_2_sigAdressen.add(this_dec.sigConnected[2].sigAdressen[1]);

    //                 if (this_dec.sigConnected[2].sigAdressen[2] > 0)
    //                 {
    //                     sigConnected_2_sigAdressen.add(this_dec.sigConnected[2].sigAdressen[2]);
    //                 };
    //             };
    //             sigConnected_2["sigFade"] = this_dec.sigConnected[2].sigFade;
    //             sigConnected_2["sigDark"] = this_dec.sigConnected[2].sigDark;

    //             JsonArray sigConnected_2_sigLamp = sigConnected_2.createNestedArray("sigLamp");
    //             sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[0]);
    //             if (this_dec.sigConnected[2].sigAdressen[1] > 0)
    //             {
    //                 sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[1]);
    //                 if (this_dec.sigConnected[2].sigAdressen[2] > 0)
    //                 {
    //                     sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[2]);
    //                     if (this_dec.sigConnected[2].sigAdressen[3] > 0)
    //                     {
    //                         sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[3]);
    //                         if (this_dec.sigConnected[2].sigAdressen[4] > 0)
    //                         {
    //                             sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[4]);
    //                             if (this_dec.sigConnected[2].sigAdressen[5] > 0)
    //                             {
    //                                 sigConnected_2_sigLamp.add(this_dec.sigConnected[2].sigLamp[5]);
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //             if (this_dec.nbrofsig > 3)
    //             {
    //                 JsonObject sigConnected_3 = sigConnected.createNestedObject();
    //                 sigConnected_3["sigId"] = this_dec.sigConnected[3].sigId;
    //                 sigConnected_3["sigType"] = this_dec.sigConnected[3].sigType;
    //                 sigConnected_3["sigDraden"] = this_dec.sigConnected[3].sigDraden;
    //                 sigConnected_3["sigChannel"] = this_dec.sigConnected[3].sigChannel;
    //                 sigConnected_3["sigNbrAdr"] = this_dec.sigConnected[3].sigNbrAdr;

    //                 JsonArray sigConnected_3_sigAdressen = sigConnected_3.createNestedArray("sigAdressen");
    //                 sigConnected_3_sigAdressen.add(this_dec.sigConnected[3].sigAdressen[0]);
    //                 if (this_dec.sigConnected[3].sigAdressen[1] > 0)
    //                 {
    //                     sigConnected_3_sigAdressen.add(this_dec.sigConnected[3].sigAdressen[1]);

    //                     if (this_dec.sigConnected[3].sigAdressen[2] > 0)
    //                     {
    //                         sigConnected_3_sigAdressen.add(this_dec.sigConnected[3].sigAdressen[2]);
    //                     };
    //                 };
    //                 sigConnected_3["sigFade"] = this_dec.sigConnected[3].sigFade;
    //                 sigConnected_3["sigDark"] = this_dec.sigConnected[3].sigDark;

    //                 JsonArray sigConnected_3_sigLamp = sigConnected_3.createNestedArray("sigLamp");
    //                 sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[0]);
    //                 if (this_dec.sigConnected[3].sigAdressen[1] > 0)
    //                 {
    //                     sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[1]);
    //                     if (this_dec.sigConnected[3].sigAdressen[2] > 0)
    //                     {
    //                         sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[2]);
    //                         if (this_dec.sigConnected[3].sigAdressen[3] > 0)
    //                         {
    //                             sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[3]);
    //                             if (this_dec.sigConnected[3].sigAdressen[4] > 0)
    //                             {
    //                                 sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[4]);
    //                                 if (this_dec.sigConnected[3].sigAdressen[5] > 0)
    //                                 {
    //                                     sigConnected_3_sigLamp.add(this_dec.sigConnected[3].sigLamp[5]);
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //                 if (this_dec.nbrofsig > 4)
    //                 {
    //                     JsonObject sigConnected_4 = sigConnected.createNestedObject();
    //                     sigConnected_4["sigId"] = this_dec.sigConnected[4].sigId;
    //                     sigConnected_4["sigType"] = this_dec.sigConnected[4].sigType;
    //                     sigConnected_4["sigDraden"] = this_dec.sigConnected[4].sigDraden;
    //                     sigConnected_4["sigChannel"] = this_dec.sigConnected[4].sigChannel;
    //                     sigConnected_4["sigNbrAdr"] = this_dec.sigConnected[4].sigNbrAdr;

    //                     JsonArray sigConnected_4_sigAdressen = sigConnected_4.createNestedArray("sigAdressen");
    //                     sigConnected_4_sigAdressen.add(this_dec.sigConnected[4].sigAdressen[0]);
    //                     if (this_dec.sigConnected[4].sigAdressen[1] > 0)
    //                     {
    //                         sigConnected_4_sigAdressen.add(this_dec.sigConnected[4].sigAdressen[1]);

    //                         if (this_dec.sigConnected[4].sigAdressen[2] > 0)
    //                         {
    //                             sigConnected_4_sigAdressen.add(this_dec.sigConnected[4].sigAdressen[2]);
    //                         };
    //                     };
    //                     sigConnected_4["sigFade"] = this_dec.sigConnected[4].sigFade;
    //                     sigConnected_4["sigDark"] = this_dec.sigConnected[4].sigDark;

    //                     JsonArray sigConnected_4_sigLamp = sigConnected_4.createNestedArray("sigLamp");
    //                     sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[0]);
    //                     if (this_dec.sigConnected[4].sigAdressen[1] > 0)
    //                     {
    //                         sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[1]);
    //                         if (this_dec.sigConnected[4].sigAdressen[2] > 0)
    //                         {
    //                             sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[2]);
    //                             if (this_dec.sigConnected[4].sigAdressen[3] > 0)
    //                             {
    //                                 sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[3]);
    //                                 if (this_dec.sigConnected[4].sigAdressen[4] > 0)
    //                                 {
    //                                     sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[4]);
    //                                     if (this_dec.sigConnected[4].sigAdressen[5] > 0)
    //                                     {
    //                                         sigConnected_4_sigLamp.add(this_dec.sigConnected[4].sigLamp[5]);
    //                                     }
    //                                 }
    //                             }
    //                         }
    //                     }
    //                     if (this_dec.nbrofsig > 5)
    //                     {
    //                         JsonObject sigConnected_5 = sigConnected.createNestedObject();
    //                         sigConnected_5["sigId"] = this_dec.sigConnected[5].sigId;
    //                         sigConnected_5["sigType"] = this_dec.sigConnected[5].sigType;
    //                         sigConnected_5["sigDraden"] = this_dec.sigConnected[5].sigDraden;
    //                         sigConnected_5["sigChannel"] = this_dec.sigConnected[5].sigChannel;
    //                         sigConnected_5["sigNbrAdr"] = this_dec.sigConnected[5].sigNbrAdr;

    //                         JsonArray sigConnected_5_sigAdressen = sigConnected_5.createNestedArray("sigAdressen");
    //                         sigConnected_5_sigAdressen.add(this_dec.sigConnected[5].sigAdressen[0]);
    //                         if (this_dec.sigConnected[5].sigAdressen[1] > 0)
    //                         {
    //                             sigConnected_5_sigAdressen.add(this_dec.sigConnected[5].sigAdressen[1]);

    //                             if (this_dec.sigConnected[5].sigAdressen[2] > 0)
    //                             {
    //                                 sigConnected_5_sigAdressen.add(this_dec.sigConnected[5].sigAdressen[2]);
    //                             };
    //                         };
    //                         sigConnected_5["sigFade"] = this_dec.sigConnected[5].sigFade;
    //                         sigConnected_5["sigDark"] = this_dec.sigConnected[5].sigDark;

    //                         JsonArray sigConnected_5_sigLamp = sigConnected_5.createNestedArray("sigLamp");
    //                         sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[0]);
    //                         if (this_dec.sigConnected[5].sigAdressen[1] > 0)
    //                         {
    //                             sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[1]);
    //                             if (this_dec.sigConnected[5].sigAdressen[2] > 0)
    //                             {
    //                                 sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[2]);
    //                                 if (this_dec.sigConnected[5].sigAdressen[3] > 0)
    //                                 {
    //                                     sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[3]);
    //                                     if (this_dec.sigConnected[5].sigAdressen[4] > 0)
    //                                     {
    //                                         sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[4]);
    //                                         if (this_dec.sigConnected[5].sigAdressen[5] > 0)
    //                                         {
    //                                             sigConnected_5_sigLamp.add(this_dec.sigConnected[5].sigLamp[5]);
    //                                         }
    //                                     }
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    serializeJson(dekoder, Serial);
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

void makeDekoderFromJson(String inputJson)
{
    // Serial.println("makeDekoderFromJson");
    int nbrOfChars = inputJson.length() + 1;
    char decData[nbrOfChars];
    // inputJson.toCharArray(decData, nbrOfChars);
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

        sCc++;
    };
    // Serial.println("nieuwe decoder waarden gevuld ");
    // printDecoder();
}

void processJsonFromClient(String clientJson)
{
    // Serial.println("processJsonFromClient");
    makeDekoderFromJson(clientJson);
    putDecoderValuesToFile();
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