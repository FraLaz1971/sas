/***************************************************************************
                          sadataset.cpp  -  description
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

#include "sadataset.h"
namespace SAdata{
SADataSet::SADataSet(){
  setDefault();
}
SADataSet::~SADataSet(){
}
}/** No descriptions */
void SAdata::SADataSet::saveASCII(){
    ofstream noutfile;
    noutfile.exceptions ( ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        noutfile.open (outfilename.c_str(), ofstream::out | ofstream::trunc);
        // write here        // noutfile << dn << endl;
        noutfile.close();
      } // close try
      catch (ofstream::failure e) {
         cout <<"Exception opening/writing file"<< endl;
      }
}
/** No descriptions */
void SAdata::SADataSet::setOutFilename(const string &dfn){
  outfilename = dfn;
}
/** No descriptions */
void SAdata::SADataSet::setDefault(){
  verbose = false;
  time_t timer;
  outfilename = (string)asctime(localtime(&timer))+"_SA.dat";
}
/** No descriptions */
void SAdata::SADataSet::init(){
}
