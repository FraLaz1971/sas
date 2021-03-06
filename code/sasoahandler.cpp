/***************************************************************************
                          SasoaHandler.cpp  -  description
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

#include "sasoahandler.h"
#include "tdsdaemon.h"
#include <vector>


namespace SApipeline{
using namespace SApipeline;
using namespace TDS;

SasoaHandler::SasoaHandler(){
	firstrun = false;
	automatic = false;
	exec = false;
	// cout << "creating SasoaHandler::SasoaHandler()" << endl;
	stage = -1;    derived = 1;
	// MODIFIED 22/03/2007
	entrystage = -1;
	sasoarun_id = 0;
	commandlist.setVerbose(false);
	setIROS(true);
}

SasoaHandler::~SasoaHandler(){

}

/** launch a test run for all sadp stages */
void SApipeline::SasoaHandler::launchTest(){
    int testvalue;
    testvalue = dreducer.executeOp1(12, 1);
    testvalue = dreducer.executeOp2(6, 0);
}
/** startup operation for the pipeline handler */
int SApipeline::SasoaHandler::init(){
  cout << "SasoaHandler::init() verbosity set to false" << endl;
  cout << "SasoaHandler::init() you may change verbosity option" << endl;
  cout << "SasoaHandler::init() modifying this method" << endl;
  mycommands.setTempDataMode("false");
  status = 1;
  orbilder.setVerbose(false);
  dreducer.setVerbose(false);
  pbuilder.setVerbose(false);
  srcxtractor.setVerbose(false);
  if (verbose) cout << "SasoaHandler::init() executed !" << endl;
  return status;
}
/** No descriptions */
void SApipeline::SasoaHandler::setDescription(){
  ////cout << "SApipeline::SasoaHandler::setDescription()" << endl;
  description = (const char *)"[pipeline global handling]";
}
/** No descriptions */
void SApipeline::SasoaHandler::clean(){

}
/** No descriptions */
 void SApipeline::SasoaHandler::startAllV5(){
  cout << "SasoaHandler::startAllV5() executing ..." << endl;
  setIROS(true);
  if (verbose) cout << "SasoaHandler::startAllV5 input file = " << mycommands.getInputFilename() << endl;
  sarchiver.filenamer.setFileName(mycommands.getInputFilename());
  setGlobalCommands();  setArchiverEnv();
  //initArchiveEnv();
  sasoarun_id++;  createSasoaRunDir();
  stage = entrystage;
  while(stage <= exitstage){
       launchCurrentStage();
       stage++;
  }
  sarchiver.retrieveArchiveDir(orbilder.getOrbitString());
  sarchiver.createCurrentArchiveDir();
  int a = sarchiver.getCurrentContactNumber();
  cout << "SasoaHandler::startAllV5() executing analysis on contact " << a << endl;
  
    string cminimo, cmaximo, outf;
    ss.str(""); ss << (a - 1); cminimo = ss.str();
    ss.str(""); ss <<  a ; cmaximo = ss.str();

    outf = "tempout.fits";
    ephMerge(cminimo, cmaximo, outf);
          
    string tempstring;
    int nf = 6;
    pair<double, double> md;
    md.first = 0.;
    md.second = 0.;    
    vector<string> v;
    DBConnector db;

  sarchiver.moveDeliverableData(sarchiver.getArchiveDir());
  deliverLogs(); // move logs to delivery dir
  sarchiver.moveDeliverableData(sarchiver.getArchiveDir()); // archive what is in the delivery dir
  							    // in the contact dir
  if (isAuto()) clearTempData();
  if(!mycommands.getTempDataMode()) clearTempData();
  mycommands.reset();
  cout << "SasoaHandler::startAllV5() ended " << a << endl;
}



/** No descriptions */
 void SApipeline::SasoaHandler::startAll(){
  setIROS(false);
  cout << "SasoaHandler::startAll() executing " << endl;
  if (verbose) cout << "SasoaHandler::startAll input file = " << mycommands.getInputFilename() << endl;
  sarchiver.filenamer.setFileName(mycommands.getInputFilename());
  setGlobalCommands();  setArchiverEnv();
  //initArchiveEnv();
  sasoarun_id++;  createSasoaRunDir();
  stage = entrystage;
  while(stage <= exitstage){
       launchCurrentStage();
       stage++;
  }
  sarchiver.retrieveArchiveDir(orbilder.getOrbitString());
  sarchiver.createCurrentArchiveDir();
  int a = sarchiver.getCurrentContactNumber();
  cout << "SasoaHandler::startAll() stages ended, I am executing analysis on contact " << a << endl;

    string cminimo, cmaximo, outf;
    ss.str(""); ss << (a - 1); cminimo = ss.str();
    ss.str(""); ss <<  (a  + 1); cmaximo = ss.str();

    outf = "tempout.fits";

try{  
    ephMerge(cminimo, cmaximo, outf);
 } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in merging ephemeris " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in merging ephemeris " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception exception in merging ephemeris" << endl;
  }          

    string tempstring;
    int nf = 6;
    pair<double, double> md;
    md.first = 0.;    md.second = 0.;    
    vector<string> v;
    //AGILEDBConnector db(dbcs);
    //DBConnector db(dbcs);
    DBConnector db;

    try{
    	md = db.getTimeInterval((a - 2), (a + 1));
	cout << "SasoaHandler::startAll() tstart = " << md.first << endl;
	cout << "SasoaHandler::startAll() tstop = " << md.second << endl;
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception" << endl;
  }

    string os1("../SATemporalDataSet/eph_tempout.fits");
    string os2("../SATemporalDataSet/eph_testout.fits");  
    double tstas, tstos;
    tstas = md.first + 756950400;
    tstos = md.second + 756950400;

try{
    ephCorrect(os1, os2, tstas, tstos);
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in correcting eph files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in correcting eph files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception" << endl;
  }

  
try{
  sarchiver.moveDeliverableData(sarchiver.getArchiveDir());
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in moving Deliverable Data" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in moving Deliverable Data" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception" << endl;
  }
//  string ts = sarchiver.getArchiveDir() + "/EMI";
    string ts = sarchiver.getArchiveDir();
    ss.str(""); ss << a; cminimo = ss.str();
    ss.str(""); ss << a ; cmaximo = ss.str();

  cout << "SasoaHandler::startAll() going to exec EMI " << endl;

try{
     execEMI(ts, cminimo, cmaximo); 
//    execEMI(ts); // orbital execution
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in executing EMI" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in  executing EMI" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in  executing EMI" << endl;
  }
