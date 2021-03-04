/***************************************************************************
                          saplotter.cpp  -  description
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

#include "saplotter.h"
namespace Graphics  {

int SAPlotter::plotsetctr = 0;

SAPlotter::SAPlotter(){
  tempstring = "sa_plot_";
  setFilenameBase(tempstring.c_str());
  plotfilename = filenamebase;
  interactive = false;
  setDelayTime(0);
  setVerbose(false);
}

SAPlotter::SAPlotter(unsigned long int xdim, unsigned long int ydim){
  init();
  setDimensions(xdim, ydim);
  tempstring = "sa_plot_";
  setFilenameBase(tempstring.c_str());
  plotfilename = filenamebase;
  interactive = false;
  setPlotTitle(plotfilename);
  plotnum = 0;  
  setVerbose(false);
  setDelayTime(0);
}

SAPlotter::SAPlotter(unsigned long int xdim, unsigned long int ydim, unsigned long int zdim){
  setDimensions(xdim, ydim, zdim);
  tempstring = "sa_plot_";
  setFilenameBase(tempstring.c_str());
  plotfilename = filenamebase;
  interactive = false;
  setPlotTitle(plotfilename);
  plotnum = 0;
  setDelayTime(0);
  setVerbose(false);
}


SAPlotter::~SAPlotter(){
}
/** No descriptions */
void SAPlotter::plot(){
}
/** No descriptions */
void SAPlotter::print(){
}
/** No descriptions */
void SAPlotter::read(string filename){
}
/** No descriptions */
void SAPlotter::start(){
}
/** No descriptions */
void SAPlotter::stop(){
}
/** No descriptions */
void SAPlotter::setData(int *x, unsigned long int *y, int dim){
  //cout << "SAPlotter::setData() started " << endl;
 int k=0;
 while(k< dim){
   channel[k] = float(x[k]);
   counts[k] =  (unsigned long int)y[k];   
   k++;
 }
}
void SAPlotter::setData(int *x, unsigned long int *y, unsigned long int *z, int dim){
  //cout << "SAPlotter::setData() (3D) started " << endl;
 int k=0;
 while(k< dim){
   channel[k] = float(x[k]);
   counts[k] =  (unsigned long int)y[k];
   depth[k] =  (unsigned long int)z[k];
   k++;
 }
  //cout << "SAPlotter::setData() (3D) ended " << endl;
}
/** No descriptions */
void SAPlotter::setXRange(float xmin, float xmax){
    stringstream ss;
    string cl("set xrange [");
    ss <<  cl << xmin <<":"<< xmax <<"]";
    cl = ss.str();
      if (verbose) cout << "executing " << cl << endl;
      gp.commandln(cl.c_str());
}
/** No descriptions */
void SAPlotter::setYRange(long int ymin, long int ymax){
    stringstream ss;
    string cl("set yrange [");
    ss <<  cl << ymin <<":"<< ymax <<"]";
    cl = ss.str();
    gp.commandln(cl.c_str());
    if (verbose) cout << "executing " << cl << endl;
}
/** No descriptions */
void SAPlotter::setZRange(long int zmin, long int zmax){
    stringstream ss;
    string cl("set zrange [");
    ss <<  cl << zmin <<":"<< zmax <<"]";
    cl = ss.str();
    gp.commandln(cl.c_str());
    if (verbose) cout << "executing " << cl << endl;
}
/** No descriptions */
void SAPlotter::setZSize(unsigned long int zs){
  depth.resize(zs);
}
/** No descriptions */
void SAPlotter::setXSize(unsigned long int xs){
  channel.resize(xs);
}
/** No descriptions */
void SAPlotter::setYSize(unsigned long int ys){
  counts.resize(ys);
}
/** No descriptions */
void SAPlotter::save(){
    string cl("save \"");
    stringstream s;  s << plotnum;
    cl +=filenamebase+s.str();  cl +=".plt";cl +="\" ";
    gp.commandln(cl.c_str());  
}
/** No descriptions */
void SAPlotter::load(const string &filename){
    plotfilename = filename;
    string cl("load ");
    cl += filename;
      gp.begin_data();
  float temp_chan; long int temp_counts;
  for(int k=0; k<x_size; k++){
      temp_chan = channel[k];  temp_counts = counts[k];
      gp.commandln("%e %d", temp_chan,   temp_counts);
  }
  gp.end_data();
  gp.commandln(cl.c_str());
}
/** No descriptions */
//void SAPlotter::setData(float *x, unsigned long int *y, long int dim){
//  cout << "SAPlotter::setData(float *, unsigned long int *, long int) started " << endl;
// int k=0;
// while(k< dim){
//   channel[k] = float(x[k]);
//   counts[k] =  (unsigned long int)y[k];
//   k++;
// }
//  cout << "SAPlotter::setData(float *, unsigned long int *, long int) ended " << endl;
//}
/** No descriptions */
void SAPlotter::setData(int *x, unsigned long int *y,  unsigned long int *z, unsigned long int dim){
  if (verbose) cout << "SAPlotter::setData() started " << endl;
 int k=0;
 while(k< dim){
   channel[k] = float(x[k]);
   counts[k] =  (unsigned long int)y[k];
   depth[k] =  (unsigned long int)z[k];   
   k++;
 }
  if (verbose) cout << "SAPlotter::setData() ended " << endl;  
}
/** No descriptions */
void SAPlotter::init(){
	string t("post");
	setTerm(t);
	tempstring = "plots"; setPlotType(tempstring);
}
void SAPlotter::setDimensions(unsigned long int xdim, unsigned long int ydim){
  x_size = xdim;
  y_size = ydim;
  channel.resize(x_size);
  counts.resize(y_size);
  plotdim = xdim;
}
/** No descriptions */
void SAPlotter::setDimensions(unsigned long int xdim, unsigned long int ydim, unsigned long int zdim){
  x_size = xdim;
  y_size = ydim;
  z_size = zdim;
  channel.resize(x_size);
  counts.resize(y_size);
  depth.resize(z_size);
  plotdim = xdim;
}
/** No descriptions */
void SAPlotter::setInteractive(bool val){
  interactive = val;
}
/** No descriptions */
void SAPlotter::setFilenameBase(const string & fnb){
  filenamebase = fnb;
}
/** No descriptions */
void SAPlotter::save(const string &filename){
    if (verbose) cout << "SAPlotter::save(const string &filename) started"<< endl;
    string cl("save \"");
    cl +=filename;  cl +="\" ";
    string hl("plot \"");
    hl += "dati_gp.dat"; hl += "\" w l";
    if (verbose) cout << "going to exec " << hl.c_str() << endl;
    gp.commandln(hl.c_str());
    if (verbose) cout << "going to exec " << cl.c_str() << endl;
    string c = getPauseCommand();    gp.commandln(c.c_str());    
    gp.commandln(cl.c_str());
    if (verbose) cout << "SAPlotter::save(const string &filename) ended"<< endl;
}
/** No descriptions */
void SAPlotter::setDelayTime(int secs){
  dtime = secs;
}
/** No descriptions */
string SAPlotter::getPauseCommand(){
  stringstream ss;
  ss << "pause " << dtime;
  tempstring = ss.str();
  return tempstring;
}
/** No descriptions */
void SAPlotter::setPlotTitle(const string &title){
  plottitle = title;
}
/** No descriptions */
void SAPlotter::setPlotSetDir(const string &psd){
  plotsetdir = psd;
}
/** No descriptions */
void SAPlotter::createPlotSetDir(){
  if (verbose) cout << "SAPlotter::createPlotSetDir() creating dir "<< plotsetdir << endl;
  stringstream ss2;  string s2;
  ss2 << "mkdir " << plotsetdir;
  s2 = ss2.str();  system(s2.c_str());
  createPlotSetSubDirs(plotsetdir);
}
/** No descriptions */
void SAPlotter::setDescription(const string &dsc){
   description = dsc;
}
/** No descriptions */
string SAPlotter::getPlotSetDir(){
  return plotsetdir;
}
/** No descriptions */
void SAPlotter::incrementPlotSetCtr(){
  plotsetctr++;
}
/** No descriptions */
int SAPlotter::getPlotSetCtr(){
  return plotsetctr;
}
/** No descriptions */
void SAPlotter::setPlotSetCtr(int psc){
  plotsetctr = psc;
}
/** No descriptions */
void SAPlotter::fixPlotSetDir(){
}
/** No descriptions */
void SAPlotter::incrementPlotCounter(){
  plotnum++;
}
/** No descriptions */
void SAPlotter::setPlotCounter(int p){
  plotnum = p;
}
/** No descriptions */
void SAPlotter::setPoint(double x, unsigned long int y, unsigned long int z){
}
}/** No descriptions */
void Graphics::SAPlotter::setVerbose(bool bval){
  verbose =  bval;
}


