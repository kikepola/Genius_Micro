#include "mbed.h"
#include "GPS.h"

 DigitalOut s1(p20);
 DigitalOut s2(p19);
 Serial pc(USBTX, USBRX);
 Serial device(p28, p27);
 GPS gps(p9, p10);


void getCordinates(){
    float x;
    char strGps[100];
    char charGps = gps.getChar();
    int i = 0;
    float result[20];

    while(charGps != '$' ){
        strGps[i] = charGps;
        charGps = gps.getChar();
        i =  i + 1;
        wait(0.1);
    }

    char msgPros[10];

    if(strstr(strGps, "GPGGA")  != NULL ){
        pc.printf("String:%s\n", strGps);
        int i = 0;
        int j = 0;
        for(i = 0; i < 14; i++){
            if(strGps[i] != ','){
                msgPros[j] = strGps[i];
                j++;
            }else{
                msgPros[j] = '\0';

                if(j != 0){
                    x = atof(msgPros);
                    result[i] = x;
                }
                j = 0;
            }
        }
    }

    for(i = 0; i < 14; i++){
        printf("%f ;", result[i]);
    }
}



 int main()
 {    
    char dado;
    s1 = 1;
    s2 = 1;
    pc.printf("Comunicacao Serial\n\r");
    while(1) {
        
        getCordinates();

    }
}

