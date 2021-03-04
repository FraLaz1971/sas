/***************************************************************************
                          sanominalpointing.cpp  -  description
                             -------------------
    begin                : Tue Jun 20 2006
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

#include "sanominalpointing.h"
#include <fstream>
using namespace std;


namespace SAdata{
using namespace SAdata;

SANominalPointing::SANominalPointing(){
}
SANominalPointing::~SANominalPointing(){
}
}
/** No descriptions */
void SAdata::SANominalPointing::setDefault(){
   //catalog_dir     =  "/home/lapa/sagile/catalog/";    /// ; Catalog repository
   //catalog_name  =  "ibis_hard_xray_catalog.txt";  ///  ; Catalog Name
   alfa = "+2.716490739370";           ///; Alfa 2000 in radians    --Longitude--
   delta  = "-0.889043443488";        ///; Delta 2000 in radians -- Latitude--
   roll  = "-0.677324728472";            ///; Roll angle in radians
   //
   //outfilename = "first.MD_IROS_Point_Pilot";
}
/** No descriptions */
void SAdata::SANominalPointing::setAlfa(string al){
  alfa = al;
}
/** No descriptions */
void SAdata::SANominalPointing::setDelta(string del){
  delta = del;
}
/** No descriptions */
void SAdata::SANominalPointing::setRoll(string rol){
  roll =  rol;
}
/** No descriptions */
string SAdata::SANominalPointing::getAlfa(){
  return alfa;
}
/** No descriptions */
string SAdata::SANominalPointing::getDelta(){
  return delta;
}
/** No descriptions */
string SAdata::SANominalPointing::getRoll(){
  return roll;
}
/** No descriptions */
void SAdata::SANominalPointing::setCatalogDir(const string &cd){
}
/** No descriptions */
void SAdata::SANominalPointing::setCatalogName(const string &cn){
}
/** No descriptions */
string SAdata::SANominalPointing::getCatalogDir(){
  return catalog_dir;
}
/** No descriptions */
string SAdata::SANominalPointing::getCatalogName(){
  return catalog_name;
}
/** No descriptions */
void SAdata::SANominalPointing::write(){
  ofstream outfile;
  outfile.open (outfilename.c_str(), ofstream::out | ofstream::app);
  outfile << "; This is a sample pointing pilot file\n";
  outfile << endl;
  outfile << endl;  
  outfile <<"CATALOG_DIR  =  "  <<  getCatalogDir() << endl; //Catalog repository
  outfile <<"CATALOG_NAME  =  "<< getCatalogName() << endl; // Catalog Name
  outfile <<"ALFA = "<< getAlfa() << endl; // Alfa 2000 in radians
  outfile <<"DELTA = "<< getDelta() << endl; // Delta 2000 in radians
  outfile <<"ROLL = "<< getRoll() << endl; // Roll in radians
  outfile.close();
}
