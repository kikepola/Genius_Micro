#include "mbed.h"
#include "GPS.h"

DigitalOut s1(p20);
DigitalOut s2(p19);
Serial pc(USBTX, USBRX);
Serial device(p28, p27);
GPS gps(p9, p10);
char command = '1';
float longitude;
float latitude;


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
        //pc.printf("String:%s\n", strGps);
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

    longitude = result[9];
    latitude = result[8];

    device.printf("lat: %f \n", longitude);
    device.printf("lon: %f \n", latitude);
}



void bluetoothCommand(){
    if(device.readable())
    {
        command = device.getc();
        if(command == '1'){
            s1 = 0;
            s2 = 1;
            device.printf("s2",command);
        }else if(command == '2'){
            s1 = 1;
            s2 = 0;
            device.printf("s1",command);
        }else if(command == '3'){
            s1 = 0;
            s2 = 0;
            device.printf("s3",command);
        }else if(command == '4'){
            s1 = 1;
            s2 = 1;
            device.printf("s4",command);
        }
    }
   
    pc.printf("%c\n",command);
    
}



 int main()
 {    
    char dado;
    pc.printf("Comunicacao Serial\n\r");
    while(1) {
        getCordinates();
        bluetoothCommand();

    }
}

