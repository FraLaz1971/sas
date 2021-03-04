/***************************************************************************
                          corrector3906.cpp  -  description
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

#include "corrector3906.h"
namespace DataCorrection{
Corrector3906::Corrector3906(){
}
Corrector3906::Corrector3906(const string &fn, const string &ofn){
     asdcflag = false;     processed = false;
     tstart = 0.;     tstop = 0.; 
     SAFitsHandler(fn, ofn);
     infilename = fn;
     outfilename = ofn;
     init();
}
Corrector3906::~Corrector3906(){
}
/*
void Corrector3906::prepare(){
  setVerbose(true);
  if (verbose) cout << "Corrector3905::prepare() the output directory where write trigger file will be " << afilename.getTriggerFileName() << endl;
  afilename.setAbsoluteFileName(infilename);
  afilename.update();
  afilename.setTrigBase("cnt");
  afilename.setCorrectorVersion("001");
  afilename.setTriggerExtension("ok");
  afilename.updateTrigger();
  afilename.show();
  string tt; tt = retrieveTrigEnvVar();
  CORR_INDIR =  tt;
  if (verbose) cout << "I will write the OK trigger filename in the directory " << CORR_INDIR << endl;
  if (verbose) cout << "Corrector3906::prepare() the OK file name will be " << afilename.getTriggerFileName() << endl;
  afilename.showTrigger();
  //removeOldOutfile();
  //openInputFile();
  //openOutputFile();
  //setVerbose(false);  
}
*/


}
