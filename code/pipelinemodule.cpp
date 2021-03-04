/***************************************************************************
                          pipelinemodule.cpp  -  description
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

#include "sadp_global.h"
 
#include "pipelinemodule.h"


namespace SApipeline{
PipelineModule::PipelineModule(){
   setVerbose(false);
   cout.setf(ios::fixed,ios::floatfield);
   tstart = 0.0;
   tstop = 999999999.0;
   derived = 0;
   description = (const char*)"";
   status = init();
   start();
	try{
   if (isFirstExec()) {
     setDefaultEnvironment();
     } else {
       if (verbose) cout << "PipelineModule::PipelineModule() default environment just set: going ahead" << endl;
     }
	} catch(const exception &e){
		cerr << "PipelineModule::PipelineModule() error in setting the default environment !" << e.what() << endl;
	} catch(const SAexception &se){
		cerr << "PipelineModule::PipelineModule() error in setting the default environment !" << se.getMsg() << endl;
	}

   setExtern(false);
   if (verbose) cout << "starting elaboration of module " << description << endl;
}
PipelineModule::PipelineModule(PipelineModule &pm) {
  // TO DO
}
PipelineModule::~PipelineModule(){
   if (verbose) cout << "ending elaboration of module " << description << endl;
}
int PipelineModule::init(){
  // initialization values
  status = 0;
  setAuto(false);
  setVerbose(false);
  setIDL(true);
  // computations
  setDescription();
  if ((derived)&&(verbose))cout << "starting elaboration of module " << description << endl;
  //setDefault();
  set_IDL_Display(false);
  return status;
}
}

/** launch the execution of the pipeline stage */
int SApipeline::PipelineModule::run(){
   return status;
}
/** launch generic pipeline module, input format is correct for every stage
can be selected as input:

- the string with the input file name (complete path)
- the string with the output file name (complete path)
- a parameters list
the string with the
*/
void SApipeline::PipelineModule::launch(string & infile, string & outfile, vector<int> & params){
  if (verbose) cout << "executing PipelineModule::launch" << endl;
 }
/** sets default input values needed for the execution (e. g. extern source code path ...) */
void SApipeline::PipelineModule::setDefault(){
   if (verbose) cout << "PipelineModule::setDefault() reading default from configuration file ..." << infile << endl;
   if (verbose)  cout << "PipelineModule::setDefault() defaults at the moment are NOT portable!" << endl;
    /** out setting from source code ### TO BE CHANGED !*/
    //    string ts;
    //    ts = getUserHome();
    source_path = getSasoaWorkDir()+"/software/pipeline/";
    input_path =  getSasoaWorkDir()+"/data/";
    output_path = getSasoaWorkDir()+"/products/";
    products_path = "/SASOA/SA/products/";            
    workdir =  getWorkDir();
}
/** No descriptions */
void SApipeline::PipelineModule::setExtern(bool value){
  extern_lan = value;
}
/** Set the input filename to read and on which perform the elaboration
the operand string fname represent the name without the path*/
void SApipeline::PipelineModule::setInputFileName(const string &fname){
  if (verbose) cout << "executing PipelineModule::setInputFilename()" << endl;
  infile = fname;
  commandlist.compars_map["infile"] = fname;
  if (verbose) cout << "infile = " << commandlist.compars_map["infile"] << endl;  
}
/** No descriptions */
void SApipeline::PipelineModule::setOutputDir(const string &fname){
  if (verbose) cout << "executing PipelineModule::setOutputDir" << endl;
  outdir = fname;
  commandlist.compars_map["outdir"] = fname;
}

/** show default setting */
void SApipeline::PipelineModule::showDefault(){
    if (verbose){
    cout << "PipelineModule::showDefault()" << infile << endl;
    /**  --- */
    cout << "source_path = "<< source_path << endl;
    cout << "input_path =" << input_path << endl;
    cout << "output_path = "<< output_path << endl;
    cout << "products_path = "<< products_path << endl;
    cout << "output dir = "<< workdir << endl;
  }
}
/** No descriptions */
bool SApipeline::PipelineModule::isExtern(){
  return  extern_lan;
}
/** returns the input filename without the extension */

