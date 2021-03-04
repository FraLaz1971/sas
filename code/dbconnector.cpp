/***************************************************************************
                          dbconnector.cpp  -  description
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

#include "dbconnector.h"
namespace DB {
DBConnector::DBConnector(){
    defdbflag = false;
    open = false;
    driver = (char *)DB_DRIVER;     
    dbname = (char *)DB_DBNAME;     
    user = (char *)DB_USER;       
    passwd = (char *)DB_PASSWD;    
    host = (char *)DB_HOST;       
    argc = 0; argv = (char **)new char[2];
    a = new QApplication(argc, argv );
}

DBConnector::DBConnector(vector <string> connstring ){
  defdbflag = false;
  driver =  (char *)connstring[0].c_str();
  dbname = (char *)connstring[1].c_str();
  user =  (char *)connstring[2].c_str();
  passwd = (char *)connstring[3].c_str();
  host = (char *)connstring[4].c_str();  
}


DBConnector::DBConnector(const string connstring[5] ){
  defdbflag = false;
  driver =  (char *)connstring[0].c_str();
  dbname = (char *)connstring[1].c_str();
  user =  (char *)connstring[2].c_str();
  passwd = (char *)connstring[3].c_str();
  host = (char *)connstring[4].c_str();  
}

DBConnector::~DBConnector(){
  if (verbose) cout << "~DBConnector()" << endl;
  try{
    if (verbose) cout << "~DBConnector() going to delete"<< endl;
    if (verbose) cout << "~DBConnector() a = "<< a << endl;
    if (verbose) cout << "~DBConnector() argv [0] "<< argv [0] << endl;
    if (verbose) cout << "~DBConnector() argv [1] "<< argv [1] << endl;
    // deleting QApplication a makes an error (qt has deleted yet perhaps)
    // delete a;
    delete[] argv;
  } catch (const exception &e){
    cerr << "error in ~DBConnector() "<< e.what() << endl;
  }
}
/** No descriptions */
bool DBConnector::createConnection(){
  try{
        if (!defdbflag) {
	defaultDB =  QSqlDatabase::addDatabase( (const char *) driver );
	if (verbose) cout << "DBConnector::createConnection() database added " << endl;
        defaultDB->setDatabaseName((const char *) dbname );
	if (verbose) cout << "DBConnector::createConnection() database name set " << endl;
        defaultDB->setUserName((const char *) user );
	if (verbose) cout << "DBConnector::createConnection() user name set " << endl;
        defaultDB->setPassword((const char *) passwd );
	if (verbose) cout << "DBConnector::createConnection() password set " << endl;
        defaultDB->setHostName((const char *) host );
	if (verbose) cout << "DBConnector::createConnection() hostname set " << endl;
	
        if ( ! defaultDB->open() ) {
            qWarning( "Failed to open database: " + defaultDB->lastError().text() );
            return FALSE;
        }
	if (verbose) cout << "DBConnector::createConnection() db now open!  " << endl;
}
    open=true;
  } catch (const exception &e){
    cerr << "DBConnector::createConnection() error in connecting to the database"<< e.what() << endl;
    open=false;
  }
  	defdbflag = true;
        return true;
}
/** No descriptions */
void DBConnector::executeInsertion(const string &s){
    QSqlQuery *query = new QSqlQuery();
    query->exec(s.c_str());  
	delete query;
}
/** No descriptions */
string DBConnector::executeQuery(const string &s){
    cout << "executing query" << endl;
    QSqlQuery query;
    query.exec(s.c_str());
    QString first, second;
    while ( query.next()) {
           first = query.value(0).toString();
           second = query.value(1).toString();
           cout << "DBConnector::executeQuery() "<< "first value : "<< first << " second value : " << second << endl;
    }
    return (string)(const char *) first;
}
/** No descriptions */
bool DBConnector::closeConnection(){
  if (open){
    //defaultDB->removeDatabase(defaultDB->databaseName());
    delete defaultDB;  
  } else{
  open = false;
  }
  return open;
}
/** No descriptions */
void DBConnector::readConnValues(const string &convalfile){
     // read 5 lines of maximun 256 characters
    char buf[5][256];    int mlinelen = 256;
    ifstream ninfile;    stringstream ss;    string fn;
    ninfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = convalfile;
        ninfile.open (fn.c_str(), ofstream::in);
        for(int k=0; k<5; k++){
          ninfile.getline(buf[k], mlinelen) ;
          ss << buf[k];
          if (verbose) cout << "DBConnector::readConnValues() connection string n."<< k << " is " << ss.str() << endl;
          ss.str("");
        }
        ninfile.close();
        
      } // close try
      catch (ofstream::failure e) {
          cout << "DBConnector::readConnValues() Exception opening/writing file"<< endl;
      }
}
/** No descriptions */
void DBConnector::saveConnValues(const string &fname, const string connvals[]){
    ofstream noutfile;    string fn; 
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = fname;
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        for (int k = 0; k<5; k++){
          noutfile << connvals[k] << endl;
        }
        noutfile.close();
      } // close try
      catch (ofstream::failure e) {
         cout <<"Exception opening/writing file"<< endl;
      }  
}
/** No descriptions */
void DBConnector::test(){
  string s[5];


  cout << "DBConnector::test() connecting to" << endl;

  if(verbose) cout << "sdriver = " << sdriver << endl;
  if(verbose) cout << "sdbname  = " << sdbname << endl;
  if(verbose) cout << "suser = "<< suser << endl;
  if(verbose) cout << "spasswd = " << spasswd << endl;
  if(verbose) cout << "shost = "<< shost << endl;

  s[0].assign(sdriver);
  s[1].assign(sdbname);
  s[2].assign(suser);
  s[3].assign(spasswd);
  s[4].assign(shost);
  
  const string fn("tempdbfile.txt");
  // create a file with arbitrary (default) db connection parameters
  saveConnValues(fn, s);
  // read the parameters written in the file and print it (test)
  readConnValues(fn);
  // set the prevoiusly user-inserted db acces coordinate values
  setConnectionValues(s);
  // use the parameters and connect to the database
  createConnection();
  // read/write on some tables
  string q("SELECT *FROM Auxiliary");
  executeQuery(q);
  q.assign("SELECT DateStart, DateStop FROM Correction WHERE logFile = 'pipp0'");
  executeQuery(q);
  // close the connection
  closeConnection();  
  }
