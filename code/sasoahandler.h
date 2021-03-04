/***************************************************************************
                          pipelinehandler.h  -  description
                             -------------------
    begin                : Wed Feb 22 2006
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

#ifndef SASOAHANDLER_H
#define SASOAHANDLER_H



//#include "sadp_global.h"
/*
#ifndef  SASOAUSERINTERFACE_H
#include "sasoauserinterface.h"
#endif

#ifndef  INTERNALINTERFACE_H
#include "internalinterface.h"
#endif
*/

#include "pipelinemodule.h"
#include "archivehandler.h"
#include "orbitrebuilder.h"
#include "datareducer.h"
#include "photonlistbuilder.h"
#include "sourceanalyser.h"
#include "sourcesextractor.h"
#include "sasoacommandlist.h"
#include "sadatacorrector.h"
#include <iostream>
#include <fstream>


namespace SApipeline{
  
using namespace SApipeline;
using namespace DataCorrection;
//using namespace TDS;
//using namespace examples;

/**

  global arbiter module for SASOA pipeline operations
  the SasoaHandler set all the definitions/parameters/arguments
  as they're common for every run or useful for a single run
  @author Francesco Lazzarotto
*/
/**
The Finite State Machine representing the elaboration is
  shown by
   *  \image html fsm.png
   *  \image latex FSM.eps "SASOA Finite State Machine" width=10cm
    */

      /**
      In the SasoaHandler the stages are addressed with the stage number, an integer
      (signed) saved in the variable named stage
      stage is part of the status of the SasoaHandler that is (almost) a finite state machine

      */  
class SasoaHandler: public PipelineModule  {
  friend class SasoaUserInterface;
public:
	SasoaHandler();
	~SasoaHandler();
  /** launch a test run for all sadp stages */
  void launchTest();
  /** No descriptions */
  void setIROS(bool bv);
  /** No descriptions */
  bool isIROS();
  /** No descriptions */
  int init();
  /** No descriptions */
  void setDescription();
  /** No descriptions */
  void clean();
  /** No descriptions */
  void startAll();
  /** No descriptions */
  void launchDataReduction();
  /** No descriptions */
  void launchPhotonListBuilding();
  /** decode command given to the pipeline */
  SasoaCommandList *  decodeCommand();
  /** No descriptions */
  void setCommand(string command);
  /** No descriptions */
  void launchCurrentStage();
  /** sets the program defined in the commandlist to be executed by the pipeline  handler */
  int setProgram(const SasoaCommandList &comlist);
  /** No descriptions */
  void launchSourceAnalyser();
  /** No descriptions */
  void launchSourcesExtractor();
  /** set startup instruction/parameter to launch a generic pipeline stage
takes as input the stage number (different default settings have to be set) */
  void setParameters(int stagenum);
  /** No descriptions */
  void setAllExtern();
  /** No descriptions */
  void setDetNam(const string & dn);
  /** No descriptions */
  void setDefaultEnvironment();
  /** No descriptions */
  void createAllBatchScripts();
  /** No descriptions */
  void setAllEnvs();
  /** No descriptions */
  void setProgramName(const string &pn);
  /** No descriptions */
  string getProgramName();
  /** No descriptions */
  void createDefaults();
  /** No descriptions */
  string getDefaultInputFilename();
  /** No descriptions */
  void setIDL(bool b);
  /** No descriptions */
  void close();
  /** No descriptions */
  void setGlobalCommands(); 
  /** No descriptions */
  void clearTempData();
    void setArchiverEnv();
    void start();
  /** No descriptions */
  void initArchiveEnv();
  /** No descriptions */
  string getCurrentInputFileName();
  /** No descriptions */
  void launchOrbitRebuilding();
  /** No descriptions */
  void createAttitudeBatchScript();
  /** No descriptions */
  void setContact(const string &cn);
  /** No descriptions */
  bool isFirstRun();
  /** No descriptions */
  void setAuto(bool bval);
  /** No descriptions */
    void setTimeInterval();
  /** No descriptions */
    void launchSourcesExtractorV5();
  /** No descriptions */
    void launchCorrector();
 /** No descriptions */
    void execEMI(const string &indir);
	/*execEMI(const string &indir, const string &contactmin, const string &contactmax)*/
    void execEMI(const string &indir, const string &contactmin, const string &contactmax);
    void ephMerge(const string &contactmin, const string &contactmax, const string &outfile);

  /** No descriptions */
    pair<double, double> getMCTimeInterval(const string &fname);
  /** No descriptions */
    void saveMCTimeInterval(const string &fname);
    void loadContact(int n);
    void Correct3905L1(int nc);
    void setDefaultEnergyRange(pair <float, float> enrange);
    pair<float, float> getDefaultEnergyRange();
    void exec_allpipe(int contactnum);
    void deliverLogs();
    void ephCorrect(const string &infile, const string &outfile, double tstart, double tstop);
    void startAllV5();
    void startAllDebug();
    void deliverEphFile();
    void setStatusOnDB(string taskname);

  ArchiveHandler sarchiver;
  
  private:

   /** */
  /** */
  OrbitRebuilder orbilder;
    /** */
  DataReducer dreducer;
  /** object implementing stage 1 functions */
  PhotonListBuilder pbuilder;
  /** object implementing stage 2 functions */
  SourceAnalyser sanalyser;
  /** object implementing stage 3 functions */
  SourcesExtractor srcxtractor;
  /** commandlist object as passed by User Interface
   there is also the commandlist object inherited by
   PipelineModule
  */
  SADataCorrector sc;
  /** */
  string PNAME;
  /** object implementing stage 0 functions */

  /** */
  SasoaCommandList mycommands; 
  /** */
  int entrystage;
  /** */
  int exitstage;
  /** stage handled at a certain time by the handler automaton (== status of the automaton) */
  int stage;
  /** */
  map<string, string>::iterator p;
  /** */
  bool automatic;
  /** */
  bool firstrun;
  /** */
  bool irosflag;

  AGILEDBConnector *dbp;
};


}
#endif
