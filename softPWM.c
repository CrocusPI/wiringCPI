/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Provide 2 channels of software driven PWM.
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
#include <pthread.h>

#include "wiringCPI.h"
#include "softPWM.h"

// MAX_PINS:
//	This is more than the number of Pi pins because we can actually softPwm
//	pins that are on GPIO expanders. It's not that efficient and more than 1 or
//	2 pins on e.g. (SPI) mcp23s17 won't really be that effective, however...

#define	MAX_PINS	1024

// The PWM Frequency is derived from the "pulse time" below. Essentially,
//	the frequency is a function of the range and this pulse time.
//	The total period will be range * pulse time in µS, so a pulse time
//	of 100 and a range of 100 gives a period of 100 * 100 = 10,000 µS
//	which is a frequency of 100Hz.
//
//	It's possible to get a higher frequency by lowering the pulse time,
//	however CPU uage will skyrocket as wiringPi uses a hard-loop to time
//	periods under 100µS - this is because the Linux timer calls are just
//	accurate at all, and have an overhead.
//
//	Another way to increase the frequency is to reduce the range - however
//	that reduces the overall output accuracy...

#define	PULSE_TIME	100

static int marks         [MAX_PINS] ;
static int range         [MAX_PINS] ;
static pthread_t threads [MAX_PINS] ;

int newPin = -1 ;


/*
 * softPwmThread:
 *	Thread to do the actual PWM output
 *********************************************************************************
 */

static PI_THREAD (softPwmThread)
{
  int pin, mark, space ;
  struct sched_param param ;

  param.sched_priority = sched_get_priority_max (SCHED_RR) ;
  pthread_setschedparam (pthread_self (), SCHED_RR, &param) ;

  pin    = newPin ;
  newPin = -1 ;

  cpiHiPri (90) ;

  for (;;)
  {
    mark  = marks [pin] ;
    space = range [pin] - mark ;

    if (mark != 0)
      gpioWrite (pin, HIGH) ;
    delayMicroseconds (mark * PULSE_TIME) ;

    if (space != 0)
      gpioWrite (pin, LOW) ;
    delayMicroseconds (space * PULSE_TIME) ;
  }

  return NULL ;
}


/*
 * softPwmWrite:
 *	Write a PWM value to the given pin
 *********************************************************************************
 */

void softPwmWrite (int pin, int value)
{
  pin &= (MAX_PINS - 1) ;

  /**/ if (value < 0)
    value = 0 ;
  else if (value > range [pin])
    value = range [pin] ;

  marks [pin] = value ;
}

/*
 * softPwmDuty:
 *	Set PWM duty cycle
 *********************************************************************************
 */

void softPwmDuty (int pin, int percentage)
{
  pin &= (MAX_PINS - 1) ;

  /**/ if (percentage < 0)
    percentage = 0 ;
  else if (percentage > 100 )
    percentage = 100 ;

  //marks [pin] = (int) (range [pin] * (percentage/100)) ;
 marks [pin] = ((float)percentage/100) * range [pin];
}


/*
 * softPwmCreate:
 *	Create a new softPWM thread.
 *********************************************************************************
 */

int softPwmCreate (int pin, int initialValue, int pwmRange)
{
  int res ;
  pthread_t myThread ;

  if (range [pin] != 0)	// Already running on this pin
    return -1 ;

  if (range <= 0)
    return -1 ;

 
  gpioWrite (pin, LOW) ;

  marks [pin] = initialValue ;
  range [pin] = pwmRange ;

  newPin = pin ;
  res    = pthread_create (&myThread, NULL, softPwmThread, NULL) ;

  while (newPin != -1)
    delay (1) ;

  threads [pin] = myThread ;

  return res ;
}


/*
 * softPwmStop:
 *	Stop an existing softPWM thread
 *********************************************************************************
 */

void softPwmStop (int pin)
{
  if (range [pin] != 0)
  {
    pthread_cancel (threads [pin]) ;
    pthread_join   (threads [pin], NULL) ;
    range [pin] = 0 ;
    gpioWrite (pin, LOW) ;
  }
}
