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


#ifndef SOFTPWM_H
#define SOFTPWM_H

#ifdef __cplusplus
extern "C" {
#endif

extern int  softPwmCreate (int pin, int value, int range) ;
extern void softPwmWrite  (int pin, int value) ;
extern void softPwmStop   (int pin) ;
extern void softPwmDuty (int pin, int percentage);


#ifdef __cplusplus
}
#endif

#endif /* SOFTPWM_H */

