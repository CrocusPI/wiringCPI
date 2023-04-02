#include <stdio.h>
#include <stdint.h>

#include "wiringCPI.h"
#include "softPWM.h"
#include "wiringRS485.h"
#include "wiringSPI.h"


int main(int argc, char** argv) {

    
//-gpio example
    
//    gpioWrite(148,HIGH);
//    delay(100); 
//    gpioWrite(148,LOW);

    //end gpio example
    
    //--softPWM
    
//    int i=0;
//    softPwmCreate(144,0,100);
//    softPwmDuty(144,50);
//    //softPwmWrite(144,5000);
//    delay(20000); 
//   
//    softPwmStop(144);
    //--end softPWM
    
    
    
//    //---serial
//    int fd;
//    char *data = "test";
//    char character;
//    fd = serialOpen("/dev/ttyS1",9600);
//    fflush (stdout) ;
//    serialPuts(fd,data);
//    delay(100); 
//    gpioWrite(148,LOW);  
//    while(1){
//    while (serialDataAvail (fd))
//    {
//      character = serialGetchar (fd); 
//      //printf (" -> %3d", serialGetchar (fd)) ;
//      printf (" -> %3d, %c\n\r", character,character) ;
//      fflush (stdout) ;
//    }
//    delay(3);    
//    }
//     
//    serialClose(fd);
//    ////--end serial
        
    
//    ////---RS485
//    int fd;
//    char *data = "test";
//    char character;
//    
//    fd = serialRS485Open("/dev/ttyS1",9600,148);
//    serialRS485Direction(OUT);
//    fflush (stdout) ;
//    serialRS485Puts(fd,data);
//    delay(100); 
//    serialRS485Direction(IN);
//    while(i<200){
//    while (serialRS485DataAvail (fd))
//    {
//      
//      character = serialRS485Getchar (fd); 
//      //printf (" -> %3d", serialGetchar (fd)) ;
//      printf (" -> %3d, %c\n\r", character,character) ;
//      fflush (stdout) ;
//    }
//    delay(100);   
//    i++;
//    }
//     
//    serialRS485Close(fd);
//    ////--end RS485
    
    
//    //-------PWM
//    pwmSetup("pwmchip0",0,1000000,500000);
//    pwmEnable();
//    delay(10000);
//    pwmDisable();
//    delay(10000);
//    pwmEnable();
//    delay(10000);
//    pwmSetDuty(300000);
//    delay(10000);
//    pwmSetDuty(800000);
//    delay(10000);
//    pwmDisable();
//    pwmClose();
//  //-----end PWM
    
   
 
////------------------- max6675------------------------------
//wiringCPISPISetup(1, 1000000, 0);
//short i=0;
//float temp;
//   
// while(i<50){
//    uint8_t txData[]={1,1};
//    uint8_t *rxData;
//    rxData = wiringCPISPIDataRW(txData,sizeof(txData));
//    for(int looper=0; looper<sizeof(txData); ++looper) {
//        printf("%02x ",rxData[looper]);
//    }
//    short reading = (rxData[0] << 8) + rxData[1];
//    reading >>= 3;
//    temp = reading * 0.25;  
//    printf("temp= %f\r\n",temp);
//    i++;
//    delay(300);
//    
// }
// //------------------- max6675------------------------------   
    
    
    
    return (0);
    
    
    
}