/** No descriptions */
string SApipeline::PipelineModule::getDefaultOutputDir(){
  return outdir;
}
/** return workdir = product_path+outdir */
string SApipeline::PipelineModule::getWorkDir(){
  return workdir;
}
/** No descriptions */
void SApipeline::PipelineModule::setWorkDir(){
  workdir = products_path+getDefaultOutputDir();
}
/** No descriptions */
void SApipeline::PipelineModule::setIDL(bool val){
  if (val) idl_on = true;
  else idl_on = false;
}
/** No descriptions */
bool SApipeline::PipelineModule::isIDLon(){
  return idl_on;
}
/** No descriptions */
void SApipeline::PipelineModule::saveDefaultPar(){
    ofstream noutfile;
    string fn;
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/defval.txt";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::app);
        noutfile << "source_path = "<< source_path << endl;
        noutfile << "input_path =" << input_path << endl;
        noutfile << "output_path = "<< output_path << endl;
        noutfile << "products_path = "<< products_path << endl;
        noutfile << "output dir = "<< workdir << endl;
        noutfile.close();
      } // close try
      catch (ofstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }
     if (verbose) cout << "Finished execution of SApipeline::PipelineModule::saveDefaultPar()" << endl;
}
/** No descriptions */
void SApipeline::PipelineModule::readDefaultPar(){
    //cout << "executing SApipeline::PipelineModule::readDefaultPar()" << endl;
    ifstream ninfile;
    string fn;
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/defval.txt";
        ninfile.open (fn.c_str(), ifstream::in);
        while(!ninfile.eof()){
           cout << ninfile.read(buf, mlinelen) << endl;
           cout << buf << endl;
        }
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }
     if (verbose) cout << "Finished execution of SApipeline::PipelineModule::readDefaultPar()" << endl;
}
/** sets on memory variables the customized work environment
(path, parameters, ...) */
void SApipeline::PipelineModule::setWorkEnv(string par[10]){
}
/** No descriptions */
string SApipeline::PipelineModule::getInputFileName(){
}
/** No descriptions */
void SApipeline::PipelineModule::setVerbose(bool val){
  verbose = val;
}
/** No descriptions */
void SApipeline::PipelineModule::set_IDL_Display(bool val){
  idl_display = val;
}
/** No descriptions */
string SApipeline::PipelineModule::retrieveFilename(const string &ext, const string &dir, int extnum){
    string syscallcom;
    syscallcom = "ls -t " +dir+"/*"+" > filelist.txt";
    system(syscallcom.c_str());    
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ifstream ninfile;
    stringstream ss;
    string fn;
    ninfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {  
        fn = "filelist.txt";
        ninfile.open (fn.c_str(), ofstream::in);
        ninfile.getline(buf, mlinelen) ;
        ss << buf;
        if (verbose) cout << "PipelineModule::retrieveFilename going to read the file " << ss.str() << endl;        
        fn = ss.str();
        ninfile.close();
      } // close try
      catch (ofstream::failure e) {
          cout << "PipelineModule::retrieveFilename Exception opening/writing file"<< endl;
      }

  switch (extnum){
    case 0:
    break;
    case 1:
      pos = fn.find_last_of(".");
      if (fn.substr(pos, -1)==ext) {   // if_1
        if (verbose) {
          if (verbose) cout << " pos = " << pos << "  extracted inputfile " <<  fn.substr(0, pos) << endl;
          if (verbose) cout << "selected the right extension" <<  endl;
        } else {
          if (verbose) cout << "the extension of the read filename is" << fn.substr(pos, -1) << endl;          
        }
    }  // close if_1
    break;
    case 2:
    break;
    default:
    break;    
  }// close_switch
    return ss.str();
     if (verbose) cout << "Finished execution of PipelineModule::retrieveFilename()" << endl;
}
/** No descriptions */
void SApipeline::PipelineModule::setEnvironment(string envstrings[4]){
   SASOA_HOME = envstrings[0];
   DETNAM = envstrings[1];
   SASOA_INST_ENV= envstrings[2];
   WORK_DET_PATH= envstrings[3];
}
/** No descriptions */
void SApipeline::PipelineModule::setDefaultEnvironment(){
    string ts[4];
    ts[0] = getSasoaHome();  // SASOA_HOME
    ts[1] = retrieveDefaultDetNam();  // DETNAM
    ts[2] = getUserHome()+"/SASOA/";  // SASOA_INST_ENV
    ts[3] = ts[2]+ts[1]+"/data/";  // WORK_DET_PATH
    setEnvironment(ts);
}
/** No descriptions */
string SApipeline::PipelineModule::getSasoaHome(){
  try{
	ss.str(""); ss << getenv("SASOA_HOME"); tempstring2 = ss.str();
	if (verbose) cout << "retrieved sasoa home = " << tempstring2 << endl;
  } catch (const exception &e ){
    cerr << "PipelineModule::getSasoaHome() error " << e.what() << endl;
  }catch (...){
    cerr << "PipelineModule::getSasoaHome() error " << endl;
    throw e;
  }
  return tempstring2;
}
/** No descriptions */
void SApipeline::PipelineModule::setSasoaHome(const string &sh){
  string tempstring = "export SASOA_HOME="+sh;
  system(tempstring.c_str());
  SASOA_HOME =  sh;
}
/** No descriptions */
void SApipeline::PipelineModule::showEnvironment(){
    cout << "SASOA_HOME = " << SASOA_HOME << endl;
  /**  the directory containing the data to process related to a particular instrument/prototype/simulator */
    cout << "DETNAM = " << DETNAM << endl;
  /** the root directory of the SASOA work environment */
    cout << "SASOA_INST_ENV = " << SASOA_INST_ENV << endl;
  /** the directory related to a certain instrument/protoytpe */
    cout << "WORK_DET_PATH = " << WORK_DET_PATH << endl;

     /** Using the archive handler pointer*/
     try{
        arc->showEnv();
     } catch(const exception &e){
        cerr << "exception "<< e.what() << endl;
     }
}
/** No descriptions */
void SApipeline::PipelineModule::passOutputFile(const string &toutdir){
 
}
/** No descriptions */
string SApipeline::PipelineModule::getUserHome(){
      string ss = (string) getenv("HOME");
      if(verbose) cout << "UserHome = "<< ss << endl;
      return ss;
}
/** No descriptions */
void SApipeline::PipelineModule::setDetNam(const string &dn){
  if (verbose) cout << description << "executing PipelineModule::setDetNam()  = " << dn << endl;
  DETNAM = dn;
}
/** Used to save the detnam used during each session that is not the first */
void SApipeline::PipelineModule::saveDefaultDetNam(const string &dn){
    ofstream noutfile;
    string fn;
    string nfilename;
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/detnam.txt";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << dn << endl;
        noutfile.close();
      } // close try
      catch (ofstream::failure e) {
         cerr <<"Exception opening/writing file"<< endl;
      }
}
/** No descriptions */
string SApipeline::PipelineModule::retrieveDefaultDetNam(){
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ifstream ninfile;
    stringstream ss;
    string fn;
    ninfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/detnam.txt";
        ninfile.open (fn.c_str(), ofstream::in);
        ninfile.getline(buf, mlinelen) ;
        ss << buf;
        if (verbose) cout << "detnam retrieved is " << ss.str() << endl;
        ninfile.close();
      } // close try
      catch (ofstream::failure e) {
          cerr << "PipelineModule::retrieveDefaultDetNam() Exception opening/writing file def/detnam.txt"<< endl;
      }
  return ss.str();
}
/** No descriptions */
string SApipeline::PipelineModule::getDetnam(){
       if (verbose) cout << "PipelineModule::getDetnam() DETNAM = "<< DETNAM << endl;
  return DETNAM;
}
/** No descriptions */
/** No descriptions */
string SApipeline::PipelineModule::getIDLSourcePath(){
  string temp =  getUserHome() + "/SASOA/"+getDetnam()+"/software/pipeline/";
  return temp;
}
/** No descriptions */
string SApipeline::PipelineModule::getSasoaWorkEnv(){
  return WORK_DET_PATH;
}
/** No descriptions */
void SApipeline::PipelineModule::setSasoaWorkEnv(const string &we){
  WORK_DET_PATH = we;
}
/** return where to find data [is a default] */
string SApipeline::PipelineModule::getInputDataPath(){
  tempstring = getUserHome()+"/SASOA/"+ getDetnam()+"/data";
  return tempstring;
}
/** No descriptions */
string SApipeline::PipelineModule::getProductPath(){
  tempstring =  getUserHome() + "/SASOA/"+getDetnam()+"/products";
  if (verbose) cout << "PipelineModule::getProductPath() " << tempstring << endl;
  return  tempstring;
}
/** No descriptions */
string SApipeline::PipelineModule::getOutputPath(){
  tempstring =  getUserHome() + "/SASOA/"+getDetnam()+"/products/"+outdir;
  return  tempstring;
}
/** No descriptions */
string SApipeline::PipelineModule::getOutputDir() const  {  
   return outdir;
}
/** No descriptions */
void SApipeline::PipelineModule::retrieveOutdir(const PipelineModule &pm){
  outdir = pm.getOutputDir();
}
/** No descriptions */
string SApipeline::PipelineModule::getInputFileName(const string &dir, const string &ext) {
    stringstream ss, ss1;
    struct dirent **namelist;
    int n;

    n = scandir(dir.c_str(), &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while(n--) {
            ss.str("");
            printf("%s \n", namelist[n]->d_name);
            ss <<  namelist[n]->d_name;
            string::size_type loc = ss.str().find( ext, 0 );
            if( loc != string::npos ) {
                if (verbose) cout << "PipelineModule::getInputFileName() Found given extension at " << loc << endl;
                if (verbose) cout << "PipelineModule::getInputFileName() selected filename " << namelist[n]->d_name << endl;
              ss1.str(ss.str())  ;
            }
            else {
                cerr << "PipelineModule::getInputFileName() Didn't find given extension" << endl;
            }     
            
            free (namelist [n]);
        }
        free (namelist);
    }
   return ss1.str();

}
/** No descriptions */
string SApipeline::PipelineModule::getDefaultInputDir() {
  tempstring = getSasoaWorkDir()+"/data";
  return tempstring;
}
/** No descriptions */
string SApipeline::PipelineModule::getInfileRoot() const {
    int pos = infile.find_last_of(".");
    if (verbose) cout << " pos = " << pos << "  extracted infile root  string " <<  infile.substr(0, pos) << endl;
    return infile.substr(0, pos);
}
/** No descriptions */
bool SApipeline::PipelineModule::executed(){
  return exec;
}
/** No descriptions */
void SApipeline::PipelineModule::setDefaultOutputDir(){
}