/*!
    \fn Graphics::SAPlotter::setTerm(const string &ts)
 */
void Graphics::SAPlotter::setTerm(const string &ts)
{
    term = ts;
}


/*!
    \fn Graphics::SAPlotter::getTerm()
 */
string Graphics::SAPlotter::getTerm()
{
    return term;
}


/*!
    \fn Graphics::SAPlotter::getExtension()
 */
string Graphics::SAPlotter::getExtension()
{
	if (term == "png") {
		tempstring = ".png";
	} else tempstring = ".ps";
	return tempstring;	
}


/*!
    \fn Graphics::SAPlotter::createPlotSetSubdirs()
 */
void Graphics::SAPlotter::createPlotSetSubDirs(const string &dirname)
{
    tempstring = "MDImg";createPlotSetSubDir(dirname, tempstring);
    tempstring = "DetImg";createPlotSetSubDir(dirname, tempstring);
    tempstring = "Pointing";createPlotSetSubDir(dirname, tempstring);
    tempstring = "ASCII";createPlotSetSubDir(dirname, tempstring);
}


/*!
    \fn Graphics::SAPlotter::createPlotSetSubDir(const string &dirname)
 */
void Graphics::SAPlotter::createPlotSetSubDir(const string &dirname, const string &subdirname)
{
  stringstream ss2;	ss2.str("");ss2 << "mkdir " << dirname << "/"<< subdirname;
  string s2 = ss2.str();  system(s2.c_str());
}


/*!
    \fn Graphics::SAPlotter::getDirPath(const string &subdir)
	return directory path for a plot subset in the plot set directory
 */
string Graphics::SAPlotter::getDirPath(const string &subdir)
{
    tempstring = getPlotSetDir() + "/" + subdir ;
	return tempstring;
}


/*!
    \fn Graphics::SAPlotter::setPlotType(const string &pt)
 */
void Graphics::SAPlotter::setPlotType(const string &pt)
{
    pts = pt;
}


/*!
    \fn Graphics::SAPlotter::getPlotSubsetDir()
 */
string Graphics::SAPlotter::getPlotSubsetDir()
{
    return getDirPath(pts);
}