/** No descriptions */


/** No descriptions */
void DBConnector::getConnectionValues(){
//  long size;  size = 256;
//  char * driver = new char[size];  char * dbname = new char[size];  char * user = new char[size];
//  char * passwd = new char[size]; char * host = new char[size];  
  try {
          cout << "Enter the name of The used DataBase driver (DB_DRIVER): "<< endl;  
          cin >> sdriver;
          cout << "you entered " << sdriver << endl;
          cout << "Enter the name of The used DataBase name (DB_DBNAME): "<< endl;
          cin >> sdbname;
          cout << "you entered " << sdbname << endl;
          cout << "Enter the name of The used DataBase user (DB_USER): "<< endl;
          cin >> suser;
          cout << "you entered " << suser << endl;
          cout << "Enter the name of The used DataBase password (DB_PASSWD): "<< endl;
          cin >> spasswd;
          cout << "you entered " << spasswd << endl;
          cout << "Enter the name of The used DataBase host (DB_HOST): "<< endl;
          cin >>shost;
          cout << "you entered " << shost << endl;
      } // close try
        catch (ofstream::failure e) {
          cout <<"Exception reading database coordinates"<< endl;
      }
//  delete driver;  delete dbname;  delete user;
//  delete passwd;  delete host;
}
/** No descriptions */
void DBConnector::writeCurrentDBDefaults(){
  string cvls[5] ;
  cvls[0] = sdriver.c_str();
  cvls[1] = sdbname.c_str();
  cvls[2] = suser.c_str();
  cvls[3] = spasswd.c_str();
  cvls[4] = shost.c_str();

  if (verbose) cout << "driver ="<< driver << endl;
  if (verbose) cout << "dbname =" << dbname << endl;
  if (verbose) cout << "user =" << user << endl;
  if (verbose) cout << "passwd =" << passwd << endl;
  if (verbose) cout  << "host ="<< host << endl;

    if (verbose) cout << "cvls[0] = "<< cvls[0]<< endl;
    if (verbose) cout << "cvls[1] = "<< cvls[1]<< endl;
    if (verbose) cout << "cvls[2] = "<< cvls[2]<< endl;
    if (verbose) cout << "cvls[3] = "<< cvls[3]<< endl;
    if (verbose) cout << "cvls[4] = "<< cvls[4]<< endl;
    
  writeDBDefaults(cvls);
}

