/***************************************************************************
                          agiledbconnector.cpp  -  description
                             -------------------
    begin                : Wed Oct 11 2006
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

#include "agiledbconnector.h"
namespace DB {
AGILEDBConnector::AGILEDBConnector(){

}

AGILEDBConnector::AGILEDBConnector(vector <string> connstring) :
DBConnector::DBConnector(connstring) 
{

}


AGILEDBConnector::~AGILEDBConnector(){

}
/** No descriptions */


}

/*!
    \fn DB::AGILEDBConnector::getL2file(int contactnum)
 */
string DB::AGILEDBConnector::getL2fileName(int contactnum)
{
	// only for debug
    tempstring = "";
    return tempstring;
}


pair<double, double> DB::AGILEDBConnector::getTimeInterval(int contactmin, int contactmax)
{
    /// @todo implement me
	vector<string> dbcs ;
	dbcs.push_back("QMYSQL3");
	dbcs.push_back("test2");
	dbcs.push_back("agiledb");
	dbcs.push_back("superflight");
	dbcs.push_back("bigfoot.iasf-roma.inaf.it");

    DBConnector *db1;
    
    db1 = new DBConnector(dbcs);
    
    
    pair <double, double> tint;
    
    vector<string> tmi;
    vector<string> tma;
//    select tstop from 'ContactTable' where contactnumber =
    // create the query that extract tstart
//    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << (contactmin - 1);
    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmin;
    string smiq = ss.str();
    cout << "AGILEDBConnector::getTimeInterval() going to execute " << smiq << endl;
    cout << "AGILEDBConnector::getTimeInterval() bench1"<< endl;
    
    // execute the first query and retrieve output string value
    tmi = db1->executeSQLQuery(smiq, 1);
    //tmi.push_back("2007-12-31T00:46:20");
    // create the query that extract tstop    
    //    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmax;
    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmax;
    string smaq = ss.str();
    cout << "AGILEDBConnector::getTimeInterval() going to execute " << smaq << endl;
    // execute the second query and retrieve output string value
    tma = db1->executeSQLQuery(smaq, 1);
    cout << "AGILEDBConnector::getTimeInterval() bench2" << endl;
    tma.push_back("2007-12-31T00:46:20");
    SADateTime sdt;
    string temps1 = tmi[0];
    string temps2 = tma[0];
    string t("");
    cout << "AGILEDBConnector::getTimeInterval() bench3" << endl;
    
    ss.str(""); ss << sdt.UTCtoAgileTime(temps1) << endl;
    t = ss.str(); tint.first = atof(t.c_str());
    cout << "AGILEDBConnector::getTimeInterval() bench4" << endl;
    
    ss.str(""); ss << sdt.UTCtoAgileTime(temps2) << endl;
    t = ss.str(); tint.second = atof(t.c_str());
    cout << "AGILEDBConnector::getTimeInterval() bench5" << endl;
	
    tint.second = atof(tma[0].c_str());
    cout << "AGILEDBConnector::getTimeInterval() bench6" << endl;
    delete db1;
    /*
    	select tstop where contactnumber = (contactmin - 1))
	select tstop where contactnumber = (contactmax ))
    */
    return tint;
}


/*!
    \fn DB::AGILEDBConnector::setSasoaStatusOnDB(int contact, string task)
 */
void DB::AGILEDBConnector::setSasoaStatusOnDB(int contact, string task)
{
  ss.str(""); ss << "setStatusOnDB.sh " << contact << " " << task << endl; 
  ts = ss.str(); ss.str("");
  cout << "executing " << ts << endl;
  system(ts.c_str());
}
