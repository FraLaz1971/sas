/***************************************************************************
                          sahistogram.h  -  description
                             -------------------
    begin                : Thu Jul 27 2006
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

#ifndef SAHISTOGRAM_H
#define SAHISTOGRAM_H

#include "SmplHist.h"
#include "sadataset.h"
#include "saplotter.h"

/**
  *@author Francesco Lazzarotto
  */

/**
  *@author Francesco Lazzarotto
  */
namespace SAdata{

using namespace SAdata;
using namespace Graphics;
using namespace std;

class SAHistogram : public SampleHistogram, public SADataSet  {
public: 
  /** No descriptions */
	SAHistogram();
  /** No descriptions */
	SAHistogram(double low, double high, double width);
  /** No descriptions */
	~SAHistogram();
  /** No descriptions */
  void saveGnuPlot(const string &filename);
  /** No descriptions */
  void loadBucket(unsigned long int bnum, float chanval, long int cnts);
protected:

  vector<float> channel;
  /** No descriptions */
  vector<long int> counts;

};

}
#endif
