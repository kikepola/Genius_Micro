#include "mbed.h"

#ifndef MBED_GPS_H
#define MBED_GPS_H

class GPS {
public:
  
    GPS(PinName tx, PinName rx);
    
    /** Sample the incoming GPS data, returning whether there is a lock
     * 
     * @return 1 if there was a lock when the sample was taken (and therefore .longitude and .latitude are valid), else 0
     */
    int sample();
    char getChar();
    
    /** The longitude (call sample() to set) */
    float longitude;

    /** The latitude (call sample() to set) */
    float latitude;
    
    float longitudeA ;
    float latitudeB ;
    
    /** The UTC time */
    float utc;
    
    char msg[256];
    
private:
    float trunc(float v);
    void getline();
    
    Serial _gps;

};

#endif
