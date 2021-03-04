/***************************************************************************
                          sourceanalyser.cpp  -  description
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

#include "sourceanalyser.h"
namespace SApipeline{

SourceAnalyser::SourceAnalyser(){
  showDefault();
  derived = 1;
  status = PipelineModule::init();
  setExtern(true);
  created_del_dir = false;
}
SourceAnalyser::~SourceAnalyser(){
}
}/** No descriptions */
int SApipeline::SourceAnalyser::init(){
}
void SApipeline::SourceAnalyser::setDescription(){
  //cout << "SApipeline::SourceAnalyser::setDescription()" << endl;
  description = "[single source specific analysis (stage 3)] ";  
}/** No descriptions */
void SApipeline::SourceAnalyser::start(){
}
void SApipeline::SourceAnalyser::launch(string & infile, string & outfile, vector<int> params){
  PipelineModule::launch(infile, outfile, params);
  if (extern_lan) launchIDL_Batch();
}
/** No descriptions */
void SApipeline::SourceAnalyser::launchIDL_Batch(){
  //system( "./launchSourceAnalysis.bash");
}
/** No descriptions */
void SApipeline::SourceAnalyser::deliverProducts(){
/** direct stage 3 execution to be handled */
/*createDeliveryScript();
  if(!created_del_dir) {
    system("./dummyDeliver.bash");
    created_del_dir = true;
    } */
  cout << "SourceAnalyser::deliverProducts() : implement me!"<< endl;
//  tempstring = "cp ../dummy/*.* "+getDeliverDirectory();
//  system(tempstring.c_str());
}
/** No descriptions */
void SApipeline::SourceAnalyser::announceDelivery(){
  cout << "SourcesAnalyser (stage 3) delivered following data: "<< endl;
  PipelineModule::announceDelivery();
  tempstring = "ls "+getSasoaWorkDir()+"/delivery/*.si";
  system(tempstring.c_str());
  tempstring = "ls "+getSasoaWorkDir()+"/delivery/*.sfl";
  system(tempstring.c_str());
  tempstring = "ls "+getSasoaWorkDir()+"/delivery/*.csl";
  system(tempstring.c_str());
}
/** No descriptions */
void SApipeline::SourceAnalyser::rmTempInputFiles(){
  arc->clear_L3_Data();
}
