/***************************************************************************
                          sapointhistosplotter.h  -  description
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

#ifndef SAPOINTHISTOSPLOTTER_H
#define SAPOINTHISTOSPLOTTER_H

#include "saplotter.h"
#include "gnuplot_base.h"
#include "gnuplot_pipe.h"
#include "gnuplot_tmpfile.h"

#include <string>
#include <sstream>
#include <vector>

/**plots pointing histogram from
IrosMap created by SA L3 EventList
  *@author Francesco Lazzarotto
  */
namespace Graphics  {

using namespace Graphics;

class SAPointHistosPlotter : public SAPlotter  {
public: 
	SAPointHistosPlotter();
	~SAPointHistosPlotter();
  /** No descriptions */
  void plot();
  /** No descriptions */
  void init();
  /** No descriptions */
  void stop();
  /** No descriptions */
  void start();
  /** No descriptions */
  void setData(vector<int> x, vector<unsigned long int> y, int dim);
  /** No descriptions */
  void showData();
  /** No descriptions */
  void setAxes(char ax);
  /** No descriptions */
  void save();
  /** No descriptions */
  void print();
  /** No descriptions */
  void plotLoaded();
  /** No descriptions */
  void setDescription(const string &dsc);
    void print(const string &pd);
protected:

  char  axes;

};
}
#endif
