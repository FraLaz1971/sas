/***************************************************************************
                          saspectrumplotter.cpp  -  description
                             -------------------
    begin                : Wed May 17 2006
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


#include "saspectrumplotter.h"
namespace Graphics  {
SASpectrumPlotter::SASpectrumPlotter(){
  plotnum = 20;
 }
SASpectrumPlotter::~SASpectrumPlotter(){
}
/** No descriptions */
void SASpectrumPlotter::read(string filename){


}
/** No descriptions */
void SASpectrumPlotter::plot(){

  gp.commandln("set xrange [0:200]");
  gp.commandln("set grid");
  gp.commandln("set title \" test graphic \"");
  gp.commandln("set xlabel \"ascissa\"");
  gp.commandln("set ylabel \"ordinata\"");  
  gp.commandln("set yrange [0:40000]");
  gp.commandln("plot '-' w l");

  gp.begin_data();
  float temp_chan; long int temp_counts;    
  for(int k=0; k<200; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();

  cout << "press enter to continue"<< endl;
  gp.commandln("pause -1");  
}
/** No descriptions */
void SASpectrumPlotter::print(){
  gp.commandln("set output \"filename.ps\" ");
  gp.commandln("set term post ");
  gp.commandln("replot");     
}
/** No descriptions */
void SASpectrumPlotter::createDefault(){
  channel.resize(200);
  counts.resize(200);
  for(int i=0; i<200; i++){
    channel[i] = (float)i;
    counts[i] = (long int)i*i;
  }
}
/** No descriptions */
void SASpectrumPlotter::start(){
  gp.begin();
}
/** No descriptions */
void SASpectrumPlotter::stop(){
  gp.end();
}
/** No descriptions */
void SASpectrumPlotter::setDescription(const string &dsc){
}
}