try{
  deliverLogs(); // move logs to delivery dir
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in  Delivering log files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in Delivering log files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in Delivering log files" << endl;
  }
/*
try{
  sarchiver.moveDeliverableData(sarchiver.getArchiveDir()); // archive what is in the delivery dir
    } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in  Delivering log files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in Delivering log files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in Delivering log files" << endl;
  }			
*/				    // in the contact dir
  if (isAuto()) clearTempData();
  if(!mycommands.getTempDataMode()) clearTempData();
  mycommands.reset();
}


/** No descriptions */
 void SApipeline::SasoaHandler::startAllDebug(){
	setIROS(false);
	cout << "SasoaHandler::startAllDebug() executing " << endl;
	if (verbose) cout << "SasoaHandler::startAllDebug() input file = " << mycommands.getInputFilename() << endl;
	sarchiver.filenamer.setFileName(mycommands.getInputFilename());
	setGlobalCommands();  setArchiverEnv();
	//initArchiveEnv();
	sasoarun_id++;  createSasoaRunDir();
	stage = entrystage;
	/* launch all stages for the selected kind of run */
	while(stage <= exitstage){
		launchCurrentStage();
		stage++;
	}
		sarchiver.retrieveArchiveDir(orbilder.getOrbitString());
		sarchiver.createCurrentArchiveDir();
		int a = sarchiver.getCurrentContactNumber();
		cout << "SasoaHandler::startAllDebug() stages ended, I am executing analysis on contact " << a << endl;		
		cout << "SasoaHandler::startAllDebug() going to MERGE ephemeris file for contact " << a << endl;
		cout << "SasoaHandler::startAllDebug() merging ephemeris file for contacts " << (a-1) << " to " << a << endl;
		//  string ts = sarchiver.getArchiveDir() + "/EMI";
		string ts = sarchiver.getArchiveDir();
		string cminimo, cmaximo, outf;
		ss.str(""); ss << (a - 1); cminimo = ss.str();
		ss.str(""); ss <<  a  ; cmaximo = ss.str();		
		cout << "" << endl;
		outf = "tempout.fits";
    /// perform ephemeris file TM3916 merging 
    try{
       cout << "SasoaHandler::startAllDebug() merging ephemeris file " << endl;
       ephMerge(cminimo, cmaximo, outf);
     } catch(const SAexception &se){
       cerr << "SasoaHandler::startAllDebug() SA exception in merging ephemeris Data TM3916" << se.getMsg() << endl;
     } catch(const exception &e){
       cerr << "SasoaHandler::startAllDebug() standard exception in merging ephemeris Data TM3916" << e.what() << endl;
     } catch(...){
       cerr << "SasoaHandler::startAllDebug() generic exception" << endl;
     } 

     cout << "SasoaHandler::startAllDebug() going to CORRECT ephemeris file for contact " << a << endl;
/*
    string tempstring;
    int nf = 6;
    pair<double, double> md;
    md.first = 0.;
    md.second = 0.;    
    vector<string> v;
    
    DBConnector db;

    try{
    	md = db.getTimeInterval((a - 2), (a + 1));
	cout << "SasoaHandler::startAllDebug() tstart = " << md.first << endl;
	cout << "SasoaHandler::startAllDebug() tstop = " << md.second << endl;
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAllDebug() exception in " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAllDebug() exception in " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAllDebug() generic exception" << endl;
  }
*/
    /*
    tstas = md.first;
    tstos = md.second;

    */

    string os1("../SATemporalDataSet/eph_tempout.fits");
    string os2("../SATemporalDataSet/eph_testout.fits");  
    
    double tstas, tstos;
    
    tstas = srcxtractor.getTstart();
    tstos = srcxtractor.getTstop();

    cout << "SasoaHandler::startAllDebug() going to correct tstart" << " in "  << tstas << endl;
    cout << "SasoaHandler::startAllDebug() going to correct tstop"  << " in " << tstos << endl;

        
try{


    ephCorrect(os1, os2, tstas, tstos);
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAllDebug() exception in correcting eph files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAllDebug() exception in correcting eph files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAllDebug() generic exception" << endl;
  }

  
try{
  sarchiver.moveDeliverableData(sarchiver.getArchiveDir());
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAllDebug() exception in moving Deliverable Data" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAllDebug() exception in moving Deliverable Data" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAllDebug() generic exception" << endl;
  }
//  string ts = sarchiver.getArchiveDir() + "/EMI";
    ts = sarchiver.getArchiveDir();
    ss.str(""); ss << a; cminimo = ss.str();
    ss.str(""); ss << a ; cmaximo = ss.str();

  cout << "SasoaHandler::startAll() going to exec EMI " << endl;

try{
     execEMI(ts, cminimo, cmaximo); 
//    execEMI(ts); // orbital execution
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in executing EMI" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in  executing EMI" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in  executing EMI" << endl;
  }
try{
  deliverLogs(); // move logs to delivery dir
  } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in  Delivering log files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in Delivering log files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in Delivering log files" << endl;
  }
	    /*
	    try{
  sarchiver.moveDeliverableData(sarchiver.getArchiveDir());
    } catch(const SAexception &se){
    cerr << "SasoaHandler::startAll() exception in  Delivering log files" << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::startAll() exception in Delivering log files" << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::startAll() generic exception in Delivering log files" << endl;
  }
    */ 
			    
			    // in the contact dir
  if (isAuto()) clearTempData();
  if(!mycommands.getTempDataMode()) clearTempData();
  mycommands.reset();
}


/** No descriptions */
void SApipeline::SasoaHandler::launchDataReduction(){
  dreducer.prepareInputFile();
  dreducer.printTimeInterval(cout);
  if (verbose) showAlert();
  dreducer.prepareLaunch();
  dreducer.setDefault(); ///
  setParameters(0);
  dreducer.launch(infile, outfile, params);
  tempstring = dreducer.getUserHome()+"/SASOA/"+dreducer.getDetnam()+"/data/L19";
  dreducer.passOutputFile(tempstring); /// control: generalize?
  dreducer.finalizeLaunch();
}
/** No descriptions */
void SApipeline::SasoaHandler::launchPhotonListBuilding(){
  pbuilder.printTimeInterval(cout);
  pbuilder.prepareLaunch();
  pbuilder.setDefault();
  pbuilder.retrieveOutdir((PipelineModule&)dreducer);
  setParameters(1);
  pbuilder.launch(infile, outfile, params);  // #### REMEMBER TO UNCOMMENT !!
  tempstring = pbuilder.getUserHome()+"/SASOA/"+dreducer.getDetnam()+"/data/L2";
  pbuilder.passOutputFile(tempstring); // control: generalize?
  tempstring2 = pbuilder.getOutputFileName();
  mycommands.setInputFileName(tempstring2);  
  srcxtractor.setInputFileName(tempstring2);
  srcxtractor.setAuto(true);
  //pbuilder.rmTempInputFiles();  // #### REMEMBER TO UNCOMMENT !!
  pbuilder.finalizeLaunch();  
}
/** decode command given to the pipeline */

