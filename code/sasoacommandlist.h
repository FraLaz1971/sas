/***************************************************************************
                          sasoacommandlist.h  -  description
                             -------------------
    begin                : Fri Mar 31 2006
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

#ifndef SASOACOMMANDLIST_H
#define SASOACOMMANDLIST_H

#include <iostream>
#include <string>

#include <vector>
#include <map>
#include <iterator>
#include "sasoacommand.h"
#include "hertagbase.h"
#include <stdio.h>
#include <sstream>
#include <exception>
#include <stdexcept>

// #include <pipelinemodule.h>
using namespace std;

namespace SApipeline{
   /**
   object implementing the sasoa commandlist
    default commands/selection are given if
    user selected commands lack some specifications.    
  *@author Francesco Lazzarotto
  */
class SasoaCommandList /*: public HertagBase */{

public:
   /** No descriptions */
  SasoaCommandList();
   /** No descriptions */
  SasoaCommandList( string &line);
  /** No descriptions */
 ~SasoaCommandList(); 
   /** No descriptions */
  void setVerbose(bool v);
  /** shows the parameters of the command */
  void showCommands();
  /** No descriptions */
  void show();
  /** No descriptions */
  void setValue(int parnum, int value);
  /** No descriptions */
  void setDescription(int parnum, string des);
  /** No descriptions */
  void pushCommand(SasoaCommand par);
  /** No descriptions */
  void insertCommand(SasoaCommand &par);
  /** No descriptions */
  string getOutputDir();
  /** No descriptions */
  string getInputdir();
  /** No descriptions */
  string getInputFilename();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  string getInfileRoot();
  /** No descriptions */
  bool isOutDirSet();
  /** No descriptions */
  void reset();
  /** No descriptions */
  void setDefaultOutDir();
  /** No descriptions */
  bool isPathAbsolute();
  /** No descriptions */
  void setAbsolutePath(bool val);
  /** No descriptions */
  bool isIDL_DisplayOn();
  /** No descriptions */
  string getSasoaHome();
  /** No descriptions */
  bool getVerboseState();
  /** No descriptions */
  string getInstrument();
  /** No descriptions */
  bool isInputFileSet();
  /** No descriptions */
  void setDefaultOutDir(const string &fn);
  /** No descriptions */
  bool isInDirSet();
  /** No descriptions */
  void setDefaultInDir(const string &id);
  /** No descriptions */
  string getValue(const string &keyword);
  /** No descriptions */
  string getAttitudeFileName();
  /** No descriptions */
  bool isDebugSet();
  /** No descriptions */
  bool getDebugValue();
  /** No descriptions */
  bool getIrosMode();
  /** No descriptions */
  bool isIrosModeSet();
  /** No descriptions */
  bool isAttFileSet();
  /** No descriptions */
  void setInputFileName(const string &ifn);
  /** No descriptions */
  void setAuto(const string & val);
  
  /** No descriptions */
  bool isAuto();
  /** No descriptions */
  void setTempDataMode(const string &tdm);
  /** No descriptions */
  bool getTempDataMode();
  /** "map" data structure containing the pairs <command, value> */
  map<string, string> compars_map;

private:

/** contains the filesystem path  where the input file is saved*/

string indir;

/** contains the filesystem path  where the output path will be saved */

string outdir;

/** contains the file name in input to the pipeline module */

string infilename;

/** contains the filename in output from the pipeline module*/

string outfilename;

/** contains the list of parameters to be given to the pipeline stage*/
/** */
string tempstring;
/** */
bool tempbool;
/** */
map<string, string >::iterator item;

/** */
int counter1;
/** */
bool absolute_path;
/** */
bool verbose;
/** */
exception e;
/** */
SasoaCommand parameter;
};

}

#endif
