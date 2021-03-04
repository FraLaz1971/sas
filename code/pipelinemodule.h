/***************************************************************************
                          pipelinemodule.h  -  description
                             -------------------
    begin                : mar feb 28 2006
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
/***************************************************************************
This software is part of the of the SuperAGILE instrument data 
analysis software library
 ***************************************************************************/

#ifndef PIPELINEMODULE_H
#define PIPELINEMODULE_H
 #include <stdlib.h>
 
 #include <string>
 #include <vector>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <dirent.h>
 #include "timer.h"
 #include "sasoacommandlist.h"
 #include "safitshandler.h"
 #include "sasoacommand.h"
 #include "sadefinitions.h"
 #include "agiledbconnector.h"
 #include "dbconnector.h"
 #include <exception>
 #include "safitshandler.h"
 #include "archivehandler.h" 
 #include "safilenamer.h"
 #include "systemconnector.h"
 

using namespace std;

namespace SApipeline{
using namespace SApipeline;
using namespace SAarchive;
using namespace DB;
using namespace System;

/**Class implementing generic functionalities of SA pipeline modules
  *@author Francesco Lazzarotto
  */

/** class pipeline module : execute a pipeline stage (=macrofilter)
takes as input a photonlist data file and gives as output  a filtered eventlist
secundary input data (files) are requested and secundary output products are produced

INPUT:
level k eventlist

secundary INPUT:
gain LUT

OUTPUT:
level k+1 eventlist

secundary OUTPUT:

1)
*/                  
/**
The activity diagram of usage and elaborations made by SASOA
 \image html sasoa_activity.png
*/
/**
  Pipeline modules are addressed with the SATask identificative : an enumerative type variable
  
  
*/

class PipelineModule  : public SAFitsHandler {
public:

  /** No descriptions */
  PipelineModule();
  /** No descriptions */
  PipelineModule(PipelineModule &pm);
	~PipelineModule();
  /** No descriptions */
  int init();
  virtual void setDescription(){};
  /** start pipeline module elaborations */
  virtual void start(){};                        
  /** launch the execution of the pipeline stage */
  virtual int run();
  /** launch generic pipeline module, input format is correct for every stage  */
  void  launch(string &infile, string &outfile, vector<int> &params);
  /** sets default input values needed for the execution    */
  /** launch generic pipeline module, input format new version  */
  void  launch(const string &infile, const string &outfile, const SasoaCommandList &params);
  /**  the first time the execution is done, user defined values are provided*/
  virtual void setDefault();
  /** No descriptions */
  virtual void launchIDL_Batch(){};
  /** No descriptions */
  void setExtern(bool value);
  /** No descriptions */
  virtual void setOutputDir(const string &dname);
  /** No descriptions */
  virtual void setInputFileName(const string &fname);
  /** show default setting */
  void showDefault();
  /** No descriptions */
  bool isExtern();
  string getDefaultOutputDir();
  /** No descriptions */
  string getWorkDir();
  /** No descriptions */
  void setWorkDir();
  /** No descriptions */
  bool isIDLon();
  /** No descriptions */
  void setIDL(bool val);
  /** read default parameters from aux file def/defval.txt */
  void readDefaultPar();
  /** save default parameters in aux file def/defval.txt*/
  void saveDefaultPar();
  /** sets on memory variables the customized work environment
(path, parameters, ...) */
  void setWorkEnv(string par[10]);
  /** No descriptions */
  virtual  string getInputFileName();
  /** No descriptions */
  void setVerbose(bool val);
  /** No descriptions */
  void set_IDL_Display(bool val);
  /** No descriptions */
  string retrieveFilename(const string &ext, const string &dir, int extnum);
  /** No descriptions */
  void setEnvironment(string envstrings[4]);
  /** No descriptions */
  void setDefaultEnvironment();
  /** No descriptions */
  void setSasoaHome(const string &sh);
  /** No descriptions */
  string getSasoaHome();
  /** No descriptions */
  void showEnvironment();
  /** No descriptions */
  void passOutputFile(const string &toutdir);
  /** No descriptions */
  string getUserHome();
  /** No descriptions */
  virtual void setDetNam(const string &dn);
  /** No descriptions */
  void saveDefaultDetNam(const string &dn);
  /** No descriptions */
  string retrieveDefaultDetNam();
  /** No descriptions */
  string getDetnam();
  /** No descriptions */
  string getIDLSourcePath();
  /** No descriptions */
  string getSasoaWorkEnv();
  /** No descriptions */
  void setSasoaWorkEnv(const string &we);
  /** No descriptions */
  virtual string getInputDataPath();
  /** No descriptions */
  string getProductPath();
  /** No descriptions */
  string getOutputPath();
  /** No descriptions */
  string getOutputDir() const;
  /** No descriptions */
  void retrieveOutdir(const PipelineModule &pm);
  /** No descriptions */
  string getInputFileName(const string & dir, const string &ext);
  /** No descriptions */
  string getDefaultInputDir()  ;
  /** No descriptions */
  string getInfileRoot() const ;
  /** gives
  true if the module has performed the elaboration
  false if not*/
  bool executed();

