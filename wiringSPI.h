/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Simplified SPI access routines
 *
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


#ifndef WIRINGSPI_H
#define WIRINGSPI_H

#ifdef __cplusplus
extern "C" {
#endif

int wiringCPISPISetup(int channel, int speed, int mode);
unsigned char * wiringCPISPIDataRW (unsigned char *data,uint8_t length);

#ifdef __cplusplus
}
#endif

#endif /* WIRINGSPI_H */

