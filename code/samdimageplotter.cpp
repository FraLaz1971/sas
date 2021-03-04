/***************************************************************************
                          samdimageplotter.cpp  -  description
                             -------------------
    begin                : Tue Aug 1 2006
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

#include "samdimageplotter.h"
namespace Graphics {
/** No descriptions */
SAMDImagePlotter::SAMDImagePlotter(){
  setXSize(1536);
  setYSize(1536);
  setZSize(1536);
//  imgdim = 1536;
  plotdim = 1536;
//  imgtype = -1;
}
/** No descriptions */
SAMDImagePlotter::~SAMDImagePlotter(){
}
/** No descriptions */
void SAMDImagePlotter::init(){
}
/** No descriptions */
//void SAMDImagePlotter::plot(int regnum){
//}
/** No descriptions */
void SAMDImagePlotter::plotLoaded(){
}
/** No descriptions */
void SAMDImagePlotter::print(){
}
/** No descriptions */
void SAMDImagePlotter::save(){
}
/** No descriptions */
//void SAMDImagePlotter::setAxes(){
//}

///** No descriptions */
//void SAMDImagePlotter::setData(){
//}
/** No descriptions */
void SAMDImagePlotter::showData(){
}
/** No descriptions */
void SAMDImagePlotter::start(){
    gp.begin();
}
/** No descriptions */
void SAMDImagePlotter::stop(){
    gp.end();
}
/** No descriptions */
void SAMDImagePlotter::plotAll(){
  gp.commandln("set grid");
  string temps = "set title \""; temps += plottitle; temps +=  "\"";
  cout << "SAImagePlotter::plot() going to exec gnuplot command " <<temps<< endl;
  gp.commandln(temps.c_str());
  gp.commandln("set xlabel \"strip\"");
  gp.commandln("set ylabel \"counts\"");
  gp.commandln("set zlabel \"sky region\"");
  gp.commandln("splot '-' with impulses");
  gp.begin_data();
  float temp_chan; long int temp_counts; long int temp_dep;
  for(int k=0; k<plotdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k]; temp_dep = depth[k];
      gp.commandln("%e %d %d", temp_chan, temp_counts, temp_dep);
  }
  gp.end_data();
    cout << "press enter to continue"<< endl;
    gp.commandln("pause -1");
  
//  if (interactive){
//    cout << "press enter to continue"<< endl;
//    gp.commandln("pause -1");
//  } else {
//    string c = getPauseCommand();
//    gp.commandln(c.c_str());
//  }
}
/** No descriptions */
void SAMDImagePlotter::setDescription(const string &dsc){
  description = dsc;
}
}