  /** No descriptions */
  void setDefaultOutputDir();
  /** No descriptions */
  virtual void rmTempInputFiles();
  /** No descriptions */
  void close();
  /** No descriptions */
  virtual void deliveryOutputData();
  /** No descriptions */
  void retrieveInputData();
  /** No descriptions */
  void createCommonDef();
  /** No descriptions */
  void setLUTs();
  /** No descriptions */
  string getSasoaWorkDir();
  /** No descriptions */

  void installDefaultLUTs();
  /** No descriptions */
  void setDefaultLUTs();
  /** No descriptions */
  virtual void deliverProducts();
  /** No descriptions */
  void createDeliveryScript();
/** Returns the directory where to deliver SASOA final products */
  string getDeliverDirectory();
  /** No descriptions */
  virtual void announceDelivery();
  /** No descriptions */
  virtual void createLaunchBatchScript();
  /** No descriptions */
  void finalizeLaunch();
  /** No descriptions */
  void prepareLaunch();
  /** No descriptions */
  void setCommand(SasoaCommand &sc);
  /** No descriptions */
  void setCommandList(const SasoaCommandList &scl);
  /** No descriptions */
  virtual int setProgram(const SasoaCommandList &scl);
  /** No descriptions */
  SasoaCommandList getCommand();
  /** No descriptions */
  string getOutputFileName();
  /** No descriptions */
  SasoaCommandList getCommandList();
  /** No descriptions */
  string retrieveSasoaHome();
  /** set the path of the input directory where to search the input file */
  void setInputDir(string indir);
  /** No descriptions */
  string getDescription();
  /** No descriptions */
  void DBConnect(const string connstring[5]);
  /** No descriptions */
  bool isFirstExec();
  /** No descriptions */
  string getSasoaRunDir();
  /** No descriptions */
  void createSasoaRunDir();
  /** No descriptions */
  int getSasoaRunID();
  /** No descriptions */
  void setArchiveHandler(ArchiveHandler *ah);
  /** No descriptions */
  void rmTempOutputFiles();
  /** No descriptions */
  void rmTempFiles();
  /** No descriptions */
  virtual void prepareInputFile();
  /** No descriptions */
  void setAuto(bool b);
    /** No descriptions */
  bool isAuto();
  /** No descriptions */
  virtual void setContact(const string &s);

  /** No descriptions */
    void setTstart(double ts);

  /** No descriptions */
    void setTstop(double ts);

  /** No descriptions */
    double getTstart();

