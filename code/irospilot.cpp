/***************************************************************************
                          irospilot.cpp  -  description
                             -------------------
    begin                : Tue Mar 20 2007
    copyright            : (C) 2007 by Francesco Lazzarotto
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

#include "irospilot.h"

namespace SApipeline{
  
IrosPilot::IrosPilot(){
  setBaseDir("../stg_2");
  setDataDir("../stg_2/attitude/version_for_sasoa/analisi/mdmap_tmp/default_mdm");
  setFileName("default_im_fn.dat");
	
}
IrosPilot::~IrosPilot(){
}



void IrosPilot::setBaseDir(const string & fn){
    base_dir = fn;
}
  /** */
  string IrosPilot::getBaseDir(){
    return base_dir;
  }
  /** */
  void IrosPilot::setDataDir(const string & dn){
    data_dir = dn;
  }
  /** */
  string IrosPilot::getDataDir(){
    return data_dir;
  }
  /** */
  void IrosPilot::setFileName(const string & fn){
    file = fn;
  }
  /** */
  string IrosPilot::getFileName(){
    return file;
  }
  /** */
  void IrosPilot::setDetector(byte d){
    detector = d;
  }
  /** */
  byte IrosPilot::getDetector(){
    return detector;
  }
  /** */
  void IrosPilot::setLadGap(unsigned short lg){}
  /** */
  unsigned short  IrosPilot::getLadGap(){}
  /** */
  void IrosPilot::setGapStart(unsigned short gs){}
  /** */
  unsigned short  IrosPilot::getGapStart(){}
  /** */
  void IrosPilot::setMaxRounds(unsigned short mr){}
  /** */
  unsigned short  IrosPilot::getMaxRounds(){}
  /** */
  void IrosPilot::setMinSigmas(unsigned short ms){}
  /** */
  unsigned short  IrosPilot::getMinSigmas(){}
  /** */
  void IrosPilot::setCatalogueOption(bool co){}
  /** */
  void IrosPilot::getCatalogueOption(){}
  
}/** No descriptions */
string SApipeline::IrosPilot::getPilotFileDir(){
  tempstring = getUserHome();
  return tempstring;
}

/*!
    \fn SApipeline::IrosPilot::createPilot(byte det, const string pfn)
     create pilot for iros run on det 0 and 
 */
void SApipeline::IrosPilot::createPilot(byte det, const string pfn)
{

  setPilotFilename(pfn); 
 if (verbose) cout << "executing IrosPilot::createPilot() " << endl;
  ofstream of;  
  of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
  try {
    if (verbose) cout << "SourcesExtractor::createPilot() on file "<< pfn << endl;
    of.open (pfn.c_str(), ofstream::out | ofstream::trunc);
    of << ";#####################################################" << endl;
    of << ";# This is a sample pilot file for the MD_IROS" << endl;
    of << ";# For the SuperAGILE pipeline SASOA " << endl;
    of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
    of << ";# modified 20/02/2008 " << endl;
            //of << ";# "+tmr.getDateString() << endl; // COMMENTED 22/03/2007
    of << ";#####################################################" << endl;
            //of << "BASE_DIR    = "<<getSasoaHome()<<"/stg_2/	      ; Base directory" << endl;
    of << "BASE_DIR    = "<<getBaseDir()<<"/	      ; Base directory" << endl;
    of << "DATA_DIR    = "<< getBaseDir() << "/" << getDataDir()<<"/ ; data root directory" << endl;
    if (verbose) cout << "IrosPilot::createPilot()) BASE_DIR    = "<<getBaseDir()<<"	      ; Base directory" << endl;
    of << "FILE	    = "+getFileName()+"    ; Input file name " << endl;
    verbose = true;
    if (verbose) cout << "IrosPilot::createPilot() iros PilotFile name    = "<< pfn <<"	      ; Base directory" << endl;
    verbose = false;           
    of << "DETECTOR    = "<<  int(det)  <<"			          ; -- Detector number" << endl;
    of << "LAD_GAP     = 18		   ; Gap between ladders" << endl;
    of << "GAP_START   = 767		   ; Strip No. after gap" << endl;
    of << "MAX_ROUNDS  = 2		   ; No. of IROS rounds" << endl;
    of << "MIN_SIGMAS  = 4.5		   ; Number of STDs." << endl;
    of << "USE_CAT     = 0 		   ; Set to 1 if catalog is to be used. " << endl;
    of <<"USE_DEFF_MASK = 1     ; 1 to use efficiency arrays" << endl;
    of <<"DEFF_MASK_NAME  = "<< getBaseDir() << "/DEff_Mask_updated_070704.eff"<< endl;
    of <<"SAFE_MODE    = 0        ; 1 if to use a safe mode"<< endl;
    of <<"S_MODE_LEVEL = 0.01 ; Fractional change of chi2 in safe mode"<< endl;
    of <<"GROUND_MASK  = 0    ; Set to 1 if need to use magnified array"<< endl;
    of <<"BKGR_MODEL   = 2    ; 1, 2, etc. for different BKGR models"<< endl;
    of <<"FIT_XA_EFF   = 0    ; Set to 1 if XA efficiency is to be fitted"<< endl;
    of <<"N_XA_PARAMS  = 48   ; How many regions to use (12, 24, 36, 48 ... - multiple of 12)"<< endl; 

    of.close();
  } catch (ofstream::failure e)      {
    cout << "IrosPilot::createPilot() Exception opening/writing file"<< e.what() << endl;    
  }

}

