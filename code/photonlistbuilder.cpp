/***************************************************************************
                          photonlistbuilder.cpp  -  description
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

#include "photonlistbuilder.h"
namespace SApipeline{
/**
  class implementing the photonlist building stage of the SA pipeline
  *@author Francesco Lazzarotto
  */
PhotonListBuilder::PhotonListBuilder(){
  exec = false;
  showDefault();
  derived = 1;
  status = PipelineModule::init();
  setExtern(true);
}
PhotonListBuilder::~PhotonListBuilder(){
}
}/** No descriptions */
int SApipeline::PhotonListBuilder::init(){

}
/** No descriptions */
void SApipeline::PhotonListBuilder::setDescription(){
    if (verbose) cout << "SApipeline::PhotonListBuilder::setDescription()" << endl;
    description = "[photon list building (stage 1)] ";
}
/** No descriptions */
void SApipeline::PhotonListBuilder::start(){
}
/** No descriptions */
void SApipeline::PhotonListBuilder::launchIDL_Batch(){
PipelineModule::launch(infile, outfile, params);
     if (isIDLon()) system( "./launchPhotonListBuilding.bash");
}
/** No descriptions */
void SApipeline::PhotonListBuilder::launch(string & infile, string & outfile, vector<int> params){
  PipelineModule::launch(infile, outfile, params);
    if (extern_lan) launchIDL_Batch();
    exec = true;
}
/** No descriptions */
void SApipeline::PhotonListBuilder::createLaunchBatchScript(){
      if (verbose) cout << "PhotonListBuilder::createLaunchBatchScript() DETNAM = "<< DETNAM << endl;
      ofstream noutfile;
      string fn;
      noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "launchPhotonListBuilding.bash";
        noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
        noutfile << "#! /bin/sh" << endl;
        noutfile <<"cd $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "echo entering directory $HOME/SASOA/"+getDetnam()+"/software/pipeline" << endl;
        noutfile << "idl stage1_idl_batch" << endl;
        noutfile << "exit" << endl;
        noutfile.close();
      }
      catch (ofstream::failure e) {
        cout << "Exception opening/writing file"<< endl;
      }
}

void SApipeline::PhotonListBuilder::rmTempInputFiles(){
  arc->clear_L19_Data();
}
/** No descriptions */
void SApipeline::PhotonListBuilder::passOutputFile(const string &toutdir){
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() executing PhotonListBuilder::passOutputFile()"<< endl;
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() the output file from stage 1 is generated in "  << outdir << endl;
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() i'm going to copy output file in "<< toutdir << endl;
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() the file name would be "<< arc->filenamer.getOutputFileName(PhotonListBuilding) << endl;
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() taking original file in " << outdir;
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() outdir = " << outdir << endl;
  string temps, temps1;
  temps1 = (string)"ls -t ";temps1.append(getProductPath());temps1.append((string)"/");temps1.append(outdir);temps1.append((string)"/*_L2.evt  | sed -n \"1p\" ");
  vector<string> sv;
  sv = syscon.dumpCommand(temps1);
string t(outdir); t.append((string)"/"); t.append((string)sv[0]);
  if(verbose)  cout << "PhotonListBuilder::passOutputFile() copying filename "<< t << endl;

temps = (string)"cp ";  temps.append((string)sv[0]); temps.append((string)" "); temps.append(toutdir); temps.append((string)"/"); temps.append(arc->filenamer.getOutputFileName(PhotonListBuilding));
syscon.execCommand(temps);
  system(temps.c_str());
  if(verbose) cout << "PhotonListBuilder::passOutputFile() exec shell command: " << temps << endl;
  if(verbose)  cout << "ended PhotonListBuilder::passOutputFile()"<< endl;

}
/** No descriptions */
string SApipeline::PhotonListBuilder::getDefaultOutputDir(){
  return outdir;
}
/** No descriptions */
void SApipeline::PhotonListBuilder::announceDelivery(){
}
/** No descriptions */
string SApipeline::PhotonListBuilder::getOutputFileName(){
  return arc->filenamer.getOutputFileName(PhotonListBuilding);
}
