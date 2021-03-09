//Written by Bill Cable 09-Mar-2021
//Library to handle loading and saving config values to individual files
//-while a seperate file for each value wastes storage and is overkill,
// it is simple and lightweight 

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

class ConfigFiles
{
public:
    char folder[13] = "config"; //folder where the config files will be stored and read
    uint8_t maxValueLen = 20;   //maximum length for a str to be read and written

    ConfigFiles(); //constructor

    bool begin(int chipSelect = -1);   //init SD & checks to make sure the folder exists and creates it if needed
    bool read(char filename[13], int *value);
    bool read(char filename[13], float *value);
    bool write(const char filename[13], int value);
    //Writing floats is more complicated and should probably be avoided
        //it could be done by converting the float to a str and then using writestr
    //bool write(char filename[13], float value);
    bool readstr(char filename[13], char *value);
    bool writestr(char filename[13], char *value);

private:
    char path[30];  //complete path to the file
    File cf;        //file
};