/*!
    \fn SApipeline::IrosPilot::createPilot()
 */
void SApipeline::IrosPilot::createPilot(byte det)
{
  ofstream of;  string fn;
  of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
  try {
    fn = "/home/agile/projects/sasoa/stg_2/.MD_IROS_Pilot";
    if (verbose) cout << "SourcesExtractor::createIrosBatch() on file "<< fn << endl;
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
    of << ";#####################################################" << endl;
    of << ";# This is a sample pilot file for the MD_IROS" << endl;
    of << ";# For the SuperAGILE pipeline SASOA " << endl;
    of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
            //of << ";# "+tmr.getDateString() << endl; // COMMENTED 22/03/2007
    of << ";#####################################################" << endl;
            //            of << "BASE_DIR    = "<<getSasoaHome()<<"/stg_2/	      ; Base directory" << endl;
    of << "BASE_DIR    = "<<getBaseDir()<<"/	      ; Base directory" << endl;
    if (verbose) cout << "SourcesExtractor::createIrosBatch() BASE_DIR    = "<<getBaseDir()<<"	      ; Base directory" << endl;
           
    of << "FILE	    = "+getFileName()+"    ; Input file name " << endl;
    verbose = true;
    if (verbose) cout << "SourcesExtractor::createIrosBatch() iros PilotFile name    = "<<getFileName()<<"	      ; Base directory" << endl;
    verbose = false;           
    of << "DETECTOR    = "<<  int(det)  <<"			          ; -- Detector number" << endl;
    of << "LAD_GAP	    = 19			       ; Gap between ladders" << endl;
    of << "GAP_START   = 768			   ; Strip No. after gap" << endl;
    of << "MAX_ROUNDS  = 5				   ; No. of IROS rounds" << endl;
    of << "MIN_SIGMAS  = 3			       ; Number of STDs." << endl;
    of << "USE_CAT	    = 0 			          ; Set to 1 if catalog is to be used. " << endl;
    of <<"USE_DEFF_MASK = 1     ; 1 to use efficiency arrays" << endl;
    of <<"DEFF_MASK_NAME  = /home/agile/projects/sasoa/stg_2/DEff_Mask_updated_070704.eff"<< endl;
    of <<"SAFE_MODE   = 1        ; 1 if to use a safe mode"<< endl;
    of <<"S_MODE_LEVEL = 0.01 ; Fractional change of chi2 in safe mode"<< endl;
    of <<"GROUND_MASK  = 0    ; Set to 1 if need to use magnified array"<< endl;
    of <<"BKGR_MODEL   = 1    ; 1, 2, etc. for different BKGR models"<< endl;

    of.close();
  } catch (ofstream::failure e)      {
    cout << "SourcesExtractor::SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what() << endl;    
  }

}
/*!
    \fn SApipeline::IrosPilot::createIrosPilot(string, string)
 */