SasoaCommandList * SApipeline::SasoaHandler::decodeCommand(){
  return &mycommands;
}

}  /** No descriptions */
void SApipeline::SasoaHandler::setCommand(string command){
  //cout << "SasoaHandler : received command =  " << command << endl;
}
/** launch the selected stage and set appropriated parameters  */
void SApipeline::SasoaHandler::launchCurrentStage(){
  agiledb = new AGILEDBConnector();
  int c = sarchiver.getCurrentContactNumber();
  cout << "SasoaHandler::launchCurrentStage() processing contact " << c << endl;
    switch(stage){
     case -1:
           cout << "entering stage -1 execution (Orbit Rebuilding)" << endl;
           //           if(!mycommands.isOutDirSet()) dreducer.setDefaultOutputDir();
           launchOrbitRebuilding();
	   setTimeInterval();
	   tempstring = "OrbitRebuilding";agiledb->setSasoaStatusOnDB(c, tempstring);
           cout << "ended stage -1 execution (Orbit Rebuilding)" << endl;
     break;
     case 0:
           cout << "entering stage 0 execution (Data Reduction)" << endl;
           //           if(!mycommands.isOutDirSet()) dreducer.setDefaultOutputDir();
           launchDataReduction();
	   tempstring = "reduction";agiledb->setSasoaStatusOnDB(c, tempstring);
           cout << "ended stage 0 execution (Data Reduction)" << endl;
     break;
      case 1:
           cout << "entering stage 1 execution (Photonlist building)" << endl;
           launchPhotonListBuilding();
	   tempstring = "photonlist";agiledb->setSasoaStatusOnDB(c, tempstring);
           cout << "ended stage 1 execution (Photonlist building)" << endl;
    break;
     case 2:
           cout << "entering stage 2 execution (Sources extraction)" << endl;
	   srcxtractor.setAGILEDBConnector(agiledb);
           srcxtractor.setProgram(mycommands); /// sets the commands for the stage 2 execution
	   if (isIROS()) {
             launchSourcesExtractorV5();
	   } else {
	     launchSourcesExtractor();
	   }
           cout << "ended stage 2 execution (Sources extraction)" << endl;
     break;
     case 3:
           cout << "entering stage 3 execution (Source analysis)" << endl;
            launchSourceAnalyser();
           cout << "ended stage 3 execution (Source analysis)" << endl;
     break;
     default:
           cout << "unknown  stage number !" << endl;
     break;
  }
  delete agiledb;
}

/** sets the program defined in the commandlist to be executed by the pipeline  handler */
int SApipeline::SasoaHandler::setProgram(const SasoaCommandList &comlist){
        status = 1;        
        try{
            cout << "executing SasoaHandler::setProgram()" << endl;
            mycommands = comlist;
            tempstring = "entrystage";
            entrystage =  atoi(mycommands.getValue(tempstring).c_str());
            tempstring = "exitstage";
            exitstage = atoi(mycommands.getValue(tempstring).c_str());
        } catch (const exception &e){
            cerr << "SasoaHandler::setProgram() caught exception "<< e.what() << endl;
            status = 1;
        }
        status = 0;
        return status;
}

/** No descriptions */
void SApipeline::SasoaHandler::launchSourcesExtractorV5(){
  setParameters(2);
  commandlist = srcxtractor.getCommandList();
  cout << "SasoaHandler::launchSourcesExtractorV5() reading the header of the file" << commandlist.getInputFilename() << endl;
  //commandlist.getInputFilename();
  srcxtractor.PipelineModule::readHeader(commandlist.getInputFilename());
  srcxtractor.printTimeInterval(cout);
  srcxtractor.prepareLaunch();
  srcxtractor.setDefault();
  
  //srcxtractor.setCommandList(mycommands);

  if (!commandlist.isPathAbsolute()) srcxtractor.setDefaultOutputDir();
  else  srcxtractor.setOutputDir(commandlist.getOutputDir()); 

  // create sapoi as input to the exposure calculator
/*
    srcxtractor.createSapoiLaunchBatch();
    srcxtractor.createSapoiDatacard();
    srcxtractor.launchSapoiCreator();

  // perform attitude correction

  srcxtractor.createAttitudeBatchScript();
  srcxtractor.createAttitudeDatacard();
  srcxtractor.launchAttitudeCorrection();

  // calculate Saga GTI

  srcxtractor.createSagaBatch();
  srcxtractor.createSagaIDLBatch();
  srcxtractor.launchSaga();

  // calculate Exposure GTI
  srcxtractor.createExposureBatch();
  srcxtractor.createExposureDatacard();
  srcxtractor.launchExposure();
*/
//  srcxtractor.getInputFileName()
//  srcxtractor.launchIrosV4( mycommands.getInputFilename() );
//  prova_outfile_L3.evt
//getAbsoluteInputFileName()
	tempstring = "outL3.evt";
	srcxtractor.launchIrosV4(srcxtractor.getAbsoluteInputFileName(), srcxtractor.getAttitudeFileName(), tempstring);

  // filter for generated GTI

  bool debug = false;
  try{
//  	srcxtractor.launchIrosMapBuilder(debug);
  } catch (const exception &e){
  cerr << "exception errror occurred in handling L3 eventlist " << e.what() << endl;
}

if (commandlist.getIrosMode() ) {


} else {
	cout << "SasoaHandler::launchSourcesExtractor() Iros is not set: saving the filtered list" << endl;
	srcxtractor.createFilteredL3List();
}
  cout << "SasoaHandler::launchSourcesExtractor() going to exec srcxtractor.passOutputFile()"<< endl;
  tempstring = srcxtractor.getUserHome()+"/SASOA/"+srcxtractor.getDetnam()+"/data/L3";
  srcxtractor.passOutputFile(tempstring); // control: generalize?
  srcxtractor.deliverProducts();
  srcxtractor.announceDelivery();
  srcxtractor.finalizeLaunch();  
}

