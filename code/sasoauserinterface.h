/***************************************************************************
                          sasoauserinterface.h  -  description
                             -------------------
    begin                : Mon Mar 20 2006
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

#ifndef SASOAUSERINTERFACE_H
#define SASOAUSERINTERFACE_H


#ifndef RLMMTEST_H
# include "rlmmtest.h"
#endif

#ifndef PIPELINEHANDLER_H
#include "pipelinemodule.h"
#endif

#ifndef SASOAHANDLER_H
#include "sasoahandler.h"
#endif

#define NDET     4
#define NREGVAL     10
#define  NCHANVAL  1536
#define  HISTSIZVAL  1024

#include "hertagbase.h"
#include "agilefilename.h"
#include "systemconnector.h"
#include "sourcesextractor.h"
#include "safilenamer.h"
#include "sasoacommandlist.h"
#include "sasoacommand.h"
#include "saparameterslist.h"
#include "orbitrebuilder.h"
#include "corrector3905.h"
#include "safitshandler.h"
#include "dbconnector.h"
#include "agiledbconnector.h"
#include "okdaemon.h"
#include "processkiller.h"
#include "irosmap.h"
#include "sal3eventlist.h"
#include "sapointhistosplotter.h"
#include "version.h"
#include "saplotter.h"
#include "saimageplotter.h"
#include "saplot.h"
#include "sadatetime.h"
#include <sstream>
#include <map>
#include <stdlib.h>
#include <timer.h>
#include <filelist.h>
#include <exception>
#include "sadatetime.h"
#include "tdsdaemon.h"
#include "saexception.h"
#include "sagti.h"
#include <stdexcept>

extern  int plotsetctr;

namespace SApipeline{


using namespace SApipeline;
using namespace TDS;
using namespace SAdata;
using namespace examples;
using namespace SAarchive;
using namespace System;
using namespace std;


/**SA pipeline commandline user interface
  *@author Francesco Lazzarotto
  */

class SasoaUserInterface : public rlmmtest, public HertagBase {

public:
	SasoaUserInterface();
    /** No descriptions */
   SasoaUserInterface(bool verbose);
   
