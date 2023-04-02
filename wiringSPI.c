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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "wiringCPI.h"

struct spi_ioc_transfer trx;
uint32_t data32;
int speed;
int fd;



int wiringCPISPISetup(int channel, int speed_, int mode) {

    int ret; 
    int mode_=0;
    speed=speed_;
    char SPI_DEVICE[]="/dev/spidev0.00";
    
    if(channel==0)
    {SPI_DEVICE[13]='0';SPI_DEVICE[14]='\0';}
    else if(channel==1)
    {SPI_DEVICE[13]='1';SPI_DEVICE[14]='\0';}
    else if(channel==2)
    {SPI_DEVICE[13]='2';SPI_DEVICE[14]='\0';}
    else if(channel==3)
    {SPI_DEVICE[13]='3';SPI_DEVICE[14]='\0';}
    else if(channel==4)
    {SPI_DEVICE[13]='4';SPI_DEVICE[14]='\0';}
    else if(channel==5)
    {SPI_DEVICE[13]='5';SPI_DEVICE[14]='\0';}
    else if(channel==6)
    {SPI_DEVICE[13]='6';SPI_DEVICE[14]='\0';}
    else if(channel==7)
    {SPI_DEVICE[13]='7';SPI_DEVICE[14]='\0';}
    else if(channel==8)
    {SPI_DEVICE[13]='8';SPI_DEVICE[14]='\0';}
    else if(channel==9)
    {SPI_DEVICE[13]='9';SPI_DEVICE[14]='\0';}
    else if(channel==10)
    {SPI_DEVICE[13]='1';SPI_DEVICE[14]='0';SPI_DEVICE[15]='\0';}
    else if(channel==11)
    {SPI_DEVICE[13]='1';SPI_DEVICE[14]='1';SPI_DEVICE[15]='\0';}
    else if(channel==12)
    {SPI_DEVICE[13]='1';SPI_DEVICE[14]='2';SPI_DEVICE[15]='\0';}
    else if(channel==13)
    {SPI_DEVICE[13]='1';SPI_DEVICE[14]='3';SPI_DEVICE[15]='\0';}
                    
    
    mode &= 3; //mode can be 0 1 2 3
            
             printf("device %s will open\n",SPI_DEVICE);
    fd = open(SPI_DEVICE, O_RDWR);
    if(fd < 0) {
        return wiringCPIFailure (WPI_FATAL, "Could not open the SPI device...: %s\r\n", strerror (errno)) ;
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE32, &data32);
    if(ret != 0) {
        wiringCPIFailure (WPI_FATAL, "Could not read SPI mode...: %s\r\n", strerror (errno)) ;
        close(fd);
        return -1;
    }

    switch(mode){
        case 0:
            mode_ |= SPI_MODE_0;
            break;
        case 1:
            mode_ |= SPI_MODE_1;
            break;
        case 2:
            mode_ |= SPI_MODE_2;
            break;
        case 3:
            mode_ |= SPI_MODE_3;
            break;
        default:
            wiringCPIFailure (WPI_FATAL, "Wrong SPI mode...: \r\n") ;
            return -1;
    }
    
    ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode_);
    if(ret != 0) {
        wiringCPIFailure (WPI_FATAL, "Could not write SPI mode...: %s\r\n", strerror (errno)) ;
        close(fd);
         return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &data32);
    if(ret != 0) {
        wiringCPIFailure (WPI_FATAL, "Could not read the SPI max speed...: %s\r\n", strerror (errno)) ;
        close(fd);
         return -1;
    }
   
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if(ret != 0) {
        wiringCPIFailure (WPI_FATAL, "Could not write the SPI max speed...: %s\r\n", strerror (errno)) ;
        close(fd);
         return -1;
    }
    
    return 0;
	
}

unsigned char * wiringCPISPIDataRW (unsigned char *data,uint8_t length) {
    uint8_t *tx_buffer;
    static uint8_t *rx_buffer;
    tx_buffer = (uint8_t *) malloc(sizeof(uint8_t)*length);
    rx_buffer = (uint8_t *) malloc(sizeof(uint8_t)*length);
    int ret;

    tx_buffer = data;
    memset (&trx,0, sizeof (trx)) ;
    trx.tx_buf = (unsigned long)tx_buffer;
    trx.rx_buf = (unsigned long)rx_buffer;
    trx.bits_per_word = 0;
    trx.speed_hz = speed;
    trx.delay_usecs = 0;
    trx.len = length;
   

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &trx);
    if(ret != 0) {
        printf("SPI transfer returned %d...\r\n", ret);
    }
    
    return rx_buffer;
    
}
