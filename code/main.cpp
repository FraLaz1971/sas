/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Tue Mar 21 13:02:28 CET 2006
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef   IOSTREAM_H
#include <iostream>
#endif

#ifndef SASOAUSERINTERFACE_H
#include <string>
#include <string>
#include <CCfits>
#include <saexception.h>
#include <FITS.h>
#include "tdsdaemon.h"
#include "sasoahandler.h"
#include "sadatetime.h"
#include "agiledbconnector.h"
#include "saephemerisdata.h"
#include "sadatacorrector.h"

using namespace CCfits;
using namespace SApipeline;
using namespace TDS;
using namespace DB;
using namespace SAExceptions;
using namespace std;

int main(int argc, char** argv)
{
  int status;
  string compare, batchline;
  cout << "this is a SAS based program"  << endl;
SasoaHandler s;
s.deliverEphFile();
 

   	AGILEDBConnector *dbp;

	vector<string> dbcs ;
	dbcs.push_back("QMYSQL3");
	dbcs.push_back("test2");
	dbcs.push_back("agiledb");
	dbcs.push_back("superflight");
	dbcs.push_back("bigfoot.iasf-roma.inaf.it");


	cout << "here 1 !!! "<< endl;

    string tempstring;    int nf = 6;
	cout << "here 2 !!! "<< endl;
    pair<double, double> md;    
	cout << "here 3 !!! "<< endl;
    md.first = 0.;    md.second = 0.;        vector<string> v;

	cout << "here 4 !!! "<< endl;
	int a = 2501;
       QApplication *aa = new QApplication(argc, argv);


  try{

	dbp = new AGILEDBConnector(dbcs);


  	//dbp->setQappPoint(aa);
	cout << "here 5 !!! "<< endl;

	vector<int> contint;
	double ntsa, ntso;
// ################################
//	ntsa = tstart + 86400;	ntso = tstop + 86400;
// ################################

	//delete aa;
	//	contint = getContactRange(ntsa, ntso);
	cout << "here 6 vado avanti !!! "<< endl;

	string gf; int nf; gf = "select * from ContactTable";	nf = 1;

	  vector<string> sv;	
	//  vector<string>::iterator svi = sv.begin();
//    dbp->loadDBDefaults();
    SAexception se;
    se.setMsg("DBConnector::executeSQLQuery() error in connecting to the database ");
    if (!dbp->createConnection()) throw se;
	cout << "here 7 !!! "<< endl;

//	contint = getContactRange(tstart, tstop);

//	setContactMin(contint[0]);		setContactMax(contint[1]);

    pair <double, double> tint;
    
    vector<string> tmi;
    vector<string> tma; stringstream ss; int contactmin, contactmax;
   contactmin = 2500; contactmax = 2501;
    ss.str(""); ss << "select tstop from ContactTable where 1 ;" << endl;
    string smiq = ss.str();
    cout << "AGILEDBConnector::getTimeInterval() going to execute " << smiq << endl;
    cout << "AGILEDBConnector::getTimeInterval() bench1"<< endl;


   QSqlQuery query;
    try{

      query.exec(smiq.c_str());
      QString first, second;
      cout << "DBConnector::getTimeInterval() n. of retrieved records = " << query.size() << endl;

      if (query.size() == -1){
 	SAexception se; string hy("no result rows for the query"); se.setMsg(hy);throw(se);
      }

    
    // execute the first query and retrieve output string value
    tmi = dbp->executeSQLOpenQuery(smiq, 1);
    cout << "AGILEDBConnector::getTimeInterval() bench1.5 tmi = " << tmi[0] << endl;
    //tmi.push_back("2007-12-31T00:46:20");
    // create the query that extract tstop    
//    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmax;
    ss.str(""); ss << "select tstop from ContactTable where contactnumber = " << contactmax;
    string smaq = ss.str();
    cout << "AGILEDBConnector::getTimeInterval() going to execute " << smaq << endl;
    // execute the second query and retrieve output string value
    tma = dbp->executeSQLOpenQuery(smaq, 1);
    cout << "AGILEDBConnector::getTimeInterval() bench2 tma = " << tma[0] << endl;
//    tma.push_back("2007-12-31T00:46:20");
    SADateTime sdt;
    string temps1;
    string temps2;
  //  string temps1 = tmi[0];
  //  string temps2 = tma[0];
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


	cout << "SasoaHandler::startAll() tstart = " << tma[0] << endl;
	cout << "SasoaHandler::startAll() tstop = " << tmi[0] << endl;
//	cout << "SasoaHandler::startAll() tstart = " << md.first << endl;
//	cout << "SasoaHandler::startAll() tstop = " << md.second << endl;
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception" << endl;
  }
	cout << "here 8 !!! "<< endl;

	se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");
    if (!dbp->closeConnection()) throw se;
	cout << "here 9 DB closed !!! "<< endl;

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }

  cout << "here 9 end !!! "<< endl;
      /*
        vector<string> stringhe; 
        vector<string>::iterator jt;
	vector<string>::iterator jt2;
	stringhe.push_back("prima");
	stringhe.push_back("seconda");
	stringhe.push_back("terza");
	
	jt = stringhe.begin();
	cout << "vector size = " << stringhe.size()  << endl;	
	while (jt != stringhe.end() ) {
		cout << jt - stringhe.begin() << " " << *jt << endl;
		if (*jt == "seconda") stringhe.erase(jt);
		jt++;
	}
	
	jt = stringhe.begin();
	cout << "vector size = " << stringhe.size()  << endl;
	while (jt != stringhe.end() ) {
		cout << jt - stringhe.begin() << " " << *jt << endl;
		if (*jt == "seconda") stringhe.erase(jt);
		jt++;
	}
	*/
	
	//exit(0);
	
	cout << "Test " << endl;
	string h("TSTART"), tempstring2("");
	
	string mfn(argv[1]);
	SAEphemerisData sed(mfn);
	sed.setVerbose(true);
	try{
		tempstring2 = sed.getPHDUKeyWord(h, 82);
		cout << "read keyword " << h << " value " << tempstring2 << endl;                  
		h = "TSTOP"; 
		tempstring2 = sed.getPHDUKeyWord(h, 82);
		cout << "read keyword " << h << " value " << tempstring2 << endl;
		//sed.report();
		cout << "tstart = " << sed.getTstart() <<  " tstop = " << sed.getTstop() <<  " duration = " << sed.getDataDuration() << endl;
	} catch (const SAexception &se){
	cerr << "error in correcting " << se.getMsg() << endl;
	} catch (const exception &e){
	cerr << "error in correcting " << e.what() << endl;
	} catch (...){
	cerr << "error in correcting " <<  endl;
	}	   
	/*
	double d1, d2, d3;
	d1 = 169807180.000000; d2 = 169807096.000000; 
	
	d3 = max(d1, d2); 
	
	cout << "the max between  " << d1 << " e " << d2 << " è "  << d3 << endl;
	*/
	//exit(0);
	/*
	SasoaHandler sh; 
 	stringstream ss; 
	string cminimo, cmaximo;
	string outf;
	
	cout << "merging ..." << endl;
	ss.str(""); ss << argv[5]; cminimo = ss.str();
	ss.str(""); ss << argv[6]; cmaximo = ss.str();

	outf = "tempout.fits";
	
	//sh.ephMerge(cminimo, cmaximo, outf);
	
	cout << "Correcting " << endl;
	
	
	SADataCorrector sc; string infile, outfile;
	double tstart, tstop;
	sc.SAFitsHandler::setVerbose(true);
 
	ss.str("");
	ss << argv[1];
	infile = ss.str(); 
	ss.str("");
        ss << argv[2];
	outfile = ss.str(); 
	
	tstart = atof(argv[3]);	tstop = atof(argv[4]);
try{	
	sc.Correct(infile, outfile, tstart, tstop);
  } catch (const SAexception &se){
 cerr << "error in correcting " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error in correcting " << e.what() << endl;
  } catch (...){
   cerr << "error in correcting " <<  endl;
  }
*/
  cout << "bye, bye."<< endl;
  system("date");
  return status;
}
#endif
