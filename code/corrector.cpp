/***************************************************************************
                          corrector.cpp  -  description
                             -------------------
    begin                : Fri Dec 14 2007
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

#include "corrector.h"
namespace DataCorrection{
Corrector::Corrector(){
  setVerbose(false);
}
Corrector::~Corrector(){
//SAFitsHandler::~SAFitsHandler()
}
}

/*!
    \fn DataCorrection::Corrector::writeTriggerFile()
 */
void DataCorrection::Corrector::writeTriggerFile()
{
 try{
    tempstring = "touch "+retrieveTrigEnvVar()+"/"+afilename.getTriggerFileName();
    if (verbose) cout << "executing " << tempstring << endl;
    system(tempstring.c_str());
  } catch (const exception &e){
    cerr << "Corrector3905::writeTriggerFile() error in writing trigger file"<< e.what() << endl;
  }
}


/*!
    \fn DataCorrection::Corrector::retrieveTrigEnvVar()
 */
string DataCorrection::Corrector::retrieveTrigEnvVar()
{
//     setVerbose(true);
    string oev("CORR_INDIR");
    string vv("$HOME");
  try{
    char *ovv;
    //setEnvVar(oev, vv, 0);
    ovv = getenv(oev.c_str());    tempstring = ovv;
    if (verbose) if (verbose) cout << "the env var where to find OK file, read from outside = "<< tempstring << endl;
//    setEnvVar(oev, vv, 1);
//    if (verbose) if (verbose) cout << "now the value is "<< getenv(oev.c_str())<< endl;
  } catch (exception &e){
    cerr << "SAFitsHandler::createOutOKFileEnvVar error in creating and exporting the environment variable"<< endl;
  }
  setVerbose(false);
  return tempstring;
}
void DataCorrection::Corrector::prepare()
{
  //setVerbose(true);
  if (verbose) cout << "Corrector::prepare() the output directory where write trigger file will be " << afilename.getTriggerFileName() << endl;
  cout << "infilename = " << infilename << endl;
  afilename.setAbsoluteFileName(infilename);
  afilename.update();
  afilename.setTrigBase("cnt");
  afilename.setCorrectorVersion("001");
  afilename.setTriggerExtension("ok");
  afilename.updateTrigger();
  if (verbose) afilename.show();
  string tt; tt = retrieveTrigEnvVar();
  CORR_INDIR =  tt;
  if (verbose)  cout << "I will write the OK trigger filename in the directory " << CORR_INDIR << endl;
  if (verbose)  cout << "Corrector3906::prepare() the OK file name will be " << afilename.getTriggerFileName() << endl;
  if (verbose) afilename.showTrigger();
}

void DataCorrection::Corrector::setASDC(bool val){
  asdcflag = val;
}