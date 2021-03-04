/***************************************************************************
                          fitsfile.h  -  description
                             -------------------
    begin                : Fri May 12 2006
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

#ifndef FITSFILE_H
#define FITSFILE_H
#include <CCfits>
#include <cmath>
   using namespace CCfits;
   using std::valarray;
/**
  *@author Francesco Lazzarotto
  */

class FitsFile {
public: 
	FitsFile();
	~FitsFile();
    int writeImage();
    int writeAscii();
    int writeBinary();
    int copyHDU();
    int selectRows();
    int readHeader();
    int readImage();
    int readTable();

};

#endif