/** No descriptions */
void SApipeline::PipelineModule::close(){
}
/** No descriptions */
void SApipeline::PipelineModule::retrieveInputData(){
}
/** No descriptions */
void SApipeline::PipelineModule::deliveryOutputData(){
}
/** create the common.def file for IDL stg_0_1  */
void SApipeline::PipelineModule::createCommonDef(){
}
/**
returns working environment directory: $HOME/SASOA/<instrument>
the instrument dir name is selected by the user the first time the program
is executed
*/
string SApipeline::PipelineModule::getSasoaWorkDir(){
  tempstring =  getUserHome() + "/SASOA/"+getDetnam();
  if (verbose) cout << "PipelineModule::getSasoaWorkDir() = " << tempstring << endl;
  return  tempstring;
}
/** Sets LUT files used by stage_0, stage_1 idl procedures */

void SApipeline::PipelineModule::setDefaultLUTs(){
  string tf; /// tf : parameter file name
  tf = getSasoaWorkDir()+"/software/pipeline/SA_photon.par";
  ofstream outfile;
  try {
  outfile.open(tf.c_str(), ofstream::out | ofstream::trunc);
  outfile << "; ###########################################################################################" << endl;
  outfile << "; ### Generated by sasoa PipelineModule::setDefaultLUTs(), do not write below: it will be overwritten ###" << endl;
  outfile << "; ###########################################################################################" << endl;
  outfile  << endl;
// gain
  outfile << "gain_LUT_dummy='N'"   << endl;
  outfile << "gain_LUT_name='"+getSasoaWorkDir()+"/caldb/gain/SA_cali_000497_070529_170724_S_orb_00000.glt'"  << endl;
// strip efficiency
  outfile << "disabled_LUT_name='"+getSasoaWorkDir()+"/caldb/strip/dsl/SAgile_070622_quar_equal_obs_1.dsl'"  << endl;
  outfile << "noisy_LUT_name='"+getSasoaWorkDir()+"/caldb/strip/nsl/SA_scie_000000_070702_114600_S_orb_00000.nsl'"  << endl;
  outfile << "wrong_LUT_name='"+getSasoaWorkDir()+"/caldb/strip/wsl/SA_scie_003356_060222_173852_S_orb_00000.wsl'"  << endl;
  outfile.close();
  } catch (exception &e){
    cerr << "thrown exception  "<< e.what() << endl;
  }
}
/** No descriptions */
void SApipeline::PipelineModule::installDefaultLUTs(){
  setDefaultLUTs();
}
/** No descriptions */
void SApipeline::PipelineModule::deliverProducts(){
}
/** Returns the directory where to deliver SASOA final products */
string SApipeline::PipelineModule::getDeliverDirectory(){
  tempstring = getSasoaWorkDir()+"/delivery";
  return tempstring;
}
/** No descriptions */
void SApipeline::PipelineModule::createDeliveryScript(){
  ofstream outfile;
  outfile.open("dummyDeliver.bash", ofstream::out | ofstream::trunc);
  outfile << "#! /bin/sh" << endl;
  outfile << "echo creating delivery dir" << endl;  
  outfile << "mkdir "+getDeliverDirectory() << endl;
  outfile.close();
}
/** No descriptions */
void SApipeline::PipelineModule::announceDelivery(){
  cout << "PipelineModule::announceDelivery() delivered following products/data: "<< endl;
}

