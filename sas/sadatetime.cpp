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
#include "sadatetime.h"

namespace SAdata {

SADateTime::SADateTime()
 : HertagBase()
{
	mjdref = 53005.00075444444444444;
	verbose = HertagBase::verbose;
}


SADateTime::~SADateTime()
{
}


}


/*!
    \fn SAdata::SADateTime::setJD( duble jv)
 */
void SAdata::SADateTime::setJD( double jv)
{
    JD = jv;
}


/*!
    \fn SAdata::SADateTime::method_1()
 */
double SAdata::SADateTime::getJD()
{
    return JD;
}


/*!
    \fn SAdata::SADateTime::setMJD(double mjd)
 */
void SAdata::SADateTime::setMJD(double mjd)
{
    MJD = mjd;
}


/*!
    \fn SAdata::SADateTime::getMJD()
 */
double SAdata::SADateTime::getMJD()
{
    return MJD;
}


/*!
    \fn SAdata::SADateTime::setOBT(double obtval)
 */
void SAdata::SADateTime::setOBT(double obtval)
{
    OBT = obtval;
}


/*!
    \fn SAdata::SADateTime::getOBT()
 */
double SAdata::SADateTime::getOBT()
{
    return OBT;
}


/*!
    \fn SAdata::SADateTime::OBTtoUTC()
 */
string SAdata::SADateTime::OBTtoUTC()
{
    return tempstring;
}


/*!
    \fn SAdata::SADateTime::setUTC(const string &utcstr)
	accept in input a string with the following format
	<year>/<month>/day <hh>:<mm>:<ss>
	example 2007/10/16 15:25:44
 */
void SAdata::SADateTime::setUTC(const string &utcstr)
{
    UTC = utcstr;
	setYear(UTC.substr(0, 4));
	setMonth(UTC.substr(5, 2));
	setDay(UTC.substr(8, 2));
	setHour(UTC.substr(11, 2));
	setMinutes(UTC.substr(14, 2));
	setSeconds(UTC.substr(17, 2));
	setMicroSeconds(0.);
	//show();
}


/*!
    \fn SAdata::SADateTime::getUTC()
 */
string SAdata::SADateTime::getUTC()
{
    return UTC;
}


/*!
    \fn SAdata::SADateTime::show()
 */
void SAdata::SADateTime::show()
{
	string ht("");
	string mo(""), da(""), ho(""), mi(""), se("");
	stringstream ff;
   	cout << "SADateTime::show() "<< endl;
//	showAlert();
    	cout << "SADateTime::show() Julian Day = "<< getJD() << endl;	
    	cout << "SADateTime::show() Modified Julian Day = "<< getMJD() << endl;
    	cout << "SADateTime::show() On Board Time"<< getOBT() << endl;
    	cout << "SADateTime::show() Universal Time Coordinate = "<< getUTC() << endl;
	cout << "SADateTime::show() Year = "<< getYear() << endl;
	cout << "SADateTime::show() Month = "<< getMonth() << endl;
	cout << "SADateTime::show() Day = "<< getDay() << endl;
	cout << "SADateTime::show() Day of year = "<< getDoy() << endl;
//	ff.str(""); ff << getHour(); ht = ff.str();
//	cout << "ht.size()" << ht.size() << endl;
//	if (ht.size()==1) ff.str(""); ff << "0" << ht; 
	cout << "SADateTime::show() hour = " << ff.str() << endl;	 
	cout << "SADateTime::show() Hour = "<< getHour() << endl;
	cout << "SADateTime::show() Min = "<< getMinutes() << endl;
	cout << "SADateTime::show() Sec = "<< getSeconds() << endl;
	cout << "SADateTime::show() MicroSec = "<< getMicroSeconds() << endl;
	
	ff.str(""); ff << getMonth(); ht = ff.str();
	if (ht.size()==1) {ff.str(""); ff << "0" << ht; mo = ff.str(); }else {
		mo = ht;
	}  
	 
	ht = "";ff.str(""); ff << getDay(); ht = ff.str();
	if (ht.size()==1) {ff.str(""); ff << "0" << ht; da = ff.str();}else {
		da = ht;
	}  
	
	ht = "";ff.str(""); ff << getHour(); ht = ff.str();
	if (ht.size()==1){ ff.str(""); ff << "0" << ht; ho = ff.str(); } else {
		ho = ht;
	} 
	
	ht = "";ff.str(""); ff << getMinutes(); ht = ff.str();
	if (ht.size()==1) {
	ff.str(""); ff << "0" << ht; mi = ff.str(); 
	} else {
		mi = ht;
	} 
	
	ht = "";ff.str(""); ff << getSeconds(); ht = ff.str();
	if (ht.size()==1) {
	ff.str(""); ff << "0" << ht; se = ff.str();
	} else {
		se = ht;
	} 
	
	cout << "SADateTime::show() datetime = "<< getDateTime() << endl;
	
    cout << "SADateTime::show() "<< endl;
}


