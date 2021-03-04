/***************************************************************************
                          saparameter.cpp  -  description
                             -------------------
    begin                : Mon May 8 2006
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

#include "saparameter.h"
namespace SApipeline{
SAParameter::SAParameter(){
}
SAParameter::SAParameter(const string &parandval){
  setTotalString(parandval);  
}

SAParameter::SAParameter(const SAParameter &par){
  description = par.description;
  value = par.value;
}
SAParameter::~SAParameter(){
}
}/** No descriptions */
void SApipeline::SAParameter::setDescription(const string &des){
  description = des;
}
/** No descriptions */
void SApipeline::SAParameter::setValue(const string &parval){
  value = parval;
}
/** No descriptions */
 string SApipeline::SAParameter::getDescription() const{
  return description;
}
/** No descriptions */
string SApipeline::SAParameter::getValue() const {
  return value;
}
/** No descriptions */
void SApipeline::SAParameter::setTotalString(const string &parandval){
    // parname=parval
  string parnam, parval;
  int p;
  p = parandval.find_first_of("=");
  parnam =  parandval.substr(0, p);
  if (verbose) cout << "SAParameter::setTotalString() parameter description = " << parnam << endl;
  parval =  parandval.substr(p+1, -1);
  if (verbose) cout << "SAParameter::setTotalString() parameter value =" << parval << endl;
  setDescription(parnam);
  setValue(parval);
}