void  SApipeline::PipelineModule::launch(const string &infile, const string &outfile, const SasoaCommandList &params){

}
/** No descriptions */
void SApipeline::PipelineModule::createLaunchBatchScript(){
}
/** No descriptions */
void SApipeline::PipelineModule::prepareLaunch(){
   timer.start();
}
/** No descriptions */
void SApipeline::PipelineModule::finalizeLaunch(){
   timer.stop();
   timer.report();
}
/** No descriptions */
void SApipeline::PipelineModule::setCommand(SasoaCommand &cmd){
  commandlist.insertCommand(cmd);
}
/** No descriptions */
void SApipeline::PipelineModule::setCommandList(const SasoaCommandList &scl){
    commandlist = scl;
}
/** No descriptions */
int SApipeline::PipelineModule::setProgram(const SasoaCommandList &scl){
  setCommandList(scl);
  /** to do
  scl. etc etc
  */
  
}
/** No descriptions */
SasoaCommandList SApipeline::PipelineModule::getCommand(){
  return commandlist;
}

/** No descriptions */
string SApipeline::PipelineModule::getOutputFileName(){
   if (verbose) cout << "PipelineModule::getOutputFileName() this module executes "<< description << endl;
  //  if (verbose) cout << << endl;
  char *tempc = "[Orbit Rebuilding (stage -1)]";
  filenamer.setFileName(infile);             
  if (*description == *tempc) {
    if (verbose)cout << "PipelineModule::getOutputFileName() output filename is ";
    outfile = filenamer.getFileName(OrbitRebuilding);
    filenamer.show();
    if (verbose) cout << "PipelineModule::getOutputFileName() set outfile to "<< outfile << endl;
  }
  return outfile;
}
/** No descriptions */
SasoaCommandList SApipeline::PipelineModule::getCommandList(){
  return commandlist;
}
/** No descriptions */
string SApipeline::PipelineModule::retrieveSasoaHome(){
  char buf[256]; // read lines of maximun 256 characters
  int mlinelen = 256;
    ifstream is;    stringstream ss;   string fn;
    is.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/defval.txt";
        is.open (fn.c_str(), ofstream::in);
        is.getline(buf, mlinelen) ;
        is.getline(buf, mlinelen) ;
        is.getline(buf, mlinelen) ;
        ss << buf;
        if (verbose) cout << "PipelineModule::retrieveSasoaHome() sasoa home dir retrieved is " << ss.str() << endl;
        is.close();
      } // close try
      catch (ifstream::failure e) {
          cerr << "PipelineModule::retrieveSasoaHome() Exception opening/writing file"<< endl;
      }
  return ss.str();
}
/** set the path of the input directory where to search the input file */
void SApipeline::PipelineModule::setInputDir(string indir){
  input_path = indir;
}
/** No descriptions */
string SApipeline::PipelineModule::getDescription(){
  tempstring = description;
  return tempstring;
}
/** No descriptions */
void SApipeline::PipelineModule::DBConnect(const string connstring[5]){
  // create a file with arbitrary (default) db connection parameters
  const string fn("databasedata.txt");
  database = new DBConnector(connstring);
  database->saveConnValues(fn, connstring);
  // read the parameters written in the file
  database->readConnValues(fn);
  // use the parameters and connect to the database
  database->createConnection();
  // read/write on some tables
  string q("SELECT * FROM Auxiliary");
  database->executeQuery(q);
  q.assign("SELECT DateStart, DateStop FROM Correction WHERE logFile = 'pipp0'");
  database->executeQuery(q);
  // close the connection
  database->closeConnection();

  delete database;  
}
/** No descriptions */
bool SApipeline::PipelineModule::isFirstExec(){
  status = 0;
  status = system("ls -a def > sasoa_log.txt 2> error.txt");
  ///control if there is ./sasoa/default.txt
  //if (verbose) cout <<"status = " << status << endl;
  if (status){ /// is the first execution of sasoa: create default   (on "file-not-present error")
      if (verbose) cout << "first execution: installing working environment!" << endl;
   }  else {
     if(verbose) cout <<"working environment yet installed: going ahead!" << endl;
  }
    return !(status);
}
/** No descriptions */
string SApipeline::PipelineModule::getSasoaRunDir(){
  stringstream ss; ss << sasoarun_id;
  tempstring =  getUserHome() + "/SASOA/"+getDetnam()+"/products/sr"+ss.str()+"_"+tmr.getDateString();
  return  tempstring;
}
/** No descriptions */
void SApipeline::PipelineModule::createSasoaRunDir(){
  string s; stringstream ss;
  ss << getSasoaRunDir(); s = "mkdir "; s += ss.str();
  system(s.c_str());
}
/** No descriptions */
int SApipeline::PipelineModule::getSasoaRunID(){
}


