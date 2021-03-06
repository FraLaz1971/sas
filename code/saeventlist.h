/***************************************************************************
                          saeventlist.h  -  description
                             -------------------
    begin                : Mon Jun 19 2006
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

#ifndef SAEVENTLIST_H
#define SAEVENTLIST_H


/**
  *@author Francesco Lazzarotto
  */
#define MAXDIMENSION  1000000

#include "timer.h"
#include <string>
#include <CCfits>
#include <Column.h>
#include <FitsError.h>
#include <KeyData.h>
#include "fitsio.h"
#include <algorithm>
#include "sadataset.h"
#include "safitshandler.h"
#include "archivehandler.h"
#include "saexception.h"
#include "safitshandler.h"
#include <utility>
 
namespace SAdata{

using namespace SAdata;
using namespace std;
using namespace SApipeline;
using namespace SAarchive;

using namespace CCfits;
using std::valarray;
using namespace SAExceptions;

class SAEventlist: public SADataSet {
public: 
	SAEventlist();
	~SAEventlist();
  virtual void setDefault();
  virtual void init();
  /** No descriptions */
  virtual void save(const string &outfilename);
  /** No descriptions */
  virtual void read(const string &infilename);
  /** No descriptions */
  void setDim(unsigned long int dm);
  /** No descriptions */
  unsigned long int getDim();
  /** No descriptions */
  void setVerbose(bool val);
  /** No descriptions */
  void setDebug(bool bval);
  /** No descriptions */
  void setTstart(double tst);
  /** No descriptions */
  void setTstop(double tsp);
  /** No descriptions */
  double getTstart();
  /** No descriptions */
  double getTstop();
    void readHeader();
	void printerror( int status);
    float getExposure();
    void setExposure(float exp);
  	void setArchiveHandler(ArchiveHandler *ah);
	bool isSaveFiltered();
	void setSaveFiltered(bool val);
    void setFilterTarget(const string &ft);
    string getFilterTarget();
    void setPlotTerm(const string &pt);
    string getPlotTerm();
    void setProductsDir(const string &pd);
    string getProductsDir();
    void retrieveTstart();
    void retrieveTstop();
    void printTimeRange( ostream &o);
    void setInputFileName(const string &ifn);

protected:

/** */
string infile;
/** */
string outfile;
/** */
//InvalidDataType idex;
string tempstring;
/** */
string tempstring2;
/** */
int i, j, k;
/** */
bool verbose;

/** */
unsigned long int dim;
/** */
vector<string> kn; //keyword names
/** */
vector<string> kv;  //keyword values
/** */
Timer tm;
/** cursor to the current outfile*/
unsigned short outfile_ctr;
/** cursor to the current infile*/
unsigned short infile_ctr;
/** */
bool debug;
/** */
double tstart;
/** */
double tstop;
/** */
float exposure;


/** */
bool success; 

/** */
SAFitsHandler *sfh;
/** */
ArchiveHandler *arc;
//FitsException fe;
/** */
bool savefiltered;
/** */
string filtertarget;
/** */
string plot_term;
/** */
string products_dir;
};
}
#endif