/*!
    \fn SAdata::SADateTime::UTCtoOBT()
 */
void SAdata::SADateTime::UTCtoOBT()
{
/*	$hh = $_POST['time_ut_hh'];
	$mm = $_POST['time_ut_mm'];
	$ss = $_POST['time_ut_ss'];
	$yy = $_POST['time_ut_yy'];
	$mt = $_POST['time_ut_mt'];
	$dd = $_POST['time_ut_dd'];
	$a = floor((14. - $mt)/12.);
	$y = $yy + 4800. - $a;
	$m = $mt + 12.*$a - 3.0;
	$JDN = $dd + floor((153.*$m + 2)/5.) + 365 * $y + floor($y/4.) - floor($y/100.) + floor($y/400.) - 32045.;
	$JD = $JDN + ($hh-12.)/24. + ($mm/1440.) + ($ss/86400.) - 2400000.5;
	$appo = ($JD - 53005.0)* (24.0*3600.0);
*/
}


/*!
    \fn SAdata::SADateTime::setYear(const string &y)
 */
void SAdata::SADateTime::setYear(const string &y)
{
    yy = atoi(y.c_str());
}


/*!
    \fn SAdata::SADateTime::setMonth(const string &m)
 */
void SAdata::SADateTime::setMonth(const string &m)
{
    mo = atoi(m.c_str());
}


/*!
    \fn SAdata::SADateTime::setDay(const string &d)
 */
void SAdata::SADateTime::setDay(const string &d)
{
    dd = atoi(d.c_str());
}


/*!
    \fn SAdata::SADateTime::setHour(const string &ho)
 */
void SAdata::SADateTime::setHour(const string &ho)
{
    hh = atoi(ho.c_str());
}


/*!
    \fn SAdata::SADateTime::setMinutes(const string &mi)
 */
void SAdata::SADateTime::setMinutes(const string &m)
{
    mi = atoi(m.c_str());
}


/*!
    \fn SAdata::SADateTime::setSeconds(const string &s)
 */
void SAdata::SADateTime::setSeconds(const string &s)
{
    ss = atoi(s.c_str());
}


/*!
    \fn SAdata::SADateTime::setMicroSeconds(double us)
 */
void SAdata::SADateTime::setMicroSeconds(double us)
{
    usec = us;
}


/*!
    \fn SAdata::SADateTime::getYear()
 */
int SAdata::SADateTime::getYear()
{
    return yy;
}


/*!
    \fn SAdata::SADateTime::getMonth()
 */
int SAdata::SADateTime::getMonth()
{
	return mo;
}


/*!
    \fn SAdata::SADateTime::getDay()
 */
int SAdata::SADateTime::getDay()
{
    return dd;
}


/*!
    \fn SAdata::SADateTime::getHour()
 */