/*!
    \fn SApipeline::PipelineModule::setArchiveHandler(ArchiveHandler *ah)
 */
void SApipeline::PipelineModule::setArchiveHandler(ArchiveHandler *ah)
{
  arc = ah;
  if (verbose) cout << "PipelineModule::setArchiveHandler() " << ah->getSasoaHome() << endl;
  arc->setArchiveRoot(ah->getArchiveRoot());
  arc->setSasoaHome(ah->getSasoaHome());
  arc->setSasoaWorkDir(ah->getSasoaWorkDir());
  arc->setArchiveDir(ah->getArchiveDir());
  tempstring = "../stg_2/EXP_DELIVERY/EARTH_OCCULTATION.gti";
  arc->setExposureGTI_filename(tempstring);
  tempstring = "../stg_2/sagagti/SAGA.gti";
  arc->setSagaGTI_filename(tempstring);
  //cout << "PipelineModule::setArchiveHandler() the output filename from the  rebuilder will be " << arc->filenamer.getFileName(OrbitRebuilding) <<  endl;
}




/*!
    \fn SApipeline::PipelineModule::rmTempInputFiles()
 */
void SApipeline::PipelineModule::rmTempInputFiles()
{
  arc->rmTempInputFiles();
}


/*!
    \fn SApipeline::PipelineModule::rmTempOutputFiles()
 */