//#define DB_DRIVER     "QMYSQL3"
//#define DB_DBNAME     "test"
//#define DB_USER       "mysql"
//#define DB_PASSWD    "database"
//#define DB_HOST       "localhost"

/** No descriptions */
void DBConnector::writeDBDefaults(const string *connvals){
    ofstream noutfile;    string fn;
    if (verbose) cout << "executing writeDBDefaults()"<< endl;
    if (verbose) cout << "connvals[0] = "<< connvals[0]<< endl;
    if (verbose) cout << "connvals[1] = "<< connvals[1]<< endl;
    if (verbose) cout << "connvals[2] = "<< connvals[2]<< endl;
    if (verbose) cout << "connvals[3] = "<< connvals[3]<< endl;
    if (verbose) cout << "connvals[4] = "<< connvals[4]<< endl;
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "DBConnection2.h";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
          noutfile << "#define DB_DRIVER     \""<< connvals[0]+"\"" << endl;
          noutfile << "#define DB_DBNAME     \""<< connvals[1]+"\"" << endl;
          noutfile << "#define DB_USER       \""<< connvals[2]+"\"" << endl;
          noutfile << "#define DB_PASSWD    \""<< connvals[3]+"\"" << endl;
          noutfile << "#define DB_HOST       \""<< connvals[4]+"\"" << endl;
        noutfile.close();
      } // close try
      catch (ofstream::failure e) {
         cout <<"Exception opening/writing file"<< endl;
      }
}
/** No descriptions */
void DBConnector::setConnectionValues(const string *connvals){
    cout << "DBConnector::setConnectionValues() executing writeDBDefaults()"<< endl;
    driver =  (char *)connvals[0].c_str();
    dbname = (char *)connvals[1].c_str();
    user = (char *)connvals[2].c_str();
    passwd = (char *)connvals[3].c_str();
    host = (char *)connvals[4].c_str();
}
/** No descriptions */
void DBConnector::showCurrentAccount(){
  cout << "DBConnector::showCurrentAccount() "<< endl;
  cout << "driver = "<< driver << endl;
  cout << "dbname = " << dbname << endl;
  cout << "user = " << user << endl;
  cout << "passwd = " << passwd << endl;
  cout  << "host = "<< host << endl;
}
/** No descriptions */
void DBConnector::loadDBDefaults(){
    if (verbose) cout << "DBConnector::loadDBDefaults() "<< endl;
    driver = (char *)DB_DRIVER;
    dbname = (char *)DB_DBNAME;
    user = (char *)DB_USER;
    passwd = (char *)DB_PASSWD;
    host = (char *)DB_HOST;
}
/** No descriptions */
void DBConnector::testDefaultConnection(){
    if (verbose) cout << "DBConnector::testDefaultConnection() "<< endl;
    loadDBDefaults();
    createConnection();
  // read/write on some tables
    string q("SELECT *FROM Auxiliary");
    executeQuery(q);
    q.assign("SELECT DateStart, DateStop FROM Correction WHERE logFile = 'pipp0'");
    executeQuery(q);
    // close the connection
    closeConnection();  
}
}/** loads COT record into the DB ContactTable */
void DB::DBConnector::loadCOTRecord(vector<string> *fieldstrings){
    string q("");         stringstream myss;
    vector<string> loc;
    vector<string>::iterator myit = fieldstrings->begin();
    while (myit != fieldstrings->end() ){
      myss.str("");
      loc.push_back(*myit);
      cout <<  "fieldstring["<< myit - fieldstrings->begin() << "] = " << *myit++ << endl;
    }
      myss << (string)"INSERT INTO ContactTable(contactnumber)";
      myss << (string)"values(";
      myss << loc[7];
      myss << (string)")";
      q = myss.str();
     cout << "q  = " << q << endl;
/*
     loadDBDefaults();
     createConnection();
     executeInsertion(q);
     closeConnection();
*/
}
/** reads COT file and save it in a DB table */
void DB::DBConnector::loadCOTFile(const string &cfn){
  //
    loadDBDefaults();
    se.setMsg("DBConnector::executeSQLQuery() error in connecting to the database ");
    if (!createConnection()) throw se;

    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256; int linenumb = 0;
    ifstream ninfile;
    stringstream ss;
    tempstring = "";
          vector<string> tempfields;
    ninfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (cfn.c_str(), ofstream::in);
        while(!ninfile.eof()){
          ninfile.getline(buf, mlinelen) ;
          ss.str("");ss << buf;  tempstring = ss.str();
          if (verbose) cout << "DBConnector::loadCOTFile() COT row read " << tempstring << endl;
          try{

            if (tempstring.size()!=0) {
		tokenizeLine(tempstring, &tempfields);
	} else {
	SAexception ss; string h("null string read in the cot file");
	ss.setMsg(h);	throw ss;
	}
          } catch (const exception &e) {
            cerr<< "DBConnector::loadCOTFile() Exception tokenizing the line "<< e.what() << endl;          
	SAexception ss; string h("null string read in the cot file");
	ss.setMsg(h);	throw ss;
          }
         //cout << "read line n." << linenumb++ << " containing fields n. " << tempfields.size() << endl;
      string q("");      stringstream  myss;   myss.str("");
      // open sql instruction
      myss << (string)"INSERT INTO ContactTable(tstart, tstop, duration, place, state, contactnumber) ";
      myss << (string)"values(";
	// tstart
      myss << (string)"\"";
      tempfields[0].replace(4, 1, "-");
      tempfields[0].replace(7, 1, "-");
      myss << tempfields[0];
      myss << " " ;
      myss << tempfields[1];      
      myss << (string)"\"";
	// tstop
      myss << (string)",";
      myss << (string)"\"";
      tempfields[2].replace(4, 1, "-");
      tempfields[2].replace(7, 1, "-");
      myss << tempfields[2];
      myss << " " ;
      myss << tempfields[3];
      myss << (string)"\"";
// duration
      myss << (string)",";
      myss << (string)"\"";
      myss << tempfields[4];
      myss << (string)"\"";
// place
      myss << (string)",";
      myss << (string)"\"";
      myss << tempfields[5];
      myss << (string)"\"";
// state
      myss << (string)",";        
      myss << (string)"\"";
      myss << tempfields[6];
      myss << (string)"\"";
// contactnumber
      myss << (string)",";
      myss << tempfields[7];
// close sql instruction
      myss << (string)")";
      q = myss.str();
     cout << "q  = " << q << endl;


	vector <string> sv;

try{

     sv = executeSQLOpenQuery(q, 0);
	
	se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }     
         //loadCOTRecord(&tempfields);
         tempfields.clear();
        }
        ninfile.close();
      } // close try
      catch (const SAexception  &se) {
          cerr<< "DBConnector::loadCOTFile() Exception reading COT file"<< se.getMsg() << endl;
      }
      catch (ifstream::failure e) {
          cerr << "DBConnector::loadCOTFile() Exception reading COT file"<<  endl;
      }
      catch (const exception &e) {
          cerr << "DBConnector::loadCOTFile() Exception reading COT file"<< e.what() << endl;
      }

    if (!closeConnection()) throw se;


}

