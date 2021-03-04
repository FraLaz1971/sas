/***************************************************************************
                          saimageplotter.cpp  -  description
                             -------------------
    begin                : Wed Jun 21 2006
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

#include "saimageplotter.h"
namespace Graphics {
SAImagePlotter::SAImagePlotter() : SAPlotter(1536, 1536) {
  setXSize(1536);
  setYSize(1536);
  imgdim = 1536;
  plotdim = 1536;
  imgtype = -1;
}
SAImagePlotter::~SAImagePlotter(){
}
/** No descriptions */

void SAImagePlotter::read(string filename){

}
/** No descriptions */
void SAImagePlotter::plot(){
  gp.commandln("set grid");
  string temps = "set title \""; temps += plottitle; temps +=  "\"";
  //cout << "SAImagePlotter::plot() going to exec gnuplot command " <<temps<< endl;
  gp.commandln(temps.c_str());
  gp.commandln("set xlabel \"strip\"");
  gp.commandln("set ylabel \"counts\"");
  gp.commandln("plot '-' w l");
  gp.begin_data();
  float temp_chan; long int temp_counts;
  for(int k=0; k<imgdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  if (interactive){
    if (verbose) cout << "SAImagePlotter::plot() press enter to continue"<< endl;
    gp.commandln("pause -1");
  } else {
    if (verbose) cout << "SAImagePlotter::plot() going ahead"<< endl;
    string c = getPauseCommand();
    gp.commandln(c.c_str());
  }
}
/** No descriptions */
void SAImagePlotter::print(){
  //cout << "SAImagePlotter::print() started" << endl;
  //string psp = get; // plot subset directory path
  string vv("set term ");vv+=getTerm();
  string tt("set output \""); 
  stringstream s;  s << plotnum;
  tt += plotsetdir+"/";
  tt +=filenamebase+s.str();  tt +=getExtension();tt +="\" ";
  //cout << "Gnuplot executing " << tt.c_str() << endl;   
  gp.commandln(tt.c_str());
  gp.commandln(vv.c_str());
  gp.commandln("plot '-' w l");
  float temp_chan; long int temp_counts;
  for(int k=0; k<imgdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  //cout << "SAImagePlotter::print() ended" << endl;
  incrementPlotCounter();
}
/** No descriptions */
void SAImagePlotter::createDefault(){
  for(int i=0; i<imgdim; i++){
    channel[i] = (float)i;
    counts[i] = (long int)0;
  }
}

/** No descriptions */
void SAImagePlotter::start(){
  gp.begin();
}

/** No descriptions */
void SAImagePlotter::stop(){
  gp.end();
}


/** No descriptions */
void SAImagePlotter::setDescription(const string &dsc){
  description = dsc;
}
/**  */

// imgtype = -1  --> not defined
// imgtype =  0  --> detector image
// imgtype =  1  --> Multi Detector Image (corrected)

void SAImagePlotter::setImageType(int imt){
  imgtype = imt;
}
/** No descriptions */
int SAImagePlotter::getImageType(){
  return imgtype;
}
}

/*!
    \fn Graphics::SAImagePlotter::print(const string &plotdir)
 */
void Graphics::SAImagePlotter::print(const string &plotdir)
{
  //string psp = get; // plot subset directory path
  string vv("set term ");vv+=getTerm();
  string tt("set output \""); 
  stringstream s;  s << plotnum;
  tt += plotdir+"/";
  tt +=filenamebase+s.str();  tt +=getExtension();tt +="\" ";
  //cout << "Gnuplot executing " << tt.c_str() << endl;   
  gp.commandln(tt.c_str());
  gp.commandln(vv.c_str());
  gp.commandln("plot '-' w l");
  float temp_chan; long int temp_counts;
  for(int k=0; k<imgdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  //cout << "SAImagePlotter::print() ended" << endl;
  incrementPlotCounter();
}