void SApipeline::IrosPilot::createPointingPilot(const string &pfn, const string &cn)
{
    // REMEMBER IT'S A DEFAULT OPTION
  SAL3Eventlist sal3;
  sal3.sapoint.setDefault();
    // REMEMBER IT'S A DEFAULT OPTION
  ofstream of;  //string fn;
  stringstream ss; string ts;
  of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
  try {
    //fn = "/home/agile/projects/sasoa/stg_2/.MD_IROS_Point_Pilot";
    if (verbose) cout << "IrosPilot::createPointingPilot(string, string) iros point pilot file name =  "<< pfn << endl;
    of.open (pfn.c_str(), ofstream::out | ofstream::trunc);
    of << ";#####################################################" << endl;
    of << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
    of << ";# For the SuperAGILE pipeline SASOA " << endl;
    of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
    of << ";# modified 22/02/2008 " << endl;
        //of << ";# "+tmr.getDateString() << endl;
    of << ";#####################################################" << endl;
    of << "CATALOG_DIR  = "<<getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
    if (verbose) cout << "SourcesExtractor::createIrosBatch() CATALOG_DIR  = "<<getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
    of << "CATALOG_NAME  =  "<<cn<<"    ; Catalog Name " << endl;
    ss.str("");ss << sal3.sapoint.getAlfa(); ts = ss.str();  
    of << "ALFA = "+ts+"            ; Alfa 2000 in radians " << endl;
    ss.str("");ss << sal3.sapoint.getDelta(); ts = ss.str();        
    of << "DELTA = "+ts+"           ; Delta 2000 in radians " << endl;
    ss.str("");ss << sal3.sapoint.getRoll(); ts = ss.str(); 
    of << "ROLL = "+ts+"            ; Roll in radians  " << endl;
    of.close();
  } catch (ofstream::failure e)  {
    cout << "IrosPilot::createPointingPilot() Exception opening/writing file"<< e.what()<< endl;
  }
}


/*!
    \fn SApipeline::IrosPilot::createPointingPilot()
 */

void SApipeline::IrosPilot::createPointingPilot()
{
    // REMEMBER IT'S A DEFAULT OPTION
  SAL3Eventlist sal3;
  sal3.sapoint.setDefault();
    // REMEMBER IT'S A DEFAULT OPTION
  ofstream of;  string fn;
  stringstream ss; string ts;
  of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
  try {
    fn = "/home/agile/projects/sasoa/stg_2/.MD_IROS_Point_Pilot";
    if (verbose) cout << "SourcesExtractor::createIrosBatch() iros point pilot file name =  "<< fn << endl;
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
    of << ";#####################################################" << endl;
    of << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
    of << ";# For the SuperAGILE pipeline SASOA " << endl;
    of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
        //of << ";# "+tmr.getDateString() << endl;
    of << ";#####################################################" << endl;
    of << "CATALOG_DIR  = "<<getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
    if (verbose) cout << "SourcesExtractor::createIrosBatch() CATALOG_DIR  = "<<getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
    of << "CATALOG_NAME  =  integral2006_catalog.txt    ; Catalog Name " << endl;
    ss.str("");ss << sal3.sapoint.getAlfa(); ts = ss.str();  
    of << "ALFA = "+ts+"            ; Alfa 2000 in radians " << endl;
    ss.str("");ss << sal3.sapoint.getDelta(); ts = ss.str();        
    of << "DELTA = "+ts+"           ; Delta 2000 in radians " << endl;
    ss.str("");ss << sal3.sapoint.getRoll(); ts = ss.str(); 
    of << "ROLL = "+ts+"            ; Roll in radians  " << endl;
    of.close();
  } catch (ofstream::failure e)  {
    cout << "SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what()<< endl;
  }
}

