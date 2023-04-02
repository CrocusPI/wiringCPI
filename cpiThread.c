/*
 *
 * Wiring library for Crocus PI
 * by (2023) Yusuf Yalcin Kardas
 * https://github.com/CrocusPI/wiringCPI
 *
 ***********************************************************************
 * This file is part of wiringCPI:
 *
 * Provide a simplified interface to pthreads
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

#include <pthread.h>
#include "wiringCPI.h"

static pthread_mutex_t piMutexes [4] ;



/*
 * cpiThreadCreate:
 *	Create and start a thread
 *********************************************************************************
 */

int cpiThreadCreate (void *(*fn)(void *))
{
  pthread_t myThread ;

  return pthread_create (&myThread, NULL, fn, NULL) ;
}

/*
 * cpiLock: cpiUnlock:
 *	Activate/Deactivate a mutex.
 *	We're keeping things simple here and only tracking 4 mutexes which
 *	is more than enough for out entry-level pthread programming
 *********************************************************************************
 */

void cpiLock (int key)
{
  pthread_mutex_lock (&piMutexes [key]) ;
}

void cpiUnlock (int key)
{
  pthread_mutex_unlock (&piMutexes [key]) ;
}

