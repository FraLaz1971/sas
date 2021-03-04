/***************************************************************************
                          saplotter.h  -  description
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

#ifndef SAPLOTTER_H
#define SAPLOTTER_H


/**
  *@author Francesco Lazzarotto
  */
#include "gnuplot_base.h"
#include "gnuplot_pipe.h"
#include "gnuplot_tmpfile.h"
#include "sadefinitions.h"
#include "archivehandler.h"
#include <string>
#include <sstream>
#include <vector>


using namespace std;
using namespace SAarchive;
namespace Graphics  {
  
using namespace Graphics;

class SAPlotter {
public: 
	SAPlotter();

  SAPlotter(unsigned long int xdim, unsigned long int ydim);
  
  SAPlotter(unsigned long int xdim, unsigned long int ydim, unsigned long int zdim);
  
	~SAPlotter();
  /** No descriptions */
  virtual void stop();
  /** No descriptions */
  virtual void start();
  /** No descriptions */
  virtual void read(string filename);
  /** No descriptions */
  virtual void print();
  /** No descriptions */
  virtual void plot();
  /** No descriptions */
  void setData(int *x, unsigned long int *y,  unsigned long int *z, unsigned long int dim);
  /** No descriptions */
  void setData(int *x, unsigned long int *y, int dim);
  /** No descriptions */
  void setData(int *x, unsigned long int *y, unsigned long int *z, int dim);
  /** No descriptions */
  void setYRange(long int ymin, long int ymax);
  /** No descriptions */
  void setXRange(float xmin, float xmax);
  /** No descriptions */
  void setZRange(long int zmin, long int zmax);
  /** No descriptions */
  void setYSize(unsigned long int ys);
  /** No descriptions */
  void setXSize(unsigned long int xs);
  /** No descriptions */
  void setZSize(unsigned long int zs);
  /** No descriptions */
  void load(const string &filename);
  /** No descriptions */
  void save();
  /** No descriptions */
//  void setData(double *x, unsigned long int *y, unsigned long int dim);
//  /** No descriptions */
//  void setData(float *x, unsigned long int *y, long int dim);
  /** No descriptions */
//  void setData(float *x, unsigned long int *y, long int dim);
  /** No descriptions */
  void setDimensions(unsigned long int xdim, unsigned long int ydim);
  /** No descriptions */
  void setDimensions(unsigned long int xdim, unsigned long int ydim, unsigned long int zdim);
  /** No descriptions */
  virtual void init();
  /** No descriptions */
  void setInteractive(bool val);
  /** No descriptions */
  void setFilenameBase(const string & fnb);
  /** No descriptions */
  void save(const string &filename);
  /** No descriptions */
  void setDelayTime(int secs);
  /** No descriptions */
  string getPauseCommand();
  /** No descriptions */
  void setPlotTitle(const string &title);
  /** No descriptions */
  void createPlotSetDir();
  /** No descriptions */
  void setPlotSetDir(const string &psd);
  /** No descriptions */
  virtual void setDescription(const string &dsc);
  /** No descriptions */
  void incrementPlotSetCtr();
  /** No descriptions */
  string getPlotSetDir();
  /** No descriptions */
  int getPlotSetCtr();
  /** No descriptions */
  void setPlotSetCtr(int psc);
  /** No descriptions */
  void fixPlotSetDir();
  /** No descriptions */
  void incrementPlotCounter();
  /** No descriptions */
  void setPlotCounter(int p);
  /** No descriptions */
  void setPoint(double x, unsigned long int y, unsigned long int z);
  /** No descriptions */
  void setVerbose(bool bval);
    string getTerm();
    void setTerm(const string &ts);
    string getExtension();
    void createPlotSetSubDir(const string &dirname, const string &subdirname);
    void createPlotSetSubDirs(const string &dirname);
    string getDirPath(const string &subdir);
    void setPlotType(const string &pt);
    string getPlotSubsetDir();
  protected:
  /** No descriptions */
  Gnuplot_Tmpfile gp;
  /** No descriptions */
  vector<float> channel;
  /** No descriptions */
  vector<long int> counts;
  /** No descriptions */
  vector<long int> depth;
  /** size of the x axis vector */
  unsigned long int x_size;
  /** size of the y axis vector */
  unsigned long int y_size;
  /** size of the z axis vector */
  unsigned long int z_size;
  /** No descriptions */
  string plotfilename;
  /** No descriptions */
  string filenamebase;
  /** No descriptions */
  string tempstring;  
  /** No descriptions */
  string plottitle;
  /** No descriptions */
  string plotsetdir;    
  /** No descriptions */
  bool interactive;  
  /** delay time before closing the plotter (seconds) */
  int dtime;  
  /** */
  bool verbose;
  /** */
  unsigned long int plotdim;
  /** */
  string description;  
  /** term to print out on*/
  string term;

  public:
  /** No descriptions */
  int plotnum;
  /** No descriptions */
  static int plotsetctr;
  /** archive handler pointer */
  ArchiveHandler *myarc;
	/** */
  string pts; // plot type string 
};

}
#endif
