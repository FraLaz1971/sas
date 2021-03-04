/***************************************************************************
                          saimageset.h  -  description
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

#ifndef SAIMAGESET_H
#define SAIMAGESET_H

#include <sadataset.h>
#include "sadetimage.h"
#include <vector>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
/**
  *@author Francesco Lazzarotto
  */
namespace SAdata{

using namespace std;
using namespace SAdata;

class SAImageSet : public SADataSet  {
public: 
	SAImageSet();
	~SAImageSet();
  /** No descriptions */
  void fill(SADetImage img);
  /** No descriptions */
  void setImage(SADetImage img, int detnum);
  /** No descriptions */
  void show();
  /** No descriptions */
  SAdata::SADetImage getImage(int detnum);
private:

vector<SADetImage> imgset;

};
}
#endif