void DB::DBConnector::testCOTConnection(){
  cout << "DBConnector::testCOTConnection() "<< endl;
    loadDBDefaults();
    createConnection();
  // read/write on some tables
    string q;
    //q = "SELECT * FROM ContactTable";
    //executeQuery(q);
    q = "INSERT INTO ContactTable(contactnumber) values(3333)";
    executeInsertion(q);
    // close the connection
    closeConnection();  
}
    /*
    loadDBDefaults();
    createConnection();
    string q("SELECT *FROM Auxiliary");
    executeQuery(q);
    q.assign("SELECT DateStart, DateStop FROM Correction WHERE logFile = 'pipp0'");
    executeQuery(q);
    // close the connection
    closeConnection();  
  // read/write on some tables

  */           //string cf[6];
          /*
          a=0; b=18;cf[0] = tempstring.substr(a, b);
          a=20; b=18;cf[1] = tempstring.substr(a, b);
          a=40; b=8;cf[2] = tempstring.substr(a, b);
          a=50; b=8;cf[3] = tempstring.substr(a, b);
          a=63; b=4;cf[4] = tempstring.substr(a, b);
          a=65; b=9;cf[5] = tempstring.substr(a, b);
          *//** execute an SQL query on the connected database and returns
a strings vector containing the result, each row is a record
          */
