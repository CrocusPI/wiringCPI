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

#ifndef WIRINGCPI_H
#define WIRINGCPI_H


    
#define HIGH            1
#define LOW             0

// Threads

#define	PI_THREAD(X)	void *X (void *dummy)

// Failure modes

#define	WPI_FATAL	(1==1)
#define	WPI_ALMOST	(1==2)


#ifdef __cplusplus
extern "C" {
#endif

extern int wiringCPIFailure (int fatal, const char *message, ...);
    
extern int  wiringCPISetup(void) ;
extern int  gpioRead(int pin) ;
extern int gpioWrite(int pin, int value) ;
extern void pwmSetup(char *pwmchip,int id,int period,int duty) ;
extern int pwmEnable(void);
extern int pwmDisable(void);
extern int pwmClose(void);
extern int pwmSetPeriod(int period);
extern int pwmSetDuty(int duty);

// Threads

extern int  cpiThreadCreate(void *(*fn)(void *)) ;
extern void cpiLock(int key) ;
extern void cpiUnlock(int key) ;
// Schedulling priority

extern int cpiHiPri (const int pri) ;

// Timing
extern void         delay             (unsigned int howLong) ;
extern void         delayMicroseconds (unsigned int howLong) ;






#ifdef __cplusplus
}
#endif

#endif /* WIRINGCPI_H */

