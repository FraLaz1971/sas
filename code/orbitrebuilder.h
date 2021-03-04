/***************************************************************************
                          orbitrebuilder.h  -  description
                             -------------------
    begin                : Wed Jul 19 2006
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

#ifndef ORBITREBUILDER_H
#define ORBITREBUILDER_H

#include "pipelinemodule.h"
#include "saexception.h"
#include "sal1coreventlist.h"


/**
  *@author Francesco Lazzarotto
  */
using namespace SAdata;
using namespace SApipeline;
using namespace SAExceptions;
using namespace System;
using namespace std;

namespace SApipeline{                    

class OrbitRebuilder : public PipelineModule  {
public: 
  /** No descriptions */
	OrbitRebuilder();
  /** No descriptions */
	OrbitRebuilder(const PipelineModule &pm);
  /** No descriptions */
	~OrbitRebuilder();
  /** No descriptions */
  int init();
  /** No descriptions */
  void setDescription();
  /** No descriptions */
  void start();
  /** No descriptions */
  void launchIDL_Batch();
  /** No descriptions */
  void launch(string & infile, string & outfile, vector<int> params);
  /** No descriptions */
  void createLaunchBatchScript();
  /** No descriptions */
  void rmTempInputFiles();
    /** No descriptions */
  void passOutputFile(const string &toutdir);
  /** No descriptions */
  string getDefaultOutputDir();
  /** No descriptions */
  void announceDelivery();
  /** No descriptions */
  void setOutputFileName(const string & outf);
  /** No descriptions */
  void test();
  /** No descriptions */
  void retrieveInputDataDir();
  /** No descriptions */
  string getInputDataDirVal();
  /** No descriptions */
  string getInputDataDirNam();
//  /** No descriptions */
//  void readInputFile(string infi);
     /** No descriptions */
  void retrieveOrbitData();
  /** No descriptions */
  void test2();
  
  /** No descriptions */
  string getOrbitString();
  
  /** No descriptions */
  string getArchiveRoot();
  
  /** No descriptions */
  void setCurrentArchiveDir();
  /** No descriptions */
  bool getTestMode();
  /** No descriptions */
  void setTestMode(bool bv);
  /** No descriptions */
  void setOrbitNumber(const string &ons);
  /** No descriptions */
  int getOrbitNumber();
  /** No descriptions */
  void setOrbitNumber(int on);
  /** No descriptions */
  void setOrbitString();
  /** No descriptions */
  void setOrbitString(const string & c1, int orbnum);
  /** No descriptions */
  void setOrbitString(const string &c1, const string &c2);
  /** No descriptions */
  void processBase();
  /** No descriptions */
  string retrieveOutputFileName();
  /** No descriptions */
  void retrieveInputFileName();
  /** No descriptions */
  string getInputDataDir();
  /** No descriptions */
  void prepare();
  void rmTempFiles();
  /** No descriptions */
  string getInputFileName();
  /** No descriptions */
  string getAutoInputFileName();
  /** No descriptions */
  void setContact(const string &cs);
  /** No descriptions */
  void setContactNumber(int cn);
  /** No descriptions */
  void processDebug();

protected:

string newfilename;


int old_contactnum;

int contactnum;

int orbnum;

/** string containing the name of the env var saving the directory where to search for the input data*/
string inputdatadirnam;

/** string value of the directory where to search for the input data*/
string inputdatadirval;

/** string saving the name of the file to be processed by the orbit rebuilder
-- a lv1 corr file --- */

string actfilenamenam;

string actfilenameval;


string cur_orb_str;

string arcoutdir;

bool testmode;

const char *t ;

char *ee;
};
}
#endif
