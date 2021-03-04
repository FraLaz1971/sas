/***************************************************************************
                          agiledbconnector.h  -  description
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

#ifndef AGILEDBCONNECTOR_H
#define AGILEDBCONNECTOR_H

#include <qapplication.h>
#include <qsqldatabase.h>
#include <qdatatable.h>
#include <qsqlcursor.h>
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qstring.h> 
#include "connector.h"
#include "dbconnector.h"
#include "agiledbconnector.h"
#include <vector>
#include <string>
#include <cstdlib>
/** default connection values*/


/**                                                        
  *@author Francesco Lazzarotto
  */
namespace DB {
  using namespace DB;  
class AGILEDBConnector: public DBConnector  {
public: 
	AGILEDBConnector();
    AGILEDBConnector(vector <string> connstring);
	~AGILEDBConnector();
	string getL2fileName(int contactnum);
	pair<double, double> getTimeInterval(int contactmin, int contactmax);
    void setSasoaStatusOnDB(int contact, string task);

};
}
#endif
