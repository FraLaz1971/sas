/***************************************************************************
                          saparameterslist.cpp  -  description
                             -------------------
    begin                : Mon May 8 2006
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

#include "saparameterslist.h"
namespace SApipeline{
SAParametersList::SAParametersList(){
}
SAParametersList::~SAParametersList(){
}
}/** No descriptions */
void SApipeline::SAParametersList::show(){
 map<string, string>::iterator it;
 it=pars_map.begin();
 while(it!= pars_map.end()){
    cout << it->first << "\t"<< it->second << endl;
    it++;
 }
}
/** No descriptions */
void SApipeline::SAParametersList::setGainLutName(const string &glutnam){
  pars_map["gain_lut_name"]  = glutnam;
}
/** No descriptions */
void SApipeline::SAParametersList::setNoisyLutName(const string &nlutnam){
  pars_map["noisy_lut_name"]  = nlutnam;
}
/** No descriptions */
void SApipeline::SAParametersList::saveParameterList(bool extlang){
    if(extlang) {  /// pass to external language batch routine
    cout << "enter parameters values please ..." << endl;
    ofstream outfile;
    string buf;
    int k=0;
    outfile.open ("def/common.def", ofstream::out | ofstream::app);
    cout << "enter name of the instrument/prototype producing data : <DETNAM>" << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/data/  " << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = SASOA_HOME + "/" + buf + "/";
    WORK_DET_PATH = defpar[k-1];

    cout << "enter directory containing input data  " << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/data/]" << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

    cout << "enter directory containing  gain/address LUT (I/0) " << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/tables/]" << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

    cout << "enter directory containing input configuration data files   " << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/conf/]" << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

    cout << "enter directory input data  " << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/products/]" << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

    cout << "enter directory input data  " << endl;
    cout << "default = [$HOME/SASOA/<DETNAM>/hk/]" << endl;
    cin >> buf; // save <DETNAM>
    if  (buf != "") defpar[k++] = WORK_DET_PATH + buf;

    int t = 0;
    while (t<20){
     outfile << defpar[t++] << endl;
    }
    outfile.close();
  // save SA_photon.par
    bool idl = true;
    savePhotonParameters(idl);
    } else {

  }
  
}
/** No descriptions */
void SApipeline::SAParametersList::setMap(const map<string, string> &passmap){
  pars_map = passmap;
}
/** No descriptions */
map<string, string> SApipeline::SAParametersList::getMap(){
}
/** No descriptions */
void SApipeline::SAParametersList::setParameter(const SAParameter &sp){
  pars_map[sp.getDescription()] = sp.getValue();
}
/** No descriptions */
void SApipeline::SAParametersList::savePhotonParameters(bool extlang){
  if (extlang){
  cout << "enter parameters values please ..." << endl;
  ofstream outfile;
  string buf;
  int k=0;
  outfile.open ("def/SA_photon.par", ofstream::out | ofstream::app);
  cout << "enter name of the instrument/prototype producing data : <DETNAM>" << endl;
  cout << "default = [$HOME/SASOA/<DETNAM>/data/]  " << endl;

  cout << "enter gain LUT file name  (with complete path)" << endl;
  cout << "default = [gain_LUT_name='$HOME/SASOA/<DETNAM>/tables/SA_cali_003667_060125_185535_S_orb_0000.glt']" << endl;
  cin >> buf; /// save gain LUT filename
  if  (buf != "") {
    defpar[k++] = "gain_LUT_name="+buf+"'";
    defpar[k++] = "gain_LUT_dummy='N'";
  }
  else {
    defpar[k++] = "gain_LUT_dummy='Y'";
  }
  cout << "enter noisy LUT file name  (with complete path)" << endl;
  cout << "default = [$HOME/SASOA/<DETNAM>/tables/SA_scie_003668_060126_172627_S_orb_00000.nsl]" << endl;
  cin >> buf; /// save noisy LUT filename
  if  (buf != "") defpar[k++] = "noisy_LUT_name="+buf+"'";

  int t = 0;
  while (t<20){
    outfile << defpar[t++] << endl;
  }
  outfile.close();
  } else {

  }
    
}
/** No descriptions */
void SApipeline::SAParametersList::saveCalibrationParameters(bool extlang){
}
