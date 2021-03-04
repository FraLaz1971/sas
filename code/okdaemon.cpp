/***************************************************************************
                          okdaemon.cpp  -  description
                             -------------------
    begin                : Tue Oct 10 2006
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

#include "okdaemon.h"
namespace SApipeline {
OKDaemon::OKDaemon(){
  setVerbose(false);
}
OKDaemon::~OKDaemon(){
}
/** No descriptions */
void OKDaemon::start(){
 int runcounter(0);
 bool t = okpresent();
 cout << "OKDaemon waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {
    if (!okpresent()) continue;
    else break;
    }
    cout << "OKDaemon::start() Running the module!! " << endl;
	
    pipepointer->start();
    cout << "OKDaemon::start() executed run n. " << runcounter++ << endl;
    start();
    cout << "OKDaemon::start() out of the loop" << endl;

}
/** No descriptions */

void OKDaemon::setPipelineModule(PipelineModule *pipepoint){
  pipe = pipepoint;
}
/** No descriptions */
bool OKDaemon::okpresent(){
try{
    bval = false;    DIR  *dir_p;
    struct dirent *dir_entry_p;
 			/* Open the current directory		*/
    dir_p = opendir(okfiledir.c_str());

			/* read each entry until NULL.		*/
    while( NULL != (dir_entry_p = readdir(dir_p)))
    {
				/* print the name of the file held in
				 * this directory entry.		*/

        if (verbose) printf(" %s entry \n", dir_entry_p->d_name);
        /** control  the */
        tempstring.assign(dir_entry_p->d_name);
        //cout << "OKDaemon::okpresent() controlling if name "<< tempstring << " is an OK file "<< endl;
        
       // b =  isOKFile(tempstring);
        
        int s = tempstring.size();
  if (s>3){
         int lastdotpos = tempstring.find_last_of(".");
         tempstring2 = tempstring.substr(lastdotpos+1);
         bool cond2;
         cond2 = !(tempstring2.compare("ok"));
        if (cond2){
           cout << "OKDaemon::okpresent() found the OK file "<< tempstring << ": handling "<< endl;          
        try{
          afname.assignTrigger(tempstring);
          afname.showTrigger();
          afname.update();
          cout << "OKDaemon::okpresent() finding data file for contact "<< afname.getContact() << ": handling "<< endl;                    
          pipepointer->setContact(afname.getContact());
          cout << "OKDaemon::okpresent() going to set contact number in the orbilder" << endl;
          pipepointer->setContact(afname.getContact());
          cout << "OKDaemon::okpresent() contact number in the orbilder set" << endl;
          //cout << "OKDaemon::okpresent() " <<  afname.show() << endl;
          pipepointer->setInputFileName(afname.total());
          pipepointer->setOutputFileName(afname.total());
        } catch (const SAexception & se){
          cerr << "error " << se.getMsg() << endl;
        }
           bval = true;
           string temps; const char *tempc;
           temps = (okfiledir+"/*.ok"); tempc = temps.c_str();
           if (verbose) cout << "OKDaemon::okpresent() removing the file "<< tempc << endl;
           temps = "mv  -f " +temps+" "+okfiledir+"/old";
           if (verbose) cout << "OKDaemon::okpresent() executing the instruction "<< temps << endl;
           system(temps.c_str());
        }
  } else {
    if (verbose) cout << "OKDaemon::okpresent() too short filename"<< endl;
  }
}

				/* Tidy up.				*/
    closedir(dir_p);
    tempstring.clear();
    } catch (const exception &e){
             cerr << "error in controlling ok file present condition"<< e.what() << endl;
    }
    return bval;
}
/** No descriptions */
void OKDaemon::testsetting(){
  string temp = arc->getSasoaWorkDir();  // ? controllare l'utilizzo
  string temp2 = temp + "/conf";
  cout << "OKDaemon::testsetting() assigning ok file path " << temp2 << endl; 
  okfiledir.assign(temp2.c_str());
  okfilename.assign("-");
}
/** No descriptions */
void OKDaemon::setOKFileDir(const string &okdir){
  okfiledir.assign(okdir);
}
/** No descriptions */
bool OKDaemon::triggerPresent(){
  
}
/** No descriptions */
bool OKDaemon::isOKFile(const string &ifn){
  try{
  cout << "OKDaemon::isOKFile() executing"<< endl;
  afname.clear();
  cout << "OKDaemon::isOKFile() cleared"<< endl;
  tempstring2.assign(ifn);
  afname.assignTrigger(tempstring2);
  cout << "OKDaemon::isOKFile() assigned trigger"<< endl;
  afname.show();
  cout << "OKDaemon::isOKFile() shown "<< endl;
//  pipepointer->arc.filenamer.setContact(afname.getContact());
  
//  tempstring2.assign("ok");
//  if (!(tempstring2.compare(afname.getTriggerExtension()))) return true;
//  cout <<"the of extension of the trigger filename is "  << afname.getTriggerExtension() << endl;
//  tempstring2 = afname.getTriggerExtension();

  cout << "OKDaemon::isOKFile() the retrieved trigger extension is "<< tempstring2 << endl;  
  if (!(tempstring2.compare("ok"))){
    b = true;
    cout << "OKDaemon::isOKFile() condition verified! the retrieved trigger extension is "<< tempstring2 << endl;
  }  else {
    b = false;
    cout << "OKDaemon::isOKFile() condition NOT verified! the retrieved trigger extension is "<< tempstring2 << endl;
}
} catch (const exception &e){
  cerr << "error in executing OKDaemon::isOKFile() "<< e.what() << endl;
}
  return b;
}
/** No descriptions */
bool OKDaemon::isWarningFile(const string &ifn){
  return b;
}
/** No descriptions */
bool OKDaemon::isErrorFile(const string &ifn){
  return bval;
}
/** No descriptions */
void OKDaemon::setTriggerFileName(const string &tfn){
  okfilename = tfn;
}
}

