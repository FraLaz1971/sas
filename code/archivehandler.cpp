/***************************************************************************
                          archivehandler.cpp  -  description
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

#include "archivehandler.h"
namespace SAarchive{
ArchiveHandler::ArchiveHandler(){
  setDefault();
  setDataDirs();
  setVerbose(false);
 ExposureGTI_filename = "../stg_2/EXP_DELIVERY/EARTH_OCCULTATION.gti";
 SagaGTI_filename = "../stg_2/sagagti/SAGA.gti";
}
ArchiveHandler::ArchiveHandler(ArchiveHandler &a)  {
  setVerbose(false);
  setArchiveRoot(a.getArchiveRoot());
  setSasoaHome(a.getSasoaHome());
  setSasoaWorkDir(a.getSasoaWorkDir());
  setArchiveDir(a.getArchiveDir());
  ArchiveHandler();
 ExposureGTI_filename = "../stg_2/EXP_DELIVERY/EARTH_OCCULTATION.gti";
 SagaGTI_filename = "../stg_2/sagagti/SAGA.gti";
}
ArchiveHandler::~ArchiveHandler(){
}
}/** gives a list of filenames for the input runid */
//vector<string> files SAarchive::ArchiveHandler::getFilenames(int runid){}


/*!
    \fn SAarchive::ArchiveHandler::clear_L2_Data()
 */
void SAarchive::ArchiveHandler::clear_L2_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L2/*_L2.evt";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L2_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::clear_L3_data()
 */
void SAarchive::ArchiveHandler::clear_L3_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L3/*_L3.evt";
  tempstring = "rm -f "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L3_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/data/L3/*.dat";
  tempstring = "rm -f "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L3_Data() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = " *_bti.fits";
  tempstring = "rm -f "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L3_Data() executing  " << tempstring << endl;
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::clear_L19_Data()
 */
void SAarchive::ArchiveHandler::clear_L19_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L19/*_L19.evt";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L19_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::clear_SAL1Cor_Data()
 */
void SAarchive::ArchiveHandler::clear_SAL1Cor_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L1/*_L1.cor";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L1Cor_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::clear_SAL1Orb_Data()
 */
void SAarchive::ArchiveHandler::clear_SAL1Orb_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L1/*_L1.orb";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_SAL1Orb_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::getSasoaHome()
 */
string SAarchive::ArchiveHandler::getSasoaHome()
{
  return SASOA_HOME;
}


/*!
    \fn SAarchive::ArchiveHandler::setSasoaHome(const string &sh)
 */
void SAarchive::ArchiveHandler::setSasoaHome(const string &sh)
{
  SASOA_HOME = sh;
  if (verbose) cout << "ArchiveHandler::setSasoaHome() " << getSasoaHome() << endl;
}
void SAarchive::ArchiveHandler::setSagaGTI_filename(const string &sh)
{
  SagaGTI_filename = sh;
  if (verbose) cout << "ArchiveHandler::setSagaGTI_filename " << getSasoaHome() << endl;
}
void SAarchive::ArchiveHandler::setExposureGTI_filename(const string &sh)
{
  ExposureGTI_filename = sh;
  if (verbose) cout << "ArchiveHandler::exposureGTI_filename() " << getSasoaHome() << endl;
}

/*!
    \fn SAarchive::ArchiveHandler::setSasoaWorkDir(const string &swd)
 */
void SAarchive::ArchiveHandler::setSasoaWorkDir(const string &swd)
{
  SASOA_WORK_DIR = swd;
  if (verbose) cout << "ArchiveHandler::setSasoaWorkDir() " << getSasoaWorkDir() << endl;
}


/*!
    \fn SAarchive::ArchiveHandler::getSasoaWorkDir()
 */
string SAarchive::ArchiveHandler::getSasoaWorkDir()
{
  //if (verbose) cout << " ArchiveHandler::getSasoaWorkDir() : " << SASOA_WORK_DIR << endl;
  try{
    tempstring = SASOA_WORK_DIR;
  } catch (const exception &e){
    cerr << "error exception "<< e.what() << endl;
  }
  return tempstring;
}


/*!
    \fn SAarchive::ArchiveHandler::clearDeliverableData()
 */
void SAarchive::ArchiveHandler::clearDeliverableData()
{
  tempstring = getSasoaWorkDir()+"/delivery/*";
  tempstring = "rm -rf "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::DeliverableData() executing  " << tempstring << endl; 
  system(tempstring.c_str());
/*  tempstring = getSasoaWorkDir()+"/delivery/*.csl";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::DeliverableData() executing  " << tempstring << endl; 
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/delivery/*.sfl";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::DeliverableData() executing  " << tempstring << endl; 
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/delivery/*.si";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::DeliverableData() executing  " << tempstring << endl; 
  system(tempstring.c_str());
  */
}


/*!
    \fn SAarchive::ArchiveHandler::copyDeliverableData(const string &dirname)
 */
