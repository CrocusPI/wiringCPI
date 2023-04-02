/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Simplified I2C access routines
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

#ifndef WIRINGI2C_H
#define WIRINGI2C_H

#ifdef __cplusplus
extern "C" {
#endif


extern int wiringCPII2CRead           (int fd) ;
extern int wiringCPII2CReadReg8       (int fd, int reg) ;
extern int wiringCPII2CReadReg16      (int fd, int reg) ;

extern int wiringCPII2CWrite          (int fd, int data) ;
extern int wiringCPII2CWriteReg8      (int fd, int reg, int data) ;
extern int wiringCPII2CWriteReg16     (int fd, int reg, int data) ;

extern int wiringCPII2CSetupInterface (const char *device, int devId) ;
extern int wiringCPII2CSetup          (const int devId) ;


#ifdef __cplusplus
}
#endif

#endif /* WIRINGI2C_H */