void SApipeline::PipelineModule::rmTempOutputFiles()
{
  arc->rmTempOutputFiles();  
}


/*!
    \fn SApipeline::PipelineModule::rmTempFiles()
 */
void SApipeline::PipelineModule::rmTempFiles()
{
  arc->rmTempInputFiles();
  arc->rmTempOutputFiles();
}

/*!
    \fn SApipeline::PipelineModule::prepareInputFile()
 */
void SApipeline::PipelineModule::prepareInputFile()
{
}
/** No descriptions */
void SApipeline::PipelineModule::setAuto(bool b){
  autoflag = b;
}
bool SApipeline::PipelineModule::isAuto(){
  return autoflag;
}/** No descriptions */
void SApipeline::PipelineModule::setContact(const string &s){
  
}


/*!
    \fn SApipeline::PipelineModule::getContact()
 */
int SApipeline::PipelineModule::getContact()
{
    return contact;
}


/*!
    \fn SApipeline::PipelineModule::getContactMax()
 */
int SApipeline::PipelineModule::getContactMax()
{
    return contactmax;
}

/*!
    \fn SApipeline::PipelineModule::getContactMin()
 */
int SApipeline::PipelineModule::getContactMin()
{
    return contactmin;
}



/*!
    \fn SApipeline::PipelineModule::getTstart()
 */
