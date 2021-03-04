/***************************************************************************
                          dbconnector.h  -  description
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

#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <qapplication.h>
#include <qsqldatabase.h>
#include <qdatatable.h>
#include <qsqlcursor.h>
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qstring.h> 
#include "connector.h"
#include "sadatetime.h"
#include <cstdlib>


/** default connection values*/
//#include "DBConnection.h"

#define DB_DRIVER     "QMYSQL3"
#define DB_DBNAME     "test2"
#define DB_USER       "agiledb"
#define DB_PASSWD     "superflight"
#define DB_HOST       "bigfoot.iasf-roma.inaf.it"

/**                                                        
  *@author Francesco Lazzarotto
  */
namespace DB {
  using namespace DB; 
  using namespace SAdata;   
class DBConnector: public Connector  {
public: 
	DBConnector();
    DBConnector(const string connstring[5]);
	DBConnector(vector <string> connstring );
	~DBConnector();
  /** No descriptions */
  bool createConnection();
  /** No descriptions */
  string executeQuery(const string &s);
  /** No descriptions */
  bool closeConnection();
  /** No descriptions */
  void readConnValues(const string &convalfile);
  /** save passed connection values in a file with passed fname  */
  void saveConnValues(const string &fname, const string connvals[5]);
  /** No descriptions */
  void test();
  /** No descriptions */
  void writeDBDefaults(const string *connvals);
  /** No descriptions */
  void getConnectionValues();
  /** No descriptions */
  void writeCurrentDBDefaults();
  /** No descriptions */
  void setConnectionValues(const string *connvals);
  /** No descriptions */
  void showCurrentAccount();
  /** No descriptions */
  void loadDBDefaults();
  /** No descriptions */
  void testDefaultConnection();
  /** loads COT record into the DB ContactTable */
  void loadCOTRecord(vector<string> *fieldstrings);
  /** reads COT file and save it in a DB table */
  void loadCOTFile(const string &cfn);
  /** No descriptions */
  void testCOTConnection();
  /** No descriptions */
  void executeInsertion(const string &s);
  /** execute an SQL query on the connected database and returns
a strings vector containing the result, each row is a record */
  vector<string> executeSQLQuery(const string &s);
  vector<string> executeSQLQuery(const string &s, int tablenfields);
  vector<string> executeSQLOpenQuery(const string &s, int tablenfields);
    pair<double, double> getTimeInterval(int contactmin, int contactmax);
    void setQappPoint(QApplication * ta);

  protected:

  vector<string> tablerows;

  QApplication *a;
  int argc;
  char **argv;
  /*DB connection strings
  that are used by the createConnection member function*/
  char *driver;
  char *dbname;
  char *user;
  char *passwd;
  char *host;

  string sdriver;
  string sdbname;
  string suser;
  string spasswd;
  string shost;

  bool open;
  bool defdbflag;
  QSqlDatabase *defaultDB;
  QSqlQuery *oquery;

};
}
#endif