/** No descriptions */
void SApipeline::SasoaHandler::launchSourcesExtractor(){
  setParameters(2);
  commandlist = srcxtractor.getCommandList();
  if (verbose) cout << "SasoaHandler::launchSourcesExtractor() EMI reading the header of the file " << commandlist.getInputFilename() << endl;
  //commandlist.getInputFilename();
  srcxtractor.PipelineModule::readHeader(commandlist.getInputFilename());
  if (verbose) cout << "SasoaHandler::launchSourcesExtractor() going to execute PipelineModule::printTimeInterval() showing tstart, tstop for given data" << endl;
  srcxtractor.printTimeInterval(cout);
  srcxtractor.prepareLaunch();
  srcxtractor.setDefault();
  
  //srcxtractor.setCommandList(mycommands);

  if (!commandlist.isPathAbsolute()) srcxtractor.setDefaultOutputDir();
  else  srcxtractor.setOutputDir(commandlist.getOutputDir()); 

  cout << "SasoaHandler::launchSourcesExtractor() going to exec srcxtractor.launchAttitude() " << endl;

  tempstring = "outL3.evt";

  try{
    srcxtractor.launchAttitude(srcxtractor.getAbsoluteInputFileName(), srcxtractor.getAttitudeFileName(), tempstring);
  } catch(const SAexception &se){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::launchSourcesExtractor() generic exception" << endl;
  }

  mycommands.getInputFilename();

  // filter for generated GTI

  bool debug = false;
  try{
//  	srcxtractor.launchIrosMapBuilder(debug);
  } catch (const exception &e){
  cerr << "exception errror in handling L3 eventlist " << e.what() << endl;
}

if (commandlist.getIrosMode() ) {
/*
  srcxtractor.passIrosMap(); 
  string temp;
  temp = srcxtractor.getSasoaHome()+"/stg_2"; 
  srcxtractor.irospilot.setBaseDir(temp);
  temp +="/"+srcxtractor.irospilot.getFileName();
  cout << "launchSourcesExtractor() launching IROS on file " << temp << endl;
  srcxtractor.setIrosMapFileName(temp);
  temp =  srcxtractor.getSasoaHome()+"/stg_2/IROS_Multi-D/launchIrosIDLBatch";
  srcxtractor.setIROS_IDLBatchFileName(temp);
  srcxtractor.printPointingBatch(cout);
  for(int i=0; i<4; i++) {
    srcxtractor.createIrosBatch(i); // create the internal iros pilot file
    srcxtractor.createPointingBatch(); // create the internal iros pilot file
    srcxtractor.showIrosBatch();
    srcxtractor.irospilot.setDetector(i);
    srcxtractor.createIrosIDLBatch(srcxtractor.getIROS_IDLBatchFileName());  // create the IDL batch    
    srcxtractor.launchIros();
  }


*/
} else {
	cout << "SasoaHandler::launchSourcesExtractor() Iros is not set: saving the filtered list" << endl;
//	srcxtractor.createFilteredL3List();
}
  cout << "SasoaHandler::launchSourcesExtractor() going to exec srcxtractor.passOutputFile()"<< endl;

try{
  srcxtractor.passOutputFile(tempstring); // control: generalize?
  } catch(const SAexception &se){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in passing the outputfile " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in passing the outputfile " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::launchSourcesExtractor() generic exception passing the outputfile " << endl;
  }

  tempstring = srcxtractor.getUserHome()+"/SASOA/"+srcxtractor.getDetnam()+"/data/L3";

try{
    srcxtractor.deliverProducts();
  } catch(const SAexception &se){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in delivering products " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in delivering products " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::launchSourcesExtractor() generic exception delivering products " << endl;
  }

try{
  srcxtractor.announceDelivery();
  } catch(const SAexception &se){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in announceDelivery() " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in announceDelivery() " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::launchSourcesExtractor() generic exception in announceDelivery() " << endl;
  }

try{

  srcxtractor.finalizeLaunch();  
  } catch(const SAexception &se){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in finalizing the sources extraction " << se.getMsg() << endl;
  } catch(const exception &e){
    cerr << "SasoaHandler::launchSourcesExtractor() exception in finalizing the sources extraction " << e.what() << endl;
  } catch(...){
    cerr << "SasoaHandler::launchSourcesExtractor() generic exception in finalizing the sources extraction " << endl;
  }
}
/** No descriptions */
void SApipeline::SasoaHandler::launchSourceAnalyser(){
 sanalyser.prepareLaunch();
 sanalyser.printTimeInterval(cout);
 sanalyser.setDefault();
 setParameters(3);
 sanalyser.launch(infile, outfile, params);
 sanalyser.deliverProducts();
 sanalyser.announceDelivery();
 sanalyser.finalizeLaunch();
 sanalyser.rmTempInputFiles();
}

