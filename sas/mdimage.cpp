/***************************************************************************
                          mdimage.cpp  -  description
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

#include "mdimage.h"
namespace SAdata{

MDImage::MDImage(){
}

MDImage::~MDImage(){
}

}/** No descriptions */
void SAdata::MDImage::plot(){
}
/** No descriptions */
void SAdata::MDImage::crateDirTree(){
  stringstream ss;
  string s("mkdir ../stg_2/IROS_Multi-D/images/");
  string comm("mkdir ");
  system(s.c_str());
  i = 0;
  while(i<NREGVAL){
    ss << "../stg_2/IROS_Multi-D/images/reg"<<i;
    stvec.push_back(ss.str());
    cout << "MDImage::crateDirTree() "<< ss.str() << endl;
    system((comm+stvec[i]).c_str());  
    i++;
  }  
}
/** SA Multi Detector Image */
void SAdata::MDImage::setPoint(int a, int b, int c, long int val){
    mdi[a][b][c] = val;
}