int SAdata::SADateTime::getHour()
{
	return hh;
}

/*!
    \fn SAdata::SADateTime::getSeconds()
 */
int SAdata::SADateTime::getMinutes()
{
	return mi;
}

/*!
    \fn SAdata::SADateTime::getSeconds()
 */
int SAdata::SADateTime::getSeconds()
{
	return ss;
}
/*!
    \fn SAdata::SADateTime::getDoy()
 */
int SAdata::SADateTime::getDoy()
{
	return doy;
}


/*!
    \fn SAdata::SADateTime::getMicroSeconds()
 */
double SAdata::SADateTime::getMicroSeconds()
{
    return usec;
}


/*!
    \fn SAdata::SADateTime::getAGILETimeUTC()
 */
string SAdata::SADateTime::getAGILETimeOriginUTC()
{
    // set UNIX time of AGILE Time
	//	timer.setUnixTimeSec(315964814);
	// show the UTC of the AGILE Time origin
//	timer.setVerbose(true);
	time_t s = 315964814;
	tempstring = 	timer.getDateTimeString(s);
	//cout << "AGILE time origin = " << tempstring << endl;
	return tempstring;
}


/*!
    \fn SAdata::SADateTime::UTCtoUnixTime()
 */
time_t SAdata::SADateTime::UTCtoUnixTime(const string &utc)
{
    setUTC(utc);
	struct tm time_struct;
	struct tm utc_time_struct;
	time_t loc;
/*
  char days[7][4]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

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

  time_struct.tm_year=getYear()-1900;
  time_struct.tm_mon=getMonth()-1;
  time_struct.tm_mday=getDay();
  time_struct.tm_sec=getSeconds();
  time_struct.tm_min=getMinutes();
  time_struct.tm_hour=getHour();
  time_struct.tm_isdst=-1;

  if(mktime(&time_struct)==-1)
   {
    printf("Error getting time.\n");
    exit(0);
   }
	loc = mktime(&time_struct);
    const time_t cloct = loc; 
	// extract the hour strings
    //cout << "ctime(cloct) --> local time string = " << ctime( &cloct ) << endl;
    //cout << "ctime(cloct) --> local time = " << cloct  << endl;
	utc_time_struct = *gmtime(&loc);
	string h1, h2;
	int hi1, hi2;
	string s1(asctime(&time_struct));
	h1 = s1.substr(11, 2); 
    //cout << "h1 = " << h1 << endl;
	string s2(asctime(&utc_time_struct)); 
	h2 = s2.substr(11, 2); 
    //cout << "h2 = " << h2 << endl;
	// control if there is legal hour
	const char * hc1 = h1.c_str(); 
	const char * hc2 = h2.c_str(); 
    //cout << "hc1 = " << hi1 << endl;
    //cout << "hc2 = " << hi2 << endl;
	hi1 = atoi(hc1); 	hi2 = atoi(hc2); 
    //cout << "hi1 = " << hi1 << endl;
    //cout << "hi2 = " << hi2 << endl;
	int offset;
    if (hi1 < hi2) hi1 += 24;
    //cout << "hi1 - hi2 = " << hi1 - hi2  << endl;
	switch(hi1-hi2){
	case 1:
	    //cout << "there is not legal hour "   << endl;	
		offset = -3600;	
	break;
	case 2:
	    //cout << "there is the legal hour "   << endl;
		offset = 0;	
	break;
	default:
	    //cout << "is not Rome Time zone! "   << endl;
	break;
	}
    const tm btc = utc_time_struct; 
    //cout << "asctime(utc_time_struct) --> UTC time = " << asctime(&utc_time_struct) << endl;
    //const time_t gloct = mktime(&utc_time_struct); 
    //cout << "ctime(gloct) --> UTC time = " << gloct  << endl;
 	// struct tm *gmtime(const time_t *timer);
	time_t result;

       //cout << " mktime(&time_struct) = " << mktime(&time_struct)  << endl;
       //cout << " mktime(&utc_time_struct) = " << mktime(&utc_time_struct)  << endl;
       //cout << " cloct - gloct = " << cloct - gloct  << endl;
       //cout << " time_struct.tm_hour = " << time_struct.tm_hour   << endl;
       //cout << " utc_time_struct.tm_hour = " << utc_time_struct.tm_hour   << endl;
       //cout << " hours diff. = " << time_struct.tm_hour - utc_time_struct.tm_hour  << endl;
       //cout << " hours diff. = " << time_struct.tm_hour - utc_time_struct.tm_hour  << endl;
/*	if (gloct==cloct){
		result = mktime(&time_struct) + 3600;
	}	else {
		result = mktime(&utc_time_struct)+ 7200;
	}*/
		//result = cloct + (cloct - gloct);
	result = cloct + offset;
	//if (result < 0) result = 0;
	return result;
}