/** set startup instruction/parameter to launch a generic pipeline stage
takes as input the stage number (different default settings have to be set) */
void SApipeline::SasoaHandler::setParameters(int stagenum){
    cout << "executing SasoaHandler::setParameters()" << endl;
    showDefault();
    set_IDL_Display(mycommands.isIDL_DisplayOn());
    ofstream noutfile;
    string fn;
    string nfilename;
    switch(stagenum){
    /** save script to launch idl batch for stage stagenum */
    case -1:
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = source_path + "stage-1_idl_batch";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "filename='" << input_path+mycommands.getInputFilename()<< "'" << endl;
        noutfile << "path_out='"<< pbuilder.getOutputDir() << "'"<< endl;
        noutfile << "stage_-1, filename, path_out" << endl;
        if(!idl_display){
            noutfile << ".r close_all_windows" << endl;
            noutfile << "close_all_windows" << endl;
        }
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
    break;
    case 0:
    try{
         if (verbose) cout << "SasoaHandler::setParameters() source_path = "<< dreducer.getIDLSourcePath() << endl;
         if (verbose) cout << "SasoaHandler::setParameters() updating idl batch command file "<<  dreducer.getIDLSourcePath() + "stage0_idl_batch" << endl;
      dreducer.setInputFilename(mycommands.getInputFilename(), "");
      cout << "The inputfile name is " << mycommands.getInputFilename() << endl;
      } catch (const exception &e){
        cerr << "SasoaHandler::setParameters() error in  setting the data reducer input filename" << e.what() << endl;
      }catch (...){
        cerr << "SasoaHandler::setParameters() error in  setting the data reducer input filename" << endl;
      }
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = dreducer.getIDLSourcePath()+ "stage0_idl_batch";
        cout << "stg_0 IDL pilot file is " << fn << endl;
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << ".r stage_0" << endl;
        if (mycommands.isInputFileSet()) {
          //if (verbose) cout << "The file is set from commandline" << endl;
           cout << "The file is set from commandline" << endl;
           noutfile << "filename='" << dreducer.getInputDataPath()+"/"+dreducer.getOldModeInputFileName() << "'" << endl;
        } else {
          //if (verbose) cout << "The file is NOT set: using default retrieving" << endl;
          tempstring =  dreducer.getInputDataPath();
          cout << "The file is NOT set: using default retrieving" << endl;
                      if (verbose) cout << "SasoaHandler::setParameters() case 0"<< endl;
          try{
                      if (verbose) cout << "filename = " +dreducer.retrieveFilename("lv1", tempstring, 1) << endl;
          noutfile << "filename='" << dreducer.retrieveFilename("lv1", tempstring, 1)<< "'" << endl;
          } catch (SAexception &s){
            cerr << " error in retrieving the DataReducer (stage 0) input filename" << s.what() << endl;
            throw e;
          }catch (...){
            cerr << " error in retrieving the DataReducer (stage 0) input filename" << endl;
            throw  e;
          }
        }
        if (verbose) cout << "output dir for stage 0 will be " << output_path+mycommands.getOutputDir() << endl;
        if(!mycommands.isPathAbsolute()) { /// automatically selected output dir
           dreducer.setOutputDir(output_path+mycommands.getOutputDir());
           outdir = dreducer.getOutputDir(); /// we use the default output dir for stage 0
           if (verbose) cout << "SasoaHandler::setParameters() outdir = " << outdir << endl;
        } else {   /// use user selected
           outdir = mycommands.getOutputDir();   /// use user-selected outdir
           if (verbose) cout << "SasoaHandler::setParameters() outdir = "<< outdir  << endl;
        }
        noutfile << "path_out='"<< dreducer.getProductPath()+"/"+dreducer.getOutputDir() << "'"<< endl;
        noutfile << "stage_0, filename, path_out" << endl;
        if(!idl_display){
            noutfile << ".r close_all_windows" << endl;
            noutfile << "close_all_windows" << endl;            
        }
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
    break;
    case 1:
      nfilename = mycommands.getInfileRoot();
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = pbuilder.getIDLSourcePath() + "stage1_idl_batch";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        if (!mycommands.isPathAbsolute()){
          if (verbose) cout << "selected path type is auto generated"<< endl;
          tempstring =  pbuilder.getInputDataPath()+"/L19";
                      if (verbose) cout << "filename = " +pbuilder.retrieveFilename("evt", tempstring, 1) << endl;
                      noutfile << "filename='" << retrieveFilename("evt", tempstring, 1 ) << "'" << endl;
        }  else {
          if (verbose) cout << "selected path type is absolute"<< endl;      
          noutfile << "filename='" << mycommands.getInputFilename() << "'" << endl;        
        }
        if (!dreducer.executed()){
           string ts2 = getInputFileName(tempstring, "evt");
           pbuilder.setInputFileName(ts2);
        }
        noutfile << "path_out='"<< pbuilder.getProductPath()+"/"+pbuilder.getOutputDir() << "'"<< endl;
        noutfile << "stage_1, filename, path_out" << endl;
        if(!idl_display){
            noutfile << ".r close_all_windows" << endl;
            noutfile << "close_all_windows" << endl;
        }
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
    break;
    case 2:
        nfilename = mycommands.getInfileRoot();
        if (mycommands.isPathAbsolute()){
          cout << "SasoaHandler::setParameters() copying absolute path file into local directory" << endl;
          tempstring = "cp "+mycommands.getInputFilename()+" "+sarchiver.get_L2_Dir();
          cout << "SasoaHandler::setParameters() copying absolute path file into local directory: executing " << tempstring << endl;
          syscon.execCommand(tempstring);
        }
        if(!mycommands.isPathAbsolute()) { /// automatically selected output dir
           srcxtractor.setOutputDir(sarchiver.get_L3_Dir());
           outdir = srcxtractor.getOutputDir(); /// we use the default output dir for stage 0
           if (verbose) cout << "SasoaHandler::setParameters() outdir = " << outdir << endl;
        } else {   /// use user selected
           outdir = mycommands.getOutputDir();   /// use user-selected outdir
           if (verbose) cout << "SasoaHandler::setParameters() outdir = "<< outdir  << endl;
        }

      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = source_path + "stage2_idl_batch";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "filename='" << input_path+mycommands.getInputFilename()<< "'" << endl;
        noutfile << "path_out='"<< output_path << "'"<< endl;
        noutfile << "stage_2, filename, path_out" << endl;
        if(!idl_display){
            noutfile << ".r close_all_windows" << endl;
            noutfile << "close_all_windows" << endl;
        }
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
    break;
    case 3:
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = source_path + "stage3_idl_batch";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "filename='" << input_path+mycommands.getInputFilename()<< "'" << endl;
        noutfile << "path_out='"<< pbuilder.getOutputDir() << "'"<< endl;
        noutfile << "stage_3, filename, path_out" << endl;
        if(!idl_display){
            noutfile << ".r close_all_windows" << endl;
            noutfile << "close_all_windows" << endl;
        }
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
    break;
    default:
    break;
  }
}
/** No descriptions */
void SApipeline::SasoaHandler::setAllExtern(){
  dreducer.setExtern(true);
  pbuilder.setExtern(true);
  srcxtractor.setExtern(true);
  sanalyser.setExtern(true);
}
/** No descriptions */
void SApipeline::SasoaHandler::setDetNam(const string & dn){
  PipelineModule::setDetNam(dn);
  dreducer.setDetNam(dn);
  pbuilder.setDetNam(dn);
  srcxtractor.setDetNam(dn);
  sanalyser.setDetNam(dn);  
}
/** No descriptions */
void SApipeline::SasoaHandler::setDefaultEnvironment(){
  PipelineModule::setDefaultEnvironment();
  dreducer.setDefaultEnvironment();
  pbuilder.setDefaultEnvironment();
  srcxtractor.setDefaultEnvironment();
  sanalyser.setDefaultEnvironment();  
}
/** No descriptions */
 void SApipeline::SasoaHandler::execEMI(const string &indir){
 string mts = "autoEMI "+indir;
 cout << "SasoaHandler::execEMI() executing " << mts.c_str() << endl;
 system(mts.c_str());
 }
 
 /** No descriptions */
 void SApipeline::SasoaHandler::execEMI(const string &indir, const string &contactmin, const string &contactmax){
 string mts = "autoEMI_new "+indir;
 mts += " "; 
 mts += contactmin;
 cout << "SasoaHandler::execEMI(const string &indir, const string &contactmin, const string &contactmax) executing " << mts.c_str() << endl;
 system(mts.c_str());
 agiledb = new AGILEDBConnector();
 int c = sarchiver.getCurrentContactNumber(); tempstring = "imaging";
 agiledb->setSasoaStatusOnDB(c, tempstring);
 delete agiledb;
 }
 
