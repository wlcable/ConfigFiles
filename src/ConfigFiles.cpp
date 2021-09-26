//Written by Bill Cable 09-Mar-2021
//Library to handle loading and saving config values to individual files
//-while a seperate file for each value wastes storage and is overkill,
// it is simple and lightweight

#include "ConfigFiles.h"

//Constructor, we don't need to do anything here
ConfigFiles::ConfigFiles()
{
}

//Begin
//-optionally inits the SD library if a chipSelect value is given
//-checks to make sure folder is present and if not creates it
bool ConfigFiles::begin(int chipSelect)
{
    // see if the card is present and can be initialized:
    if (chipSelect > 0) //only if a chipSelect value was given, default -1
    {
        if (!SD.begin(chipSelect))
        {
            //Serial.println("SD Card failed, or not present");
            return false;
        }
    }
    //make sure that the folder is there
    if (!SD.exists(folder))
    {
        if (!SD.mkdir(folder))
            return false;
    }
    return true;
}

//Read Bool
//-reads an bool from the file using parseInt
bool ConfigFiles::read(const char filename[13], bool *value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    if (!SD.exists(path))
        return false;
    cf = SD.open(path, FILE_READ);
    if (cf)
    {
        if (cf.parseInt() != 0)
            *value = true;
        else
            *value = false;
    }
    else
    {
        return false;
    }
    return true;
}

//Read Int
//-reads an int from the file using parseInt
bool ConfigFiles::read(const char filename[13], int *value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    if (!SD.exists(path))
        return false;
    cf = SD.open(path, FILE_READ);
    if (cf)
    {
        *value = cf.parseInt();
    }
    else
    {
        return false;
    }
    return true;
}

//Read Float
//-reads a float from the file using parseFloat
bool ConfigFiles::read(const char filename[13], float *value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    if (!SD.exists(path))
        return false;
    cf = SD.open(path, FILE_READ);
    if (cf)
    {
        *value = cf.parseFloat();
    }
    else
    {
        return false;
    }
    return true;
}

//Write Bool
//-writes an bool to the file
//-file is overwritten if it exists
bool ConfigFiles::write(const char filename[13], bool value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    cf = SD.open(path, (O_READ | O_WRITE | O_CREAT | O_TRUNC)); //open the file for writing discarding contents
    if (cf)
    {
        if (value)
            cf.print("1");
        else
            cf.print("0");
        cf.close();
    }
    else
        return false;
    return true;
}

//Write Int
//-writes an int to the file
//-file is overwritten if it exists
bool ConfigFiles::write(const char filename[13], int value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    cf = SD.open(path, (O_READ | O_WRITE | O_CREAT | O_TRUNC)); //open the file for writing discarding contents
    if (cf)
    {
        cf.print(value);
        cf.close();
    }
    else
        return false;
    return true;
}

//Write Str
//-writes an char to the file
//-file is overwritten if it exists
bool ConfigFiles::writestr(const char filename[13], char *value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    cf = SD.open(path, (O_READ | O_WRITE | O_CREAT | O_TRUNC)); //open the file for writing discarding contents
    if (cf)
    {
        cf.print(value);
        cf.close();
    }
    else
        return false;
    return true;
}

//Write Float
//-this is complicated and should be avoided
//-a better approach would be to convert the float to a string in the main program,
// then use writestr to write it to the file
// bool ConfigFiles::write(char filename[13], float value)
// {

//     return true;
// }

//Read Str
//-reads a char from a file
//-length is limited to maxValueLen
//-make sure to pass a pointer to a char array that is big enough :-)
bool ConfigFiles::readstr(const char filename[13], char *value)
{
    //open the file
    sprintf(path, "%s/%s", folder, filename);
    if (!SD.exists(path))
        return false;
    cf = SD.open(path, FILE_READ);
    if (cf)
    {
        if (cf.available())
        {
            cf.read(value, maxValueLen);
        }
        cf.close();
    }
    else
        return false;
    return true;
}