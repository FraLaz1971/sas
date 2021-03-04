/***************************************************************************
                          sal3event.cpp  -  description
                             -------------------
    begin                : Wed Jun 21 2006
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

#include "saephemerisdata.h"
namespace SAdata{
SAEphemerisData::SAEphemerisData(){
}


SAEphemerisData::~SAEphemerisData(){
try{
	closeInputFile();
} catch (const SAexception &se){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing input file" << se.getMsg() << endl;
} catch (const exception &e){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing input file " << e.what() << endl;
} catch (...){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing input file " <<  endl;
}
try{
  closeOutputFile();
  } catch (const SAexception &se){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing output file " << se.getMsg() << endl;
} catch (const exception &e){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing output file " << e.what() << endl;
} catch (...){
cerr << "SAEphemerisData::~SAEphemerisData() error in closing output file " <<  endl;
}
}

SAEphemerisData::SAEphemerisData(const string &mifn): SAFitsHandler(mifn){
  cout << "SAEphemerisData() inputfile " << mifn << endl;
  openInputFile();
  //report();
}
/*
SAEphemerisData::report(){
}
*/
}