double SApipeline::PipelineModule::getTstart()
{
    return tstart;
}

/*!
    \fn SApipeline::PipelineModule::getTstop()
 */
double SApipeline::PipelineModule::getTstop()
{
    return tstop;
}

/*!
    \fn SApipeline::PipelineModule::setTstop()
 */
void SApipeline::PipelineModule::setTstop(double tso)
{
    tstop = tso;
}
/*!
    \fn SApipeline::PipelineModule::setTstart()
 */
void SApipeline::PipelineModule::setTstart(double tsa)
{
    tstart = tsa;
}

/*!
    \fn SApipeline::PipelineModule::printTimeInterval(outstream &o)
 */
void SApipeline::PipelineModule::printTimeInterval(ostream &o)
{
	o << "TSTART ,  "<< tstart << endl;
	o << "TSTOP ,  "<< tstop << endl;
}

/*!
    \fn SApipeline::PipelineModule::readHeader()
 */
void SApipeline::PipelineModule::readHeader(const string &fname)
{
	fitsfile * in;	   int mystatus = 0;
 
        // This call reads just the header 
	FITS *pInfile;
	tempstring = arc->get_L2_Dir()+"/"+fname.c_str();
	const char * b = (const char *)tempstring.c_str(); 
		
	if (verbose) cout << "PipelineModule::readHeader() reading the header of the file " << infile << endl;   
	if (fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);

      try{
  			//pInfile = new FITS(infile,Read);
 			//fitsfile * in = (fitsfile*) new fitsfile[1];
   	   		// if(fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);
        	 // define a reference for clarity. (std::auto_ptr<T>::get returns a pointer
	  } catch(CCfits::FitsException& c){
    	 	cerr << "PipelineModule::readHeader() error in opening the inputfile "<< endl;
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
         if (verbose) cout << "PipelineModule::readHeader() : read TSTART = " << mytstart << endl;

	fits_read_key(in, TDOUBLE, (char *)"TSTOP",
                  &mytstop, komm, &mystatus);
         if (verbose) cout << "PipelineModule::readHeader() : read TSTOP = " << mytstop << endl;

	tstart = mytstart;
	tstop = mytstop;

}
void SApipeline::PipelineModule::fillFilelist(const string &listfilename){
  char buf[256]; // read lines of maximun 256 characters
  int mlinelen = 256;
    ifstream is;    stringstream ss;   string fn;
    is.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = listfilename;
        is.open (fn.c_str(), ofstream::in);
        while(!is.eof()){
          is.getline(buf, mlinelen) ;
          ss.str("");ss << buf; filelist.push_back(ss.str());
        }
        if (verbose) cout << "sasoa home dir retrieved is " << ss.str() << endl;
        is.close();
      } // close try
      catch (ifstream::failure e) {
          cerr << "PipelineModule::fillFilelist() Exception opening/writing file "<< listfilename << endl;
      }
      if (verbose) cout << "n. of files filled int the filelist string vector:  " << filelist.size() << endl;
  //return ss.str();

}


/*!
    \fn SApipeline::PipelineModule::setInputFilename(const string & fn)
 */
void SApipeline::PipelineModule::setInputFilename(const string & fn)
{
    infile = fn;
}


/*!
    \fn SApipeline::PipelineModule::setOutputFilename(const string &ofn)
 */
void SApipeline::PipelineModule::setOutputFilename(const string &ofn)
{
	outfile = ofn;
}
/*!
    \fn SApipeline::PipelineModule::setInputFilename(const string & fn)
 */
void SApipeline::PipelineModule::setContactMax(int cma)
{
    contactmax = cma;
}


/*!
    \fn SApipeline::PipelineModule::setOutputFilename(const string &ofn)
 */
void SApipeline::PipelineModule::setContactMin(int cmi)
{
	contactmin = cmi;
}


/*!
    \fn SApipeline::PipelineModule::setAGILEDBConnector(AGILEDBConnector *adb)
 */
void SApipeline::PipelineModule::setAGILEDBConnector(AGILEDBConnector *adb)
{
    agiledb = adb;
}