vector<string> DB::DBConnector::executeSQLQuery(const string &s){
    loadDBDefaults();
    se.setMsg("DBConnector::executeSQLQuery() error in connecting to the database ");
    if (!createConnection()) throw se;
    cout << "executing query" << endl;
    QSqlQuery query;
    query.exec(s.c_str());
    QString first, second;
    cout << "n. of records " << query.size() << endl;
	string str;
    int i = 0; stringstream myss; myss.str("");
//	vector<string> sts; 
    while ( query.next()) {
			for(i=0; i<6; i++){
				if (i>0) myss << " ";
				myss << query.value(i).toString();
			}
		   myss << endl;
           cout << myss.str() << endl; str = myss.str();
           tablerows.push_back(str);
           }
    se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");
    if (!closeConnection()) throw se;
    return tablerows;
}

vector<string> DB::DBConnector::executeSQLQuery(const string &s, int tablenfields){
    loadDBDefaults();
    se.setMsg("DBConnector::executeSQLQuery() error in connecting to the database ");
    if (!createConnection()) throw se;
    if (verbose) cout << "DBConnector::executeSQLQuery() executing query" << endl;
    QSqlQuery query;
    try{
      query.exec(s.c_str());
      QString first, second;
      if (verbose) cout << "DBConnector::executeSQLQuery() n. of retrieved records = " << query.size() << endl;
      string str;
      int i = 0; stringstream myss; myss.str("");
//	vector<string> sts; 
      while ( query.next()) {
			for(i=0; i<tablenfields; i++){
				if (i>0) myss << " ";
				myss << query.value(i).toString();
			}
		   myss << endl;
           if (verbose) cout << myss.str() << endl; 
		   str = myss.str();
           tablerows.push_back(str);myss.str("");
           }
    se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");
    if (!closeConnection()) throw se;
    } catch(const exception &e){
    	cerr << "DBConnector::executeSQLQuery() error" << e.what() << endl;
    }
    return tablerows;
}
vector<string> DB::DBConnector::executeSQLOpenQuery(const string &s, int tablenfields){
    se.setMsg("DBConnector::executeSQLQuery() error in connecting to the database ");
    if (verbose) cout << "DBConnector::executeSQLQuery() executing query" << endl;
    try{
      oquery = (QSqlQuery *) new  QSqlQuery();
      oquery->exec(s.c_str());
      QString first, second;
      if (verbose) cout << "DBConnector::executeSQLQuery() n. of retrieved records = " << oquery->size() << endl;
      string str;
      int i = 0; stringstream myss; myss.str("");
//	vector<string> sts; 
      while ( oquery->next()) {
			for(i=0; i<tablenfields; i++){
				if (i>0) myss << " ";
				myss << oquery->value(i).toString();
			}
		   myss << endl;
           if (verbose) cout << myss.str() << endl; 
		   str = myss.str();
           tablerows.push_back(str);myss.str("");
           }
    se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");
    } catch(const exception &e){
    	cerr << "DBConnector::executeSQLQuery() error" << e.what() << endl;
    }
	delete oquery;
    return tablerows;
}
/*!
    \fn DB::DBConnector::getTimeInterval(int contactmin, int contact max)
    return the time interval for the given AGILE contacts range
 */