/*
;DETECTOR    = 0         ; +Z Detector number
;DETECTOR    = 1         ; -X Detector number
;DETECTOR    = 2         ; -Z Detector number
;DETECTOR    = 3         ; +X Detector number
*/

/*!
    \fn SApipeline::IrosPilot::setDefaultPilot(const string &pfn)
 */
void SApipeline::IrosPilot::readDefaultPilot(const string &pfn)
{
    ifstream ninfile;
    string fn; pilotlines.clear();
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (pfn.c_str(), ifstream::in);
        while(!ninfile.eof()){
           cout << ninfile.read(buf, mlinelen) << endl;
	   pilotlines.push_back(buf);
           if (verbose) cout << "saving " <<  buf << endl;
        }
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file" << endl;
      }
     if (verbose) cout << "Finished execution of SApipeline::PipelineModule::readDefaultPar()" << endl;

}


/*!
    \fn SApipeline::IrosPilot::setDefaultPointPilotFilename(const string &ppfn)
 */
void SApipeline::IrosPilot::readDefaultPointPilot(const string &ppfn)
{
    ifstream ninfile;
    string fn; pointpilotlines.clear();
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (ppfn.c_str(), ifstream::in);
        while(!ninfile.eof()){
           cout << ninfile.read(buf, mlinelen) << endl;
	   pilotlines.push_back(buf);
           if (verbose) cout << "saving " <<  buf << endl;
        }
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file" << endl;
      }
     if (verbose) cout << "Finished execution of SApipeline::PipelineModule::readDefaultPar()" << endl;

}

  /** No descriptions */
void SApipeline::IrosPilot::setPilotFilename(const string &pfn){
 pilotfilename = pfn;
}

  /** No descriptions */
void SApipeline::IrosPilot::setPointPilotFilename(const string &ppfn){
 pointpilotfilename = ppfn;
}

  /** No descriptions */
string SApipeline::IrosPilot::getPilotFilename(){
 return pilotfilename;
}

  /** No descriptions */
string SApipeline::IrosPilot::getPointPilotFilename(){
 return pointpilotfilename;
}

  /** No descriptions */
  void SApipeline::IrosPilot::setOutfilePrefix(const string &prfn){
      outfileprefix = prfn;
  }

  /** No descriptions */
  string SApipeline::IrosPilot::getOutfilePrefix(){
      return outfileprefix;
  }

  /** No descriptions */
  void SApipeline::IrosPilot::setLogfileName(const string &lfn){
	logfilename = lfn;
  }

  /** No descriptions */
  string SApipeline::IrosPilot::getLogfileName(){
	return logfilename;
}

  /** No descriptions */
  void SApipeline::IrosPilot::setCatalogName(const string & cn){
	catalogname = cn;
  }

  /** No descriptions */
  string SApipeline::IrosPilot::getCatalogName(){
	return catalogname;
  }

  /** No descriptions */
void SApipeline::IrosPilot::launchIros(byte det){
setVerbose(true);
iroscommand = getBaseDir()+ "/IROS-Multi-D/launchIros";
pilotfilename = getPilotFilename();
if (verbose) cout << "launching IROS processing " << endl;
if (verbose) cout << "IROS command " << iroscommand << endl;
if (verbose) cout << "pilot file name " << pilotfilename << endl;
if (verbose) cout << "pointing pilot file name " << pointpilotfilename << endl;
if (verbose) cout << "log file name " << logfilename << endl;
if (verbose) cout << "prefix for output files " << outfileprefix << endl;
ss.str(""); ss <<  iroscommand << " " << pilotfilename <<  " " << pointpilotfilename << " " << logfilename << " " << outfileprefix <<  endl;
tempstring = ss.str();
if (verbose) cout << "executing " << tempstring << endl;
syscon.execCommand(tempstring);

/*
string iroscommand;
string pilotfilename;
string pointpilotfilename;
string logfilename;
string outfileprefix;


./launchIros "/home/lazza/projects/attitude_launcher/MD_IROS_Pilot_v4_test_0" "/home/lazza/.MD_IROS_Point_Pilot_v4" "iros_out.log" "thisprefix"
*/

}

