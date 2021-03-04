/***************************************************************************
                          saplot.h  -  description
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

#ifndef SAPLOT_H
#define SAPLOT_H


/**
  *@author Francesco Lazzarotto
  */
#include "hertagbase.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

namespace Graphics  {
using namespace Graphics;  
class SAPlot: public HertagBase {
public: 
	SAPlot();
	~SAPlot();
  /** No descriptions */
  void saveGnuPlot(const string &filename);
  /** No descriptions */
  void printData(ostream &s);
  /** No descriptions */
  void setDimension(unsigned long int dm);
  /** No descriptions */
  void printASCIIData(ostream &s);
  /** No descriptions */
  void setPoint(float xval, long int yval);

 protected:

  /** No descriptions */
  vector<float> x;
  /** No descriptions */
  vector<long int> y;
  /** No descriptions */
  unsigned long int dim;
  /** No descriptions */
  unsigned long int limit;  
  /** No descriptions */
  string tempstring;  

};
}
#endif
