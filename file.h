#ifndef __file_h__
#define __file_h__
#include <SPIFFS.h>






String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);







#endif
