/***************************************************************************
                          orbitrebuilder.cpp  -  description
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

#include "orbitrebuilder.h"
namespace SApipeline{

OrbitRebuilder::OrbitRebuilder(){
  setDescription();
  int status = init();
}
OrbitRebuilder::~OrbitRebuilder(){
    if(verbose) cout << "OrbitRebuilder::init() DataBase connection module destroyed!" << endl;
}
OrbitRebuilder::OrbitRebuilder(const PipelineModule &pm){
  // insert code ...
}
}
int SApipeline::OrbitRebuilder::init(){
  orbnum = 0;
  cur_orb_str = "000000";
  testmode = false;
  inputdatadirnam.assign("REBUILDER_INDIR");
  inputdatadirval.clear();
  actfilenamenam.assign("REBUILDER_INFILE");
  actfilenameval.clear();
  if(verbose)cout << "OrbitRebuilder::init() inputdatadirnam = "<< inputdatadirnam << endl;
  if(verbose)cout << "OrbitRebuilder::init() inputdatadirval"<<  inputdatadirval << endl;
  if(verbose) cout << "OrbitRebuilder::init() DataBase connection module launched" << endl;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setDescription(){
    if (verbose) cout << "SApipeline::OrbitRebuilder::setDescription()" << endl;
    description = "[Orbit Rebuilding (stage -1)]";
}
/** No descriptions */
void SApipeline::OrbitRebuilder::start(){
  test2();  
}
/** No descriptions */
void SApipeline::OrbitRebuilder::launchIDL_Batch(){
PipelineModule::launch(infile, outfile, params);
     if (isIDLon()) system( "./launchPhotonListBuilding.bash");
}
/** No descriptions */
void SApipeline::OrbitRebuilder::launch(string & infile, string & outfile, vector<int> params){
  PipelineModule::launch(infile, outfile, params);
    if (extern_lan) launchIDL_Batch();
    exec = true;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::createLaunchBatchScript(){
      if (verbose) cout << "OrbitRebuilder::createLaunchBatchScript() DETNAM = "<< DETNAM << endl;
      ofstream noutfile;
      string fn;
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "launchPhotonListBuilding.bash";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "#! /bin/sh" << endl;
        noutfile <<"cd $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "echo entering directory $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "idl stage-1_idl_batch" << endl;
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
}

void SApipeline::OrbitRebuilder::rmTempInputFiles(){
  //arc->clear_SAL1Cor_Data();
}
/** No descriptions */
void SApipeline::OrbitRebuilder::passOutputFile(const string &toutdir){
  if(verbose)  cout << "executing OrbitRebuilder::passOutputFile()"<< endl;
  if(verbose)  cout << "the output file from stage 0 is generated in "  << outdir << endl;
  if(verbose)  cout << "i'm going to copy output file in "<< toutdir << endl;
  string temps;
  temps = "cp --preserve=timestamp "+getProductPath()+"/"+outdir+"/*_L2.evt "+toutdir;
  system(temps.c_str());
  if(verbose) cout << "shell command: " << temps << endl;
  if(verbose)  cout << "ended OrbitRebuilder::passOutputFile()"<< endl;
}
/** No descriptions */
string SApipeline::OrbitRebuilder::getDefaultOutputDir(){
  return outdir;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::announceDelivery(){
  if (verbose) cout << "OrbitRebuilder::announceDelivery() delivered OrbitRebuilder products!" << endl;
}
///** No descriptions */

/** No descriptions */
void SApipeline::OrbitRebuilder::setOutputFileName(const string &outf){
  outfile = outf;
  if (verbose) cout << "OrbitRebuilder::readInputFile() reading file " << outfile << endl;
 SAFitsHandler::setOutputFileName(outf);
}
/** No descriptions */
void SApipeline::OrbitRebuilder::test(){
    try{
    if (verbose) cout << "executing OrbitRebuilder::test() "<< endl;
    retrieveInputDataDir();

	//############################
	//#### control  
	//############################
    
    database = (DBConnector *) new DBConnector();
    if (verbose) database->setVerbose(true);
    database->showCurrentAccount();
    database->testDefaultConnection();
    delete database;

    fitser = new SAFitsHandler(getInputDataPath()+"/"+infile);
    if (verbose) fitser->setVerbose(true);
    fitser->setOutputFileName(filenamer.getFileName(OrbitRebuilding));
    fitser->process();
    delete fitser;

    } catch (const exception &e){
      cout << "OrbitRebuilder::test() error"<< e.what() << endl;
    } catch (...){
      cout << "OrbitRebuilder::test() general error"<< endl;
    }

    setVerbose(false);
}
/** No descriptions */
void SApipeline::OrbitRebuilder::retrieveInputDataDir(){

  try{
    if (verbose) cout << "OrbitRebuilder::retrieveInputDataDir() going to read value in the env var "<< inputdatadirnam << endl;
    inputdatadirnam.assign("REBUILDER_INDIR");
    //t  = inputdatadirnam.c_str();
    syscon.setShellMode(true);
    inputdatadirval.assign(syscon.getEnvVar(inputdatadirnam));
    //inputdatadirval.assign("/home/lazza/SASOA/SA/data");
    //tempstring = syscon.getEnvVar(inputdatadirnam);
    //if (verbose) cout << tempstring << endl;
    if (verbose) cout <<"OrbitRebuilder::retrieveInputDataDir() name of the env var " << inputdatadirnam.c_str()  << endl;
    if (verbose) cout <<"OrbitRebuilder::retrieveInputDataDir() retrieved input data directory for the OrbitRebuilder " << inputdatadirval  << endl;
  } catch (const exception &e){
    cerr << "OrbitRebuilder::retrieveInputDataDir() error in reading the env var " << e.what() << endl;    
  }
}
/** No descriptions */
string SApipeline::OrbitRebuilder::getInputDataDirNam(){
  return inputdatadirnam;
}
/** No descriptions */
string SApipeline::OrbitRebuilder::getInputDataDirVal(){
  return inputdatadirval;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::retrieveOrbitData(){
   // ### insert here db interrogatione and orbit number
   // retrieving
   // test function orbit info retrieving from db
   if (testmode) {
     //database->test();
     }
   // test function orbit info creating
   if (testmode) {
     try{
        setOrbitString();
      } catch (...){
         cerr << "retrieveOrbitData() error in executing setOrbitString(); " << endl;
         throw e;
      }
      orbnum++;
   }
}
/** No descriptions */
void SApipeline::OrbitRebuilder::test2(){
    try{
      if (verbose) cout << "executing OrbitRebuilder::test2() "<< endl;
      DBConnector db;
      db.testDefaultConnection();
      db.writeCurrentDBDefaults();
    } catch (const exception &e){
      cerr << "handling error in SasoaUserInterface::handle_testdb() "<< e.what() << endl;
    } catch (...){
      cerr << "handling error in SasoaUserInterface::handle_testdb() non "<<  endl;
    }
}


/*!
    \fn SApipeline::OrbitRebuilder::getOrbitNumber()
 */
string SApipeline::OrbitRebuilder::getOrbitString()
{
  return cur_orb_str;
}


/*!
    \fn SApipeline::OrbitRebuilder::getArchiveRoot()
 */
string SApipeline::OrbitRebuilder::getArchiveRoot()
{
  tempstring = getSasoaWorkDir()+"/archive";
  return tempstring;
}


/*!
    \fn SApipeline::OrbitRebuilder::setOutputDir()
 */
void SApipeline::OrbitRebuilder::setCurrentArchiveDir()
{
  arcoutdir = getArchiveRoot()+"/"+getOrbitString();
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setTestMode(bool bv){
  testmode = bv;
}
/** No descriptions */
bool SApipeline::OrbitRebuilder::getTestMode(){
  return testmode;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setOrbitNumber(int on){
}
/** No descriptions */
int SApipeline::OrbitRebuilder::getOrbitNumber(){
  return orbnum;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setOrbitNumber(const string &ons){
  orbnum = atoi(ons.c_str());
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setOrbitString(const string & c1, const string & c2){
   //orbnum
   tempstring = c1;
   cur_orb_str = tempstring+"_"+c2;
}
void SApipeline::OrbitRebuilder::setOrbitString(const string & c1, int orbnum){
   //orbnum
  tempstring = c1;
   cur_orb_str = tempstring+"_"+arc->getFormattedStringNumber(orbnum);
}
void SApipeline::OrbitRebuilder::setOrbitString(){
   //orbnum
   tempstring = arc->filenamer.getContact();
   cur_orb_str = tempstring+"_"+arc->getFormattedStringNumber(orbnum);
}
/** Base functionality */
void SApipeline::OrbitRebuilder::processBase(){
  //tempstring = inputdatadirnam + inputdatadirval;

  prepare();
  if (verbose) cout << "OrbitRebuilder::processBase() env var name containing the name of the dir where to search for the input file "<< getInputDataDirNam() << endl;
  if (verbose)cout << "OrbitRebuilder::processBase() directory where to search for the input file "<< getInputDataDirNam() << endl;
  if (verbose)cout << "OrbitRebuilder::processBase() "<< getInputDataDirVal() << endl;
  if (verbose)cout << "OrbitRebuilder::processBase() going to process file "<< getInputFileName() << endl;

  if(!commandlist.isPathAbsolute()){
      tempstring = arc->get_SAL1Cor_Dir() + "/"+getInputFileName();
    } else {
      if(verbose) cout << "OrbitRebuilder::processBase() Executing retrieveInputFileName();" << endl;
      retrieveInputFileName();
      tempstring = getInputFileName();      
//      tempstring = getNewFileName();
    }
//      if(verbose) cout << "Executing retrieveInputFileName();" << endl;
//		reading header from sal1cor fitsfile to extract tstart & tstop 

        fitsfile * in;	   int mystatus = 0;
         
         // This call reads just the header 
	FITS *pInfile;
	const char * b = tempstring.c_str(); 
		
		cout << "SAEventlist::readHeader() reading the header of the file " << infile << endl;   
		if (fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);

      try{
  			//pInfile = new FITS(infile,Read);
 			//fitsfile * in = (fitsfile*) new fitsfile[1];
   	   		// if(fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);
        	 // define a reference for clarity. (std::auto_ptr<T>::get returns a pointer
	  } catch(CCfits::FitsException& c){
    	 	cerr << "SAEventlist::readHeader() error in opening the inputfile "<< endl;
     		cerr << "perhaps the input file doesn't exist? "<< endl;     
			exit(1);
		}

      char komm[256]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;
		int nkeys;

      char val[256];
      char card[256];

       //if (fits_get_hdrspace(in, &nkeys, NULL, &mystatus)) printerror(mystatus);
	fits_get_hdrspace(in, &nkeys, NULL, &mystatus);
	fits_read_key(in, TDOUBLE, (char *)"TSTART",
                  &mytstart, komm, &mystatus);
         cout << "OrbitRebuilder::readHeader() : read TSTART = " << mytstart << endl;

	fits_read_key(in, TDOUBLE, (char *)"TSTOP",
                  &mytstop, komm, &mystatus);
         cout << "OrbitRebuilder::readHeader() : read TSTOP = " << mytstop << endl;

tstart = mytstart;
tstop = mytstop;
/*

	  SAL1CorEventlist sal1cor(tempstring);
	  sal1cor.readHeader();
*/	

      if (isAuto()) {
        tempstring2 = arc->filenamer.getInputFileName(OrbitRebuilding);
        if(verbose) cout << "OrbitRebuilder::processBase() Expected Input File Name value given by the archive handler = " << tempstring2 << endl;
      } else {
        tempstring2 = getInputFileName();
        if(verbose) cout << "OrbitRebuilder::processBase() Expected Input File Name value given by the commandline = " << tempstring2 << endl;        
      }
//      tempstring2 = arc->curcont;
      if(verbose) cout << "OrbitRebuilder::processBase() Expected Input File Name value given by the archive handler = " << tempstring2 << endl;
      SAFitsHandler::setInputFileName(arc->get_SAL1Cor_Dir()+"/"+tempstring2);
      if(verbose) cout << "OrbitRebuilder::processBase() Set Input File Name value given by the archive handler in the FitsHandler to perform OrbitRebuilding task" << tempstring2 << endl;
      arc->showEnv();
      arc->retrieveAllFileNames();
      if(verbose) cout << "OrbitRebuilder::processBase() output file name will be " << arc->getSAL1Orb_FileName() << endl;
      tempstring2 = arc->get_SAL1Orb_Dir()+"/"+arc->getSAL1Orb_FileName();
      SAFitsHandler::setOutputFileName(tempstring2);  
  try {
    setRelativeFileNames();
    show();
    /*
    if (processSafe()) {
      cerr << "OrbitRebuilder::processBase() error in processing the FITS file !!" << endl;
      throw se;
    } 
    */                      
    if (process()) {
      cerr << "OrbitRebuilder::processBase() error in processing the FITS file !!" << endl;
      throw se;
    }                       
    closeInputFile();
    closeOutputFile();   
  } catch (...) {
    cerr << "OrbitRebuilder::processBase() error in executing OrbitRebuilding  " << endl;
  }
}
/** No descriptions */
string SApipeline::OrbitRebuilder::retrieveOutputFileName(){
  return arc->filenamer.getFileName(OrbitRebuilding);
}
/*    try{
    orbilder.setRelativeFileNames();
    orbilder.prepare();
    orbilder.show();
  } catch(exception &e){
    cerr << "corrector 3905 main() exception! Type "<< e.what() << endl;
  } catch(CCfits::FitsException& c){
    cerr << "corrector 3905 main() FITS exception! "<< endl;
  }
  cout << "AGILE 3905 corrector end task"<< endl;
 }
  *//** No descriptions */
void SApipeline::OrbitRebuilder::retrieveInputFileName(){
  try{
    if (verbose) cout << "OrbitRebuilder::retrieveInputFileName() going to read value in the env var "<< actfilenamenam << endl;
    const char *t  = actfilenamenam.c_str();
    actfilenameval = (string) getenv(t);
    if (verbose) cout <<"OrbitRebuilder::retrieveInputFileName() name of the env var " << actfilenamenam.c_str()  << endl;
    if (verbose) cout <<"OrbitRebuilder::retrieveInputFileName() retrieved input data directory for the OrbitRebuilder " << actfilenameval  << endl;
  } catch (const exception &e){
    cerr << "OrbitRebuilder::retrieveInputFileName() error in reading the env var " << e.what() << endl;
  }
    
}
/** prepare all the setting needed for the nominal execution */
void SApipeline::OrbitRebuilder::prepare(){
  // ##########################
  // ##########################
  // ##### INSERTED FOR DEBUG
  // ##########################
  // ##########################
  system("./getenvar.sh");
  // ##########################
  // ##########################
  retrieveInputDataDir();
  //retrieveInputFileName();  
}


/*!
    \fn SApipeline::OrbitRebuilder::rmTempFiles()
 */
void SApipeline::OrbitRebuilder::rmTempFiles()
{
  rmTempInputFiles();
  rmTempOutputFiles();
}
/** No descriptions */
string SApipeline::OrbitRebuilder::getInputFileName(){
  if(!isAuto()){
    if (verbose) cout << "OrbitRebuilder::getInputFileName() using the file name set by commandline" << endl;
    tempstring = commandlist.getInputFilename();  
  } else {
    if (verbose) cout << "OrbitRebuilder::getInputFileName() using the automatically retrieved file name" << endl;
    tempstring = getAutoInputFileName();
  }
  return tempstring;
}
/** No descriptions */
string SApipeline::OrbitRebuilder::getAutoInputFileName(){
  tempstring = arc->filenamer.getFileName(Correction);
    if (verbose) cout << "OrbitRebuilder::getAutoInputFileName()  automatically retrieved file name = "<< tempstring << endl;
  return tempstring;
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setContact(const string &cs){
  arc->filenamer.setContact(cs);
  tempstring = cs;
  setContactNumber(atoi(cs.c_str()));
}
/** No descriptions */
void SApipeline::OrbitRebuilder::setContactNumber(int cn){
  
}
/** No descriptions */
void SApipeline::OrbitRebuilder::processDebug(){
    fitser = new SAFitsHandler(getInputDataPath()+"/"+infile);
    fitser->setVerbose(true);
    fitser->setOutputFileName(filenamer.getFileName(OrbitRebuilding));
    fitser->process();
    delete fitser;
}