/*!
    \fn SAdata::SADateTime::UTCtoAgileTime(const string &utc)
 */
double SAdata::SADateTime::UTCtoAgileTime(const string &utc)
{
	double temps;
    // get unix time of utc	1072821600
	// agiletime(utc) = UnixTime(utc) - UnixTime(AGILEOrigin)
	temps = double(UTCtoUnixTime(utc) - getAGILETimeOrigin());
	// calcola la differenza fra AGILETime & UnixTime
	
	return temps+usec/1000000;
}

/*!
    \fn SAdata::SADateTime::AGILETimeToUnixTime(double at)
 */
double SAdata::SADateTime::AGILETimeToUnixTime(double at)
{
	setAGILETime(at);
	double temp = 1072915200 + ATseconds;
	return temp;
}
/*!
    \fn SAdata::SADateTime::AGILETimeToUTC(double at)
 */
string SAdata::SADateTime::AGILETimeToUTC(double at)
{
    /// @todo implement me
	//cout << "AGILETimeOrigin = " << getAGILETimeOrigin() << endl;
	setAGILETime(at);
	double r = 0.;
	double temp = 1072915200 + ATseconds;
	//cout << "usec = " << getMicroSeconds() << endl;
	/*
	if ((usec/100000)> 5) {
		r = 1.;
	//	cout << "rounding usec to 1 sec" << endl;
	} else {	
	//	cout << "rounding usec to 0 sec" << endl;	
	}
	temp += r;
	*/
	tempstring =  timer.getDateTimeString(temp);
	stringstream sp;
	sp.str("");sp<<ATus; tempstring2 = sp.str();
	tempstring += "_"+tempstring2;
	return tempstring;
}

string SAdata::SADateTime::AGILETimeToTT(double at)
{
    /// @todo implement me
	cout << "executing SADateTime::AGILETimeToTT() AGILETimeOrigin = " << getAGILETimeOrigin() << endl;
	setAGILETime(at+getTTOffset());
	double r = 0.;
	double temp = 1072915200 + ATseconds;
	if (verbose) cout << "SADateTime::AGILETimeToTT() usec = " << getMicroSeconds() << endl;
	if ((usec/100000)> 5) {
		r = 1.;
		if (verbose) cout << "SADateTime::AGILETimeToTT() rounding usec to 1 sec" << endl;
	} else {	
		if (verbose) cout << "SADateTime::AGILETimeToTT() rounding usec to 0 sec" << endl;	
	}
	temp += r;
	tempstring =  timer.getDateTimeString(temp);
	stringstream sp;
	sp.str("");sp<<ATus; tempstring2 = sp.str();
	tempstring += "_"+tempstring2;
	return tempstring;
}

/*!
    \fn SAdata::SADateTime::setAGILETime(double at)
 */
void SAdata::SADateTime::setDoy(const string &dy){
	doy = atoi(dy.c_str());
}

/*!
    \fn SAdata::SADateTime::setAGILETime(double at)
 */
