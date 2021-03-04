/***************************************************************************
                          sadataset.h  -  description
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

#ifndef SADATASET_H
#define SADATASET_H


/**
  *@author Francesco Lazzarotto
  */

#define NREGVAL     10
#define  NCHANVAL  1536
#define  HISTSIZVAL  1024

    
#include "sadefinitions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "timer.h"

#include <vector>

namespace SAdata{
  using namespace std;
  using namespace SAdata;
  
class SADataSet {
public: 
	SADataSet();
	~SADataSet();
  /** No descriptions */
  void saveASCII();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  void setOutFilename(const string &dfn);
  /** No descriptions */
  void init();
protected:
    /** */
  string outfilename;
    /** */
    int k;
    /** */
    int i;
    /** */
    int w;
   /** */
    int x;
   /** */
    int y;
   /** */
    int z; 
   /** */
    bool verbose;
    /** */
    bool cond1;
   /** */
    bool cond2;
   /** */
    bool cond3;
   /** */
  Timer tm;
};
}
#endif
