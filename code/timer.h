/***************************************************************************
                          timer.h  -  description
                             -------------------
    begin                : Mon Mar 27 2006
    copyright            : (C) 2006 by Francesco Lazzarotto
    email                : lazza@rm.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

/**
  *@author Francesco Lazzarotto
  */

/*
     NULL is the value of a null pointer constant.
    CLOCKS_PER_SEC is the number of processor clocks per second.

    size_t is the unsigned integer result of the sizeof keyword.
    clock_t is a type suitable for storing the processor time.
    time_t is a type suitable for storing the calendar time.

    struct tm is a structure used to hold the time and date. Its members are as follows:

         int tm_sec;    // seconds after the minute (0 to 61) 
         int tm_min;    // minutes after the hour (0 to 59) 
         int tm_hour;   // hours since midnight (0 to 23) 
         int tm_mday;   // day of the month (1 to 31) 
         int tm_mon;    // months since January (0 to 11) 
         int tm_year;   // years since 1900 
         int tm_wday;   // days since Sunday (0 to 6 Sunday=0) 
         int tm_yday;   // days since January 1 (0 to 365) 
         int tm_isdst;  // Daylight Savings Time 

*/

using namespace std;

class Timer {
public: 
	Timer();
	~Timer();
  /** No descriptions */
  void report();
  /** No descriptions */
  void stop();
  /** No descriptions */                     
  void start();
  /** No descriptions */
  string getDateString();
  void setUnixTimeSec(time_t t);
    string getDateTimeString(time_t t);
    string getUTCDateTimeString(time_t t);
    void setVerbose(double v);
    void UTCtoUnixTime(const string &UTC);
    time_t getUnixTime();
  
  protected:
  time_t start_time;	        // define start time time_t
  time_t stop_time;         	// define 'now'.
  time_t date_time;          // time of an event 
  string date;
  string tempstring;
  bool verbose;
  time_t unix_time_secs;

};

#endif