	~SasoaUserInterface();
  /** No descriptions */
   void handle_exitstage(int stagenumber);
  /** No descriptions */
   int handle_entrystage(int stagenumber);
  /** No descriptions */
  int run();
  /** No descriptions */
  int setModule(int module /*PipelineModule *module*/);
  /** No descriptions */
  void initPipeline();
  /** gives the received command to the pipeline */
  void setCommand(string commandline);
  /** decode the command line for pipeline operations */
  void decodeCommand(string line);
  /** No descriptions */
  void setBatch(bool val);
  /** No descriptions */
  void handle_quit();
  /** No descriptions */
  void handle_showcommandlist();
  /** No descriptions */
  void install();
  /** No descriptions */
  bool isFirstExec();
  /** create defaults basing on the selected instrument */
  void handle_setInstrument();
  /** No descriptions */
  void configureDefault();
  /** No descriptions */
  void handle_testiros();
  /** No descriptions */
  void handle_conf();
  /** shows user defined parameters */
  void showDefPar();
  /** No descriptions */
  void handle_showdef();
  /** No descriptions */
  void handle_showparameters();  
  /** No descriptions */
  void createDefPar();
  /** No descriptions */
  void setSasoaHome(const string &home);
  /** No descriptions */
  void setDetnam(const string &det);
  /** No descriptions */
  void init();
  /** No descriptions */
  void handle_syntax();
  /** No descriptions */
  void configureParameters() ;
  /** No descriptions */
  void handle_showconf();
  /** No descriptions */
  void showParamemeters();
  /** No descriptions */
  void setDefaultParameters();
  /** No descriptions */
  void eraseModule(const string & des);
  /** No descriptions */
  void addModule(const string &des,  const int &stagenum );
  /** No descriptions */
  void handle_sethome();
  /** No descriptions */
  void handle_showenv();
  /** No descriptions */
  void handle_verbose();
  /** No descriptions */
  void handle_EMIDaemon();
  /** No descriptions */
  void handle_rm_workenv();
  /** No descriptions */
  void handle_data();
  /** No descriptions */
  void refreshDefPar();
  /** No descriptions */
  void handle_refresh();
  /** No descriptions */
  void handle_cutL3file();
  /** No descriptions */
  void handle_testirosmap();
  /** No descriptions */
  void handle_correction();
  /** No descriptions */
  void handle_testrebuilder();
  /** No descriptions */
  void handle_testokdaemon();
  /** No descriptions */
  void handle_testdb();
  /** No descriptions */
  void handle_killprocess();
  /** No descriptions */
  void handle_admin();
  /** No descriptions */
  string getSasoaHome();
  /** No descriptions */
  void killAllProcs();
  /** No descriptions */
  void handle_l3test();
  /** No descriptions */
  void handle_pointing();
  /** No descriptions */
  void handle_testgnuplot();
  /** No descriptions */
  void handle_newtest();
  /** No descriptions */
  void handle_mdimg();
  /** No descriptions */
  void clean();
  /** No descriptions */
  void handle_datetest();
  /** No descriptions */
  void handle_testproducts();
  /** No descriptions */
  void handle_cutL3();
  /** No descriptions */
  void handle_detimage();
  /** No descriptions */
  void handle_otherimage();
  /** No descriptions */
  void handle_plotallmdimages();
  /** No descriptions */
  void handle_cleardata();
  /** No descriptions */
  void handle_startokdaemon();
  /** No descriptions */
  void handle_testattitude();
  /** No descriptions */
  void handle_testsystem();
  /** No descriptions */
  void exec_l3test(bool interactive);
  /** No descriptions */
  void handle_stage3test();
  /** No descriptions */
  void handle_stage2test();
  /** No descriptions */
  void handle_createirosmap();
  /** No descriptions */
  void handle_filelist();
  /** No descriptions */
  void handle_gti();
  /** No descriptions */
  void handle_multicontact();
  /** No descriptions */
  void handle_energy();
  /** No descriptions */
  void	handle_splitdata();
  /** No descriptions */
  void handle_loadcontact();
  /** No descriptions */
  void handle_unzip();
  /** No descriptions */
  void handle_autogti();
  /** No descriptions */
  void handle_setcontactsdir();
  /** No descriptions */
  void handle_allpipe();
  /** No descriptions */
  void handle_prepare();
  /** No descriptions */
  void handle_EMIpiperun(const string &cl);
  /** No descriptions */
  void handle_IROSpiperun(const string &cl);
  /** No descriptions */
  void handle_piperun(const string &cl);
  /** No descriptions */
  void exec_allpipe(int contactnum);
  /** No descriptions */
  void exec_allEMIpipe(int contactnum);
  /** No descriptions */
  void exec_allIROSpipe(int contactnum);
  /** No descriptions */
  void handle_newdaemon();
  /** No descriptions */
  void exec_EMI(int contactnum);
  /** No descriptions */
  void handle_setLUTs();
  /** No descriptions */
  void handle_quat_to_sapoi();
  /** No descriptions */
  void handle_extract_exposure();
  /** No descriptions */
  void handle_loadContcSSH();
  /** No descriptions */
  void exec_runContact(int contactnum);
  /** No descriptions */
  void exec_runEMIContact(int contactnum);
  /** No descriptions */
  void exec_runIROSContact(int contactnum);
  /** No descriptions */
  void exec_quat_to_sapoi(const string &c);
  /** No descriptions */
  void exec_loadContactSSH(int contactnum);
  /** No descriptions */
  void handle_asdc_daemon();
  /** No descriptions */
  void handle_exposure();
  /** No descriptions */
  void handle_largefile();
  /** No descriptions */
  void exec_gti(const string &l3file, const string &gtifile);
  /** No descriptions */
  void burst();
  /** No descriptions */
  void exec_burst(const string &fnam, double tmin, double tmax);
  /** No descriptions */
  void handle_TDS();
  /** No descriptions */
  void exec_attitude(int contactnum);
  private:
  int status;

 /** */  

 OKDaemon dem;
 /** */  
 SasoaHandler * pipeline;
 /** SA command list object*/
 SasoaCommandList comlist;
 /** single pair <command, value> to be inserted in the command list*/
 SasoaCommand parameter;
 /** */
  bool first_execution;
 /** name of the instrument to process data  */
  string instr;
 /** default parameters (path and other ...) for the pipeline set by user*/
  string defpar[20];
 /** string containing instruction to pass to the OS shell*/
  string sysinstr;
 /** */
  //string tempstring;
 /** */
  //stringstream ss;
 /** */  
  string SASOA_HOME;
 /** */
  string DETNAM;
 /** */
  string WORK_DET_PATH;
 /** */
  SAParametersList saparlist;
 /** map structure associating description name to stage number */
  map<string, int> pipmod;
 /** */
  bool verbose;
 /** */
  int counter;
 /** */    
};
}
#endif
/** No descriptions */

