/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Handle a serial port for RS485
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

#ifndef WIRINGRS485_H
#define WIRINGRS485_H

#ifdef __cplusplus
extern "C" {
#endif

#define OUT 1
#define IN 0

extern int   serialRS485Open      (const char *device, const int baud,unsigned int directionpin) ;
extern void  serialRS485Close     (const int fd) ;
extern void  serialRS485Flush     (const int fd) ;
extern void  serialRS485Putchar   (const int fd, const unsigned char c) ;
extern void  serialRS485Puts      (const int fd, const char *s) ;
extern void  serialRS485Printf    (const int fd, const char *message, ...) ;
extern int   serialRS485DataAvail (const int fd) ;
extern int   serialRS485Getchar   (const int fd) ;
extern void  serialRS485Direction (const int direction);

#ifdef __cplusplus
}
#endif

#endif /* WIRINGRS485_H */