void SAarchive::ArchiveHandler::copyDeliverableData(const string &dirname)
{
  cout << "ArchiveHandler::copyDeliverableData() executing" << endl;
  tempstring = "cp -r "+getDeliveryDir()+"/* "+dirname;
  cout << "ArchiveHandler::copyDeliverableData() executing" << tempstring << endl;
  system(tempstring.c_str());
  tempstring = "cp ../SATemporalDataSet/eph_testout.fits "+dirname;
  cout << "ArchiveHandler::copyDeliverableData() executing" << tempstring << endl;
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::moveDeliverableData(const string &dirname)
 */
void SAarchive::ArchiveHandler::moveDeliverableData(const string &dirname)
{
  copyDeliverableData(dirname);
  clearDeliverableData();
}


/*!
    \fn SAarchive::ArchiveHandler::showEnv()
 */
void SAarchive::ArchiveHandler::showEnv()
{
  cout << "ArchiveHandler::showEnv()"<< endl;
  cout << "#############################################################################"<< endl;
  cout << "# SASOA_HOME = "<< getSasoaHome() << endl; 
  cout << "# SASOA_WORK_ENV = "<< getSasoaWorkDir() << endl;
  cout << "# SAL1 cor dir = "<< get_SAL1Cor_Dir() << endl;
  cout << "# SAL1 orb dir = " << get_SAL1Orb_Dir() << endl;
  cout << "# L1.9 Dir = " << get_L19_Dir() << endl;
  cout << "# L2 Dir =  "<< get_L2_Dir() << endl;
  cout << "# L3 Dir = "<< get_L3_Dir() << endl;
  cout << "#############################################################################"<< endl;
}


/*!
    \fn SAarchive::ArchiveHandler::getDeliveryDir()
 */
string SAarchive::ArchiveHandler::getDeliveryDir()
{
  return DELIVERY_DIR;
}


/*!
    \fn SAarchive::ArchiveHandler::setDeliveryDir(const string &dd)
 */
void SAarchive::ArchiveHandler::setDeliveryDir(const string &dd)
{
  DELIVERY_DIR = dd;
}


/*!
    \fn SAarchive::ArchiveHandler::setDefault()
 */
void SAarchive::ArchiveHandler::setDefault()
{
	/* add a configuration file reading ...*/
    arc_dir_len = 6;
	ATTITUDE_DIR = "../stg_2/attitude/version_for_sasoa";
	EXPOSURE_DIR = "../stg_2/EXP_DELIVERY"; 
	SAGA_DIR = "../stg_2/sagagti";
}


/*!
    \fn SAarchive::ArchiveHandler::createCurrentArchiveDir()
 */
void SAarchive::ArchiveHandler::createCurrentArchiveDir()
{
   string temp = "mkdir "+getArchiveDir();
   if (verbose) cout << "ArchiveHandler::createCurrentArchiveDir() executing  "<< temp << endl;
   system(temp.c_str());
}
/*!
    \fn SAarchive::ArchiveHandler::createTDSArchiveDir()
 */
void SAarchive::ArchiveHandler::createTDSArchiveDir(double tstart, double tstop)
{
   string temp = "mkdir "+getTDSArchiveDir(tstart, tstop);
   if (verbose) cout << "ArchiveHandler::createCurrentArchiveDir() executing  "<< temp << endl;
   system(temp.c_str());
}

void SAarchive::ArchiveHandler::createTDSSourceArchiveDir(double tstart, double tstop, double src_ra, double src_dec)
{
/*
   string temp = "mkdir "+getTDSArchiveDir(tstart, tstop);
   if (verbose) cout << "ArchiveHandler::createCurrentArchiveDir() executing  "<< temp << endl;
   system(temp.c_str());
*/
}
/*!
    \fn SAarchive::ArchiveHandler::setArchiveRoot(const string &ar)
 */
void SAarchive::ArchiveHandler::setArchiveRoot(const string &ar)
{
  ARCHIVE_ROOT = ar;
}


/*!
    \fn SAarchive::ArchiveHandler::getArchiveRoot()
 */
string SAarchive::ArchiveHandler::getArchiveRoot()
{
  return ARCHIVE_ROOT;
}


/*!
    \fn SAarchive::ArchiveHandler::setArchiveDir(const string & ad)
 */
void SAarchive::ArchiveHandler::setArchiveDir(const string & ad)
{
  ARCHIVE_DIR = ad;
}


/*!
    \fn SAarchive::ArchiveHandler::getArchiveDir()
 */
string  SAarchive::ArchiveHandler::getArchiveDir()
{
  return ARCHIVE_DIR;
}
/*!
    \fn SAarchive::ArchiveHandler::getTDSArchiveDir(double tstart, double tstop)
 */
string  SAarchive::ArchiveHandler::getTDSArchiveDir(double tstart, double tstop)
{

  SADateTime sc;  
  string temp1, temp2, temp3, temp4, temp5;
  string longstartdoy, longstopdoy; string zero("0");
  sc.setAGILETime(tstart);
  ss.str(""); ss << sc.getDoy(); longstartdoy = ss.str();
  int s = int(longstartdoy.size());int c = 0; 
  while (s<3){
    longstartdoy.insert(c, zero);
    s++; c++;
  }
  ss.str(""); ss << longstartdoy;   temp1 = ss.str();
  ss.str(""); ss << sc.getYear();   temp4 = ss.str();
  temp2 = getArchiveDir();
  sc.setAGILETime(tstop);
  ss.str(""); ss << sc.getDoy(); longstopdoy = ss.str();
  s = int(longstopdoy.size()); c = 0;
  while (s<3){
    longstopdoy.insert(c, zero);
    s++; c++;
  }
  ss.str(""); ss << longstopdoy;   temp3 = ss.str();
  ss.str(""); ss << sc.getYear();   temp5 = ss.str();
  ss.str("");ss<<temp2<<"_"<< temp1<<"_"<< temp4<<"_"<<temp3<<"_"<< temp5;
  if (verbose) cout << "ArchiveHandler::getTDSArchiveDir() created string" << ss.str() << endl;
  setArchiveDir(ss.str());
  return ARCHIVE_DIR;
}
/*!
    \fn SAarchive::ArchiveHandler::getTDSArchiveDir(double tstart, double tstop)
 */
string  SAarchive::ArchiveHandler::getTDSSourceArchiveDir(double tstart, double tstop, double src_ra, double src_dec)
{

  SADateTime sc;  
  string temp1, temp2, temp3, temp4, temp5;
  string longstartdoy, longstopdoy; string zero("0");
  sc.setAGILETime(tstart);
  ss.str(""); ss << sc.getDoy(); longstartdoy = ss.str();
  int s = int(longstartdoy.size());int c = 0; 
  while (s<3){
    longstartdoy.insert(c, zero);
    s++; c++;
  }
  ss.str(""); ss << longstartdoy;   temp1 = ss.str();
  ss.str(""); ss << sc.getYear();   temp4 = ss.str();
  temp2 = getArchiveDir();
  sc.setAGILETime(tstop);
  ss.str(""); ss << sc.getDoy(); longstopdoy = ss.str();
  s = int(longstopdoy.size()); c = 0;
  while (s<3){
    longstopdoy.insert(c, zero);
    s++; c++;
  }
  ss.str(""); ss << longstopdoy;   temp3 = ss.str();
  ss.str(""); ss << sc.getYear();   temp5 = ss.str();
  ss.str("");ss<<temp2<<"_"<< temp1<<"_"<< temp4<<"_"<<temp3<<"_"<< temp5;
  if (verbose) cout << "ArchiveHandler::getTDSSourceArchiveDir() created string" << ss.str() << endl;
  setArchiveDir(ss.str());
  return ARCHIVE_DIR;
}
/*!
    \fn SAarchive::ArchiveHandler::retrieveArchiveDir()
    retrive directory containing output for orbital analysis
 */
void SAarchive::ArchiveHandler::retrieveArchiveDir(const string &ad)
{
  ARCHIVE_DIR = getArchiveRoot()+"/"+ad;
}


/*!
    \fn SAarchive::ArchiveHandler::moveFile(const string &infile, const string &outdir)
 */
void SAarchive::ArchiveHandler::moveFile(const string &infile, const string &outdir)
{
  tempstring = "mv "+infile+" "+outdir;
  if (verbose) cout << "ArchiveHandler::moveFile() executing " << tempstring.c_str() << endl;
  system(tempstring.c_str());
}
/** No descriptions */

/** gives back in output a formatted string taking in input an in t (as example an orbit, contact or string number) */
string SAarchive::ArchiveHandler::getFormattedStringNumber(int n){
  ss.str(""); ss << n;
  tempstring = ss.str();
  
  // determine the total length of the string
  int rest = arc_dir_len - tempstring.size();
  // determine how many char to add
  if (rest > 0) {
  // add them
    tempstring.insert(0, rest, '0');
  }
  //string& insert( size_type index, size_type num, char ch );
  
  if (verbose) cout << "ArchiveHandler::getFormattedStringNumber() returning "<< tempstring << endl;
  return tempstring;
}

string SAarchive::ArchiveHandler::getFormattedStringNumber(int n, int dir_len){
  ss.str(""); ss << n;
  tempstring = ss.str();
  
  // determine the total length of the string
  int rest = dir_len - tempstring.size();
  // determine how many char to add
  if (rest > 0) {
  // add them
    tempstring.insert(0, rest, '0');
  }
  //string& insert( size_type index, size_type num, char ch );
  
  if (verbose) cout << "ArchiveHandler::getFormattedStringNumber() returning "<< tempstring << endl;
  return tempstring;
}


/** retrieve the used data directories defaults, saved in the text file updated recently */
void SAarchive::ArchiveHandler::retrieveDataDirs(){
}
/** save on a text file the data directories used at the moment in the processing */
void SAarchive::ArchiveHandler::saveDataDirs(){
}

void SAarchive::ArchiveHandler::set_SAL1Cor_Dir(const string &l1corn){
            SAL1Cor_Dir =  l1corn;
}

void SAarchive::ArchiveHandler::set_SAL1Orb_Dir(const string &l1orbn){
            SAL1Orb_Dir =  l1orbn;
}

void SAarchive::ArchiveHandler::set_L19_Dir(const string &l19n){
         L19_Dir =  l19n;
}

void SAarchive::ArchiveHandler::set_Contacts_Dir(const string &cd){
  CONTACTS_DIR =  cd;
}

void SAarchive::ArchiveHandler::set_L2_Dir(const string &l2n){
        L2_Dir =  l2n;
}
    
void SAarchive::ArchiveHandler::set_L3_Dir(const string &l3n){
        L3_Dir =  l3n;
}
    
void SAarchive::ArchiveHandler::set_L1_Dir(const string &l1n){
        L1_Dir =  l1n;
}

string SAarchive::ArchiveHandler::get_L1_Dir(){
       return L1_Dir;
}
string SAarchive::ArchiveHandler::get_SAL1Cor_Dir(){
       return SAL1Cor_Dir;
}
string SAarchive::ArchiveHandler::get_SAL1Orb_Dir(){
       return SAL1Orb_Dir;
}
string SAarchive::ArchiveHandler::get_L19_Dir(){
       return L19_Dir;
}
string SAarchive::ArchiveHandler::get_L2_Dir(){
       return L2_Dir;
}
string SAarchive::ArchiveHandler::get_L3_Dir(){
       return L3_Dir;
}
string SAarchive::ArchiveHandler::get_Contacts_Dir(){
  return CONTACTS_DIR;
}

string SAarchive::ArchiveHandler::get_Att_Filename(int contactnum){
//	string instr(". ../SATemporalDataSet/centstring.sh; centstring 3124 VAR; echo $VAR"); string CENTSTRING;
	vector<string> mvs; 
	//mvs = syscon.dumpCommand(instr); CENTSTRING = mvs[0];
	mvs.clear();
	string myAtt_filename;
	//ss << ". ../SATemporalDataSet/centstring.sh; centstring" << contactnum << "CENTSTRING;echo $HOME/SASOA/SA/input/$CENTSTRING/00" << contactnum;
//	ss.str(""); ss << "ls /home/agile/SASOA/SA/products/processed/PKP"<<contactnum<<"_0_3905_000_L1/*L2.evt";  
	ss.str(""); ss << ". ../SATemporalDataSet/centstring.sh; centstring " << contactnum << " CENTSTRING; gzip -d $HOME/SASOA/SA/input/$CENTSTRING/0" << contactnum<<"/*3914*.gz";  
	if (verbose) cout << "ArchiveHandler::get_Att_Filename() executing " << ss.str() << endl;
	string mc = ss.str();
	syscon.execCommand(mc);
	ss.str(""); ss << ". ../SATemporalDataSet/centstring.sh; centstring " << contactnum << " CENTSTRING; ls $HOME/SASOA/SA/input/$CENTSTRING/0" << contactnum<<"/*3914*.lv1";  
	if (verbose) cout << "ArchiveHandler::get_Att_Filename() retrieved " << ss.str();
	mc = ss.str();mvs = syscon.dumpCommand(mc);
	vector<string>::iterator it = mvs.begin(); 
	while (it < mvs.end()){
	 if (verbose) cout << "value " << *it << endl;
	 myAtt_filename = *it++;
	}
       return myAtt_filename;
}

string SAarchive::ArchiveHandler::get_L2_Filename(int contactnum){
	string myL2_filename("");
	ss.str(""); ss << "ls /home/agile/SASOA/SA/products/processed/PKP"<<contactnum<<"_0_3905_000_L1/*L2.evt";  
	string mc = ss.str();
	vector<string> mvs = syscon.dumpCommand(mc);
	vector<string>::iterator it = mvs.begin(); 
	while (it < mvs.end()){
	 if (verbose) cout << "value " << *it << endl;
	 myL2_filename = *it++;
	}
       return myL2_filename;
}
/** No descriptions */
void SAarchive::ArchiveHandler::setDataDirs(){
    tempstring = getSasoaWorkDir()+"/data/L1";
    set_SAL1Cor_Dir(tempstring);
    tempstring = getSasoaWorkDir()+"/data/L1";
    set_SAL1Orb_Dir(tempstring);
    tempstring = getSasoaWorkDir()+"/data/L19";
    set_L19_Dir(tempstring);
    tempstring = getSasoaWorkDir()+"/data/L2";
    set_L2_Dir(tempstring);
    tempstring = getSasoaWorkDir()+"/data/L3";
    set_L3_Dir(tempstring);
    tempstring = getSasoaWorkDir()+"/data/L1";
    set_L1_Dir(tempstring);
}


/** find the L1 cor files needed by the Orbit Rebuilder stage */
void SAarchive::ArchiveHandler::findL1Cor(const string &cnts){
  // create the queue of L1 Cor files to be processed by the Orbit Rebuilder
}
/** No descriptions */
string SAarchive::ArchiveHandler::getCurrentL1CorFileName(){
  return  SAL1Cor_filename;
}
/** No descriptions */
string SAarchive::ArchiveHandler::getSAL1Orb_FileName(){
  return SAL1Orb_filename;
}
/** No descriptions */
void SAarchive::ArchiveHandler::retrieveAllFileNames(){
  SAL1Orb_filename = filenamer.getFileName(OrbitRebuilding);
}


/*!
    \fn SAarchive::ArchiveHandler::getDefaultOutputDir()
 */
string SAarchive::ArchiveHandler::getDefaultOutputDir()
{
  tempstring = getSasoaWorkDir();
  return tempstring;
}


/*!
    \fn SAarchive::ArchiveHandler::getDefaultOutputDir(SATask st)
 */
string SAarchive::ArchiveHandler::getDefaultOutputDir(SATask st)
{
  switch(st){
    case Preprocessing:
      tempstring = ".";      
    break;
    case Correction:
      tempstring = get_SAL1Cor_Dir();
    break;
    case OrbitRebuilding:
      tempstring = get_SAL1Orb_Dir();
    break;
    case DataReducing:
      tempstring = get_L19_Dir();
    break;
    case PhotonListBuilding:
      tempstring = get_L2_Dir();
    break;
    case SourcesExtraction:
      tempstring = get_L3_Dir();
    break;
    case SourceAnalysis:
      tempstring = get_L19_Dir();
    break;
    case IrosMapBuilding:
      tempstring = ".";
    break;    
    default:
      tempstring = ".";
    break;  
  }
  return tempstring;
}

/*!
    \fn SAarchive::ArchiveHandler::clearDefaultData()
 */
void SAarchive::ArchiveHandler::clearDefaultData()
{
  try{
   clear_SAL1Cor_Data();
   clear_SAL1Orb_Data();
   clear_OLD_L1_Data();
   clear_L1_Data();
   clear_L19_Data();
   clear_L2_Data();
   clear_L3_Data();
   clearProducts();
   clearIROS();   
   clearDeliverableData();
  } catch (const exception &e) {
    cerr << "ArchiveHandler::clearDefaultData() thrown exception " << e.what() << endl;
  }  
}


/*!
    \fn SAarchive::ArchiveHandler::rmTempOutputFiles()
 */
void SAarchive::ArchiveHandler::rmTempOutputFiles()
{
  clearDefaultData();
}
void SAarchive::ArchiveHandler::rmTempInputFiles()
{
  //to do 
}
void SAarchive::ArchiveHandler::rmTempFiles()
{
  rmTempInputFiles();
  rmTempOutputFiles();
}
/** No descriptions */
void SAarchive::ArchiveHandler::clearIROS(){
  tempstring = getSasoaHome()+"/stg_2/*.dat";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clearIROS() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaHome()+"/stg_2/*MD_IROS_Statistics*.*";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clearIROS() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaHome()+"/stg_2/*.ascii";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clearIROS() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaHome()+"/stg_2/*.ps";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clearIROS() executing  " << tempstring << endl;
  system(tempstring.c_str());
}
/** No descriptions */
void SAarchive::ArchiveHandler::clear_OLD_L1_Data(){
  tempstring = getSasoaWorkDir()+"/data/L1/*_L1.lv1";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_OLD_L1_Data() executing  " << tempstring << endl;
  system(tempstring.c_str());
 tempstring = getSasoaWorkDir()+"/data/L1/*.lv1";
  tempstring = "rm "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_OLD_L1_Data() executing  " << tempstring << endl;
  system(tempstring.c_str());

}
void SAarchive::ArchiveHandler::clearProducts(){
  tempstring2 = " "+getSasoaWorkDir()+"/products/processed";
  tempstring = getSasoaWorkDir()+"/products/*.*";
  tempstring = "mv "+tempstring;
  tempstring = tempstring + tempstring2;
  if (verbose) cout << "ArchiveHandler::clearProducts() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/products/*cal";
  tempstring = "mv "+tempstring;
  tempstring = tempstring + tempstring2;
  if (verbose) cout << "ArchiveHandler::clearProducts() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/products/sr*";
  tempstring = "mv "+tempstring;
  tempstring = tempstring + tempstring2;
  if (verbose) cout << "ArchiveHandler::clearProducts() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/products/PKP*";
  tempstring = "mv "+tempstring;
  tempstring = tempstring + tempstring2;
  if (verbose) cout << "ArchiveHandler::clearProducts() executing  " << tempstring << endl;
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/products/SA*";
  tempstring = "mv "+tempstring;
  tempstring = tempstring + tempstring2;
  if (verbose) cout << "ArchiveHandler::clearProducts() executing  " << tempstring << endl;
  system(tempstring.c_str());  
  
}


/*!
    \fn SAarchive::ArchiveHandler::getAttitudeDir()
 */
string SAarchive::ArchiveHandler::getAttitudeDir()
{
    return ATTITUDE_DIR;
}


/*!
    \fn SAarchive::ArchiveHandler::getExposureDir()
 */
string SAarchive::ArchiveHandler::getExposureDir()
{
    return EXPOSURE_DIR;
}


/*!
    \fn SAarchive::ArchiveHandler::getSagaDir()
 */
string SAarchive::ArchiveHandler::getSagaDir()
{
    return SAGA_DIR;
}


/*!
    \fn SAarchive::ArchiveHandler::loadOrbit(int orbnum)
 */
void SAarchive::ArchiveHandler::loadOrbit(int orbnum)
{
  loadContact(orbnum);
}

/*!
    \fn SAarchive::ArchiveHandler::loadContact(int contnum)
 */
void SAarchive::ArchiveHandler::loadContact(int contnum)
{
  if (verbose) cout << "ArchiveHandler::loadContact() loading contact data"<< endl;
  
  if (verbose) cout << "ArchiveHandler::loadContact() contact archive root: "<< CONTACTS_DIR << endl;
  cout << "ArchiveHandler::loadContact() loading contact n. : "<< contnum << endl;  
  // 
  ss.str(""); ss << get_Contacts_Dir(); ss << "/"; ss << getFormattedStringNumber(contnum); 
  //
  //
}


/*!
    \fn SAarchive::ArchiveHandler::setDefaultContactsDir()
 */
void SAarchive::ArchiveHandler::setDefaultContactsDir(const string &cd)
{
  ofstream noutfile;
  string fn;
  noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
  try {
    fn = "def/contacts_dir.txt";
    noutfile.open (fn.c_str(), ofstream::out);
    noutfile << cd << endl;
    noutfile.close();
  } // close try
  catch (ofstream::failure e) {
    if (verbose) cout << "Exception opening/writing file"<< endl;
  }
  if (verbose) cout << "Finished execution of SApipeline::PipelineModule::saveDefaultPar()" << endl;
}


/*!
    \fn SAarchive::ArchiveHandler::getDefaultContactsDir()
 */
string SAarchive::ArchiveHandler::getDefaultContactsDir()
{
  char buf[256]; // read lines of maximun 256 characters
  int mlinelen = 256;
  ifstream ninfile;
  stringstream ss;
  string fn;
  ninfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
  try {
    fn = "def/contacts_dir.txt";
    ninfile.open (fn.c_str(), ofstream::in);
    ninfile.getline(buf, mlinelen) ;
    ss << buf;
    if (verbose) cout << "getDefaultContactsDir default contacts dir retrieved is " << ss.str() << endl;
    ninfile.close();
  } // close try
  catch (ofstream::failure e) {
    cerr << "PipelineModule::retrieveDefaultDetNam() Exception opening/writing file"<< endl;
  }
  return ss.str();
}


/*!
    \fn SAarchive::ArchiveHandler::getLoaded3905FileName()
 */
string SAarchive::ArchiveHandler::getLoaded3905FileName()
{
  try{
    if (verbose) cout << "ArchiveHandler::getLoaded3905FileName() execution "  << endl;
    if (verbose) cout << "SasoaUserInterface::handle_allpipe() ended "<< endl;
    tempstring = "ls "+get_L1_Dir()+"/*3905*.lv1";
    resfiles = syscon.dumpCommand(tempstring);
    if (verbose) cout << "ArchiveHandler::getLoaded3905FileName() n. of retrieved files = " << resfiles.size() << endl;
    if (resfiles.size() == 0){
      tempstring2="error: retrieved no 3905 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    if (resfiles.size() > 1){
      tempstring2="error: retrieved more than 1 3905 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    // create infile value string
  } catch(exception &e){
    cerr << "ArchiveHandler::getLoaded3905FileName() error in setting default contacts dir" << endl;
      cerr << e.what() << endl;
  }   catch(...){
    cerr << "ArchiveHandler::getLoaded3905FileName() error!" << endl;
  }
  if (verbose)  cout << "ArchiveHandler::getLoaded3905FileName() tempstring " << tempstring << endl;
  if (verbose) cout << "ArchiveHandler::getLoaded3905FileName() returning " << tempstring << endl;
  return filenamer.getRelativeFileName(resfiles[0]);
}

string SAarchive::ArchiveHandler::getLoadedCor3905FileName()
{
  try{
    if (verbose) cout << "ArchiveHandler::getLoadedCor3905FileName() execution "  << endl;
    if (verbose) cout << "SasoaUserInterface::handle_allpipe() ended "<< endl;
    tempstring = "ls "+get_L1_Dir()+"/*3905*_L1.cor";
    resfiles = syscon.dumpCommand(tempstring);
    if (verbose) cout << "ArchiveHandler::getLoadedCor3905FileName() n. of retrieved files = " << resfiles.size() << endl;
    if (resfiles.size() == 0){
      tempstring2="error: retrieved no Cor3905 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    if (resfiles.size() > 1){
      tempstring2="error: retrieved more than 1 Cor3905 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    // create infile value string
  } catch(exception &e){
    cerr << "ArchiveHandler::getLoadedCor3905FileName() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  }   catch(...){
    cerr << "ArchiveHandler::getLoadedCor3905FileName() error!" << endl;
  }
  if (verbose) cout << "ArchiveHandler::getLoadedCor3905FileName() tempstring " << tempstring << endl;
  if (verbose) cout << "ArchiveHandler::getLoadedCor3905FileName() returning " << tempstring << endl;
  return filenamer.getRelativeFileName(resfiles[0]);
}

string  SAarchive::ArchiveHandler::getLoaded3914FileName()
{
  try{
    if (verbose) cout << "ArchiveHandler::getLoaded3914FileName() execution "  << endl;
    tempstring = "ls "+get_L1_Dir()+"/*3914*.lv1";
    resfiles = syscon.dumpCommand(tempstring);
    if (verbose) cout << "ArchiveHandler::getLoaded3905FileName() n. of retrieved files = " << resfiles.size() << endl;
    if (resfiles.size() == 0){
      tempstring2="error: retrieved no 3914 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    if (resfiles.size() > 1){
      tempstring2="error: retrieved more than 1 3914 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    // create infile value string
  } catch(exception &e){
    cerr << "ArchiveHandler::getLoaded3914FileName() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  }   catch(...){
    cerr << "ArchiveHandler::getLoaded3914FileName() error!" << endl;
  }
  return filenamer.getRelativeFileName(resfiles[0]);
}
string  SAarchive::ArchiveHandler::getLoaded3916FileName()
{
  try{
    if (verbose) cout << "ArchiveHandler::getLoaded3916FileName() execution "  << endl;
    tempstring = "ls "+get_L1_Dir()+"/*3916*.lv1";
    resfiles = syscon.dumpCommand(tempstring);
    if (verbose) cout << "ArchiveHandler::getLoaded3916FileName() n. of retrieved files = " << resfiles.size() << endl;
    if (resfiles.size() == 0){
      tempstring2="error: retrieved no 3916 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    if (resfiles.size() > 1){
      tempstring2="error: retrieved more than 1 3916 L1 file name to return";
      se.setMsg(tempstring2);
      throw(se);
    }
    // create infile value string
  } catch(exception &e){
    cerr << "ArchiveHandler::getLoaded3916FileName() error in setting default contacts dir" << endl;
    cerr << e.what() << endl;
  }   catch(...){
    cerr << "ArchiveHandler::getLoaded3916FileName() error!" << endl;
  }
  return filenamer.getRelativeFileName(resfiles[0]);
}


/*!
    \fn SAarchive::ArchiveHandler::getCurrentContactNumber()
 */
int SAarchive::ArchiveHandler::getCurrentContactNumber()
{
    tempstring = filenamer.getContact();
	return atoi(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::getCurrentSagaGTI_FileName()
 */
string SAarchive::ArchiveHandler::getCurrentSagaGTI_FileName()
{
    return SagaGTI_filename;
}


/*!
    \fn SAarchive::ArchiveHandler::getCurrentExposureGTI_FileName()
 */
string SAarchive::ArchiveHandler::getCurrentExposureGTI_FileName()
{
    return ExposureGTI_filename;
}

string SAarchive::ArchiveHandler::getIrosMapFileName()
{
    return Irosmap_filename;
}
void SAarchive::ArchiveHandler::setIrosMapFileName(const string &imfn)
{
    Irosmap_filename = imfn;
}

/*!
    \fn SAarchive::ArchiveHandler::clear_L1_Data()
 */
void SAarchive::ArchiveHandler::clear_L1_Data()
{
  tempstring = getSasoaWorkDir()+"/data/L1/*";
  tempstring = "rm -rf  "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L1_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
  tempstring = getSasoaWorkDir()+"/delivery/*.*";
  tempstring = "rm -rf  "+tempstring;
  tempstring = tempstring + "";
  if (verbose) cout << "ArchiveHandler::clear_L1_Data() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}


/*!
    \fn SAarchive::ArchiveHandler::clearTempData()
 */
void SAarchive::ArchiveHandler::clearTempData()
{
	clearDefaultData();
}


/*!
    \fn SAarchive::ArchiveHandler::getHundredContactsDir(int contactnum)
 */
string SAarchive::ArchiveHandler::getHundredContactsDir(int contactnum)
{
   tempstring = getFormattedStringNumber(contactnum); 
   tempstring2 = "XX";
   tempstring.replace(4, tempstring2.length(), tempstring2);
   if (verbose) cout << "ArchiveHandler::getHundredContactsDir() returning " << tempstring << endl;
   return tempstring; 
}


/*!
    \fn SAarchive::ArchiveHandler::loadContactSSH(const string &thishost, const string &remotehost, int contactnum)

	the local host is given in input as
	user@complete.local.host.name 

	the remote host is given in input as
	user@complete.remote.host.name 

 */
void SAarchive::ArchiveHandler::loadContactSSH(const string &thishost, const string &remotehost, int contactnum)
{
  	if (verbose) cout << "executing ArchiveHandler::loadContactSSH() loading CONTACT " << contactnum << endl;
    
	if (verbose) cout << "ArchiveHandler::loadContactSSH() I will download from remote host " << thishost << endl;

	if (verbose) cout << "ArchiveHandler::loadContactSSH() to the local host " << remotehost << endl;

	if (verbose) cout << "ArchiveHandler::loadContactSSH() checking the authorization ... " <<  endl;

	// 1) control if the  local host is allowed to communicate with the remote host 

		// 1.1) control if there is the private key in the local host
		
		// retrieve the private key filename

		// retrieve username
		string pk = thishost.substr(thishost.find_first_of("@")+1, (thishost.find_first_of(".")-(thishost.find_first_of("@")+1)));

		if (verbose) cout << "ArchiveHandler::loadContactSSH() local hostname =  " << pk << endl;
		// tt contains the privatekey complete path name
		pk = getUserHome()+"/cron/"+pk+"-rsync-key";

		cout << "ArchiveHandler::loadContactSSH() private key filename =  " << pk << endl;

		string mc = "if [ ! -f " + pk + " ]; then echo WRONG; else echo OK; fi;";

		string temps; //  private key file control message string

		// read the output 
		if (verbose) cout << "ArchiveHandler::loadContactSSH() going to exec  " << mc << endl;
		vector<string> vecs;
		try{
		vecs = syscon.dumpCommand(mc);
		} catch(const exception &e){
			cerr << "ArchiveHandler::loadContactSSH() error"<< e.what()<< endl;
		} catch(...){
			cerr << "ArchiveHandler::loadContactSSH() error"<< endl;
		}

		string ts("OK");
			if (vecs.size()>0){
			cout << "vecs.size() = "<< vecs.size()<< endl;			
			cout << "vecs[0] = "<< vecs[0]<< endl;			
			}
/*		if (vecs[0]==ts) {
			cout << "localhost private key present going ahead "<< endl;			
		} else {
			temps = "localhost private key not present! (or non-standard private key name) ";
			cout << temps << endl;
			se.setMsg(temps);	throw(se);
		}
	*/	

		// compose the retrieving command

		// compose ssh authorization string = sss
		string sss = "\"ssh -i "+ pk +"\"";

		string recom = "rsync -avz -e "+sss+" "+remotehost+":"+getIASFContactInputDir(contactnum)+"*"+" "+getDefaultInputDir(contactnum);

		// launch the retrieving command
		if (verbose) cout << "ArchiveHandler::loadContactSSH() going to exec  " << recom << endl;

		syscon.execCommand(recom);

/*
"rsync -avz -e "ssh -i /home/lazzarotto/cron/agilehp6-rsync-key" agile@spirit.iasf-roma.inaf.it:/home/agile/SASOA/SA/input/0013XX/001323 /h
ome/lazzarotto/SASOA/SA/input/0013XX/"
*/

}


/*!
    \fn SAarchive::ArchiveHandler::getIASFContactInputDir(int contactnum)
		returns the complete path input directory name of the IASF archive, given the contact number
 */
string SAarchive::ArchiveHandler::getIASFContactInputDir(int contactnum)
{
    tempstring1 = getSasoaWorkDir() + "/input/"+getHundredContactsDir(contactnum)+"/"+getFormattedStringNumber(contactnum);
	return tempstring1;
}


/*!
    \fn SAarchive::ArchiveHandler::getUserHome()
 */
string SAarchive::ArchiveHandler::getUserHome()
{
	string h("HOME");tempstring3 = syscon.getEnvVar(h);
	return tempstring3;
}


/*!
    \fn SAarchive::ArchiveHandler::getDefaultInputDir(int contactnum)
 */
string SAarchive::ArchiveHandler::getDefaultInputDir(int contactnum)
{
     tempstring3 = getSasoaWorkDir() + "/input/"+getHundredContactsDir(contactnum);
	return tempstring3;
}


/*!
    \fn SAarchive::ArchiveHandler::getCurrentSOE_Name()
 */
string SAarchive::ArchiveHandler::getCurrentSOE_Name()
{
	tempstring = getSasoaHome()+"/stg_2/sagagti/sasoa_current.SOE";
    return tempstring; 
}


/*!
    \fn SAarchive::ArchiveHandler::setAttitudeDir(const string &attdir)
 */
void SAarchive::ArchiveHandler::setAttitudeDir(const string &attdir)
{
    attitude_dir = attdir;
}


/*!
    \fn SAarchive::ArchiveHandler::setEphemeridesDir(const string &ephdir)
 */
void SAarchive::ArchiveHandler::setEphemeridesDir(const string &ephdir)
{
    ephemerides_dir = ephdir;
}


/*!
    \fn SAarchive::ArchiveHandler::setEphemeridesDir(const string &ephdir)
 */
string SAarchive::ArchiveHandler::getEphemeridesDir()
{
    return ephemerides_dir;
}


/*!
    \fn SAarchive::ArchiveHandler::deliveryIrosProducts()
 */
void SAarchive::ArchiveHandler::deliveryIrosProducts(const string &prefix)
{

  string sh_varname; string sh_value;
  sh_varname = "SASOA_LIB"; 
  try{
   sh_value = syscon.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "ArchiveHandler::deliveryIrosProducts() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "ArchiveHandler::deliveryIrosProducts(): errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "ArchiveHandler::deliveryIrosProducts(): errror in getting SASOA_HOME env var" << endl;
  }
    tempstring = sh_value; tempstring += "/../";
    tempstring += "./packIrosProducts "; tempstring += prefix;
    syscon.execCommand(tempstring);
}