/** No descriptions */
void SApipeline::SasoaHandler::createAllBatchScripts(){
  dreducer.createLaunchBatchScript();
  pbuilder.createLaunchBatchScript();
//  srcxtractor.createLaunchBatchScript();
//  sanalyser.createLaunchBatchScript();  
}
/** No descriptions */
void SApipeline::SasoaHandler::setAllEnvs(){
}
/** No descriptions */
string SApipeline::SasoaHandler::getProgramName(){
 return PNAME; 
}
/** No descriptions */
void SApipeline::SasoaHandler::setProgramName(const string &pn){
  PNAME = pn;
}
/** No descriptions */
void SApipeline::SasoaHandler::createDefaults(){
}
/** No descriptions */
string SApipeline::SasoaHandler::getDefaultInputFilename(){
  switch (stage) {
    case -1:
      tempstring = orbilder.getInputFileName();
    break;
    case 0:
      tempstring =  dreducer.getInputFileName();
    break;
    case 1:
      tempstring =  pbuilder.getInputFileName();
    break;
    case 2:
      tempstring =  srcxtractor.getInputFileName();
    break;
    case 3:
      tempstring =  sanalyser.getInputFileName();
    break;
    default:
      tempstring2 = "unknown stage number";
      se.setMsg(tempstring2);
      throw se;
      tempstring = "nofilename";
    break;
  }
  return tempstring;
}
/** No descriptions */
void SApipeline::SasoaHandler::setIDL(bool b){
    PipelineModule::setIDL(b);
    dreducer.setIDL(b);
    pbuilder.setIDL(b);
    srcxtractor.setIDL(b);
    sanalyser.setIDL(b); 
}
/** No descriptions */
void SApipeline::SasoaHandler::close(){
    dreducer.rmTempInputFiles();
    pbuilder.rmTempInputFiles();
//    srcxtractor.rmTempInputFiles();
//    sanalyser.rmTempInputFiles();
}
/** set original commandlist to all stages */
void SApipeline::SasoaHandler::setGlobalCommands(){
  orbilder.setCommandList(mycommands);
  dreducer.setCommandList(mycommands);
  srcxtractor.setCommandList(mycommands);
  pbuilder.setCommandList(mycommands);
  srcxtractor.setCommandList(mycommands);
  sanalyser.setCommandList(mycommands);
}


/*!
    \fn SApipeline::SasoaHandler::clearTempData()
 */
void SApipeline::SasoaHandler::clearTempData()
{
  sarchiver.clearTempData();
}


/*!
    \fn SApipeline::SasoaHandler::setArchiverEnv()
 */
void SApipeline::SasoaHandler::setArchiverEnv()
{
  if (verbose) cout << "SasoaHandler::setArchiverEnv() going to set SASOA_HOME " << getSasoaHome() << endl;
  if (verbose) cout << "SasoaHandler::setArchiverEnv() going to set SASOA_WORK_DIR " << getSasoaWorkDir() << endl;
  tempstring = getSasoaHome();
  sarchiver.setSasoaHome(tempstring);
  tempstring = getSasoaWorkDir();
  sarchiver.setSasoaWorkDir(tempstring);
  srcxtractor.setArchiveHandler(&sarchiver);
  orbilder.setArchiveHandler(&sarchiver);
    /** */
  dreducer.setArchiveHandler(&sarchiver);
  /** object implementing stage 1 functions */
  pbuilder.setArchiveHandler(&sarchiver);
  /** object implementing stage 2 functions */
  sanalyser.setArchiveHandler(&sarchiver);
  /** object implementing stage 3 functions */
  
  
}


/*!
    \fn SApipeline::SasoaHandler::start()
    put here the defoult entrystage and exitstage for the
    automatic pipeline
 */
