//Test program for ConfigFiles

#include <Arduino.h> //The main-macros of c++
#include <stdlib.h>
#include <ConfigFiles.h>

int MeasNum; //counts the number of measurements, one measurement can have more than one sample
char Name[18], NewName[18];

//SD card and file related
#define chipSelect 4 //for SD card

ConfigFiles cfg;

void setup()
{
    // Open serial communications for debugging:
    Serial.begin(9600);
    while (!Serial)
    {
    }
    delay(2000);
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD Card failed, or not present");
        while (1)
            ; //stop
        return;
    }
    //cfg.folder can be changed, default is CONFIG
    cfg.maxValueLen = 20;   //default is 20
    
    if (!cfg.begin())
    {
        Serial.println("Error begin ConfigFiles");
    }
    //get defaults from SD card, if they exist
    if (!cfg.read("MeasNum.cfg", &MeasNum))
    {
        Serial.println("Error couldn't read MeasNum from file, loading default");
        MeasNum = 0;
    }
    if (!cfg.readstr("testtext.cfg", Name))
    {
        Serial.println("Error couldn't read Name from file, loading default");
        sprintf(Name, "ConfigFiles");
    }
}

void loop()
{
    delay(5000);
    //Measurement Number Test
    if (!cfg.write("MeasNum.cfg", MeasNum))
    {
        Serial.print("Error writing file!");
        Serial.println(MeasNum);
    }
    else
    {
        Serial.print("Wrote to file, MeasNum: ");
        Serial.println(MeasNum);
    }
    //Name Test
    sprintf(NewName,"%s %d",Name,MeasNum);
    if (!cfg.writestr("testtext.cfg", NewName))
    {
        Serial.println("Error writing file testtext.cgf!");
    }
    else
    {
        Serial.print("Wrote to file, testtext.cgf, ");
        Serial.println(NewName);
    }
    //Serial.println(MeasNum);
    MeasNum++;
}