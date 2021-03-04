/***************************************************************************
                          mdimage.h  -  description
                             -------------------
    begin                : Mon Jul 31 2006
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

#ifndef MDIMAGE_H
#define MDIMAGE_H

#define NDET     4
#define NREGVAL     10
#define  NCHANVAL  1536
#define  HISTSIZVAL  1024

/**
  *@author Francesco Lazzarotto
  */

#include <cstdlib>
#include "sadataset.h"

namespace SAdata{

using namespace SAdata;
using namespace std;

class MDImage: public SADataSet {
public: 
	MDImage();
	~MDImage();
  /** No descriptions */
  void plot();
  /** No descriptions */
  void crateDirTree();
  /** SA Multi Detector Image */
  void setPoint(int a, int b, int c, long int val);
  protected:

  /** No descriptions */
  long int mdi[NREGVAL][NDET][NCHANVAL];
  /** No descriptions */
  int i;
  /** No descriptions */
  int j;
  /** No descriptions */
  int k;
  /** No descriptions */
  vector <string> stvec;
  /** No descriptions */
//  SAMDImagePlotter mdplotter;  
};
}
#endif