void SApipeline::SasoaHandler::start()
{
  cout << "SasoaHandler::start() executing a pipeline run" << endl;
  entrystage = -1;
  exitstage = 3;
  startAll();
  firstrun = true;
}
/** No descriptions */
void SApipeline::SasoaHandler::initArchiveEnv(){
  string temp;
  sarchiver.setSasoaHome(getSasoaHome());
  sarchiver.setSasoaWorkDir(getSasoaWorkDir());
  temp = getSasoaWorkDir()+"/delivery";
  sarchiver.setDeliveryDir(temp);
  temp = getSasoaWorkDir()+"/archive";
  sarchiver.setArchiveRoot(temp);
  temp = "00000";
  sarchiver.setArchiveDir(temp);
    
  if (mycommands.isPathAbsolute()){
      cout << "SasoaHandler::initArchiveEnv() : the path in the commadlist is absolute "<< endl;
    SAFitsHandler::setInputFileName(mycommands.getInputFilename());
    SAFitsHandler::setRelativeFileNames();
    tempstring = SAFitsHandler::rel_infilename;
  } else {
    tempstring = "PKP000000_0_3905_000_L1.lv1";
    mycommands.setInputFileName(tempstring);  
  }
  try{
    switch(status){
      case -1:
    sarchiver.filenamer.setFileName(tempstring);
      break;
      case 0:
    sarchiver.filenamer.setFileName(tempstring);
      break;
      case 1:
        if (verbose) cout << "SasoaHandler::initArchiveEnv() setting input filename for PhotonListBuilding task" << endl;
        sarchiver.filenamer.setFileName(tempstring, PhotonListBuilding);
      break;
      case 2:
    sarchiver.filenamer.setFileName(tempstring, SourcesExtraction);
      break;
      case 3:
    sarchiver.filenamer.setFileName(tempstring);
      break;
      case 4:
    sarchiver.filenamer.setFileName(tempstring);
      break;
      case 5:
    sarchiver.filenamer.setFileName(tempstring);
      break;
      default:
    cerr << "SasoaHandler::initArchiveEnv() error : unknown processing stage number "<< endl;      
      break;
    }
  } catch(...)
  {
    cerr << "SasoaHandler::initArchiveEnv() error in setting the filename  "<< endl;
  }
  /** set all data level dirs L1, L2 , L3 ... */
  sarchiver.setDataDirs();
  orbilder.setArchiveHandler(&sarchiver);
    /** */
  dreducer.setArchiveHandler(&sarchiver);
  /** object implementing stage 1 functions */
  pbuilder.setArchiveHandler(&sarchiver);
  /** object implementing stage 2 functions */
  sanalyser.setArchiveHandler(&sarchiver);
  /** object implementing stage 3 functions */
  srcxtractor.setArchiveHandler(&sarchiver);

}
/** No descriptions */
string SApipeline::SasoaHandler::getCurrentInputFileName(){
  tempstring = mycommands.getInputFilename();
  return  tempstring;
}
/** No descriptions */
void SApipeline::SasoaHandler::launchOrbitRebuilding(){
 orbilder.prepareLaunch();
 orbilder.setDefault();
 setParameters(-1);
 //// REMEMBER     !!
 orbilder.setTestMode(true);
//// REMEMBER       !!
try{
  orbilder.retrieveOrbitData();
 } catch (...){
   cerr << "launchOrbitRebuilding() error in retrieving orbit data " << endl;
 }
 orbilder.launch(infile, outfile, params);
 orbilder.processBase();
  /** TEST */
 orbilder.deliverProducts();
 orbilder.announceDelivery();
 orbilder.finalizeLaunch();
}
/** No descriptions */
void SApipeline::SasoaHandler::setContact(const string &cn){
  cout << "SasoaHandler::setContact() now contact number is "<< cn << endl;
  orbilder.setContact(cn);
}
/** No descriptions */
bool SApipeline::SasoaHandler::isFirstRun(){
  return firstrun;
}
/** No descriptions */
void SApipeline::SasoaHandler::setAuto(bool bval){
  PipelineModule::setAuto(bval);
  orbilder.setAuto(bval);
  dreducer.setAuto(bval);
  pbuilder.setAuto(bval);
  srcxtractor.setAuto(bval);
  sanalyser.setAuto(bval);  
}


/*!
    \fn SApipeline::SasoaHandler::setTimeInterval()
 */
void SApipeline::SasoaHandler::setTimeInterval()
{
  cout << "setting time interval of processed eventlist in all the processing stages" << endl;
  double mytstart, mytstop;
 
  mytstart = orbilder.getTstart();
  mytstop = orbilder.getTstop();

  dreducer.setTstart(mytstart);
  dreducer.setTstop(mytstop);

  pbuilder.setTstart(mytstart);
  pbuilder.setTstop(mytstop);
  srcxtractor.setTstart(mytstart);
  srcxtractor.setTstop(mytstop);
  sanalyser.setTstart(mytstart);
  sanalyser.setTstop(mytstop);  
}


/*!
    \fn SApipeline::SasoaHandler::launchCorrector()
 */
void SApipeline::SasoaHandler::launchCorrector()
{
    /// @todo implement me
}


/*!
    \fn SApipeline::SasoaHandler::getMCTimeInterval()
 */
pair<double, double> SApipeline::SasoaHandler::getMCTimeInterval(const string &fname)
{
   char buf[256]; // read lines of maximun 256 characters
  int mlinelen = 256;
    ifstream is;    stringstream ss;   string fn;
    is.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = fname;
        is.open (fn.c_str(), ofstream::in);
		ss.str("");
        is.getline(buf, mlinelen);
        ss << buf;
        if (verbose) cout << "SasoaHandler::getMCTimeInterval() reading " << ss.str() << endl;
		tempstring = ss.str();
		int pos = tempstring.find_first_of(",");
		ss.str("");
        is.getline(buf, mlinelen) ;
        ss << buf;
        if (verbose) cout << "SasoaHandler::getMCTimeInterval() reading " << ss.str() << endl;
        is.close();
      } // close try
      catch (ifstream::failure e) {
          cout << "PipelineModule::retrieveSasoaHome() Exception opening/writing file"<< endl;
      }
  timeinterval.first=tstart;  timeinterval.second=tstop;
  return timeinterval;   
}


/*!
    \fn SApipeline::SasoaHandler::saveMCTimeInterval(const string &fname)
 */
void SApipeline::SasoaHandler::saveMCTimeInterval(const string &fname)
{
    ofstream of; string fn(fname);
    cout << "SourcesExtractor::createIrosIDLBatch() on file " << fn << endl;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
    try {
        of.open (fn.c_str(), ofstream::out | ofstream::trunc);
        printTimeInterval(of);
        printTimeInterval(cout);
    	of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createExposureDatacard() Exception opening/writing file"<< e.what() << endl;
  }
}

/*!
    \fn SApipeline::SasoaHandler::loadContact(int n)
 */
void SApipeline::SasoaHandler::loadContact(int n){
    cout << "executing SasoaHandler::loadContact()" << endl;
  try{
    
    tempstring = sarchiver.getFormattedStringNumber(n, 6);
    if (verbose) cout << "SasoaHandler::loadContact formatted string = " << tempstring << endl;

    // load 3905 data    
    ss.str(""); ss << sarchiver.getDefaultContactsDir(); ss << "/";
    ss << sarchiver.getFormattedStringNumber(n, 6);
    tempstring = ss.str();
    if (verbose) cout << "SasoaHandler::loadContact created string " << tempstring << endl;
    
    tempstring.insert(0, " cp ");tempstring.append("/*3905*.* ");
    tempstring.append(sarchiver.get_L1_Dir());
    if (verbose) cout << "SasoaHandler::loadContact created string " << tempstring << endl;
    syscon.execCommand(tempstring);
    
    // load 3914 data    
    ss.str(""); ss << sarchiver.getDefaultContactsDir(); ss << "/";
    ss << sarchiver.getFormattedStringNumber(n, 6);
    tempstring = ss.str();
    if (verbose) cout << "SasoaHandler::loadContact()  created string " << tempstring << endl;
    
    tempstring.insert(0, " cp ");tempstring.append("/*3914*.* ");
    tempstring.append(sarchiver.get_L1_Dir());
    if (verbose) cout << "SasoaHandler::loadContact() created string " << tempstring << endl;
    syscon.execCommand(tempstring);
    
    // load 3916 data    
    ss.str(""); ss << sarchiver.getDefaultContactsDir(); ss << "/";
    ss << sarchiver.getFormattedStringNumber(n, 6);
    tempstring = ss.str();
    if (verbose) cout << "SasoaHandler::loadContact() created string " << tempstring << endl;
    tempstring.insert(0, " cp ");tempstring.append("/*3916*.* ");
    tempstring.append(sarchiver.get_L1_Dir());
    if (verbose) cout << "SasoaHandler::loadContact() created string " << tempstring << endl;
    syscon.execCommand(tempstring);
    cout << "SasoaHandler::loadContact() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaHandler::loadContact() error in loading L1 input data" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaHandler::loadContact() FITS error in loading L1 input data" << endl;
  }   catch(...){
    cerr << "SasoaHandler::loadContact() generic error!" << endl;
  }
}

