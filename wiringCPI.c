/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Modified from wiringPi Library wrote by 2012 Gordon Henderson
 * https://projects.drogon.net/raspberry-pi/wiringpi/
 * *********************************************************************
 *
 *    wiringCPI is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringCPI is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringCPI.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#include <gpiod.h>
#include "wiringCPI.h"
#include "softPWM.h"

#ifndef	TRUE
#define	TRUE	(1==1)
#define	FALSE	(1==2)
#endif

// Environment Variables
#define	ENV_DEBUG	"WIRINGCPI_DEBUG"
#define	ENV_CODES	"WIRINGCPI_CODES"

int wiringCPIDebug       = FALSE ;
int wiringCPIReturnCodes = FALSE ;
const char *chipname = "gpiochip0";
static int pwmPeriod;


short int pwmid;
char *pwmchipname = "pwmchip0";

const char *cpiModel [2] =
        {
                "Unknown",
                "Zero",
        } ;

const char *cpiVersion [5] =
        {
                "Unknown",
                "1.0",
                "1.1",
                "1.2",
                "2",
        } ;



int pwmSetPeriod(int period){
    int fd ;
    char fName [128];
    char variable[32];
    pwmPeriod = period;
    sprintf (fName,"/sys/class/pwm/%s/pwm%hd/period",pwmchipname,pwmid);
    sprintf (variable,"%d",period);
    if(wiringCPIDebug)
        printf("%s set to %d\n",fName,period);
    if((fd = open (fName, O_RDWR))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmSetPeriod err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    close (fd);
    return 0;
}
int pwmSetDuty(int percentage){
    int fd ;
    char fName [128];
    char variable[32];
    if(percentage < 0)
        percentage=0;
    else if(percentage>100)
        percentage=100;
    
    sprintf (fName,"/sys/class/pwm/%s/pwm%hd/duty_cycle",pwmchipname,pwmid);
    
    sprintf (variable,"%d",(int)((percentage/100)*(float)pwmPeriod));
    if(wiringCPIDebug)
        printf("%s set to %d\n",fName,percentage);
    if((fd = open (fName, O_RDWR))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmSetDuty err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    close (fd);
     return 0;
}
int pwmEnable(){
    int fd ;
    char fName [128];
    char variable[32];
    sprintf (fName,"/sys/class/pwm/%s/pwm%hd/enable",pwmchipname,pwmid);
    sprintf (variable,"%hd",HIGH);
    if(wiringCPIDebug)
        printf("%s set to %hd\n",fName,HIGH);
    if((fd = open (fName, O_RDWR))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmEnable err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    close (fd);
     return 0;
}
int pwmSelect(){
    int fd ;
    char fName [128];
    char variable[32];
    sprintf (fName,"/sys/class/pwm/%s/export",pwmchipname);
    sprintf (variable,"%hd",pwmid);
    if(wiringCPIDebug)
        printf("%s set to %hd\n",fName,pwmid);
    if((fd = open (fName, O_WRONLY))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmSelect err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    //write(fd,"0\n",2);
    close (fd);
     return 0;
}

int pwmClose(){
    int fd ;
    char fName [128];
    char variable[32];
    sprintf (fName,"/sys/class/pwm/%s/unexport",pwmchipname);
    sprintf (variable,"%hd",pwmid);
    if(wiringCPIDebug)
        printf("%s set to %hd\n",fName,pwmid);
    if((fd = open (fName, O_WRONLY))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmClose err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    close (fd);
     return 0;
}
int pwmDisable(){
    int fd ;
    char fName [128];
    char variable[32];
    sprintf (fName,"/sys/class/pwm/%s/pwm%hd/enable",pwmchipname,pwmid);
     
    sprintf (variable,"%hd",LOW);
    if(wiringCPIDebug)
        printf("%s set to %hd\n",fName,LOW);
    if((fd = open (fName, O_RDWR))< 0)
        return wiringCPIFailure (WPI_FATAL, "wiringCPI: func: pwmDisable err: unable to open %s: %s\n", fName, strerror (errno)) ;
    write(fd,variable,strlen(variable));
    close (fd);
     return 0;
}
void pwmSetup(char *pwmchip,int id,int period,int duty){
    pwmid=id;
    pwmchipname=pwmchip;
    pwmSelect();
    pwmSetPeriod(period);
    pwmSetDuty(duty);
    
}
void pwmToneWrite (int pin, int freq){

}

int get_gpio_info(int pin){
    return 0;
}

int gpioWrite(int pin,int value){
    struct gpiod_chip *chip;
    struct gpiod_line *line;
 

    chip = gpiod_chip_open_by_name(chipname);
    line = gpiod_chip_get_line(chip, pin);
    // Open line for output
    gpiod_line_request_output(line, "writedata", 0);
    // Write value to line
    gpiod_line_set_value(line, value);
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}

int gpioWriteByte(int pin,int value){
    struct gpiod_chip *chip;
    struct gpiod_line *line;
   

    chip = gpiod_chip_open_by_name(chipname);
    line = gpiod_chip_get_line(chip, pin);
    // Open line for output
    gpiod_line_request_output(line, "writedata", 0);

    int mask = 1 ;
    for (pin = 0 ; pin < 8 ; ++pin)
    {

        delay(1);
        gpiod_line_set_value(line, value & mask);
        mask <<= 1 ;
    }
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}

int gpioRead(int pin){
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int val;

    chip = gpiod_chip_open_by_name(chipname);
    line = gpiod_chip_get_line(chip, pin);
    // Open line for input
    gpiod_line_request_input(line, "readdata");
    // Get value from Pin
    val = gpiod_line_get_value(line);
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return val;
}

int wiringCPIFail (int fatal, const char *message, ...)
{
    va_list argp ;
    char buffer [1024] ;

    if (!fatal && wiringCPIReturnCodes)
        return -1 ;

    va_start (argp, message) ;
    vsnprintf (buffer, 1023, message, argp) ;
    va_end (argp) ;

    fprintf (stderr, "%s", buffer) ;
    exit (EXIT_FAILURE) ;

    return 0 ;
}

static uint64_t epochMilli, epochMicro ;

static void initialiseEpoch (void)
{
    struct timeval tv ;

    gettimeofday (&tv, NULL) ;
    epochMilli = (uint64_t)tv.tv_sec * (uint64_t)1000    + (uint64_t)(tv.tv_usec / 1000) ;
    epochMicro = (uint64_t)tv.tv_sec * (uint64_t)1000000 + (uint64_t)(tv.tv_usec) ;
}


void delay (unsigned int millisecond)
{
    struct timespec sleeper, dummy ;

    sleeper.tv_sec  = (time_t)(millisecond / 1000) ;
    sleeper.tv_nsec = (long)(millisecond % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
}

void delayMicrosecondsHard (unsigned int microsecond)
{
    struct timeval tNow, tLong, tEnd ;

    gettimeofday (&tNow, NULL) ;
    tLong.tv_sec  = microsecond / 1000000 ;
    tLong.tv_usec = microsecond % 1000000 ;
    timeradd (&tNow, &tLong, &tEnd) ;

    while (timercmp (&tNow, &tEnd, <))
    gettimeofday (&tNow, NULL) ;
}

void delayMicroseconds (unsigned int microsecond)
{
    struct timespec sleeper ;
    unsigned int uSecs = microsecond % 1000000 ;
    unsigned int wSecs = microsecond / 1000000 ;

    /**/ if (microsecond ==   0)
        return ;
    else if (microsecond  < 100)
        delayMicrosecondsHard (microsecond) ;
    else
    {
        sleeper.tv_sec  = wSecs ;
        sleeper.tv_nsec = (long)(uSecs * 1000L) ;
        nanosleep (&sleeper, NULL) ;
    }
}
unsigned int millis (void)
{
    struct timeval tv ;
    uint64_t now ;

    gettimeofday (&tv, NULL) ;
    now  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000) ;

    return (uint32_t)(now - epochMilli) ;
}
unsigned int micros (void)
{
    struct timeval tv ;
    uint64_t now ;

    gettimeofday (&tv, NULL) ;
    now  = (uint64_t)tv.tv_sec * (uint64_t)1000000 + (uint64_t)tv.tv_usec ;

    return (uint32_t)(now - epochMicro) ;
}

int wiringCPISetup (void){

    if (getenv (ENV_DEBUG) != NULL)
        wiringCPIDebug = TRUE ;

    if (getenv (ENV_CODES) != NULL)
        wiringCPIReturnCodes = TRUE ;

   if (geteuid () != 0)
        (void)wiringCPIFailure (WPI_FATAL, "wiringCPISetup: Must be root. (Did you forget sudo?)\n") ;

    initialiseEpoch () ;
    return 0;
}


int wiringCPIFailure (int fatal, const char *message, ...)
{
  va_list argp ;
  char buffer [1024] ;

  if (!fatal && wiringCPIReturnCodes)
    return -1 ;

  va_start (argp, message) ;
    vsnprintf (buffer, 1023, message, argp) ;
  va_end (argp) ;

  fprintf (stderr, "%s", buffer) ;
  exit (EXIT_FAILURE) ;

  return 0 ;
}