pair<double, double> DB::DBConnector::getTimeInterval(int contactmin, int contactmax)
{
    loadDBDefaults(); string s; int tablenfields;
    se.setMsg("DBConnector::getTimeInterval() error in connecting to the database ");
    if (!createConnection()) throw se;
    if (verbose) cout << "DBConnector::getTimeInterval() executing " << endl;
    pair <double, double> tint;
    string smiq,smaq;
    vector<string> tmi;	vector<string> tma;
//    select tstop from 'ContactTable' where contactnumber =
    // create the query that extract tstart
//    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << (contactmin - 1);
    stringstream myss;
    myss.str(""); myss << "select tstop from ContactTable where contactnumber = " << contactmin;
    smiq = myss.str();
    cout << "DBConnector::getTimeInterval() going to execute : " << smiq << endl;
    //cout << "bench1"<< endl;
    


    // execute the first query and retrieve output string value
    s = smiq;
    tablenfields = 6;
    QSqlQuery query;
    try{
      query.exec(s.c_str());
      QString first, second;
      cout << "DBConnector::getTimeInterval() n. of retrieved records = " << query.size() << endl;


   /* vector<string> tmi;
    cout << "DBConnector::getTimeInterval() debug going to execute executeSQLQuery(smiq, 6);" << smiq << endl;
    cout << "DBConnector::getTimeInterval() debug bench1"<< endl;
    
    // execute the first query and retrieve output string value
    tmi = executeSQLQuery(smiq, 6);
    cout << "tmi[0] = "<< tmi[0] << endl;
*/
      if (query.size() == -1){
 	SAexception se; string hy("no result rows for the query"); se.setMsg(hy);throw(se);
      }

      string str;
      int i = 0; stringstream myss; myss.str("");
//	vector<string> sts; 
      while ( query.next()) {
			for(i=0; i<tablenfields; i++){
				if (i>0) myss << " ";
				myss << query.value(i).toString();
			}
		   myss << endl;
           cout << myss.str() << endl; str = myss.str();
           tablerows.push_back(str);
           }
	} catch (const SAexception &se){
	   cerr << "DBConnector::getTimeInterval() error" << se.what()<< endl;
	   throw(se);	   
	} catch (const exception &e){
	   cerr << "DBConnector::getTimeInterval() error" << e.what()<< endl;
	   } 
	catch (...){
	   cerr << "DBConnector::getTimeInterval() error" << endl;
	   }

    //tmi = executeSQLQuery(smiq, 6);
    tmi.clear();
    tmi = tablerows;
    // create the query that extract tstop    
//    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmax;
    ss.str(""); ss << "select tstop from ContactTable where contactnumber = " << contactmax;
    smaq = ss.str();
    cout << "going to execute " << smaq << endl;
        s = smaq;
    tablenfields = 6;
    tablerows.clear();
    try{
      query.exec(s.c_str());
      QString first, second;
      cout << "DBConnector::executeSQLQuery() n. of retrieved records = " << query.size() << endl;
      if (query.size() == -1){
 	SAexception se; string hy("no result rows for the query"); se.setMsg(hy);throw(se);
      }
      string str;
      int i = 0; stringstream myss; myss.str("");
//	vector<string> sts; 
      while ( query.next()) {
			for(i=0; i<tablenfields; i++){
				if (i>0) myss << " ";
				myss << query.value(i).toString();
			}
		   myss << endl;
           cout << myss.str() << endl; str = myss.str();
           tablerows.push_back(str);
           }
	} catch (const SAexception &se){
	   cerr << "DBConnector::getTimeInterval() error" << se.what()<< endl;
	   throw(se);

	}  catch (const exception &e){
	   cerr << "DBConnector::getTimeInterval() error" << e.what()<< endl;
	   }
	   catch (...){
	   cerr << "DBConnector::getTimeInterval() error" << endl;
	   }
    //tmi = executeSQLQuery(smiq, 6);
    tma.clear();
    tma = tablerows;
    // create the query that extract tstop    
//    ss.str(""); ss << "select tstop from 'ContactTable' where contactnumber = " << contactmax;
    ss.str(""); ss << "select tstop from ContactTable where contactnumber = " << contactmax;
    smaq = ss.str();

    
    //cout << "bench2" << endl;
    // execute the second query and retrieve output string value
    //tma = executeSQLQuery(smaq, 6);
    SADateTime sdt;
    string temps1 = tmi[0];
    string temps2 = tma[0];
    string t;
    
    //cout << "bench3" << endl;
    t = "";
    ss.str(""); ss << sdt.UTCtoAgileTime(temps1) << endl;
    t = ss.str(); tint.first = atof(t.c_str());
    cout << "bench4" << endl;
    
    t = "";
    ss.str(""); ss << sdt.UTCtoAgileTime(temps2) << endl;
    t = ss.str(); tint.second = atof(t.c_str());
    //cout << "bench5" << endl;
    se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");
    if (!closeConnection()) throw se;
    
    return tint;
}


/*!
    \fn DB::DBConnector::setQappPoint()
 */
void DB::DBConnector::setQappPoint(QApplication *ta)
{
	 a = ta;
}
