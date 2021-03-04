/***************************************************************************
                          sasoacommand.cpp  -  description
                             -------------------
    begin                : Fri Mar 31 2006
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
#include "sasoacommand.h"

namespace SApipeline{
SasoaCommand::SasoaCommand(){
  description = "parametro";
  value  = "1";
}
/** Copy constructor*/
SasoaCommand::SasoaCommand(const SasoaCommand & parameter ){
  value = parameter.value;
  description = parameter.description;
}
//SasoaCommand::=
SasoaCommand::~SasoaCommand(){
}
/** return value of the parameter */
string SasoaCommand::getValue(){
  return value;
}

string SApipeline::SasoaCommand::getDescription(){
  return description;
}
/** write on screen the parameter */
void SApipeline::SasoaCommand::print(){
  cout  << "| " << " description = "<< description << "| |" <<  " value = " << value <<"| "  <<  endl;

}

}// END NAMESPACE/** No descriptions */
void SApipeline::SasoaCommand::setValue(string val){
  value = val;
}
/** No descriptions */
void SApipeline::SasoaCommand::setDescription(string des){
  description = des;
}
