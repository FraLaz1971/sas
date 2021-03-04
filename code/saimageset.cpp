/***************************************************************************
                          saimageset.cpp  -  description
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

#include "saimageset.h"
namespace SAdata{
SAImageSet::SAImageSet(){
}
SAImageSet::~SAImageSet(){
}
/** No descriptions */
void SAImageSet::fill(SADetImage img){
  imgset.push_back(img);
}
}/** No descriptions */
void SAdata::SAImageSet::show(){
}
/** No descriptions */
SAdata::SADetImage SAdata::SAImageSet::getImage(int detnum){
}

void SAdata::SAImageSet::setImage(SAdata::SADetImage img, int detnum){
   imgset[detnum] =  img;
}