/*!
    \fn SApipeline::OKDaemon::test()
 */
void SApipeline::OKDaemon::test()
{
  bool t = okpresent();
  cout << "OKDaemon::test waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {
    if (!okpresent()) continue;
    else break;
  }
  cout << "Running the module!! " << endl;
  string temps("[Orbit Rebuilding (stage -1)]");
  if (pipemodule.getDescription() == temps) {
    cout << "OKDaemon::start() starting SA pipeline module "<< pipemodule.getDescription() << endl;
    OrbitRebuilder *reb = new OrbitRebuilder(pipemodule);
    reb->OrbitRebuilder::start();
  }
  if (verbose) cout << "OKDaemon::start() out of the loop" << endl;
}
/** No descriptions */
string SApipeline::OKDaemon::getContactString(const string &oks){
  cout << "OKDaemon::getContactString()" << endl;
  afilename.assignTrigger(oks);
  afilename.updateTrigger();
  afilename.show();
  afilename.showTrigger();
  return afilename.getContact();
}
/** No descriptions */
string SApipeline::OKDaemon::getNewFileName(){
  tempstring =  afilename.total();
  if (verbose) cout << "OKDaemon::getNewFileName() the file transmitted is "<< tempstring << endl;
  return tempstring;
}
/** No descriptions */
void SApipeline::OKDaemon::setSasoaHandler(SasoaHandler *sh){
  pipepointer = sh;  
}
/*!
    \fn SApipeline::OKDaemon::emiloop()
 */
