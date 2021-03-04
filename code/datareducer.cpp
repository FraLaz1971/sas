/***************************************************************************
                          datareducer.cpp  -  description
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

#include "datareducer.h"


namespace SApipeline{

DataReducer::DataReducer(){
  exec = false;
  showDefault();
  derived = 1;
  status = 0; // error status 0 = failfree
  status = PipelineModule::init();
  setInputDataPath(WORK_DET_PATH);
  setExtern(true);
}
DataReducer::~DataReducer(){
}
/** No descriptions */
int DataReducer::setL1Data(char * datafilename){
  return 0;
}
/** No descriptions */
int DataReducer::setParameters(char * parfilename){
  return 0;
}
/** returns a L1_9 eventlist object */

int DataReducer::getL1_9_Batch(int mode){
  return status;  
}
}/** specific sadp module initialization */
int SApipeline::DataReducer::init(){
  start();
}
/** No descriptions */
void SApipeline::DataReducer::setDescription(){
  //if (verbose) cout << "SApipeline::DataReducer::setDescription()" << endl;
  description = "[data reduction (stage 0)] ";
}
/** No descriptions */
void SApipeline::DataReducer::start(){

}
/** No descriptions */
int SApipeline::DataReducer::executeOp1(int operand1, int operand2){
  try{
      if (operand1>operand2) throw(e1);
  } catch(Type1Exception e1){
       cerr << "Error: " << e1.what() << endl;    
       e1.handle1();
       return executeInnerOp(operand1, operand2);
  }    
  return 0;
}
/** No descriptions */
int SApipeline::DataReducer::executeOp2(int operand1, int operand2){

  try{
      if (operand1>operand2) throw(e2);
  } catch(Type2Exception e2) {
       cerr << "exception Error: " << e2.what() << endl;
       e2.handle2();
       return executeInnerOp(operand1, operand2);
  }
  return 0;
}
/** No descriptions */
int SApipeline::DataReducer::executeInnerOp(int operand1, int operand2){
try{
      if ((operand1 > 10)&&(operand2<3)) throw (e);
    } catch(SAexception e) {
       cerr << "exception Error: " << e.what() << endl;
        // e.handleGeneral();
       return -1;
  } 
  return 0;
}
/** launch stage0 via idl batch */
void SApipeline::DataReducer::launchIDL_Batch(){
  if (verbose) cout << "executing DataReducer::launchIDL_Batch()" << endl;
  if (isIDLon()) system( "./launchDataReduction.bash");
}
/** No descriptions */
void SApipeline::DataReducer::launch(string & infile, string & outfile, vector<int> params){
  if  (isExtern()) launchIDL_Batch();
  exec = true;
}
/** No descriptions */
void SApipeline::DataReducer::setInputFilename(const string &fname, const string &mode){
  infile = fname;
}
/** No descriptions */
void SApipeline::DataReducer::setOutputDir(const string &od){
  outdir = od;
}

/** No descriptions */

