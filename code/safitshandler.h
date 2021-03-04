/***************************************************************************
                          safitshandler.h  -  description
                             -------------------
    begin                : Tue Sep 19 2006
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
#ifndef SAFITSHANDLER_H
#define SAFITSHANDLER_H

#include "archivehandler.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <CCfits>
#include <cmath>
#include <FITS.h>
//#include "sakeyword.h"
#include <KeyData.h>
#include "safilenamer.h"
#include "hertagbase.h"
#include "archivehandler.h"


/**Base program to handle FITS files
  *@author Francesco Lazzarotto
  */

namespace SApipeline{
using namespace SApipeline;
using namespace SAarchive;
using namespace std;
using namespace CCfits;
using std::valarray;
class SAFitsHandler : public HertagBase {
public:
    SAFitsHandler(bool testflag);
    SAFitsHandler();
    SAFitsHandler(const string &infile, const string &outfile);
    /** constructor for read-only applications */
    SAFitsHandler(const string &infile);
  ~SAFitsHandler();
  /** No descriptions */
  void setOutputFileName(const string &ofn);
  /** No descriptions */
  void setInputFileName(const string &ifn);
  /** No descriptions */
  virtual int process();
  /** No descriptions */
  void closeInputFile();
  /** No descriptions */
  void openInputFile();
  /** No descriptions */
  void closeOutputFile();
  /** No descriptions */
  void openOutputFile();
  /** No descriptions */
  void readInputFile();
  /** No descriptions */
  void saveOutputFile();
  /** reports standard information about the fits file (works for EACH file) */
  void report();
  /** No descriptions */
  void setVerbose(bool mode);
  /** No descriptions */
  void init();
  /** No descriptions */
  void setRelativeFileNames();
  /** No descriptions */
  void show();
  /** No descriptions */
  void removeOldOutfile();
  /** set an environment variable with a given name (oev), with the value oevn where to write the trigger (OK) file to trigger the following(s) application(s)
 */
  void setOutTrigFileEnvVar(const string &oev, const string &vn);
/** retrieve the I/O dir strings from yet present information*/
  void retrieveIODataDirs();
  /** */
  void retrieveInputDataDir();
  
  /** */
  int processSafe();

  /** */
  void printerror(int status);
  /** */
  string getPHDUKeyWord(const string &keyname, int keytype);
  /** */  
  string getKeyWord(const string &keyname, int keytype, int hdunum);
  /** */  
  void readHeader(const string &hduname);
    double getDataDuration();
    double getTstart();
    double getTstop();

protected:
  /** true if the infilename variable is set with a (reasonable) string */
  bool infileset;
  /** true if the outfilename variable is set with a (reasonable) string */
  bool outfileset;
  /** true if the infiledir variable is set with a (reasonable) string */
  bool infiledirset;
  /** true if the outfiledir variable is set with a (reasonable) string */
  bool outfiledirset;

  /** file name object to handle filenames involved with the FITS handler*/
AGILEFileName afilename;

ArchiveHandler archiver;
/** complete path or relative to the current local directory
this will be used by the reading procedure*/
string infilename;
/**   complete path or relative to the current local directory
this will be used by the writing procedure */
string outfilename;
/** input filename relative  to the input data directory directory (without the path) */
string rel_infilename;
/** output filename relative  to the output data directory (without the path) */
string rel_outfilename;
/** directory path string where the procedure expects the input file */
string inputfiledir;
/** directory path string where the procedure will create the output file */
string outputfiledir;
/** */
int status;

//std::auto_ptr<FITS> outFile(0); // pointer to the output file
//
//std::auto_ptr<FITS> pInfile(new FITS("PKP000647_f_3905_000.lv1",Read,hdus,false));

FITS *poutFile;

FITS  *pinFile;

std::auto_ptr<FITS> outFileRef;

std::auto_ptr<FITS> inFileRef;

std::vector<string> hdus;

/*true if the input file is open*/
bool in_open;

/*true if the output file is open*/
bool out_open;


fitsfile *infptr;      // pointer to the FITS file, defined in fitsio.h 

fitsfile *outfptr;     // pointer to the new FITS file   


vector<string> kn; //keyword names
			/** */
vector<double> kv;  //keyword double values
   	
vector<string> sv;  //keyword string values

vector<int> iv;  //keyword integer values

double tstart;

double tstop;

double duration;
   
};
}
#endif
