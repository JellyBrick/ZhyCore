#ifndef EXTRAFUNCS_H
#define EXTRAFUNCS_H
#include "string"

struct UUiD
{
    int64_t data1;
    int64_t data2;
};

double GetStartTime( void );
float getMs(void);
int mt_rand(int min,int max);
std::string zlib_decode(std::string const& data);
void CharStrAppend(char charstr[],const char beapped [],int & offset);
std::string ctos(unsigned char i);
unsigned char atoc(char *p);

#endif // EXTRAFUNCS_H
