/***************************************************************************
                          sadetimage.h  -  description
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

#ifndef SADETIMAGE_H
#define SADETIMAGE_H


/**
  *@author Francesco Lazzarotto
  */
#include "sadataset.h"
#include "sahistogram.h"

namespace SAdata{
class SADetImage: public SAHistogram {
public: 
	SADetImage();
	~SADetImage();
  /** No descriptions */
  void load(const SADetImage &simg);
  /** No descriptions */
  bool operator< (const SADetImage &sdi);
private:

byte detid;



};
}
#endif
