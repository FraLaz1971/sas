/***************************************************************************
                          sadatetime  -  description
                             -------------------
    begin                : mar ago 28 2007
    copyright            : (C) 2007 by Francesco Lazzarotto
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
#ifndef SADATASADATETIME_H
#define SADATASADATETIME_H

#include "hertagbase.h"
#include "timer.h"

namespace SAdata {

/**
	@author Francesco Lazzarotto <lazza@rm.iasf.cnr.it>
*/
class SADateTime : public HertagBase
{
public:
    SADateTime();

    ~SADateTime();
    void setJD( double jv);
    double getJD();
    void setMJD(double mjd);
    double getMJD();
    void setOBT(double obtval);
    double  getOBT();
    string OBTtoUTC();
    void setUTC(const string &utcstr);
    string getUTC();
    void show();
    void UTCtoOBT();
    void setDay(const string &d);
    void setDoy(const string &dy);
    void setMonth(const string &m);
    void setYear(const string &y);
    void setHour(const string &ho);
    void setMinutes(const string &mi);
    void setSeconds(const string &s);
    void setMicroSeconds(double us);
    int getYear();
    int getDay();
    int getMonth();
	int getMinutes();
    int getSeconds();
    int getHour();
    int getDoy();
    double getMicroSeconds();
    string getAGILETimeOriginUTC();
    time_t UTCtoUnixTime(const string &utc);
    double UTCtoAgileTime(const string &utc);
    string AGILETimeToUTCDateTime(double at);
    string AGILETimeToUTC(double at);
    void setAGILETime(double at);
    double AGILETimeToUnixTime(double at);
    time_t getAGILETimeOrigin();
    void constructTime(struct tm*);
    string getDateTime();
    void setDateTime(const string &dt);
    void setMJDref(double mj);
    double getMJDref();
    double getAGILETime();
    string AGILETimeToTT(double at);
    double getTTOffset();
    
	protected:
	double OBT;
	double JD; // Juilian day
	double MJD; // modified julian day
	double mjdref;	
	string UTC; // 
	string TT; // terrestrial time
	string datetime; // complete datetime in compatible format (2007-12-23T02:17:58)
	double RXTEdecmd; //RXTE decimal mission day 
	unsigned long int SwiftSS01;
	int yy;		// year string
	int mo;  // months in a year
 	int dd;		// days in a month string
	int hh;	// hours in a day field
	int mi;	// minutes in a hour field
	int ss; 	// seconds in a minute field 
	int usec;
	int doy;
	double ATseconds; // AGILE Time seconds
	double UNIXTSeconds; // UnixTime seconds
	int ATus; // Agile Time microseconds
	int UNIXTus; // Unix Time microseconds
	double ttoffset;
	stringstream mss;
	Timer timer;
};

}

#endif