/*!
    \fn SApipeline::SasoaHandler::Correct3905L1(int nc)
 */
void SApipeline::SasoaHandler::Correct3905L1(int nc)
{
  ss.str("");ss<<nc;string ifn(ss.str());ss.str("");
  string infileval, outfileval;
  try{
    // retrieve L1 filename for the given the contact
    tempstring = "ls "+sarchiver.get_L1_Dir()+"/*"+ifn+"*3905*.lv1";
    vector<string> resfiles = syscon.dumpCommand(tempstring);
    if (verbose) cout << "SasoaUserInterface::handle_correction() n. of retrieved files = " << resfiles.size() << endl;
    if (resfiles.size() == 0){
      tempstring2="error: retrieved no L1 file to correct";
      se.setMsg(tempstring2);
      throw(se);
    }
    if (resfiles.size() > 1){
      tempstring2="error: retrieved more then L1 file to correct";
      se.setMsg(tempstring2);
      throw(se);
    }
    // create infile value string
    infileval=resfiles[0];
    if (verbose) cout << "SasoaUserInterface::handle_correction() running correction on file "<< infileval << endl;
    sarchiver.filenamer.setContact(ifn);
    tempstring2 = sarchiver.filenamer.getOutputFileName(Correction);
    if (verbose) cout << "SasoaUserInterface::handle_correction() corrected output file name will be "<< tempstring2 << endl;
    // create outfile value string
    outfileval = sarchiver.get_L1_Dir() + "/"+tempstring2;
    // create command string
    tempstring2 = "cor_3905 infile="+infileval+" outfile="+outfileval;
    if (verbose) cout << "SasoaUserInterface::handle_correction() going to exec the string "<< tempstring2 << endl;
    syscon.execCommand(tempstring2);
    // run commandstring
    if (verbose) cout << "SasoaUserInterface::handle_correction() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_correction() error in correcting L1 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_correction() FITS error in correcting L1 eventlist" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_correction() error!" << endl;
  }
  
}

/*!
    \fn SApipeline::SasoaHandler::setDefaultEnergyRange()
 */
void SApipeline::SasoaHandler::setDefaultEnergyRange(pair<float, float> enrange)
{
    /// @todo implement me
}

/*!
    \fn SApipeline::SasoaHandler::getDefaultEnergyRange()
 */
pair<float, float> SApipeline::SasoaHandler::getDefaultEnergyRange()
{
    /// @todo implement me
}

/*!
    \fn SApipeline::SasoaHandler::exec_allpipe(int contactnum)
 */
void SApipeline::SasoaHandler::exec_allpipe(int contactnum)
{
	cout << "SasoaHandler::exec_allpipe() running sasoa for contact " << contactnum << endl;
}

/*!
    \fn SApipeline::SasoaHandler::deliverLogs()
 */
void SApipeline::SasoaHandler::deliverLogs()
{
	cout << "SasoaHandler::deliverLogs"<< endl;
	tempstring = "";
	tempstring = "mv -f *out.log  *err.log "+sarchiver.getArchiveDir();
	syscon.execCommand(tempstring);
}

void SApipeline::SasoaHandler::ephMerge(const string &contactmin, const string &contactmax, const string &outfile){
	string temps0;
	ss.str("");
	ss << "rm -f ../SATemporalDataSet/eph_" << outfile; temps0 = ss.str();
	cout << "SasoaHandler::ephMerge() executing " << temps0 << endl;	
	syscon.execCommand(temps0);
	ss.str("");
	ss << "rm -f ../SATemporalDataSet/eph_*.fits"; temps0 = ss.str();
	cout << "SasoaHandler::ephMerge() executing " << temps0 << endl;	
	syscon.execCommand(temps0); 
	string temps1; ss.str(""); 
	ss << "cd ../SATemporalDataSet; ./ephMerge.sh " << contactmin << " " << contactmax << " " << outfile;
	temps1 = ss.str();
	cout << "SasoaHandler::ephMerge() executing " << temps1 << endl;	
	syscon.execCommand(temps1);
}
void SApipeline::SasoaHandler::ephCorrect(const string &infile, const string &outfile, double tstart, double tstop){
	if (verbose) cout << "executing SasoaHandler::ephCorrect() " << endl;
	if (verbose) cout << "executing SasoaHandler::ephCorrect(" << infile << ", " << outfile << ", " << tstart << ", " << tstop << ") " << endl;
	sc.Correct(infile, outfile, tstart, tstop);
}

  /** No descriptions */
void SApipeline::SasoaHandler::setIROS(bool bv){
  irosflag = bv;
}
  /** No descriptions */
bool SApipeline::SasoaHandler::isIROS(){
  return irosflag;
}

/*!
    \fn SApipeline::SasoaHandler::deliverEphFile()
 */
void SApipeline::SasoaHandler::deliverEphFile()
{
	string temps0, temps1, temps2;
	temps0 = sarchiver.get_L1_Dir();
	cout << "SasoaHandler::deliverEphFile() = " << temps0 << endl;
	temps1 = temps0+"/*3916*.lv1";
	ss.str("");
	ss << "cp -f " << temps1 << " " <<  sarchiver.getArchiveDir() << "/eph_testout.fits";
	temps2 = ss.str();
	cout << "SasoaHandler::deliverEphFile() executing " << temps2 << endl;	
	syscon.execCommand(temps2);
}

/*!
    \fn SApipeline::SasoaHandler::setStatusOnDB(string taskname)
 */
void SApipeline::SasoaHandler::setStatusOnDB(string taskname)
{
  agiledb = new AGILEDBConnector();
  int c = sarchiver.getCurrentContactNumber(); agiledb->setSasoaStatusOnDB(c, taskname);
  delete agiledb;
}
