/***************************************************************************
                          agiletimer.cpp  -  description
                             -------------------
    begin                : Fri Dec 14 2007
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

#include "agiletimer.h"
namespace SApipeline {
namespace TDS {

AGILETimer::AGILETimer(){

}
AGILETimer::~AGILETimer(){
}

}
}

/*!
    \fn SApipeline::TDS::AGILETimer::AGILETimeToUTC()
 */
string SApipeline::TDS::AGILETimer::AGILETimeToUTC(double tf)
{
  int status = 0;
  cout.setf(ios::fixed,ios::floatfield);
  SADateTime datetime; stringstream ss;
  string usga; ss.str(""); ss << tf; usga = ss.str(); 
  string usecs = usga.substr(usga.find_last_of(".")+1);
  //cout << "last_of(\".\") position = " << usga.find_last_of(".") << endl;
  //cout << "usecs string = " << usecs << endl;
  int usecti = atoi(usecs.c_str());
  if (usga.find_last_of(".")==4294967295) usecti = 0;
  //cout << "microseconds int = " << usecti << endl;
  //double usef = double(usecti);
  //cout << "usefs = " << usef << endl;
  //cout << "usefs/1000000 = " << usef/1000000 << endl;
  double temps;
  temps = double(tf+(usecti/1000000));
  return datetime.AGILETimeToUTC(temps);

}

string SApipeline::TDS::AGILETimer::AGILETimeToUTCDateTime(double tf)
{
  int status = 0;
  cout.setf(ios::fixed,ios::floatfield);
  SADateTime datetime; stringstream ss;
  string usga; ss.str(""); ss << tf; usga = ss.str(); 
  string usecs = usga.substr(usga.find_last_of(".")+1);
  //cout << "last_of(\".\") position = " << usga.find_last_of(".") << endl;
  //cout << "usecs string = " << usecs << endl;
  int usecti = atoi(usecs.c_str());
  if (usga.find_last_of(".")==4294967295) usecti = 0;
  //cout << "microseconds int = " << usecti << endl;
  //double usef = double(usecti);
  //cout << "usefs = " << usef << endl;
  //cout << "usefs/1000000 = " << usef/1000000 << endl;
  double temps;
  temps = double(tf+(usecti/1000000));
  datetime.setAGILETime(temps);
//  return datetime.AGILETimeToUTCDateTime(temps);
  return datetime.getDateTime();
}

/*!
    \fn SApipeline::TDS::AGILETimer::UTCToAGILETime()
 */
double SApipeline::TDS::AGILETimer::UTCToAGILETime(string temps2)
{
	mytime = datetime.UTCtoAgileTime(temps2);
	return mytime;
}
