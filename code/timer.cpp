/***************************************************************************
                          timer.cpp  -  description
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

#include "timer.h"

Timer::Timer(){
  verbose = false;
}
Timer::~Timer(){
}
/** No descriptions */
void Timer::start(){
  start_time = time(NULL);
  cout << "start time = " << asctime(localtime(&start_time)) << endl;
}
/** No descriptions */
void Timer::stop(){
  stop_time = time(NULL);
  cout << "stop time = " << asctime(localtime(&stop_time)) << endl;
}
/** No descriptions */
void Timer::report(){
  int ts = 0;  int tsr = 0;  int tm = 0;
  ts = difftime(stop_time, start_time);
  tm = int(ts/60);
  tsr = ts%60;
  //cout << "elapsed time (sec.) " << difftime(stop_time, start_time) << " min "<< tm << " sec "<< tsr << endl;
  cout << "elapsed time:  " << difftime(stop_time, start_time) << " sec \n"<< tm  << " min "<< tsr << " sec "<<  endl;
}
/** No descriptions */
string Timer::getDateString(){
             /* Calender time is the number of seconds since 1/1/1970   	*/

  date_time = time((time_t *)NULL);		/* Get the system time and put it
                                             					 * into 'date_time' as 'calender time' */
  struct tm *l_time;

  l_time = gmtime(&date_time);		 /* Convert 'calender time' to
					                                          * 'local time' - return a pointer
					                                          * to the 'tm' structure. localtime
					                                          * reserves the storage for us.	*/
  stringstream ss; ss << asctime(l_time);
  tempstring = ss.str();        
  string str1 = tempstring;
  int stringcrs = 1;
   string::size_type loc;
   
  if (verbose) cout << "Timer::getDateString() original date string is "<< str1 << endl;

  while (stringcrs<str1.length()){
    loc = str1.find_first_of(" ", stringcrs );    
    if( loc != string::npos ){
      //cout << "Found blank at" << loc << endl;
      str1.replace(loc, 1, "_", 1);
    }
    else{
      //cout << "Didn't find blank" << endl;
    }
    stringcrs++;
  }
  
  loc = str1.find_first_of("\n", 0 );
  string temps;
  str1.replace(loc, 1, "", 0);
    
  if (verbose) cout << "Timer::getDateString() now the string is "<< str1 << endl;
  tempstring = str1;
  //tempstring = "debugstring";
  return tempstring;
}


/*!
    \fn Timer::setUnixTimeSec(unsigned long int)
 */
void Timer::setUnixTimeSec(time_t t)
{
    unix_time_secs = t;
	start_time = t;
}
/*!
    \fn Timer::getUTCDateString(time_t t)
 */

string Timer::getUTCDateTimeString(time_t t)
{
 //date_time = time((time_t *)&t);		// Get the system time and put it
  date_time = t;                                //  * into 'date_time' as 'calender time' 

  if (verbose) cout << "I have set date_time = " << date_time << endl;
  struct tm *l_time;

  l_time = gmtime(&date_time);		 				/* 
					                                          * 'gmtime' - return a pointer
					                                          * to the 'tm' structure. gmtime
					                                          * reserves the storage for us.	*/
  stringstream ss; ss << asctime(l_time);
  tempstring = ss.str();        
  string str1 = tempstring;
  int stringcrs = 1;
   string::size_type loc;
   
   cout << "Timer::getUTCDateTimeString() original (UTC) date string is "<< str1 << endl;

  while (stringcrs<str1.length()){
    loc = str1.find_first_of(" ", stringcrs );    
    if( loc != string::npos ){
      //cout << "Found blank at" << loc << endl;
      str1.replace(loc, 1, "_", 1);
    }
    else{
      //cout << "Didn't find blank" << endl;
    }
    stringcrs++;
  }
  
  loc = str1.find_first_of("\n", 0 );
  string temps;
  str1.replace(loc, 1, "", 0);
    
  if (verbose) cout << "Timer::getUTCDateTimeString() now the string is "<< str1 << endl;
  tempstring = str1;
  //tempstring = "debugstring";
  return tempstring;
}

/*!
    \fn Timer::getDateString(time_t t)
 */
string Timer::getDateTimeString(time_t t)
{
             /* Calender time is the number of seconds since 1/1/1970   	*/

  //date_time = time((time_t *)&t);		// Get the system time and put it
  date_time = t;                                //  * into 'date_time' as 'calender time' 

  if (verbose) cout << "I have set date_time = " << date_time << endl;
  struct tm *l_time;

  l_time = gmtime(&date_time);		 				/* 
					                                          * 'gmtime' - return a pointer
					                                          * to the 'tm' structure. gmtime
					                                          * reserves the storage for us.	*/
  stringstream ss; ss << asctime(l_time);
  tempstring = ss.str();        
  string str1 = tempstring;
  int stringcrs = 1;
   string::size_type loc;
   
  if (verbose) cout << "Timer::getDateString() original (UTC) date string is "<< str1 << endl;

  while (stringcrs<str1.length()){
    loc = str1.find_first_of(" ", stringcrs );    
    if( loc != string::npos ){
      //cout << "Found blank at" << loc << endl;
      str1.replace(loc, 1, "_", 1);
    }
    else{
      //cout << "Didn't find blank" << endl;
    }
    stringcrs++;
  }
  
  loc = str1.find_first_of("\n", 0 );
  string temps;
  str1.replace(loc, 1, "", 0);
    
  if (verbose) cout << "Timer::getDateString() now the string is "<< str1 << endl;
  tempstring = str1;
  //tempstring = "debugstring";
  return tempstring;
}


/*!
    \fn Timer::setVerbose(double v)
 */
void Timer::setVerbose(double v)
{
    verbose = v;
}


/*!
    \fn Timer::UTCtoUnixTime(const string &UTC)
 */
void Timer::UTCtoUnixTime(const string &UTC)
{


}


/*!
    \fn Timer::getUnixTime()
 */
time_t Timer::getUnixTime()
{
    return date_time;
}
