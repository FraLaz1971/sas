/***************************************************************************
                          sasoauserinterface.cpp  -  description
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
#include "sasoauserinterface.h"

namespace SApipeline{    

SasoaUserInterface::SasoaUserInterface(): counter(0){
  first_execution = false;
  pipeline = new SasoaHandler();
  install(); /// install the source and the environment directories
  install(); /// install the source and the environment directories  
  init();
  batch = false;
}
/** Consctuctor accepts boolean flag to enable verbose messages*/
SasoaUserInterface::SasoaUserInterface(bool verb){
  first_execution = false;
  verbose = verb;
  pipeline = new SasoaHandler();
  install(); /// install the source and the environment directories
  install(); /// install the source and the environment directories
  init();
  batch = false;
}

SasoaUserInterface::~SasoaUserInterface(){
}
/** this instructions launch the pipeline: if there is the command entrystage the execution is launched */
int SasoaUserInterface::handle_entrystage(int stagenumber){

//  pipeline->initArchiveEnv();
//
//  pipeline->setArchiverEnv();
  pipeline->setAuto(false);
  status = 1;
  try{
             /** decode commands from the written line and save them in the commandlist object*/
    decodeCommand(sasoa_command);
             /** shows inserted parameters in the commandlist object*/
    if (verbose) comlist.showCommands();
            /** pass parameters to the pipeline handler
            the whole commandlist object is passed*/
            
        /** if outdir is not set the default value is used and the output of each stage is saved there
        */
    if (!(comlist.isOutDirSet()))  comlist.setDefaultOutDir(pipeline->sarchiver.getDefaultOutputDir());
        /** if indir is not set the default value is used*/
    if (!(comlist.isInDirSet()))  comlist.setDefaultInDir(pipeline->getDefaultInputDir());
//    pipeline->setIDL(false);
    if(pipeline->setProgram(comlist)) throw (HertagBase::e);
    /** start global pipeline flow execution */
    pipeline->startAll();
    /** the commandlist object is reset each time the run is executed*/
    comlist.reset();
    } catch (const exception &e) {
      cerr << "SasoaUserInterface::handle_entrystage() caught exception "<< e.what() << endl;
    }
    status = 0;
//    SAPlotter::incrementPlotSetCtr();
    SAPlotter::plotsetctr++;
    
    return status;
}
/** No descriptions */
void SasoaUserInterface::handle_exitstage(int stagenumber){
   switch(stagenumber){
     case 0:
          if (verbose) cout <<"exiting stage 0 execution (Data Reduction)" << endl;
     break;
     case 1:
          if (verbose) cout <<"exiting stage 1 execution (PhotonList Building)" << endl;
     break;
     case 2:
        if (verbose) cout <<"exiting stage 2 execution (...)" << endl;
     break;
     case 3:
        if (verbose) cout <<"exiting stage 3 execution (...)" << endl;
     break;
     default:
          if (verbose) cout <<"unknown  stage number !" << endl;
     break;
  }

}/** No descriptions */
int SasoaUserInterface::run(){
   //if (verbose) cout <<"executing SasoaUserInterface::run  " << endl;
   status = rlmmtest::run();
}

}
int SApipeline::SasoaUserInterface::setModule(/*PipelineModule  * */int module){
  //pipeline = (const PipelineHandler *) module;
	return 0;
}/** No descriptions */
void SApipeline::SasoaUserInterface::initPipeline(){
  if (verbose) cout <<"starting pipeline functions!" << endl;
}
/** gives the received command to the pipeline */
void SApipeline::SasoaUserInterface::setCommand(string commandline){
  pipeline->setCommand(commandline);
}
/** decode the command line for pipeline operations */
void SApipeline::SasoaUserInterface::decodeCommand(string line){
     if (verbose) cout <<"executing SasoaUserInterface::decodeCommand()" << endl;
     if (verbose) cout <<"line = " << line << endl;

    // read the substring til the ", " character  [sub]
     int i=0; // count the characters in a substring
     int k=0;  // count the substrings
    string sing, partial, brick;
    vector<string> subs; // substring to decode
    vector<string>::iterator it;
    it = subs.begin();
    string::iterator siter = line.begin();
    bool condition=0;
    while(siter != line.end()){ /// until the end of the string
        i = (siter)-line.begin(); /// position of the character
        sing = *siter;
        siter++;
        if  ((line.substr(i, 1)==(string)",")||(line.substr(i, 1)==(string)";")){
          condition = 1;
           /** now saving in vector of commands */;
          subs.push_back(partial);
          partial.erase(0);
          it++;
        }
        else {
          condition = 0;
          partial.append(sing);
          }
     }
   string instr, val;
   it = subs.begin();
   string sing2;
  int j=0; // count the space at the beginning of the string
   k=0;
     while(it != subs.end()){
     brick = *it;
   // erase space at the beginning of the [instruction value] string
     j=0;
     while (brick.substr(j, 1)==" ") {
        brick = brick.substr(j+1, -1);
        j++;
    }
        /** if (verbose) cout <<" subs["<< it - subs.begin() << "] = " << *it << endl; */
          k = brick.find((string)" ");
        /** if (verbose) cout <<"position of space = " << k << endl; */
        instr = brick.substr(0, k);
        /**       if (verbose) cout <<"instruction = " << instr << endl; */
        parameter.setDescription(instr);
        val = brick.substr(k+1, 1000);
        /** erase whitespace at the beginning*/
        /**        if (verbose) cout <<"argument = " << val << endl;   */
       while (val.substr(j, 1)==" ") {
          val = val.substr(j+1, -1);
          j++;    
        }
          parameter.setValue(val);
          comlist.insertCommand(parameter);
        it++;
    }
    // if not outdir command is not present set the default  creating outdir from infile root
    // if infile is not present create a default value
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_quit(){
  system("../clean.sh");
  killAllProcs();  killAllProcs();  killAllProcs();  
  rlmmtest::handle_quit();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::setBatch(bool val){
  rlmmtest::setBatch(val);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_showcommandlist(){
    cout << "executing SasoaUserInterface::handle_showcommandlist()"<< endl;
    comlist.showCommands();
}

void SApipeline::SasoaUserInterface::handle_showparameters(){
    cout << "executing SasoaUserInterface::handle_showparameters()"<< endl;
    cout << "indir\tmeaning"<< endl;
    cout << "infile\tmeaning"<< endl;
    cout << "path\tmeaning"<< endl;
    cout << "outdir\tmeaning"<< endl;
    cout << "outfile\tmeaning"<< endl;
    cout << "idl_display\tmeaning"<< endl;
    cout << "sethome\tmeaning"<< endl;
    cout << "verbose\tmeaning"<< endl;
    cout << "instrument\tmeaning"<< endl;
    cout << "attfile\tmeaning"<< endl;
    cout << "debug\tmeaning"<< endl;
    cout << "iros\tmeaning"<< endl;
    cout << "auto\tmeaning"<< endl;    
}

/** Perform all installation needed by SASOA
  - work directories tree
  - default parameters creation
  - default input files retrieving
   */
void SApipeline::SasoaUserInterface::install(){
  if (verbose) cout << "executing :SasoaUserInterface::install() "<< endl;
  /// if is the first run create default
  /// create the $SASOA_HOME/def dir
  status = 0;
  status = system("ls -a def > sasoa_log.txt 2> error.txt");
  ///control if there is ./sasoa/default.txt
  //if (verbose) cout <<"status = " << status << endl;
  if (status){ /// is the first execution of sasoa: create default   (on "file-not-present error")
      if (verbose) cout <<"first execution: installing working environment!" << endl;
     /// create  directory for tempfiles
   if (verbose) cout <<"going to execute mkdir def" << endl;
    system("mkdir def");
    ofstream noutfile;
    string fn;
    string nfilename;
    cout <<"creating the $HOME/SASOA working environment" << endl;
    cout <<"enter your option for the the sasoa work directory tree" << endl;
    cout <<"e.g. the name of the instrument/detector producing data to analyse [SA]" << endl;
    cin >> instr;
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/defval.txt";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "executed, true" << endl;
        noutfile << "instrument, " << instr << endl;
        noutfile << "sasoa_home, " << getenv("PWD") << endl;                
        noutfile.close();
      } // close try
      catch (ofstream::failure te) {
         cerr <<"Exception opening/writing file"<< endl;
      }
         first_execution = true;
    // create $HOME/<DETNAM> directory tree
    if (verbose) cout <<"selected " << instr << " for instrument name: proceeding "<< endl;
    stringstream ss;
    string mystr;
    ss <<  "./create_workenv.bash " + instr;
    mystr = ss.str();
    system(mystr.c_str());
    // install default needed by stage_0 and stage_1
   pipeline->saveDefaultDetNam(instr);
   setDetnam(instr);
  }  else {
     if(verbose) cout <<"working environment yet installed: going ahead!" << endl;
     instr = pipeline->retrieveDefaultDetNam();
     if(verbose) cout << "retrieved instrument = "<< instr << endl;
     setDetnam(instr);
     pipeline->setDetNam(instr);
     pipeline->setDefaultEnvironment();
     pipeline->createAllBatchScripts();
     pipeline->setDefaultLUTs();
   }
}
/** No descriptions */
bool SApipeline::SasoaUserInterface::isFirstExec(){
  return first_execution;
}
/** create defaults basing on the selected instrument */
void SApipeline::SasoaUserInterface::handle_setInstrument(){
    decodeCommand(sasoa_command);
             /** shows inserted parameters in the commandlist object*/
    comlist.showCommands();
    if (verbose) cout <<"going to set INSTRUMENT = " << comlist.getInstrument() << endl;
    pipeline->setDetNam(comlist.getInstrument());
    DETNAM = comlist.getInstrument();
    refreshDefPar();
}

void SApipeline::SasoaUserInterface::configureDefault(){
   cout <<"enter parameters values please ..." << endl;
  ofstream outfile;
  string buf;
  int k=0;
  outfile.open ("def/defval.txt", ofstream::out | ofstream::app);
   cout <<"enter name of the instrument/prototype producing data : <DETNAM>" << endl;
   cout <<"default = [$HOME/SASOA/PFM/data/  " << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = SASOA_HOME + "/" + buf + "/";
  WORK_DET_PATH = defpar[k-1];

   cout <<"enter directory containing input data  " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/data/]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

   cout <<"enter directory containing  gain/address LUT (I/0) " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/tables/]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

   cout <<"enter directory containing input configuration data files   " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/conf/]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

   cout <<"enter directory input data  " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/products/]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

   cout <<"enter directory input data  " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/hk/]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

   cout <<"enter gain_LUT_name (absolute path)  " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/tables/SA_cali_003667_060125_185535_S_orb_0000.glt]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] =  buf;
  saparlist["gain_LUT_name"] = buf;

   cout <<"enter noisy_LUT_name  (absolute path) " << endl;
   cout <<"default = [$HOME/SASOA/<DETNAM>/tables/SA_scie_003356_060222_173852_S_orb_00000.nsl]" << endl;
  cin >> buf; // save <DETNAM>
  if  (buf != "") defpar[k++] =  buf;
  saparlist["noisy_LUT_name"] = buf;
  saparlist.setMap(saparlist);
  int t = 0;
  while (t<20){
  outfile << defpar[t++] << endl;
  }
  outfile.close();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_conf(){
    configureDefault();
}
/** shows user defined parameters */
void SApipeline::SasoaUserInterface::showDefPar(){
   cout <<"user defined parameters are " << endl;
  int j=0;
   cout <<"user defined parameters are " << endl;
  while (j<20){
     cout <<"parameter  n. " << j << " = "<< defpar[j++] << endl;
  }
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_showdef(){
  showDefPar();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::createDefPar(){
  stringstream ss; ss << (string)getenv("HOME") + "/SASOA";
  sysinstr = ss.str(); 
  setSasoaHome(sysinstr);
  int i=0;
  defpar[i++]  = SASOA_HOME;  // SASOA_HOME
  defpar[i++]  = DETNAM;  WORK_DET_PATH =  SASOA_HOME + "/" + DETNAM ;
  defpar[i++]  = WORK_DET_PATH + "/data/";
  defpar[i++]  = WORK_DET_PATH + "/tables/'";
  defpar[i++]  = WORK_DET_PATH + "/conf/";
  defpar[i++]  = WORK_DET_PATH + "/products/";
  defpar[i++]  = WORK_DET_PATH + "/hk/";
}
/** No descriptions */
void SApipeline::SasoaUserInterface::setSasoaHome(const string &home){
  if (home != "") SASOA_HOME  = home;
  else SASOA_HOME = "/home/agile/sasoa";
}
/** No descriptions */

/** No descriptions */
void SApipeline::SasoaUserInterface::setDetnam(const string &det){
  DETNAM = det;
  defpar[1] = DETNAM;
  pipeline->setDetNam(DETNAM);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::init(){  
   cout <<"enter 'help' to know commands" << endl;
   cout <<"info @ http://bigfoot.iasf-roma.inaf.it/~agile/SAweb/UserManual" << endl;
   //SAPlotter::setPlotSetCtr(0);
   createDefPar();
   setDefaultParameters();
   pipeline->setVerbose(false);
   pipeline->setArchiverEnv();
   pipeline->initArchiveEnv();
   dem.setArchiveHandler(&pipeline->sarchiver);

}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_syntax(){
   cout <<endl;
   cout <<"command-line syntax is the following: " << endl;
   cout <<endl;
   cout <<"entrystage (0..3), exitstage (0..3)[, indir ($HOME/SASOA/<DETNAM>/data),]"  << endl;
   cout <<"[outdir ($HOME/SASOA/<DETNAM>/products)][, infile nomefile.lv1][, par1  val1][, ...] [, parN valN];" << endl;
   cout <<endl;
   cout <<"examples of command-line syntax are: "<< endl;
   cout << endl;
   cout <<"entrystage -1, exitstage 3, infile PKP010266_0_3905_000.cor, attfile ../../sal2_to_l3_ex_short/ag3914_gc.fits;"<< endl;
   cout << endl;                           
   cout <<"entrystage 0, exitstage 0, infile PKP010266_0_3905_000.lv1;"<< endl;
   cout << endl;
   cout <<"entrystage 0, exitstage 2, infile PKP010266_0_3905_000.lv1, attfile ../../sal2_to_l3_ex_short/ag3914_gc.fits;"<< endl;
   cout << endl;
   cout << endl;
   cout <<"entrystage 2, exitstage 2, infile src_0.0049crab_x+6.0043171_z+12.849998_500ks_l2.fits, attfile /home/agile/prova_grmc_satellite_on_gc_3914.fits;"<< endl;
   cout << endl;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::configureParameters(){

}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_showconf(){
  handle_showcommandlist();
  showDefPar();
  showParamemeters();                 
}
/** No descriptions */
void SApipeline::SasoaUserInterface::showParamemeters(){
  saparlist.show();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::setDefaultParameters(){
  /// parameters to save in SA_photon.par
  saparlist["gain_LUT_name"] = pipeline->getSasoaWorkDir()+"/tables/SA_cali_003667_060125_185535_S_orb_0000.glt"; 
  saparlist["noisy_LUT_name"] = pipeline->getSasoaWorkDir()+"/tables/SA_scie_003356_060222_173852_S_orb_00000.nsl";
  saparlist["gain_LUT_dummy"]="N";
  /// parameters to save in common.def
  saparlist["path_in"]=pipeline->getSasoaWorkDir()+"/data/";;/// input path of TE_Acq program
  saparlist["path_tab"]=pipeline->getSasoaWorkDir()+"/tables/";/// output path of address identification tables
  saparlist["path_conf"]=pipeline->getSasoaWorkDir()+"/conf/";/// input path of configuration files
  saparlist["path_res"]=pipeline->getSasoaWorkDir()+"/products/";/// input path of products
  saparlist["path_hk"]=pipeline->getSasoaWorkDir()+"/hk/";/// input path of HK files
  saparlist.setMap(saparlist);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::addModule(const string &des, const int &stagenum ){
  pipmod[des] = stagenum;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::eraseModule(const string &des){
    map<string, int>::iterator cur  = pipmod.begin();
    pipmod.erase(cur);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_sethome(){
  try{
        decodeCommand(sasoa_command);
             /** shows inserted parameters in the commandlist object*/
        comlist.showCommands();
        if (verbose) cout <<"going to set SASOA_HOME = " << comlist.getSasoaHome() << endl;
        pipeline->setSasoaHome(comlist.getSasoaHome());
      } catch (const exception &e){
        cerr << "handling exception :"<< e.what() << endl;      
    }
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_showenv(){
  pipeline->initArchiveEnv();
  pipeline->setArchiverEnv();  
  pipeline->setArchiveHandler(&pipeline->sarchiver);
  pipeline->showEnvironment();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_verbose(){
  try{
    decodeCommand(sasoa_command);
             /** shows inserted parameters in the commandlist object*/
    comlist.showCommands();
    if (verbose) cout <<"going to set verbose state = " << comlist.getVerboseState() << endl;
    pipeline->setVerbose(comlist.getVerboseState());
    verbose = comlist.getVerboseState();
    } catch (const exception &e){
      cerr << "handled exception "<< e.what()<< endl;
    }
}
/** rm def directory created at the first installation moment */
void SApipeline::SasoaUserInterface::handle_rm_workenv(){
    system("rm -ri def");    
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_data(){
  cout << "following input data files are available:" << endl;
  cout << endl;
  sysinstr = "ls "+WORK_DET_PATH+"/data/*.lv1 "+WORK_DET_PATH+"/data/*.evt "+WORK_DET_PATH+"/data/*.fits " +WORK_DET_PATH+"/data/*.cor "+WORK_DET_PATH+"/data/*.orb ";
  system(sysinstr.c_str());
  tempstring = "ls "+pipeline->sarchiver.get_L1_Dir()+"/*.*";
  pipeline->syscon.execCommand(tempstring);
  cout << "type only the relative filename (without the path)"<< endl;
  cout << "or use the parameter path, absolute"<< endl;   
}
/** No descriptions */
void SApipeline::SasoaUserInterface::refreshDefPar(){           
  createDefPar();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_refresh(){
  refreshDefPar();
}                                            
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testirosmap(){
  string fn("../stg_2/flist_test_f19_agile_059.map");
  IrosMap imp;
  imp.loadBinary(fn);         string sd = "test.dat";
  imp.saveBinary(sd);
  ofstream of;
  of.open("flist_dump.txt", ofstream::out | ofstream::trunc);
  imp.show(of);
  of.close();
  fn = "../stg_2/test.dat";
  IrosMap imp2;
  imp2.loadBinary(fn);
  of.open("test2_dump.txt", ofstream::out | ofstream::trunc);
  imp2.show(of);
  of.close();
  
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_correction(){  
  cout << "Executing SasoaUserInterface::handle_correction()"<< endl; 
  string infileval, outfileval; 
  string ifn;
  cout << "insert contact number of L1 file to correct" << endl;
  cin >> ifn;
  try{
    pipeline->sarchiver.set_Contacts_Dir(string("/disco2/gtb_mirror/gtb.iasfbo.inaf.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/LV1"));
    // retrieve L1 filename for the given the contact
    tempstring = "ls "+pipeline->sarchiver.get_L1_Dir()+"/*"+ifn+"*3905*.lv1";
    vector<string> resfiles = pipeline->syscon.dumpCommand(tempstring);
    cout << "SasoaUserInterface::handle_correction() n. of retrieved files = " << resfiles.size() << endl;
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
    pipeline->sarchiver.filenamer.setContact(ifn);
    tempstring2 = pipeline->sarchiver.filenamer.getOutputFileName(Correction);
    if (verbose) cout << "SasoaUserInterface::handle_correction() corrected output file name will be "<< tempstring2 << endl;
    // create outfile value string
    outfileval = pipeline->sarchiver.get_L1_Dir() + "/"+tempstring2;
    // create command string
    tempstring2 = "cor_3905 infile="+infileval+" outfile="+outfileval;
    if (verbose) cout << "SasoaUserInterface::handle_correction() going to exec the string "<< tempstring2 << endl;
    pipeline->syscon.execCommand(tempstring2);
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
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testrebuilder(){
  OrbitRebuilder reb;
  string fn("PKP007039_0_3905_000.lv1");
  reb.setInputFileName(fn);
  cout << "SasoaUserInterface::handle_testrebuilder() the output filename will be "<< reb.getOutputFileName() << endl;
  cout << "the retrieved default detnam is " << reb.retrieveDefaultDetNam() << endl;
  reb.test();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testokdaemon(){
  OKDaemon dem;
  dem.testsetting();
  OrbitRebuilder reb;
  string fn("PKP007039_0_3905_000.lv1");
  reb.setInputFileName(fn);
  cout << "SasoaUserInterface::handle_testokdaemon() the output filename will be "<< reb.getOutputFileName() << endl;
  cout << "the retrieved default detnam is " << reb.retrieveDefaultDetNam() << endl;
  dem.setPipelineModule(&reb);
  dem.test();   
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testdb(){
    string cminimo, cmaximo, outf;
    cminimo = "3001";
    cmaximo = "3002";
    outf = "testout.fits";
    pipeline->ephMerge(cminimo, cmaximo, outf);
          
    string tempstring;
    int nf = 6;
    pair<double, double> md;
    md.first = 0.;
    md.second = 0.;    
    vector<string> v;
    DBConnector db;
    
    try{
    //vector<string>::iterator it = v.begin();
    	md = db.getTimeInterval(3000, 3002);
	cout << "md.first = " << md.first << endl;
	cout << "md.second = " << md.second << endl;
    } catch (const exception &e){
    	cerr << "SasoaUserInterface::handle_testdb() error " << e.what() << endl;
    }

    string os1("../SATemporalDataSet/eph_testout.fits");
    string os2("../SATemporalDataSet/eph_other.fits");  
    double tstas, tstos;
    tstas = md.first + 756950400;
    tstos = md.second + 756950400;
    pipeline->ephCorrect(os1, os2, tstas, tstos);

}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_killprocess(){
  string tempstring("sasoa");
  ProcessKiller kp(tempstring);
  kp.test();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_admin(){
    cout << "SASOA pipeline"<< endl;
    cout << "administrative commands:"<< endl;    
    cout
       << "\twhich\tShow which history is in use\n"
       << "\tdump\tDump key bindings\n"
       << "\tlist\tDump current history\n"
       << "\tsyntax\tShow command-line syntax\n"
       << "\tshowdef\tShow user defined default\n"
       << "\tshowenv\tShow environment\n"
       << "\tshowpar\tShow command list\n"             
       << "\tshowconf\tShow the whole configuration\n"
       << "\tsethome\tSet the sasoa home\n"
       << "\tstartok\tStart the ok daemon\n"        
       << "\tteststage2\tStart the stage2test\n"
       << "\tteststage3\tStart the stage3test\n"
       << "\tinstrument\tSet instrument/prototype name\n"
       << "\tverbose\tSet verbose execution messages\n"
      << "\tcorrection\tPerform correction test\n"
      << "\tfilelist\tPerform file list ops test\n"
      << "\tkillprocess\tPerform killprocess test\n"
      << "\trefresh\tPerform refresh operation\n"
      << "\tsystem\tPerform system connector test operation\n"
      << "\tcutl3\tPerform refresh operation\n"
      << "\tallpipe\tPerform sasoa run from L1 to sky-images\n"        
      << "\ttestrebuilder\tPerform rebuilding operation test\n"
      << "\tverbose\tset/unset verbose execution\n"
      << "\ttestirosmap\tPerform irosmap creation test\n"
      << "\ttestokdaemon\tPerform ok daemon test\n"
      << "\tattest\tPerform attitude correction test\n"
      << "\ttestdb\tPerform database test\n"
      << "\tsetcontactsdir\tchange contacts dir default\n"        
      << "\tl3test\tPerform multi DetImg creation\n"
      << "\tl3test\tprepare contact data to be processed\n"
      << "\tpointing\tPerform pointing histograms test\n"
      << "\tsetluts\tmodify default LUTs\n"
      << "\tsetcontactsdir\tmodify contact dir\n"
      << "\tgnptest\tPerform gnuplot pilot test\n"
      << "\tcleardata\tPerform temporary data removing\n"        
      << "\tdetimage\tPerform detector image test\n"
      << "\tautogti\tPerform auto gti test\n"
      << "\tattest\tPerform attitude correction test\n"        
      << "\tmdimg\tPerform Multi det. image test\n"
      << "\tdatetest\tPerform date string test\n"
      << "\tloadcontact\tload data given a certain contact number\n"
      << "\tplotallmd\tPerform global MDImg test\n"
      << "\ttestiros\tPerform iros test\n"
      << "\tcutL3file\tPerform l3 data cutting\n"   
      << "\tenergy\tPerform l3 energy filter\n"   
      << "\tunzip\tunzip loaded data\n"           
      << "\tsplitdata\tPerform l3 data detector splitting\n"   
      << "\tmulticontact\tPerform l3 data cutting\n"     
      << "\ttestproducts\tPerform products gemeration test\n"            
      << "\trm_workenv\tPerform working environment deletion (caution!)\n"             
      << "\tadmin\tShow This commands\n" << endl;       
}
/** No descriptions */
string SApipeline::SasoaUserInterface::getSasoaHome(){
  return pipeline->getSasoaHome();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::killAllProcs(){
  string tempstring("xterm");
  ProcessKiller *kp;
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  tempstring = "launchIrosIDLBatch";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  tempstring="sasoa";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  tempstring="\"sh -c\"";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  tempstring="\"gdb ./sasoa\"";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_l3test(){
  exec_l3test(true);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_pointing(){

  string ifn;

    cout << "insert input file name"<< endl;
    cin >> ifn;
  
  try{
  if (verbose) cout << "SasoaUserInterface::handle_pointing() testing L3 eventlist pointing histogram creation" << endl;
  if (verbose) cout << "SasoaUserInterface::handle_l3test() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
	string hdn0("PACKETS");
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;
    sal3.readHeaders(hdn0);
    sal3.readHeaders(hdn);
    sal3.read(fn);
    sal3.fixProdSetDir();
    sal3.createProdSetDir();
    sal3.setDebug(false);
    string imf1 = "test_irosmap.dat";
    sal3.createPointHistos();
    //    sal3.createDefaults();
    if (verbose) cout << "SasoaUserInterface::handle_pointing() plotting pointing histograms"<< endl;
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');
    if (verbose) cout << "SasoaUserInterface::handle_pointing() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_pointing() error in creating  processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_pointing() FITS error in processing L3 eventlist" << endl;
}

}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testgnuplot(){
  cout << "testing gnuplot pilot functions start" << endl;
  SAPointHistosPlotter phplot;
  SAPlot splot;
  splot.setDimension(1024);
  for(int i=0; i<1024; i++){
    splot.setPoint(i, i*0.33);
  }
    string s("dati_gp.dat");
    splot.saveGnuPlot(s);
  phplot.setXSize(1024);
  phplot.setYSize(1024);
  phplot.setAxes('p');
  phplot.init();
  phplot.SAPlotter::setXRange(0, 1024);
  phplot.SAPlotter::setYRange(0, (long int)1024);
  phplot.start();
  phplot.SAPlotter::start();
  string ps("plot.plt");
  phplot.SAPlotter::save(ps.c_str());
  cout << "press enter to continue"<< endl; 
  phplot.load("plot.plt");
  phplot.SAPlotter::stop();
  phplot.stop();
  cout << "testing gnuplot pilot functions end" << endl;
}
/** No descriptions */

void SApipeline::SasoaUserInterface::handle_newtest(){
  cout << "executing newtest()" << endl;
  try{
  if (verbose) cout << "testing L3 eventlist pointing histogram creation" << endl;
    string  fitsfilename("/data1/agile/data/sim_with_bkg/cut.fits");
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;
    sal3.read(fn);
    string imf1 = "test_irosmap.dat";
    sal3.fixProdSetDir();
    sal3.createProdSetDir();
    sal3.setDebug(false);
    sal3.saveIrosMap3(imf1);
    if (verbose) cout << "SasoaUserInterface::handle_newtest() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_newtest() error in processing L3 eventlist" << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_newtest() FITS error in processing L3 eventlist" << endl;
  }

}
  /** No descriptions */
void SApipeline::SasoaUserInterface::handle_mdimg(){
  cout << "executing mdimg()" << endl;
  try{
  if (verbose) cout << "testing L3 eventlist pointing histogram creation" << endl;
    string  fitsfilename("/data1/agile/data/sim_with_bkg/cut.fits");
    SAL3Eventlist sal3;    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;

    //sal3.readHeaders(hdn);
    sal3.read(fn);
    sal3.fixProdSetDir();
    sal3.createProdSetDir();
    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);
    sal3.getAllDetImages();

    string imf1 = "test_mdimg.dat";

    try{
         sal3.saveIrosMap3(imf1);     
      } catch(const exception &e){
          cerr << "exception in SAL3Eventlist::saveIrosMap() " << e.what() << endl;
      }
      
     // plot midimgs
    if (verbose) cout << "SasoaUserInterface:::handle_mdimg() plotting mdimgs"<< endl;
    sal3.setImageType(1);
    sal3.plotMDImage();    
    //    // plot pointing histograms
    
    if (verbose) cout << "plotting pointing histograms"<< endl;
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

    sal3.setFCounter(0);
    

    if (verbose) cout << "SasoaUserInterface:::handle_mdimg() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface:::handle_mdimg() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface:::handle_mdimg() FITS error in processing L3 eventlist" << endl;
  } catch(SAexception &se){
    cerr << se.what() << endl;
    cerr << se.getMsg() << endl;
  }

}
/** No descriptions */
void SApipeline::SasoaUserInterface::clean(){  
  string tempstring("xterm");
  ProcessKiller *kp;
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  cout << "deleted xterm"<< endl;
  tempstring = "launchIrosIDLBatch";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  cout << "deleted launchIrosIDLBatch"<< endl;
  tempstring="\"sh -c\"";
  kp = new ProcessKiller(tempstring);
  kp->killProcs();
  delete kp;
  cout << "deleted sh -c"<< endl;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_datetest(){
  cout << "SasoaUserInterface::handle_datetest() executing"<< endl;
  Timer  tm;
  cout << "the date string is " << tm.getDateString() << endl;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testproducts(){
  cout << "SasoaUserInterface::handle_testproducts() executing"<< endl;
  try{
  if (verbose) cout << "testing L3 eventlist processing" << endl;
    string  fitsfilename("/data1/agile/data/sim_with_bkg/test/cut2.fits");
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setDebug(false);
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;
    sal3.readHeaders(hdn);
    sal3.read(fn);
    sal3.fixProdSetDir();
    sal3.createProdSetDir();
    sal3.getAllDetImages(); string imf1 = "test_irosmap.dat";
    sal3.saveIrosMap3(imf1);
    if (verbose) cout << "SasoaUserInterface::handle_l3test() plotting pointing histograms"<< endl;
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');
    if (verbose) cout << "SasoaUserInterface::handle_l3test() ended"<< endl;
  } catch(SAexception &e){
    cerr << "SasoaUserInterface::handle_l3test() error in processing L3 eventlist" << se.getMsg() << endl;
    cerr << e.what() << endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_l3test() error in creating  processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_l3test() FITS error in processing L3 eventlist" << endl;
}
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_detimage(){
  try{
      string  fitsfilename("/data1/agile/data/sim_with_bkg/prova_grmc_satellite_on_gc_l3_100ks_01.fits");
      SAL3Eventlist sal3;
      sal3.init();
      sal3.setDebug(false);
      sal3.setInputFilename(fitsfilename);
      string hdn("EVENTS");  string fn(fitsfilename);
      if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;
      sal3.readHeaders(hdn);
      sal3.read(fn);
      sal3.fixProdSetDir();
      sal3.createProdSetDir();
      sal3.setImageType(0);
      sal3.getAllDetImages();
    } catch(const exception &e){
      cerr << "handled exception "<< e.what() << endl;      
    }
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_plotallmdimages(){
  cout << "SasoaUserInterface::handle_plotallmdimages() executing"<< endl;
  cout << "executing mdimg()" << endl;
  try{
  if (verbose) cout << "testing L3 eventlist pointing histogram creation" << endl;
    string  fitsfilename("$SASOA_HOME/stg_2/attitude/v0.0.0/bin/prova_outfile_L3.evt");
    SAL3Eventlist sal3;    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "read dim = " << sal3.getInputDimension() << endl;

    sal3.readHeaders(hdn);   sal3.read(fn);
    sal3.fixProdSetDir();    sal3.createProdSetDir();
    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);
    sal3.getAllDetImages();

    string imf1 = "test.dat";

    try{
      sal3.saveIrosMap3(imf1);
      } catch(const exception &e){
          cerr << "exception in SAL3Eventlist::saveIrosMap() " << e.what() << endl;
      }

    //   plot pointing histograms

    if (verbose) cout << "plotting pointing histograms"<< endl;
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

    sal3.setFCounter(0);

    if (verbose) cout << "SasoaUserInterface:::handle_mdimg() plotting pointing histograms"<< endl;
    sal3.plotTotMDImage();
    if (verbose) cout << "SasoaUserInterface:::handle_mdimg() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface:::handle_mdimg() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface:::handle_mdimg() FITS error in processing L3 eventlist" << endl;
  } catch(SAexception &se){
    cerr << se.what() << endl;
    cerr << se.getMsg() << endl;
  }
  
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_otherimage(){

    int fcntr = 0;
    SAImagePlotter sp;
    SAPlot *splot;
    sp.setXSize(NCHANVAL);  sp.setYSize(NCHANVAL);
    sp.setImageType(1);
    if (debug) sp.setInteractive(true);
    else  sp.setInteractive(false);
    stringstream ss; ss.str("");  ss << "MDimg_";
    sp.setFilenameBase(ss.str());
    int *xxi = new int[1536];
    unsigned long int *yyi = new unsigned long int[1536];

  for (int k=0; k<NREGVAL; k++){ // cicle on sky regions
    //        splot.setDimension(NREGVAL);
    for (int i=0; i<NDET; i++){ // cicle on detectors
      splot = new SAPlot();      splot->setDimension(1536);
      string st = sp.getPlotSetDir(); st+="/";
      st+="MDimage_";      ss.str("");      ss<<fcntr;
      st+= ss.str();  st+=".dat";

      for (int j=0; j<NCHANVAL; j++){ // cicle on detectors
      //  fill the X display plot & ASCII
            xxi[j] = j; yyi[j] = j*j; splot->setPoint((float)xxi[j], (long)yyi[j] );
      } // end cicle on strips
      // save the data passing the filename
      splot->saveGnuPlot(st);
      delete splot;
      ss.str("");
      ss << "MDImage region " << k << " detector " << i ;
      string tempstring = ss.str();
      // pass data & plot
      sp.setData(xxi, yyi, NCHANVAL);
      sp.start();
      sp.setPlotTitle(tempstring);
      sp.plot();      sp.print();  
      sp.stop();
      // load the plot
      fcntr++;
    } // end cicle on detectors
  }  // end cicle on sky regions
  delete [] xxi;  delete [] yyi;
}
void SApipeline::SasoaUserInterface::handle_testiros(){
try{
    SourcesExtractor srcxtractor;
    pipeline->initArchiveEnv();
    tempstring = pipeline->getSasoaHome();
    pipeline->sarchiver.setSasoaHome(tempstring);
    tempstring = pipeline->getSasoaWorkDir();
    pipeline->sarchiver.setSasoaWorkDir(tempstring);
    srcxtractor.setArchiveHandler(&pipeline->sarchiver);
    pipeline->setVerbose(true);
 

    string timfn;
    cout << "SasoaUserInterface::handle_testiros()"<< endl;
    cout << "enter the irosmap file name"<< endl;
    cin >> timfn;    
    srcxtractor.setIrosMapFileName(timfn);
    string temp;
    temp = srcxtractor.getSasoaHome()+"/stg_2/";
    srcxtractor.irospilot.setBaseDir(temp);
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
  srcxtractor.deliverProducts();
  srcxtractor.announceDelivery();
  srcxtractor.finalizeLaunch();  
} catch(...){
	cerr << "error in running the pipeline" << endl;
}
}
void SApipeline::SasoaUserInterface::handle_cutL3(){
  try{
  if (verbose) cout << "SasoaUserInterface::handle_cutL3() testing L3 eventlist processing" << endl;
    string  fitsfilename("/data1/agile/data/sim_with_bkg/testiros.fits");
    string  outfilename("/data1/agile/data/sim_with_bkg/cut.fits");    
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_cutL3() read dim = " << sal3.getInputDimension() << endl;
    sal3.readHeaders(hdn);
    sal3.readPart(fn, 0, 1000);

    int k=0;
    
    while(k<100){                                  
      sal3.getEvent(k).show();
      k++;  
    }
    
    sal3.savePart(outfilename, 1000);
        
    if (verbose) cout << "SasoaUserInterface::handle_cutL3() SasoaUserInterface::handle_l3test() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_cutL3() error in creating  processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_cutL3() FITS error in processing L3 eventlist" << endl;
}
}

void SApipeline::SasoaUserInterface::handle_cutL3file(){

  string ifn;
  long int nr;
  cout << "enter input filename (complete path)"<< endl;
  cin >> ifn;
  cout << "enter n. of events "<< endl;
  cin >> nr;
  
  try{
  if (verbose) cout << "SasoaUserInterface::handle_cutL3() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    stringstream ss1; ss1 << counter++;
    
    string  outfilename("/data1/agile/data/sim_with_bkg/cut");
    outfilename+=ss1.str();
    outfilename+=".fits";    
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_cutL3() read dim = " << sal3.getInputDimension() << endl;
    //sal3.readHeaders(hdn);
    sal3.readPart(fn, 0, nr);

    int k=0;

    while((k<nr/100)&&(k<100)){
      sal3.getEvent(k).show();
      k++;
    }

    sal3.savePart(outfilename, nr);

    if (verbose) cout << "SasoaUserInterface::handle_cutL3() SasoaUserInterface::handle_l3test() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_cutL3() error in creating  processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_cutL3() FITS error in processing L3 eventlist" << endl;
}
  
}

void SApipeline::SasoaUserInterface::handle_cleardata(){
  cout << "executing SasoaUserInterface::handle_cleardata()" << endl;  
  pipeline->sarchiver.setVerbose(true);
  pipeline->setArchiverEnv();
  pipeline->sarchiver.showEnv();
  pipeline->clearTempData();
}

/*!
    \fn SApipeline::SasoaUserInterface::handle_startokdaemon()
 */
void SApipeline::SasoaUserInterface::handle_startokdaemon()
{
  cout << "executing SasoaUserInterface::handle_startokdaemon()" << endl;
  /** Initialize the archiver environment for all the pipeline stages*/
  pipeline->setVerbose(true);
  pipeline->setArchiverEnv();
  pipeline->initArchiveEnv();
  pipeline->setAuto(true);
  //pipeline->showEnvironment();
  OKDaemon dem;
  dem.testsetting();

//  dem.setPipelineModule((PipelineModule *)pipeline);
  dem.setSasoaHandler(pipeline);
  try{
    dem.start();
  } catch(const SAexception &s) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << s.getMsg() << endl;
  } catch(const exception &e) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << e.what() << endl;
  }catch(...) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " <<  endl;    
  }
  pipeline->setVerbose(false);
}

/*!
    \fn SApipeline::SasoaUserInterface::handle_testattitude()
 */
void SApipeline::SasoaUserInterface::handle_testattitude()
{
  cout << "executing SasoaUserInterface::handle_testattitude()" << endl;
  pipeline->setArchiverEnv();
  pipeline->srcxtractor.launchAttitudeCorrection();
  tempstring = pipeline->srcxtractor.getUserHome()+"/SASOA/"+pipeline->srcxtractor.getDetnam()+"/data/L3";
  pipeline->srcxtractor.passOutputFile(tempstring); // control: generalize?
}
void SApipeline::SasoaUserInterface::exec_attitude(int contactnum)
{
  cout << "executing SasoaUserInterface::exec_testattitude(int contactnum)" << endl;
  pipeline->setArchiverEnv();
  try{
	pipeline->srcxtractor.launchAttitudeCorrection(contactnum, contactnum);
  } catch(const SAexception &se){
  	cerr << "error in launching attitude correction task " << se.getMsg() << endl; 
  } catch (const exception &e){
  	cerr << "error in launching attitude correction task " << e.what() << endl; 
  } catch(...){
  	cerr << "error in launching attitude correction task " << endl; 
  }
  tempstring = pipeline->srcxtractor.getUserHome()+"/SASOA/"+pipeline->srcxtractor.getDetnam()+"/data/L3";
  pipeline->srcxtractor.passOutputFile(tempstring); // control: generalize?
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_testsystem(){
  cout << "executing SasoaUserInterface::handle_testsystem()" << endl;
  SystemConnector sc;
  sc.setVerbose(true);
  sc.setShellMode(true);
  string str("REBUILDER_INDIR");
  if (verbose) cout << "SasoaUserInterface::handle_testsystem() var =  " << sc.retrieveEnvVar() << endl; 
  sc.testCommand();
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_stage3test(){
  cout << "SasoaUserInterface::handle_stage3test() TO DO !"<< endl;
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_stage2test(){
   handle_testattitude();
   exec_l3test(false);
}
/** No descriptions */
void SApipeline::SasoaUserInterface::exec_l3test(bool interactive){

  string ifn;

  if (interactive) {
    cout << "insert input file name"<< endl;
    cin >> ifn;
  } else {
    ifn =  "$HOME/SASOA/SA/data/prova_outfile_L3.evt";
  }
  
  try{
  if (verbose) cout << "SasoaUserInterface::exec_l3test( testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "SasoaUserInterface::exec_l3test() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename); string hdn0("PACKETS"); 
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::exec_l3test() read dim = " << sal3.getInputDimension() << endl;
try{
    sal3.readHeaders(hdn0);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist header" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist header" << endl;
}
try{
    sal3.readDebug(fn);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist" << endl;
}

try{
    sal3.createPointHistos();
} catch (const exception &e){
	cerr << "error in creating point histos " << e.what() << endl;
} catch (...){
	cerr << "error in creating point histos" << endl;
}

    sal3.fixProdSetDir();
    sal3.createProdSetDir();

    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);

try{
    sal3.getAllDetImages();
} catch (const exception &e){
	cerr << "error in getting detector images " << e.what() << endl;
} catch (...){
	cerr << "error in getting detector images" << endl;
}

    string imf1 = ifn+"test_irosmap.dat";
	cout << "SasoaUserInterface::exec_l3test() saving irosmap on file " << imf1 << endl;

         cout << "SasoaUserInterface::exec_l3test() going to exec saveIrosMap3 "<< endl;
       try{
         sal3.saveIrosMap3(imf1);
         cout << "SasoaUserInterface::exec_l3test() executed saveIrosMap3 "<< endl;
      } catch(const exception &e){
          cerr << "exception in saving the iros map " << e.what() << endl;
      }


    sal3.setFCounter(0);
    sal3.setImageType(1);
    sal3.setDebug(false);
    sal3.plotMDImage();

    //  plot pointing histograms

    if (verbose) cout << "SasoaUserInterface::exec_l3test() plotting pointing histograms"<< endl;
    sal3.setDebug(false);
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

     cout << "SasoaUserInterface::handle_l3test() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_l3test() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_l3test() FITS error in processing L3 eventlist" << endl;
}   catch(...){
    cerr << "SasoaUserInterface::handle_l3test() error!" << endl;

}
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_createirosmap(){

  string ifn = sasoa_command.substr(15, -1);
  if (verbose) cout << "SasoaUserInterface::handle_createirosmap() going to read file = "<< ifn << endl;

  if (verbose) cout << "SasoaUserInterface::handle_createirosmap() sasoa_command = "<< sasoa_command << endl;

  try{
  if (verbose) cout << "SasoaUserInterface::handle_createirosmap() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "SasoaUserInterface::handle_createirosmap() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_createirosmap() read dim = " << sal3.getInputDimension() << endl;

    sal3.readDebug(fn);

    sal3.createPointHistos();
    sal3.fixProdSetDir();
    sal3.createProdSetDir();

    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);
    sal3.getAllDetImages();

    string imf1 = ifn+"test_irosmap.dat";

    try{
      system("rm test_irosmap.dat");
    }catch(...){cerr << "I/O error in removing dat file"<< endl;}


         cout << "going to exec saveIrosMap3 "<< endl;
       try{
         sal3.saveIrosMap3(imf1);
         cout << "executed saveIrosMap3 "<< endl;
      } catch(const exception &e){
          cerr << "exception in saving the iros map" << e.what() << endl;
      }


    sal3.setFCounter(0);
    sal3.setImageType(1);
    sal3.setDebug(false);
    sal3.plotMDImage();

    //  plot pointing histograms

    if (verbose) cout << "plotting pointing histograms"<< endl;
    sal3.setDebug(false);
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

     cout << "SasoaUserInterface::handle_l3test() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_l3test() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_l3test() FITS error in processing L3 eventlist" << endl;
}   catch(...){
    cerr << "SasoaUserInterface::handle_l3test() error!" << endl;
}
}
/** No descriptions */
void SApipeline::SasoaUserInterface::handle_filelist(){
  string sarg1("ls *");
  FileList *outfilelist = new FileList(sarg1);
  outfilelist->show();
  delete outfilelist;

  string temps0 = pipeline->sarchiver.filenamer.getNameRoot();
  if (verbose) cout << "SasoaUserInterface::handle_filelist() base name for delivered files : " << temps0 << endl;
  if (verbose) cout << "SasoaUserInterface::handle_filelist() source file to copy" << endl;
  string sarg("ls ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl");
  FileList *soutfilelist = new FileList(sarg);
  soutfilelist->show();

  // create the file list with the destination files
  if (verbose) cout << "SasoaUserInterface::handle_filelist() destinations " << endl;
  string sarg2 = "ls ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl | sed 's/..\\/stg_2\\/SA_scie_000000_060626_150000_S_orb_00000/"+temps0+"/'";
  FileList *doutfilelist = new FileList(sarg2);
  doutfilelist->show();

  list<string> *rel1 = (list<string>*)soutfilelist;
  list<string> *rel2 = (list<string>*)doutfilelist;
  list<string>::iterator rit1 = soutfilelist->begin();
  list<string>::iterator rit2 = doutfilelist->begin();
  while (rit1 != soutfilelist->end()){
       tempstring = "mv "+(*rit1)+" "+pipeline->getSasoaWorkDir()+"/delivery/"+(*rit2);
       cout << "copy command = " << tempstring << endl;
       rit1++; rit2++;
  }

  delete soutfilelist;
  delete doutfilelist;
}

void SApipeline::SasoaUserInterface::handle_gti(){
  string ifn;
  bool interactive = true;
  if (interactive) {
    cout << "insert L3eventlist file name"<< endl;
    cin >> ifn;
  } else {
    cout << "handle_gti() input file name is not set: using default" << endl;
    ifn =  "../stg_2/attitude/versione_for_sasoa/bin/prova_outfile_L3.evt";
  }

  try{
  if (verbose) cout << "SasoaUserInterface::handle_gti() testing L3 eventlist processing and GTI filtering" << endl;
    string  fitsfilename(ifn);
    cout << "SasoaUserInterface::handle_gti() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;     	sal3.init();
  	sal3.SAEventlist::setArchiveHandler(&pipeline->sarchiver);	
	sal3.SAEventlist::setSaveFiltered(false); 
	sal3.SAEventlist::setSaveFiltered(true);

    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_l3test() read dim = " << sal3.getInputDimension() << endl;

    //sal3.read(fn);
try{
    sal3.readDebug(fn);
} catch (const SAexception &se){
	cerr << "handle_gti() error in reading the l3 evlist" << se.getMsg() << endl;
} catch (const exception &e){
	cerr <<  "handle_gti() error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "handle_gti()error in reading the l3 evlist" << endl;
}

// asking for the GTI file

// processing GTI filtering

  string gtifn;
  bool interactive = true;
  if (interactive) {
    cout << "insert GTI file name"<< endl;
    cin >> gtifn;
  } else {
    ifn =  "../stg_2/EXP_DELIVERY/EARTH_OCCULTATION.gti";
  }
	sal3.filterAllGTI(gtifn);

} catch (const exception &e){
	cerr << "error in processing the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in processing  the l3 evlist" << endl;
}

}

  /** No descriptions */
void SApipeline::SasoaUserInterface::handle_multicontact(){
	cout << "executing SasoaUserInterface::handle_multicontact()" << endl;
	pipeline->saveMCTimeInterval("timeinterval.txt");
	pair<double, double> mti;
	mti = pipeline->getMCTimeInterval("timeinterval.txt");
}


/*!
    \fn SApipeline::SasoaUserInterface::handle_energy()
 */
void SApipeline::SasoaUserInterface::handle_energy()
{

  string ifn;
  
  cout << "insert input file name"<< endl;
  cin >> ifn;
 
  
  try{
  if (verbose) cout << "SasoaUserInterface::handle_energy() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "handle_energy() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_energy() read dim = " << sal3.getInputDimension() << endl;

    //sal3.read(fn);
try{
    sal3.readDebug(fn);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist" << endl;
}

        float nmin, nmax;
        cout << "insert energy range min"<< endl;
        cin >> nmin;
        cout << "insert energy range max"<< endl;
        cin >> nmax;
       
	sal3.filterEnergy(nmin, nmax);
	string mytempstring = "energy_filtered_L3.fits";
	sal3.saveFiltered(mytempstring);
     cout << "SasoaUserInterface::handle_energy() filtered list will be "<< mytempstring << endl;

	mytempstring = "energy_filtered_save.fits";
	//sal3.effect();
	//sal3.clearTempVectors();
	sal3.filterEnergy(nmin, nmax);
	mytempstring = "energy_filtered_save.fits";
	sal3.effect();
	sal3.save(mytempstring);
     cout << "SasoaUserInterface::handle_energy() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_energy() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_energy() FITS error in processing L3 eventlist" << endl;
}   catch(...){
    cerr << "SasoaUserInterface::handle_energy() error!" << endl;

}
}
void SApipeline::SasoaUserInterface::handle_splitdata()
{
    cout << "Executing  handle_splitdata " << endl;

  string ifn;

  cout << "insert input file name"<< endl;
  cin >> ifn;
  try{
  if (verbose) cout << "SasoaUserInterface::handle_splitdata() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "handle_splitdata() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_splitdata() read dim = " << sal3.getInputDimension() << endl;
try{
    sal3.readDebug(fn);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist" << endl;
}
	sal3.filterAllDetectors();
     cout << "SasoaUserInterface::handle_splitdata() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_splitdata() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_splitdata() FITS error in processing L3 eventlist" << endl;
}   catch(...){
    cerr << "SasoaUserInterface::handle_splitdata() error!" << endl;

}
}

void SApipeline::SasoaUserInterface::handle_loadcontact()
{
  cout << "Executing SasoaUserInterface::handle_loadcontact()"<< endl; 
  int ifn;
  cout << "insert contact number" << endl;
  cin >> ifn;
  int contactnum = ifn;
  try{
  
      cout << "executing SasoaUserInterface::handle_loadcontact() ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::handle_loadcontact() related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

	tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::handle_loadcontact() I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

	tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
	if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::handle_loadcontact() the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
    cout << "SasoaUserInterface::handle_loadcontact() default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;

        tempstring = pipeline->sarchiver.getFormattedStringNumber(ifn, 6);
    cout << "SasoaUserInterface::handle_loadcontact() formatted string = " << tempstring << endl;
}
    // load 3905 data    
    ss.str(""); ss << pipeline->sarchiver.getDefaultContactsDir(); ss << "/";
    ss << pipeline->sarchiver.getFormattedStringNumber(ifn, 6);
    tempstring = ss.str();
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    
    tempstring.insert(0, " cp ");tempstring.append("/*3905*.gz ");
    tempstring.append(pipeline->sarchiver.get_L1_Dir());
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    pipeline->syscon.execCommand(tempstring);
    
    // load 3914 data    
    ss.str(""); ss << pipeline->sarchiver.getDefaultContactsDir(); ss << "/";
    ss << pipeline->sarchiver.getFormattedStringNumber(ifn, 6);
    tempstring = ss.str();
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    
    tempstring.insert(0, " cp ");tempstring.append("/*3914*.gz ");
    tempstring.append(pipeline->sarchiver.get_L1_Dir());
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    pipeline->syscon.execCommand(tempstring);
    
    // load 3916 data    
    ss.str(""); ss << pipeline->sarchiver.getDefaultContactsDir(); ss << "/";
    ss << pipeline->sarchiver.getFormattedStringNumber(ifn, 6);
    tempstring = ss.str();
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    
    tempstring.insert(0, " cp ");tempstring.append("/*3916*.gz ");
    tempstring.append(pipeline->sarchiver.get_L1_Dir());
    cout << "SasoaUserInterface::handle_loadcontact() created string " << tempstring << endl;
    pipeline->syscon.execCommand(tempstring);
    cout << "SasoaUserInterface::handle_loadcontact() ended"<< endl;
    
  } catch(const exception &e){
    cerr << "SasoaUserInterface::handle_loadcontact() error in loading contact data eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_loadcontact() FITS in loading contact data eventlist" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_loadcontact() in loading contact data!" << endl;
  }
}

void SApipeline::SasoaUserInterface::handle_unzip(){
  tempstring = "gzip -fd ";
  tempstring += pipeline->sarchiver.get_L1_Dir();
  tempstring += "/*.gz ";
  pipeline->syscon.execCommand(tempstring);  
}

/*!
    \fn SApipeline::SasoaUserInterface::handle_autogti()
 */
void SApipeline::SasoaUserInterface::handle_autogti()
{
  cout << "SasoaUserInterface::handle_autogti()" << endl;
  handle_extract_exposure(); string t("pippo");
  exec_quat_to_sapoi(t);
  pipeline->srcxtractor.createSagaBatch();
  pipeline->srcxtractor.launchSaga();
  pipeline->srcxtractor.createExposureBatch();
  pipeline->srcxtractor.createExposureDatacard();
  pipeline->srcxtractor.launchExposure();
}

void SApipeline::SasoaUserInterface::handle_setcontactsdir(){
  cout << "SasoaUserInterface::handle_setcontactsdir()" << endl;
  cout << "Executing SasoaUserInterface::handle_setcontactsdir()"<< endl; 
  string ifn;
  cout << "insert default contacts dir to set " << endl;
  cin >> ifn;
  try{
    pipeline->sarchiver.setDefaultContactsDir(ifn);
    cout << "SasoaUserInterface::handle_setcontactsdir() now reading "<< endl;
    cout << "SasoaUserInterface::handle_setcontactsdir() read " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::handle_setcontactsdir() ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_setcontactsdir() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_setcontactsdir() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_setcontactsdir() error!" << endl;
  }
  
}

void SApipeline::SasoaUserInterface::handle_allpipe(){
  cout << "SasoaUserInterface::handle_allpipe()" << endl;
  cout << "Executing SasoaUserInterface::handle_allpipe()"<< endl; 
  int ifn;
  cout << "insert default contact number of L1 data to process " << endl;
  cin >> ifn;
  try{
    cout << "SasoaUserInterface::handle_allpipe() taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::handle_allpipe() ended"<< endl;
    pipeline->loadContact(ifn);
	handle_unzip();
    pipeline->Correct3905L1(ifn);
    if (verbose){
    cout << "SasoaUserInterface::handle_allpipe() executing with 3905 file "<< pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::handle_allpipe() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::handle_allpipe() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
    }
    tempstring = "entrystage -1, exitstage 2, infile "+pipeline->sarchiver.getLoadedCor3905FileName()+","+" attfile "+pipeline->sarchiver.getLoaded3914FileName()+", ephfile "+pipeline->sarchiver.getLoaded3916FileName()+", tempdata true;";
    cout << "SasoaUserInterface::handle_allpipe() tempstring = " << endl;
    handle_piperun(tempstring);
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_allpipe() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_allpipe() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_allpipe() error!" << endl;
  }
  
}

/*!
    \fn SApipeline::SasoaUserInterface::handle_EMIpiperun(const string &cl)
 */
void SApipeline::SasoaUserInterface::handle_EMIpiperun(const string &cl)
{
  sasoa_command = cl;
  pipeline->setAuto(false);
  status = 1;
  try{
    /** decode commands from the written line and save them in the commandlist object*/
    decodeCommand(sasoa_command);
    /** shows inserted parameters in the commandlist object*/
    comlist.showCommands();
            /** pass parameters to the pipeline handler
    the whole commandlist object is passed*/
            
        /** if outdir is not set the default value is used and the output of each stage is saved there
         */
    if (!(comlist.isOutDirSet()))  comlist.setDefaultOutDir(pipeline->sarchiver.getDefaultOutputDir());
    /** if indir is not set the default value is used*/
    if (!(comlist.isInDirSet()))  comlist.setDefaultInDir(pipeline->getDefaultInputDir());
//    pipeline->setIDL(false);
    if(pipeline->setProgram(comlist)) throw (HertagBase::e);
    /** start global pipeline flow execution */
    /** To run with EMI and without DB access*/
    pipeline->setIROS(false);
    pipeline->startAllDebug();
    /** the commandlist object is reset each time the run is executed*/
    comlist.reset();
  } catch (const exception &e) {
    cerr << "SasoaUserInterface::handle_entrystage() caught exception "<< e.what() << endl;
  }
  status = 0;
//    SAPlotter::incrementPlotSetCtr();
  SAPlotter::plotsetctr++;
}
/*!
    \fn SApipeline::SasoaUserInterface::handle_IROSpiperun(const string &cl)
 */
void SApipeline::SasoaUserInterface::handle_IROSpiperun(const string &cl)
{
  sasoa_command = cl;
  pipeline->setAuto(false);
  status = 1;
  try{
    /** decode commands from the written line and save them in the commandlist object*/
    decodeCommand(sasoa_command);
    /** shows inserted parameters in the commandlist object*/
    comlist.showCommands();
            /** pass parameters to the pipeline handler
    the whole commandlist object is passed*/
            
        /** if outdir is not set the default value is used and the output of each stage is saved there
         */
    if (!(comlist.isOutDirSet()))  comlist.setDefaultOutDir(pipeline->sarchiver.getDefaultOutputDir());
    /** if indir is not set the default value is used*/
    if (!(comlist.isInDirSet()))  comlist.setDefaultInDir(pipeline->getDefaultInputDir());
//    pipeline->setIDL(false);
    if(pipeline->setProgram(comlist)) throw (HertagBase::e);
    /** start global pipeline flow execution */
    /** MODIFIED ON 21/02/2008 */
    /** by Francesco Lazzarotto*/
    /** To run with IROS V4 and without DB access*/

    pipeline->startAllV5();
    /** the commandlist object is reset each time the run is executed*/
    comlist.reset();
  } catch (const exception &e) {
    cerr << "SasoaUserInterface::handle_entrystage() caught exception "<< e.what() << endl;
  }
  status = 0;
//    SAPlotter::incrementPlotSetCtr();
  SAPlotter::plotsetctr++;
}
/*!
    \fn SApipeline::SasoaUserInterface::handle_piperun(const string &cl)
 */
void SApipeline::SasoaUserInterface::handle_piperun(const string &cl)
{
  sasoa_command = cl;
  pipeline->setAuto(false);
  status = 1;
  try{
    /** decode commands from the written line and save them in the commandlist object*/
    decodeCommand(sasoa_command);
    /** shows inserted parameters in the commandlist object*/
    comlist.showCommands();
            /** pass parameters to the pipeline handler
    the whole commandlist object is passed*/
            
        /** if outdir is not set the default value is used and the output of each stage is saved there
         */
    if (!(comlist.isOutDirSet()))  comlist.setDefaultOutDir(pipeline->sarchiver.getDefaultOutputDir());
    /** if indir is not set the default value is used*/
    if (!(comlist.isInDirSet()))  comlist.setDefaultInDir(pipeline->getDefaultInputDir());
//    pipeline->setIDL(false);
    if(pipeline->setProgram(comlist)) throw (HertagBase::e);
    /** start global pipeline flow execution */
    /** MODIFIED ON 21/02/2008 */
    /** by Francesco Lazzarotto*/
    /** To run with IROS V4 and without DB access*/

    pipeline->startAllV5();
    /** the commandlist object is reset each time the run is executed*/
    comlist.reset();
  } catch (const exception &e) {
    cerr << "SasoaUserInterface::handle_entrystage() caught exception "<< e.what() << endl;
  }
  status = 0;
//    SAPlotter::incrementPlotSetCtr();
  SAPlotter::plotsetctr++;
  
}

  /** No descriptions */
void SApipeline::SasoaUserInterface::handle_prepare(){
  cout << "SasoaUserInterface::handle_prepare()" << endl;
  cout << "Executing SasoaUserInterface::handle_prepare()"<< endl; 
  int ifn;
  cout << "insert contact number of L1 data to process " << endl;
  cin >> ifn;
  try{
    cout << "SasoaUserInterface::handle_prepare() taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::handle_prepare() ended"<< endl;
    pipeline->loadContact(ifn);
    handle_unzip();
    pipeline->Correct3905L1(ifn);
    if (verbose){
    cout << "SasoaUserInterface::handle_prepare() executing with 3905 file "<< pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::handle_prepare() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::handle_prepare() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
    }
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_prepare() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_prepare() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_prepare() error!" << endl;
  }

}


/*!
    \fn SApipeline::SasoaUserInterface::exec_allEMIpipe(int contactnum)
 */
void SApipeline::SasoaUserInterface::exec_allEMIpipe(int contactnum)
{
  cout << "Executing SasoaUserInterface::exec_allEMIpipe on data for contact "<< contactnum << endl; 
  verbose = false; int ifn = contactnum;  ss.str("");ss<<contactnum;string scn(ss.str());ss.str("");
  pipeline->sarchiver.filenamer.setContact(scn);
  try{
	handle_cleardata();
    cout << "SasoaUserInterface::exec_allEMIpipe taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::exec_allEMIpipe() taking SA data of contact "<< contactnum << endl;
    pipeline->loadContact(ifn);
    handle_unzip();
    tempstring = "loaddata";pipeline->setStatusOnDB(tempstring); 
    pipeline->Correct3905L1(ifn); 
    tempstring = "correction";pipeline->setStatusOnDB(tempstring); 
    cout << "SasoaUserInterface::handle_allEMIpipe() pipeline->setStatusOnDB(task) task = " << tempstring << endl;
    if (verbose){
    cout << "SasoaUserInterface::exec_allEMIpipe() executing with 3905 file "<< pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::exec_allEMIpipe() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::exec_allEMIpipe() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
    }
    tempstring = "entrystage -1, exitstage 2, infile "+pipeline->sarchiver.getLoadedCor3905FileName()+","+" attfile "+pipeline->sarchiver.getLoaded3914FileName()+", ephfile "+pipeline->sarchiver.getLoaded3916FileName()+";";
    cout << "SasoaUserInterface::handle_allEMIpipe() command tempstring = " << tempstring << endl;
    cout << "SasoaUserInterface::handle_allEMIpipe() executing handle_EMIpiperun(tempstring);" << endl;
    handle_EMIpiperun(tempstring);
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_allEMIpipe() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_allEMIpipe() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_allEMIpipe() error!" << endl;
  }

}

/*!
    \fn SApipeline::SasoaUserInterface::exec_allIROSpipe(int contactnum)
 */
void SApipeline::SasoaUserInterface::exec_allIROSpipe(int contactnum)
{
  cout << "Executing SasoaUserInterface::exec_allIROSpipe"<< endl; 

  int ifn = contactnum;
  try{
	handle_cleardata();
    cout << "SasoaUserInterface::exec_allIROSpipe taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::exec_allIROSpipe() taking SA data of contact "<< contactnum << endl;
    pipeline->loadContact(ifn);
	handle_unzip();
    pipeline->Correct3905L1(ifn);
    if (verbose){
    cout << "SasoaUserInterface::exec_allIROSpipe() executing with 3905 file "<< pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::exec_allIROSpipe() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::exec_allIROSpipe() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
    }
    tempstring = "entrystage -1, exitstage 2, infile "+pipeline->sarchiver.getLoadedCor3905FileName()+","+" attfile "+pipeline->sarchiver.getLoaded3914FileName()+", ephfile "+pipeline->sarchiver.getLoaded3916FileName()+";";
    cout << "SasoaUserInterface::exec_allIROSpipe() tempstring = " << endl;
    handle_IROSpiperun(tempstring);
  } catch(exception &e){
    cerr << "SasoaUserInterface::exec_allIROSpipe() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::exec_allIROSpipe() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::exec_allIROSpipe() error!" << endl;
  }

}

/*!
    \fn SApipeline::SasoaUserInterface::exec_allpipe(int contactnum)
 */
void SApipeline::SasoaUserInterface::exec_allpipe(int contactnum)
{
  cout << "Executing SasoaUserInterface::exec_allpipe"<< endl; 
  int ifn = contactnum;
  try{
	handle_cleardata();
    cout << "SasoaUserInterface::exec_allpipe taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::exec_allpipe() taking SA data of contact "<< contactnum << endl;
    pipeline->loadContact(ifn);
	handle_unzip();
    pipeline->Correct3905L1(ifn);
    if (verbose){
    cout << "SasoaUserInterface::exec_allpipe() executing with 3905 file "<< pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::exec_allpipe() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::exec_allpipe() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
    }
    tempstring = "entrystage -1, exitstage 2, infile "+pipeline->sarchiver.getLoadedCor3905FileName()+","+" attfile "+pipeline->sarchiver.getLoaded3914FileName()+", ephfile "+pipeline->sarchiver.getLoaded3916FileName()+";";
    cout << "SasoaUserInterface::handle_allpipe() tempstring = " << endl;
    handle_piperun(tempstring);
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_allpipe() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_allpipe() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_allpipe() error!" << endl;
  }
}
void SApipeline::SasoaUserInterface::handle_newdaemon(){

  dem.testsetting();
  pipeline->setVerbose(false);
  pipeline->setArchiverEnv();
  pipeline->initArchiveEnv();
  pipeline->setAuto(true);
  //pipeline->showEnvironment();
  dem.testsetting();

//  dem.setPipelineModule((PipelineModule *)pipeline);
  dem.setSasoaHandler(pipeline);
  try{
    dem.newtest();
  } catch(const SAexception &s) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << s.getMsg() << endl;
  } catch(const exception &e) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << e.what() << endl;
  }catch(...) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " <<  endl;    
  }
  pipeline->setVerbose(false);

}
void SApipeline::SasoaUserInterface::handle_EMIDaemon(){
  cout << "SasoaUserInterface::handle_EMIDaemon()  "<< endl;
  dem.testsetting();
  pipeline->setVerbose(false);
  pipeline->setArchiverEnv();
  pipeline->initArchiveEnv();
  pipeline->setAuto(true);
  //pipeline->showEnvironment();
  dem.testsetting();

//  dem.setPipelineModule((PipelineModule *)pipeline);
  dem.setSasoaHandler(pipeline);
  cout << "SasoaUserInterface::handle_EMIDaemon()  "<< endl;
  try{
    dem.emiloop();
  } catch(const SAexception &s) {
    cerr << "SasoaUserInterface::handle_EMIDaemon() pipeline error " << s.getMsg() << endl;
  } catch(const exception &e) {
    cerr << "SasoaUserInterface::handle_EMIDaemon() pipeline error " << e.what() << endl;
  }catch(...) {
    cerr << "SasoaUserInterface::handle_EMIDaemon() pipeline error " <<  endl;    
  }
  pipeline->setVerbose(false);

}
/*!
    \fn SApipeline::SasoaUserInterface::handle_setLUTs()
 */
void SApipeline::SasoaUserInterface::handle_setLUTs()
{
    cout << "SasoaUserInterface::handle_setLUTs setting luts" << endl;
    pipeline->setDefaultLUTs();
}


/*!
    \fn SApipeline::SasoaUserInterface::handle_quat_to_sapoi()
 */
void SApipeline::SasoaUserInterface::handle_quat_to_sapoi()
{
  cout << "SasoaUserInterface::handle_quat_to_sapoi" << endl;
  cout << "Executing SasoaUserInterface::handle_quat_to_sapoi"<< endl; 
  int ifn;
  cout << "insert contact number of L1 data to process " << endl;
  cin >> ifn;
  try{
    cout << "SasoaUserInterface::handle_quat_to_sapoi taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::handle_prepare() ended"<< endl;
    pipeline->loadContact(ifn);
    handle_unzip();
    cout << "SasoaUserInterface::handle_quat_to_sapoi executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    pipeline->srcxtractor.createSapoiLaunchBatch();
    pipeline->srcxtractor.createSapoiDatacard();
    pipeline->srcxtractor.launchSapoiCreator();
    if (verbose){
    }
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_quat_to_sapoi FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error!" << endl;
  }
}


/*!
    \fn SApipeline::SasoaUserInterface::handle_extract_exposure()
 */
void SApipeline::SasoaUserInterface::handle_extract_exposure()
{
  cout << "SasoaUserInterface::handle_extract_exposure()" << endl;
  cout << "Executing SasoaUserInterface::handle_extract_exposure()"<< endl; 
  string ifn;
  cout << "insert filename of corrected L1 data to process " << endl;
  cin >> ifn;
  try{
      char komm[256];  double mytstart; double mytstop; mytstart = 0.; mytstop = 0.;
      int nkeys; char val[256];      char card[256];      fitsfile * in;	   int mystatus = 0;         
         // This call reads just the header 
	FITS *pInfile;
	const char * b =(const char *) ifn.c_str(); 
		
		cout << "handle_extract_exposure() reading the header of the file " << ifn << endl;   

		if (fits_open_file(&in, b, READONLY, &mystatus)) pipeline->printerror(mystatus);


	if(fits_get_hdrspace(in, &nkeys, NULL, &mystatus)) pipeline->printerror(mystatus);
	if(fits_read_key(in, TDOUBLE, (char *)"TSTART",
                  &mytstart, komm, &mystatus)) pipeline->printerror(mystatus);
         cout << "handle_extract_exposure() : read TSTART = " << float(mytstart) << endl;

	if(fits_read_key(in, TDOUBLE, (char *)"TSTOP",
                  &mytstop, komm, &mystatus)) pipeline->printerror(mystatus);
         cout << "handle_extract_exposure() : read TSTOP = " << float(mytstop) << endl;

	pipeline->srcxtractor.setTstart(mytstart);
	pipeline->srcxtractor.setTstop(mytstop);

  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_extract_exposure() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_extract_exposure() FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_extract_exposure()!" << endl;
  }
}


/*!
    \fn SApipeline::SasoaUserInterface::exec_quat_to_sapoi(const string &c)
 */
void SApipeline::SasoaUserInterface::exec_quat_to_sapoi(const string &c)
{
  cout << "SasoaUserInterface::handle_quat_to_sapoi" << endl;
  cout << "Executing SasoaUserInterface::handle_quat_to_sapoi"<< endl; 
  string ifn = c;
  try{
    cout << "SasoaUserInterface::handle_quat_to_sapoi taking contacts data from " << pipeline->sarchiver.getDefaultContactsDir() << endl;
    cout << "SasoaUserInterface::handle_prepare() ended"<< endl;
    cout << "SasoaUserInterface::handle_quat_to_sapoi executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    pipeline->srcxtractor.createSapoiLaunchBatch();
    pipeline->srcxtractor.createSapoiDatacard();
    pipeline->srcxtractor.launchSapoiCreator();
    if (verbose){
    }
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_quat_to_sapoi FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error!" << endl;
  }
}

/*!
    \fn SApipeline::SasoaUserInterface::exec_loadContcSSH()
 */
void SApipeline::SasoaUserInterface::exec_loadContactSSH(int contactnum)
{
    cout << "executing SasoaUserInterface::exec_loadContactSSH() ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::exec_loadContactSSH() related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

	tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_loadContactSSH() I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

	tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
	if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::exec_loadContactSSH() the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
    cout << "SasoaUserInterface::handle_loadContcSSH() default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	}
	exec_allpipe(contactnum);
tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/archive/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_loadContactSSH() I will produce " << tempstring << endl;
	
}

void SApipeline::SasoaUserInterface::handle_loadContcSSH(){
 cout << "SasoaUserInterface::handle_loadContcSSH()" << endl;
  cout << "Executing SasoaUserInterface::handle_loadContcSSH()"<< endl; 
  int ifn;
  cout << "insert contact number of L1 data to download using ssh " << endl;
  cin >> ifn;
  try{
    cout << "SasoaUserInterface::handle_loadContcSSH() default contacts dir was  " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	exec_loadContactSSH(ifn);

    if (verbose){
    cout << "SasoaUserInterface::handle_prepare() executing with 3905 file "<< 	pipeline->sarchiver.getLoadedCor3905FileName()<< endl;
    cout << "SasoaUserInterface::handle_prepare() executing with 3914 file "<< pipeline->sarchiver.getLoaded3914FileName()<< endl;
    cout << "SasoaUserInterface::handle_prepare() executing with 3916 file "<< pipeline->sarchiver.getLoaded3916FileName()<< endl;
	}

  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_quat_to_sapoi FITS error in setting default contacts dir" << endl;
  }   catch(...){
    cerr << "SasoaUserInterface::handle_quat_to_sapoi error!" << endl;
  }
}

void SApipeline::SasoaUserInterface::exec_EMI(int contactnum){
    cout << "executing SasoaUserInterface::exec_EMI ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::exec_EMI() related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

	tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_EMI() I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

	tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
	if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::exec_EMI() the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
    cout << "SasoaUserInterface::exec_EMI() default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	}
	exec_allEMIpipe(contactnum);
tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/archive/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_EMI() I will produce " << tempstring << endl;

}

void SApipeline::SasoaUserInterface::exec_runEMIContact(int contactnum)
{
    cout << "executing SasoaUserInterface::exec_runEMIContact ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::exec_runEMIContact related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

	tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_runEMIContact I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

	tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
	if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::exec_runEMIContact the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
    cout << "SasoaUserInterface::handle_runEMIContact default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	}
	exec_allEMIpipe(contactnum);
tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/archive/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_runEMIContact I will produce " << tempstring << endl;

}
void SApipeline::SasoaUserInterface::exec_runIROSContact(int contactnum)
{
    cout << "executing SasoaUserInterface::exec_runIROSContact ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::exec_runIROSContact related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

	tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_runIROSContact I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

	tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
	if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::exec_runIROSContact the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
    cout << "SasoaUserInterface::handle_runIROSContact default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	}
	exec_allIROSpipe(contactnum);
tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/archive/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
cout << "SasoaUserInterface::exec_runIROSContact I will produce " << tempstring << endl;

}
void SApipeline::SasoaUserInterface::exec_runContact(int contactnum)
{
    cout << "executing SasoaUserInterface::exec_runContact ON CONTACT " << contactnum << endl;
    cout << "SasoaUserInterface::exec_runContact related hundred contact string is " << pipeline->sarchiver.getHundredContactsDir(contactnum) << endl;

    tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
    cout << "SasoaUserInterface::exec_runContact I have to download " << tempstring << endl;
	
	// if needed set the default contacts dir

     tempstring2  = pipeline->sarchiver.getSasoaWorkDir() + "/input/"+pipeline->sarchiver.getHundredContactsDir(contactnum);
     if (pipeline->sarchiver.getDefaultContactsDir()!=tempstring2) { 		
		cout << "SasoaUserInterface::exec_runContact the default contacts dir is different setting the new ... "  << endl;
		pipeline->sarchiver.setDefaultContactsDir(tempstring2);
     cout << "SasoaUserInterface::handle_runContact default contacts dir now is   " << pipeline->sarchiver.getDefaultContactsDir() << endl;
	}
	exec_allpipe(contactnum);
     tempstring = pipeline->sarchiver.getSasoaWorkDir() + "/archive/"+pipeline->sarchiver.getHundredContactsDir(contactnum)+"/"+pipeline->sarchiver.getFormattedStringNumber(contactnum);
     cout << "SasoaUserInterface::exec_runContact I will produce " << tempstring << endl;
	
}

/*!
    \fn SApipeline::SasoaUserInterface::handle_asdc_daemon()
 */
void SApipeline::SasoaUserInterface::handle_asdc_daemon()
{
 dem.testsetting();
  pipeline->setVerbose(false);
  pipeline->setArchiverEnv();
  pipeline->initArchiveEnv();
  pipeline->setAuto(true);
  //pipeline->showEnvironment();
  dem.testsetting();

//  dem.setPipelineModule((PipelineModule *)pipeline);
  dem.setSasoaHandler(pipeline);
  try{
    dem.asdc_test();
  } catch(const SAexception &s) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << s.getMsg() << endl;
  } catch(const exception &e) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " << e.what() << endl;
  }catch(...) {
    cerr << "SasoaUserInterface::handle_startokdaemon() pipeline error " <<  endl;    
  }
  pipeline->setVerbose(false);
}


/*!
    \fn SApipeline::SasoaUserInterface::handle_exposure()
 */
void SApipeline::SasoaUserInterface::handle_exposure()
{
  string ifn;

    cout << "insert input file name"<< endl;
    cin >> ifn;
  
  try{
  if (verbose) cout << "SasoaUserInterface::handle_exposure() testing L3 eventlist processing" << endl;
    string  fitsfilename(ifn);
    cout << "going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;
    sal3.init();
    sal3.setInputFilename(fitsfilename); string hdn0("PACKETS"); 
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_exposure() read dim = " << sal3.getInputDimension() << endl;

try{
    sal3.readDebug(fn);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist" << endl;
}
  sal3.retrieveExposure();
  double a = sal3.getExposure();
  double sta = sal3.getTstart();
  double sto = sal3.getTstop();
   cout << "SasoaUserInterface::handle_exposure() read dim = " << sal3.getInputDimension() << endl;
   cout << "SasoaUserInterface::handle_exposure() exposure = " << a << endl;

	cout << "SasoaUserInterface::handle_exposure() measurement time = " << sto - sta << endl;

} catch (const exception &e){
	cerr << "error r" << e.what() << endl;
} catch (...){
	cerr << "error r" << endl;
}
}


/*!
    \fn SApipeline::SasoaUserInterface::handle_largefile()
 */
void SApipeline::SasoaUserInterface::handle_largefile()
{
   cout << "SasoaUserInterface::handle_largefile() executing " << endl;
}



/*!
    \fn SApipeline::SasoaUserInterface::exec_gti(const string &gtifile)
 */
void SApipeline::SasoaUserInterface::exec_gti(const string &l3file, const string &gtifile)
{

  string ifn;
  bool interactive = false;

    ifn =  l3file;
 
  try{
  if (verbose) cout << "SasoaUserInterface::handle_gti() testing L3 eventlist processing and GTI filtering" << endl;
    string  fitsfilename(ifn);
    cout << "SasoaUserInterface::handle_gti() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;     	sal3.init();
  	sal3.SAEventlist::setArchiveHandler(&pipeline->sarchiver);	
	sal3.SAEventlist::setSaveFiltered(false); 
	sal3.SAEventlist::setSaveFiltered(true);

    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  string fn(fitsfilename);
    if (verbose) cout << "SasoaUserInterface::handle_l3test() read dim = " << sal3.getInputDimension() << endl;

try{
    sal3.readDebug(fn);
} catch (const SAexception &se){
	cerr << "handle_gti() error in reading the l3 evlist" << se.getMsg() << endl;
} catch (const exception &e){
	cerr <<  "handle_gti() error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "handle_gti()error in reading the l3 evlist" << endl;
}

// asking for the GTI file

// processing GTI filtering

	sal3.filterAllGTI(gtifile);
} catch (const exception &e){
	cerr << "error in processing the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in processing  the l3 evlist" << endl;
}

}


/*!
    \fn SApipeline::SasoaUserInterface::burst()
 */
void SApipeline::SasoaUserInterface::burst()
{
   cout << "SasoaUserInterface::burst executing " << endl;
	try{
   string ifn; double tmi , tma; tmi = 0; tma = 0;

    cout << "insert input file name"<< endl;
    cin >> ifn;
    cout << "insert burst Time start "<< endl;
    cin >> tmi;
    cout << "insert input file name"<< endl;
    cin >> tma;

	try {
		exec_burst(ifn, tmi, tma);
	} catch(const exception &e){
		cerr << "error in filtering the data for burst time interval "<< endl;
	}

	} catch (const exception &e){
		cerr << "error in input data insertion "<< e.what()<< endl;
	}
}

/*!
    \fn SApipeline::SasoaUserInterface::exec_burst(const string &fnam, double tmin, double tmax)
 */
void SApipeline::SasoaUserInterface::exec_burst(const string &fnam, double tmin, double tmax)
{
  try{
  if (verbose) cout << "SasoaUserInterface::exec_burst() testing L3 eventlist processing and burst interval time filtering" << endl;
    string  fitsfilename(fnam);
    if (verbose) cout << "SasoaUserInterface::exec_burst() going to read file = "<< fitsfilename << endl;
    SAL3Eventlist sal3;     	sal3.init();
  	sal3.SAEventlist::setArchiveHandler(&pipeline->sarchiver);	
	sal3.SAEventlist::setSaveFiltered(true);
    sal3.setInputFilename(fitsfilename);
    string hdn("EVENTS");  
    if (verbose) cout << "SasoaUserInterface::exec_burst() read dim = " << sal3.getInputDimension() << endl;
try{
    sal3.readDebug(fitsfilename);
} catch (const SAexception &se){
	cerr << "exec_burst() error in reading the l3 evlist" << se.getMsg() << endl;
} catch (const exception &e){
	cerr <<  "exec_burst() error in reading the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "exec_burst()error in reading the l3 evlist" << endl;
}

// asking for the GTI file

// processing GTI filtering

	if (verbose) cout << "tstart = " << sal3.getTstart() << endl;
	if (verbose) cout << "tstop = " << sal3.getTstop() << endl;

	sal3.filterTime(tmin, tmax);
	SADateTime tmm, TMM;
	tmm.show();	TMM.show();

	string f("time_filtered.evt");
	sal3.saveFiltered(f);
} catch (const exception &e){
	cerr << "error in processing the l3 evlist" << e.what() << endl;
} catch (...){
	cerr << "error in processing  the l3 evlist" << endl;
}

}
void SApipeline::SasoaUserInterface::handle_TDS(){
try{
	TDSDaemon tds;
	tds.start(0., 6.);
} catch (const SAexception &se){
	cerr << "SasoaUserInterface::handle_TDS() error in TDS processing" << se.getMsg() << endl;
} catch (const exception &e){
	cerr << "SasoaUserInterface::handle_TDS() error in TDS processing" << e.what() << endl;
} catch (...){
	cerr << "SasoaUserInterface::handle_TDS() error in TDS processing" << endl;
}
}