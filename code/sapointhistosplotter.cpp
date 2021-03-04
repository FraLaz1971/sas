/***************************************************************************
                          sapointhistosplotter.cpp  -  description
                             -------------------
    begin                : Thu Dec 7 2006
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

#include "sapointhistosplotter.h"

namespace Graphics  {
  
SAPointHistosPlotter::SAPointHistosPlotter() : SAPlotter(1024, 1024) {
    
}

SAPointHistosPlotter::~SAPointHistosPlotter(){

}

/** No descriptions */
void SAPointHistosPlotter::plot(){
  stringstream ss; string  comm;
  ss << "set title \"" << "SA Pointing Histogram " << axes << " Axes " << "\"";
  comm = ss.str();
  //cout << "SAPointHistosPlotter::plot() started"<< endl;
  gp.commandln("set grid");
  //gp.commandln("set title \" SA Pointing Histogram \"");
  gp.commandln(comm.c_str());  
  gp.commandln("set xlabel \"skybin\"");
  gp.commandln("set ylabel \"counts\"");
  gp.commandln("plot '-' w l");
  gp.begin_data();
  float temp_chan; long int temp_counts;
  for(int k=0; k<plotdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  if (interactive){
    //cout << "press enter to continue"<< endl;
    gp.commandln("pause -1");
  } else {
    string c = getPauseCommand();
    gp.commandln(c.c_str());
  }
}

void SAPointHistosPlotter::init(){
  //cout << "starting SAPointHistosPlotter::init() "<< endl;
  channel.resize(1024);
  counts.resize(1024);
  //cout << "SAPointHistosPlotter::init() ended"<< endl;
}

void SAPointHistosPlotter::setData(vector<int> x, vector<unsigned long int> y, int dim){
 //cout << "SAPointHistosPlotter::setData() started " << endl;
 init();
 int k=0;
 while(k< dim){
   channel[k] = float(x[k]);
   counts[k] =  (unsigned long int)y[k];
   k++;
 }
 //cout << "SAPointHistosPlotter::setData() ended " << endl;
}


void SAPointHistosPlotter::start(){
    gp.begin();
}

void SAPointHistosPlotter::stop(){
    gp.end();
}

void SAPointHistosPlotter::showData(){
  //cout << "SAPointHistosPlotter::showData() started"<< endl;
  float temp_chan; long int temp_counts;
  for(int k=0; k<plotdim; k++){
      //cout << channel[k] << "\t" << counts[k] << "\n";
  }
  //cout << "SAPointHistosPlotter::showData() ended"<< endl;
}

void SAPointHistosPlotter::setAxes(char ax){
  axes = ax;
}

void SAPointHistosPlotter::print(){
  //cout << "SAPointHistosPlotter::print() started" << endl;
  string tt("set output \"");
  stringstream s;  s << plotnum;
  tt += plotsetdir+"/";
  tt +=filenamebase+s.str();  tt +=".ps";tt +="\" ";
  //cout << "Gnuplot executing " << tt.c_str() << endl;
  gp.commandln(tt.c_str());
  gp.commandln("set term post");
  gp.commandln("plot '-' w l");
  float temp_chan; long int temp_counts;
  for(int k=0; k<plotdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  //cout << "SAPointHistosPlotter::print() ended" << endl;
  incrementPlotCounter();
}

void SAPointHistosPlotter::save(){
}

void SAPointHistosPlotter::plotLoaded(){
  //cout << "SAPointHistosPlotter::plotLoaded() started"<< endl;
  stringstream ss; string  comm;
  ss << "set title \"" << "SA Pointing Histogram " << axes << " Axes " << "\"";
  comm = ss.str();
  gp.commandln("set grid");
  gp.commandln(comm.c_str());
  gp.commandln("set xlabel \"skybin\"");
  gp.commandln("set ylabel \"counts\"");
  gp.commandln("plot '-' w l");
  gp.begin_data();
  float temp_chan; long int temp_counts;
  for(int k=0; k<plotdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
   //cout << "SAPointHistosPlotter::plotLoaded() ended"<< endl;
  if (interactive){
    //cout << "press enter to continue"<< endl;
    gp.commandln("pause -1");
  } else {
    string c = getPauseCommand();
    gp.commandln(c.c_str());
  }
}
 
void SAPointHistosPlotter::setDescription(const string &dsc){
  // I don't know what it has to do!
}

}

/*!
    \fn Graphics::SAPointHistosPlotter::print(const string &pd)
 */
void Graphics::SAPointHistosPlotter::print(const string &pd)
{
  string vv("set term ");vv+=getTerm();
  string tt("set output \"");
  //cout << "Gnuplot executing " << tt.c_str() << endl;

/*

  string vv("set term ");vv+=getTerm();
  cout << "instruction = "<< vv << endl;
  string tt("set output \""); 
  stringstream s;  s << plotnum;
  tt += plotdir+"/";
  tt +=filenamebase+s.str();  tt +=getExtension();tt +="\" ";
  //cout << "Gnuplot executing " << tt.c_str() << endl;   
  gp.commandln(tt.c_str());
  gp.commandln(vv.c_str());
  gp.commandln("plot '-' w l");

*/
  stringstream s;  s << plotnum;
  tt += pd+"/";
  tt +=filenamebase+s.str();  tt +=getExtension();tt +="\" ";
  //cout << "Gnuplot executing " << tt.c_str() << endl;   
  gp.commandln(vv.c_str());
  gp.commandln(tt.c_str());
  gp.commandln("plot '-' w l");
  float temp_chan; long int temp_counts;
  for(int k=0; k<plotdim; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  //cout << "SAPointHistosPlotter::print() ended" << endl;
  incrementPlotCounter();

}
