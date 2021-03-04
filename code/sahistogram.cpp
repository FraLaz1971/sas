/***************************************************************************
                          sahistogram.cpp  -  description
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

#include "sahistogram.h"
namespace SAdata{
SAHistogram::SAHistogram(){
}
SAHistogram::SAHistogram(double low, double high, double width){
}
SAHistogram::~SAHistogram(){
}
}/** No descriptions */
void SAdata::SAHistogram::saveGnuPlot(const string &filename){
    ofstream noutfile;
    string fn;
    noutfile.exceptions ( ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
                fn = "dati_gp.dat";
                noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
                printBuckets(noutfile);
                noutfile.close();
            } // close try
      catch (ofstream::failure e) {
         cout <<"Exception opening/writing file"<< endl;
      }

}
/** No descriptions */
void SAdata::SAHistogram::loadBucket(unsigned long int bnum, float chanval, long int cnts){
  try{
      channel[bnum] = chanval;
      counts[bnum] = cnts;
  } catch (const exception& e) {
      cout << "thrown exception "<< e.what() << endl;    
  }
}
