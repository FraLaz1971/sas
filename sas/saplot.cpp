/***************************************************************************
                          saplot.cpp  -  description
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

#include "saplot.h"
namespace Graphics  {

/** No descriptions */
SAPlot::SAPlot(){
  dim = 0;
  limit = 0;
  verbose = false;
}
/** No descriptions */
SAPlot::~SAPlot(){
}

/** No descriptions */
void SAPlot::saveGnuPlot(const string &filename){
verbose = true;
  if (verbose) cout << "SAPlot::saveGnuPlot() started saving on file " << filename << endl;
    ofstream noutfile;
    string fn;
    noutfile.exceptions ( ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
                fn = filename;
                noutfile.open (fn.c_str(), ofstream::out | ofstream::trunc);
                printData(noutfile);
                noutfile.close();
            } // close try
      catch (ofstream::failure e) {
         cerr <<"SAPlot::saveGnuPlot() Exception opening/writing file"<< endl;
      }
      catch (...) {
         cerr <<"SAPlot::saveGnuPlot() Exception opening/writing file"<< endl;
      }
      
      if (verbose) cout << "SAPlot::saveGnuPlot() ended " << endl;
}
/** No descriptions */
void SAPlot::printData(ostream &s){
  if (verbose) cout << "SAPlot::printData() started " << endl;
  for(unsigned long int i = 0; i < dim; i++) {
       s << x[i] << "\t" << y[i] << "\n";
  }
  if (verbose) cout << "SAPlot::printData() ended " << endl;
}
/** No descriptions */
void SAPlot::setDimension(unsigned long int dm){
  dim = dm;
  x.resize(dim);
  y.resize(dim);
}
/** No descriptions */
void SAPlot::printASCIIData(ostream &s){
  if (verbose) cout << "SAPlot::printASCIIData() started " << endl;
  printData(s);
  if (verbose) cout << "SAPlot::printASCIIData() ended " << endl;
}
/** No descriptions */
void SAPlot::setPoint(float xval, long int yval){
  try{
    x[limit] = xval;
    y[limit] = yval;  
    limit++;
  } catch(const exception &e){
    cerr << e.what() << endl;
  }
}
}
