/***************************************************************************
                          safilenamer.cpp  -  description
                             -------------------
    begin                : Mon Sep 18 2006
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

#include "safilenamer.h"

namespace SAarchive{

SAFileNamer::SAFileNamer(){
  stringstream ss; ss << "pkpNNNNNN_C_PPSS_XXX.cor";
  temp = ss.str();
  filename.assignName(temp);
}

SAFileNamer::SAFileNamer(SATask stask){
    mytask = stask;
}

SAFileNamer::~SAFileNamer(){

}


/** returns a string containing the *output* file name for the specific SA task output filename */

//Preprocessing, Correction, OrbitRebuilding, PhotonListBuilding, SourcesExtraction, SourceAnalysis  ... and other tasks
string SAFileNamer::getFileName(SATask stask){
  verbose = true;
  string t1("MDI");
  corext = "cor";
  olddrext = "lv1";
  rebext = "orb";
  imext = "dat";
  pbext = "evt";
  sub1 = "L1";
  sub19 = "L19";
  sub2 = "L2";
  sub3 = "L3";
  if (verbose) cout << "SAFileNamer::getFileName() creating output filename for task! "<< stask << endl;
  switch(stask){
    case Preprocessing:
    break;
    case  Correction:
        filename.setOrbdata(false);
        filename.setExtension(corext);
        if (verbose) cout << "SAFileNamer::getFileName(): now the extension is "<< filename.getExtension() << endl;
        if (verbose) cout << "SAFileNamer::getFileName(): Correction task   "<<  endl;
        // remember to write the right orbit number
        filename.setSubExtension(true);
        filename.setSubExtension(sub1);
        filename.update();
        tempstring = filename.total();
    break;
    case OrbitRebuilding:
        filename.setOrbdata(true);
        filename.setExtension(rebext);
        if (verbose) cout << "SAFileNamer::getFileName(): now the extension is "<< filename.getExtension() << endl;
        if (verbose) cout << "SAFileNamer::getFileName(): OrbitRebuilding task   "<<  endl;
        // remember to write the right orbit number
        filename.setOrbitNumber(filename.getContact());
        filename.setSubExtension(true);
        filename.setSubExtension(sub1);        
        filename.update();
        tempstring = filename.total();
    break;    
    case DataReducing:
        filename.setExtension(pbext);
        filename.setOrbdata(true);
    break;
    case PhotonListBuilding:
        filename.setOrbdata(true);
        filename.setExtension(pbext);
        cout << "now the extension is "<< filename.getExtension() << endl;
        filename.setSubExtension(true);
        filename.setSubExtension(sub2);
        filename.update();
        tempstring = filename.total();    
    break;
    case SourcesExtraction:
        filename.setOrbdata(true);
        filename.setExtension(pbext);
        filename.setSubExtension(true);
        filename.setSubExtension(sub3);
        filename.update();
        tempstring = filename.total();
    break;
    case SourceAnalysis:
        filename.setOrbdata(true);
        filename.setExtension(pbext);
        filename.setSubExtension(true);
        filename.setSubExtension(sub3);
        filename.update();
        tempstring = filename.total();
    break;
    case IrosMapBuilding:
      filename.setOrbdata(true);
      filename.setBase(t1);
      filename.setExtension(imext);
      filename.update();
      tempstring = filename.total();
    break;
    case OldDataReduction:
      filename.setOrbdata(true);
      filename.setExtension(olddrext);      
      filename.update();
      tempstring = filename.total();
    break;
    case AttitudeCorrection:
      filename.setOrbdata(true);
      filename.setExtension(olddrext);
      filename.update();
      tempstring = "prova_outfile_L3.evt";
    break;
    default:
      cout << "unknown SA task! "<< endl;
    break;
  }
  verbose = false;
  return tempstring;
}

}
/** No descriptions */
void SAarchive::SAFileNamer::show(){
  filename.show();
}
/** No descriptions */
void SAarchive::SAFileNamer::setFileName(const string &fn){
  filename.assignName(fn);
}
/** No descriptions */
void SAarchive::SAFileNamer::init(){
  procext = "lv1";
  corext = "cor";
  rebext = "orb";
  dredext = "evt";
  pbext = "evt";
  srexext = "evt";
  sranext = "evt";
}
/** No descriptions */
void SAarchive::SAFileNamer::setTask(SATask ts){
  mytask = ts;
}
/** No descriptions */
string SAarchive::SAFileNamer::getOutputFileName(SATask stask){
  return getFileName(stask);
}
/** No descriptions */
string SAarchive::SAFileNamer::getInputFileName(SATask stask){
  tempstring =  getFileName(SATask((stask - 1)));
  switch(stask){
    case IrosMapBuilding:
      if (verbose) cout << "SAFileNamer::getInputFileName() correct input filename for IrosMapBuilding = " << tempstring << endl;
      tempstring = getFileName(SourcesExtraction);
      if (verbose) cout << "SAFileNamer::getInputFileName() correct input filename for IrosMapBuilding = " << tempstring << endl;
      tempstring = "prova_outfile_L3.evt";
      if (verbose) cout << "SAFileNamer::getInputFileName() USED ! correct input filename for IrosMapBuilding = " << tempstring << endl;
    break;    
  }
  return tempstring;
}
/** Set the Input filename for the specified task*/
void SAarchive::SAFileNamer::setFileName(const string &fname, SATask stask){
  switch(stask){
    case Preprocessing:
    break;
    case  Correction:
    break;
    case OrbitRebuilding:
        filename.setOrbdata(true);
        filename.setExtension(rebext);
        if (verbose) cout << "SAFileNamer::getFileName(): now the extension is "<< filename.getExtension() << endl;
        if (verbose) cout << "SAFileNamer::getFileName(): OrbitRebuilding task   "<<  endl;
        // remember to write the right orbit number
        filename.setOrbitNumber(filename.getContact());
        filename.setSubExtension(true);
        filename.setSubExtension(sub1);
        filename.update();
        tempstring = filename.total();
    break;
    case DataReducing:
    break;
    case PhotonListBuilding:
        filename.setExtension(pbext);
        cout << "SAFileNamer::getFileName() now the extension is "<< filename.getExtension() << endl;
        filename.setSubExtension(true);
        filename.setSubExtension(sub2);
        filename.update();
        tempstring = filename.total();
    break;
    case SourcesExtraction:
        filename.setSubExtension(true);
        filename.setSubExtension(sub3);
        filename.update();
        tempstring = filename.total();
    break;
    case SourceAnalysis:
    break;
    case IrosMapBuilding:
      filename.setExtension(imext);
      filename.update();
      tempstring = filename.total();
    break;
    case OldDataReduction:
      filename.setExtension(olddrext);
      filename.update();
      tempstring = filename.total();
    break;
    case AttitudeCorrection:
      filename.setExtension(olddrext);
      filename.update();
      tempstring = "prova_outfile_L3.evt";
    break;
    default:
      cout << "SAFileNamer::setFileName() unknown SA task! "<< endl;
    break;
  }
    filename.assignName(tempstring);
}
/** No descriptions */
string SAarchive::SAFileNamer::getBase(){
  return filename.getBase();
}
/** No descriptions */
string SAarchive::SAFileNamer::getNameRoot(){
  tempstring = filename.getNameRoot();
  return tempstring;
}
/** No descriptions */
string SAarchive::SAFileNamer::getRSOPName(string type){
  cout << "SAFileNamer::getRSOPName() for type "<< type<< endl;
  return tempstring;
}
/** No descriptions */
void SAarchive::SAFileNamer::setContact(const string &cs){
  filename.setContact(cs);
}
/** No descriptions */
string SAarchive::SAFileNamer::getContact(){
  return filename.getContact();
}


/*!
    \fn SAarchive::SAFileNamer::get_3914_FileName()
 */
string SAarchive::SAFileNamer::get_3914_FileName()
{
    tempstring = "PKP000625_1_3914_000.lv1";
	return tempstring;
}


/*!
    \fn SAarchive::SAFileNamer::get_3916_FileName()
 */
string SAarchive::SAFileNamer::get_3916_FileName()
{
    tempstring = "PKP000625_1_3916_000.lv1";
	return tempstring;
}


/*!
    \fn SAarchive::SAFileNamer::getRelativeFileName(const string &allpathfn)
 */
string SAarchive::SAFileNamer::getRelativeFileName(const string &allpathfn)
{
  tempstring =  allpathfn.substr(allpathfn.find_last_of( "/")+1);
  return tempstring;
}


/*!
    \fn SAarchive::SAFileNamer::getContactNumber()
 */
int SAarchive::SAFileNamer::getContactNumber()
{
     return filename.getContactNumber();
}