void SApipeline::OKDaemon::emiloop()
{
  int runcounter(0);
  bool t = okpresent();
  cout << "OKDaemon::emiloop() waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {
    if (!okpresent()) continue;
    else break;
  }
  cout << "OKDaemon::emiloop() Running sasoa !! " << endl;
  cout << "OKDaemon::emiloop() current contact number = "<< arc->getCurrentContactNumber() << endl;
  ss.str(""); ss << arc->getCurrentContactNumber() ; tempstring2 = ss.str();   
  string tempstring3 = "\" > ";  tempstring3 += tempstring2;   tempstring3 += "_out.log 2> ";  
  tempstring3 += tempstring2; tempstring3 += "_err.log";
  tempstring = "./sasoa -b \"runEMIcontact, "+tempstring2+tempstring3;
  cout << "OKDaemon::emiloop() going to exec string "<< tempstring << endl;
  syscon.execCommand(tempstring);
  emiloop();
  if (verbose) cout << "OKDaemon::emiloop() out of the contact run loop" << endl;
}
/*!
    \fn SApipeline::OKDaemon::newtest()
 */
void SApipeline::OKDaemon::newtest()
{
 int runcounter(0);
  bool t = okpresent();
  cout << "waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {

    if (!okpresent()) continue;
    else break;
  }
  cout << "OKDaemon::newtest() Running sasoa !! " << endl;
  cout << "OKDaemon::newtest() current contact number = "<< arc->getCurrentContactNumber() << endl;
  ss.str(""); ss << arc->getCurrentContactNumber() ; tempstring2 = ss.str();   
  tempstring = "./sasoa_0_0_6 -b \"runcontact, "+tempstring2+"\" > out.log 2> err.log";
  cout << "OKDaemon::newtest() going to exec string "<< tempstring << endl;
  syscon.execCommand(tempstring);
  newtest();
  if (verbose) cout << "OKDaemon::newtest() out of the contact run loop" << endl;
/*
 int runcounter(0);
 bool t = okpresent();
 cout << "OKDaemon waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {
    if (!okpresent()) continue;
    else break;
    }
    cout << "OKDaemon::start() Running the module!! " << endl;
	
    pipepointer->start();
    cout << "OKDaemon::start() executed run n. " << runcounter++ << endl;
    start();
    cout << "OKDaemon::start() out of the loop" << endl;*/
}


/*!
    \fn SApipeline::OKDaemon::syncRemoteOKfileDir()
 */
void SApipeline::OKDaemon::syncRemoteOKfileDir()
{
  tempstring2 = getSasoaWorkDir()+"/conf/*";
  tempstring1 = getSasoaWorkDir()+"/newconf";
  tempstring = "rsync "+tempstring2;
  if (verbose) cout << "OKDaemon::syncRemoteOKfileDir() tempstring =  " << tempstring << endl; 
  tempstring = tempstring + " " + tempstring1;
  if (verbose) cout << "OKDaemon::syncRemoteOKfileDir() executing  " << tempstring << endl; 
  system(tempstring.c_str());
}

/*!
    \fn SApipeline::OKDaemon::asdc_test()
 */
void SApipeline::OKDaemon::asdc_test()
{
 int runcounter(0);
  bool t = okpresent();
  cout << "waiting for trigger file named "<< okfilename << " in directory "<< okfiledir << endl;
  while (true) {

    if (!okpresent()) continue;
    else break;
  }
  cout << "OKDaemon::c Running sasoa !! " << endl;
  cout << "OKDaemon::asdc_test() current contact number = "<< arc->getCurrentContactNumber() << endl;
	string localhost("agile@bigfoot.iasf-roma.inaf.it"), remotehost("agile@bigfoot.iasf-roma.inaf.it");
  ss.str(""); ss << arc->getCurrentContactNumber() ; tempstring2 = ss.str();
  arc->loadContactSSH(localhost, remotehost, arc->getCurrentContactNumber()); 
  tempstring = "./sasoa_0_0_6 -b \"runcontact, "+tempstring2+"\" > "+tempstring2+"_out.log 2> "+tempstring2+"_err.log";
  cout << "OKDaemon::asdc_test() going to exec string "<< tempstring << endl;
  syscon.execCommand(tempstring);
  asdc_test();
  if (verbose) cout << "OKDaemon::asdc_test() out of the contact run loop" << endl;
}
