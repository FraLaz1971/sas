/***************************************************************************
                          sagti  -  description
                             -------------------
    begin                : mer giu 13 2007
    copyright            : (C) 2007 by Francesco Lazzarotto
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
#ifndef SADATASAGTI_H
#define SADATASAGTI_H

#include <utility>
#include <vector>
#include <string>
#include "safitshandler.h"

using namespace std;
using namespace SApipeline;


namespace SAdata  {

/**
	@author Francesco Lazzarotto <lazza@rm.iasf.cnr.it>
*/


class SAGTI: public vector<GTI>, public SAFitsHandler {

public:

    SAGTI();

    ~SAGTI();

    void read(const string &gtifile);

    void save(const string &gtifile);
    double getDistance(GTI g);

protected: 
	vector<GTI>::iterator gticur;
      GTI tempgti;
	long int nrows;
	long int ij, ii;

   int hdunum,  nfound, anynull;
    int frow, felem, nelem, longnull;
    float floatnull;
    double Doublenull;

};


}

#endif