  /** No descriptions */
    double getTstop();
  /** No descriptions */
    void printTimeInterval(ostream &o);
  /** No descriptions */
    void readHeader(const string &fname);
  /** fill the filelist string vector with a list read from an input text file */
    void fillFilelist(const string &listfilename);
   /** */
    void setOutputFilename(const string &ofn);
   /** */
    void setInputFilename(const string & fn);
   /** */
    void setContactMin(int cmi);
   /** */
    void setContactMax(int cma);
   /** */
    int getContact();
   /** */
    int getContactMax();
   /** */
    int getContactMin();
    void setAGILEDBConnector(AGILEDBConnector *adb);

public:
string tempstring;
/** remember to change to protected if needed*/  
ArchiveHandler *arc;

protected:

   /** */
vector<string> filelist;

   /** */
double tstart;

   /** */
double tstop;

   /** */
int contactmin;

   /** */
int contactmax;

   /** */
int contact;

/** set on/off screen messages on screen*/
//bool verbose;
/** reports the description of the specific module elaboration type*/
bool derived; // flag on the inheritance level
/** string definining which kind of pipeline module
    identifies also the elaboration stage
    description = "DataReduction"       -->  stage = 0
    description = "PhotonListBuilding"  -->  stage = 1
    description = "SourcesExtractor"    -->  stage = 2
    description = "SurceAnalyser"       -->  stage = 3
    description = "Correction"          -->  stage = 4
    description = "OrbitRebuilder"      -->  stage = 5    
  */
  const char * description;
  /** string containing inputfilename (complete path)*/
  string infile;
    /** string containing outputfilename (complete path)*/
  string outfile;
    /** parameters vector*/
  vector <int> params;
  /** reports the status of execution of some elaboration
  [status == 0 -> correct state]
  [status == 1 -> error type 1 ]
  [status == 1 -> error type 2 ]
  ...
  ...
  [status == n -> error type n ]
  */

  /** */
  int pos;
  /** */
  int sasoarun_id;
  /** */
  bool extern_lan;
  /// oroginal work environment variables from edm_software file common.def
  string path_in;       /// input path of TE_Acq program
  /** */
  string path_tab;    /// output path of address identification tables
  /** */
  string path_conf;  /// input path of configuration files
  /** */
  string path_res;    /// input path of products
  /** */
  string path_hk;     /// input path of HK files
  /** the directory where to install the sasoa package source root directory */
  string SASOA_HOME;
  /**  the directory containing the data to process related to a particular instrument/prototype/simulator */
  string DETNAM;
  /** the root directory of the SASOA work environment */
  string SASOA_INST_ENV;
  /** the directory related to a certain instrument/protoytpe */
  string WORK_DET_PATH;
  /** saves the directory path containing the extern source code performing the pipeline elaboration (if needed)*/
  string source_path;
  /** path of the directory containing data input from sasoa*/
  string input_path;
  /** path of the directory containing output data from sasoa that can be (main) input for sasoa*/
  string output_path;
  /** path of the directory containing output (data) products that are not (main) input for sasoa */
  string products_path;
  /** data working directory containing all data related to a SASOA measurement set input
  the name is extracted from the lv1 file name truncating the .lv1 extension
  workdir is equal to product_path+outdir*/
  string workdir;
  /** */
  string outdir;
  /** flag to set on idl processing */
  bool idl_on;
  /** flag to set on idl display plot function */
  bool idl_display;
 /** */
  bool exec;
 /** */
  bool created_del_dir;
 /** */
  bool autoflag; 
 /** */
  Timer timer;
 /** */
  int i;
 /** */
  SasoaCommandList  commandlist;
 /** */
  exception e;
 /** */
  SAFileNamer filenamer;
 /**Module that handles the FITS data file */
  SAFitsHandler *fitser;
/** pointer to a DB connector object*/
  DBConnector *database;
/** pointer to a AGILE DB connector object*/
  AGILEDBConnector *agiledb;
 /** */
  SystemConnector syscon;

  GTI mygti;

  pair<double, double> timeinterval;

  pair<float, float> energyinterval;

  };
}
#endif