void SAdata::SADateTime::setAGILETime(double at)
{
    	unsigned long int atint = floor(at);
	ATus = int(1000000*(at - double(atint) )+0.5);
	ATseconds = at-(at - double(atint));
	double temp = 1072915200 + ATseconds;
	timer.setUnixTimeSec(temp);
    	const time_t t = timer.getUnixTime();
    	const time_t nt = ATseconds + 1072915200;
 	struct tm time_struct = *gmtime(&nt);
	constructTime(&time_struct);
	if (verbose) cout << "SADateTime::setAGILETime() at = " << at  << endl;
	if (verbose) cout << "SADateTime::setAGILETime() atint = " << atint  << endl;
	if (verbose) cout << "SADateTime::setAGILETime() ATseconds = " << ATseconds  << endl;
	if (verbose) cout << "SADateTime::setAGILETime() ATus = " << ATus << endl;
}


/*!
    \fn SAdata::SADateTime::getAGILETimeOrigin()
 */
time_t SAdata::SADateTime::getAGILETimeOrigin()
{
	struct tm time_struct;
	struct tm utc_time_struct;
	time_t loc;
/*
  char days[7][4]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

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

  time_struct.tm_year=2004-1900;
  time_struct.tm_mon=0;
  time_struct.tm_mday=1;
  time_struct.tm_sec=0;
  time_struct.tm_min=0;
  time_struct.tm_hour=0;
  //time_struct.tm_yday=0; 
  time_struct.tm_isdst=-1;

  if(mktime(&time_struct)==-1)
   {
    printf("Error getting time.\n");
    exit(0);
   }
	loc = mktime(&time_struct);
    const time_t cloct = loc; 
    //cout << "ctime(loc) AGILE Time Origin--> local time = " << ctime( &cloct ) << endl;
	utc_time_struct = *gmtime(&loc);
    const tm btc = utc_time_struct; 
    //cout << "asctime(utc_time_struct) AGILE Time Origin --> UTC time = " << asctime(&utc_time_struct) << endl;
//	 struct tm *gmtime(const time_t *timer);
	return mktime(&utc_time_struct);
}


/*!
    \fn SAdata::SADateTime::constructTime(struct tm*)
 */
void SAdata::SADateTime::constructTime(struct tm* mtm)
{
/*
         int tm_sec;    // seconds after the minute (0 to 61) 
         int tm_min;    // minutes after the hour (0 to 59) 
         int tm_hour;   // hours since midnight (0 to 23) 
         int tm_mday;   // day of the month (1 to 31) 
         int tm_mon;    // months since January (0 to 11) 
         int tm_year;   // years since 1900 
         int tm_wday;   // days since Sunday (0 to 6 Sunday=0) 
         int tm_yday;   // days since January 1 (0 to 365) 
         int tm_isdst;  // Daylight Savings Time 

  time_struct.tm_year=2004-1900;
  time_struct.tm_mon=0;
  time_struct.tm_mday=1;
  time_struct.tm_sec=0;
  time_struct.tm_min=0;
  time_struct.tm_hour=0;
  
*/
	string ht("");
	string mo(""), da(""), ho(""), mi(""), se("");
	stringstream ff;

	mss.str(""); mss<<mtm->tm_mday;
    setDay(mss.str());
	mss.str(""); mss<<mtm->tm_yday+1;
    setDoy(mss.str());
	mss.str(""); mss<<mtm->tm_mon+1;
    setMonth(mss.str());
	mss.str(""); mss<<mtm->tm_year+1900;
    setYear(mss.str());
	mss.str(""); mss<<mtm->tm_hour;
    setHour(mss.str());
	mss.str(""); mss<<mtm->tm_min;
    setMinutes(mss.str());
	mss.str(""); mss<<mtm->tm_sec;
    setSeconds(mss.str());
	if (verbose) cout << "SADateTime::constructTime() AGILETime usecs = " <<  ATus << endl;  
    setMicroSeconds(ATus);
	ff.str(""); ff << getMonth(); ht = ff.str();
//	cout << "ht = "<< ht << "ht.size() "<< ht.size() << endl;
	if (ht.size()==1) {ff.str(""); ff << "0" << ht; mo = ff.str(); }else {
		mo = ht;
	}  
	 
	ht = "";ff.str(""); ff << getDay(); ht = ff.str();
//	cout << "ht = "<< ht << "ht.size() "<< ht.size() << endl;
	if (ht.size()==1) {ff.str(""); ff << "0" << ht; da = ff.str();}else {
		da = ht;
	}  
	
	ht = "";ff.str(""); ff << getHour(); ht = ff.str();
//	cout << "ht = "<< ht << "ht.size() "<< ht.size() << endl;
	if (ht.size()==1){ ff.str(""); ff << "0" << ht; ho = ff.str(); } else {
		ho = ht;
	} 
	
	ht = "";ff.str(""); ff << getMinutes(); ht = ff.str();
//	cout << "ht = "<< ht << "ht.size() "<< ht.size() << endl;
	if (ht.size()==1) {
	ff.str(""); ff << "0" << ht; mi = ff.str(); 
	} else {
		mi = ht;
	} 
	
	ht = "";ff.str(""); ff << getSeconds(); ht = ff.str();
//	cout << "ht = "<< ht << "ht.size() "<< ht.size() << endl;
	if (ht.size()==1) {
	ff.str(""); ff << "0" << ht; se = ff.str();
	} else {
		se = ht;
	} 
	
	ff.str("");ff << getYear() << "-" << mo << "-" << da << "T" << ho << ":" <<mi << ":" << se;
	setDateTime(ff.str());
	if (verbose) cout << "SADateTime::constructTime() AGILETime usecs = " <<  ATus << endl;  
	double thistime =  getAGILETime();
	if (verbose) cout << "SADateTime::constructTime() AGILETime (sec+usecs) = " << thistime << endl;  
	thistime = thistime/86400; 
	thistime +=getMJDref();
	setMJD(thistime);
	if (verbose) cout << "SADateTime::constructTime() MJD = " << getMJD() << endl;  
}



/*!
    \fn SAdata::SADateTime::getDateTime()
 */
string SAdata::SADateTime::getDateTime()
{
    return datetime;
}


/*!
    \fn SAdata::SADateTime::setDateTime(const string &dt)
 */
void SAdata::SADateTime::setDateTime(const string &dt)
{
    datetime = dt;
}


/*!
    \fn SAdata::SADateTime::setMJDref(double mj)
 */
void SAdata::SADateTime::setMJDref(double mj)
{
    mjdref = mj;
}


/*!
    \fn SAdata::SADateTime::getMJDref()
 */
double SAdata::SADateTime::getMJDref()
{
    return mjdref;
}


/*!
    \fn SAdata::SADateTime::getAGILETime()
 */
double SAdata::SADateTime::getAGILETime()
{
    if (verbose) cout << "SADateTime::getAGILETime() ATseconds = "<< ATseconds << endl;
    if (verbose) cout << "SADateTime::getAGILETime() ATus = "<< ATus << endl;
    return ATseconds + (double(ATus)/1000000);
}

double SAdata::SADateTime::getTTOffset()
{
    ttoffset = 65.;
    return ttoffset;
}

string SAdata::SADateTime::AGILETimeToUTCDateTime(double at)
{
	cout << "SADateTime::AGILETimeToUTCDateTime() executing "<< endl;
	setAGILETime(at);
	double temp = 1072915200 + ATseconds;
	tempstring =  timer.getUTCDateTimeString(temp);
	stringstream sp;
	sp.str("");sp<<ATus; tempstring2 = sp.str();
	tempstring += "_"+tempstring2;
	return tempstring;
}