/** No descriptions */
string SApipeline::DataReducer::getOutputDir(){
  return outdir;
}
/** create the bash script that launches IDL batch script */
void SApipeline::DataReducer::createLaunchBatchScript(){
     if (verbose) cout << "DataReducer::createLaunchBatchScript() DETNAM = "<< DETNAM << endl;
      ofstream noutfile;
      string ff;
      ff = "launchDataReduction.bash";
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        noutfile.open (ff.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "#! /bin/sh" << endl;
        noutfile <<"cd $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "echo entering directory $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "idl stage0_idl_batch" << endl;
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "DataReducer::createLaunchBatchScript() Exception opening/writing file"<< ff << endl;
      }
}
/** No descriptions */
string SApipeline::DataReducer::getInputDataPath(){
  return inputdatapath;
}
/** No descriptions */             
void SApipeline::DataReducer::passOutputFile(const string &toutdir){
  if(verbose)  cout << "executing DataReducer::passOutputFile()"<< endl;
  if(verbose)  cout << "DataReducer::passOutputFile( the output file from stage 0 is generated in "  << outdir << endl;
  if(verbose)  cout << "DataReducer::passOutputFile( i'm going to copy output file in "<< toutdir << endl;
  string temps;
//  temps = "cp --preserve=timestamp " +getProductPath()+"/"+outdir+"/*_L19.evt  | sed -n \"1p\" "+toutdir;
  temps = "ls  -t " +getProductPath()+"/"+outdir+"/*_L19.evt  | sed -n \"1p\" ";
  //system(temps.c_str());
  vector<string> s;
  s = syscon.dumpCommand(temps);
  if(verbose) cout << "DataReducer::passOutputFile() shell command: " << temps << endl;
  k = s.size();
  if(verbose) cout << "DataReducer::passOutputFile() number of retrieved strings: " << k << endl;
  if (k>1) {
    se.setMsg("error : retrieved more than an L19 file !");
    throw se;
    }   else if (k==0){
          se.setMsg("error : NO L19 file retrieved!");
          throw se;
    }
  if(verbose) cout << "DataReducer::passOutputFile() file name to be passed: " << s[0] << endl;
  temps =  "cp "+s[0]+" "+toutdir;
  syscon.execCommand(temps);
  system(temps.c_str());
  if(verbose)  cout << "ended DataReducer::passOutputFile()"<< endl;
}
/** default retrieving of inputfilename */
string SApipeline::DataReducer::getInputFileName() {
  return PipelineModule::getInputFileName(getDefaultInputDir(), "lv1");
}
/** default retrieving of input dir */
//string SApipeline::DataReducer::getDefaultInputDir(){
//  tempstring = PipelineModule::getSasoaWorkDir()+"/data";
//  return tempstring;
//}
/** No descriptions */
void SApipeline::DataReducer::rmTempInputFiles(){
  arc->clear_SAL1Orb_Data();
}
/** No descriptions */
void SApipeline::DataReducer::announceDelivery(){
}


/*!
    \fn SApipeline::DataReducer::prepareInputFile()
 */
void SApipeline::DataReducer::prepareInputFile()
{
  if (verbose) showAlert();
  if (verbose) cout << "executing DataReducer::prepareInputFile()  " << endl;
  if (verbose) cout << "DataReducer::prepareInputFile() The inputfile is " << commandlist.getInputFilename() << endl;
  tempstring = arc->get_SAL1Orb_Dir();
  tempstring = tempstring + "/" + arc->filenamer.getFileName(OrbitRebuilding);
  if (verbose) cout << "DataReducer::prepareInputFile() now changing to old file name that was " << tempstring << endl;
  tempstring1  = tempstring;
  tempstring = arc->get_SAL1Orb_Dir();
  tempstring2 = tempstring + "/" + arc->filenamer.getFileName(OldDataReduction);
  if (verbose) cout << "DataReducer::prepareInputFile() new input file will be " << tempstring2 << endl;
  tempstring3 = "cp "+ tempstring1 + " "+tempstring2;
  if (verbose) cout << "DataReducer::prepareInputFile() executing " << tempstring3 << endl;
  system(tempstring3.c_str());
  DataReducer::setInputDataPath(arc->get_SAL1Orb_Dir());
  commandlist.setInputFileName(arc->filenamer.getFileName(OldDataReduction));
  setOldModeInputFileName(arc->filenamer.getFileName(OldDataReduction));
}


/*!
    \fn SApipeline::DataReducer::setInputDataPath()
 */
void SApipeline::DataReducer::setInputDataPath(const string &idp)
{
  if (verbose) cout << "executing DataReducer::setInputDataPath() = "<< idp << endl;
  inputdatapath = idp;
}


/*!
    \fn SApipeline::DataReducer::getOldModeInputFileName()
 */
string SApipeline::DataReducer::getOldModeInputFileName()
{
  return oldmodeinfile;
}


/*!
    \fn SApipeline::DataReducer::setOldModeInputFileName(const string &ifn)
 */
void SApipeline::DataReducer::setOldModeInputFileName(const string &ifn)
{
  oldmodeinfile = ifn;
}
