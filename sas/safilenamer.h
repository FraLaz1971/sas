/***************************************************************************
                          safilenamer.h  -  description
                             -------------------
    begin                : Mon Sep 18 2006
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

#ifndef SAFILENAMER_H
#define SAFILENAMER_H


/**
  *@author Francesco Lazzarotto
  */
#include <iostream>
#include <string>
#include "archivemodule.h"
#include "agilefilename.h"

namespace SAarchive{
  
using namespace SAarchive;
using namespace std;

class SAFileNamer : public ArchiveModule {
public: 
	SAFileNamer();
	SAFileNamer(SATask stask);
  
	~SAFileNamer();
  /** returns a string containing the file name for the specific SA task output filename */
  string getFileName(SATask stask);
  /** No descriptions */
  void show();
  /** No descriptions */
  void setFileName(const string &fname);
  /** No descriptions */
  void init();
  /** No descriptions */
  void setTask(SATask ts);
  /** No descriptions */
  string getInputFileName(SATask stask);
  /** No descriptions */
  string getOutputFileName(SATask stask);
  /** No descriptions */
  void setFileName(const string &fname, SATask stask);
  /** No descriptions */
  string getBase();
  /** No descriptions */
  string getNameRoot();
  /** No descriptions */
  string getRSOPName(string type);
  /** No descriptions */
  void setContact(const string &cs);
  /** No descriptions */
  string getContact();
  /** No descriptions */
  string get_3914_FileName();
  /** No descriptions */
  string get_3916_FileName();
  /** returns as output a relative filename string given an all path filename string as input*/
  string getRelativeFileName(const string &allpathfn);
    int getContactNumber();

private:
AGILEFileName filename;
SATask mytask;
string procext; string corext; string rebext; string dredext;
string pbext; string srexext; string sranext;
string sub1;
string sub19;
string sub2;
string sub3;
string temp;
string olddrext;
string imext;
};
}
#endif
