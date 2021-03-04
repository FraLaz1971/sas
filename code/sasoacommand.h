/***************************************************************************
                          sasoacommand.h  -  description
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

#ifndef SASOACOMMAND_H
#define SASOACOMMAND_H




#include <string>
#include <iostream>
namespace SApipeline{
  using namespace std;
  /**
    Class implementing a single SA pipeline
    command, composed by a pair
    <description, value>
  *@author Francesco Lazzarotto
  */
class SasoaCommand {
public:
  friend class SasoaCommandList;
  SasoaCommand();
	SasoaCommand(const SasoaCommand & parameter );
	~SasoaCommand();
  /** return value of the parameter */
  string getValue();
  /** write on screen the parameter */
  void print();
  /** No descriptions */
  string getDescription();
  /** No descriptions */
  void setDescription(string des);
  /** No descriptions */
  void setValue(string value);
  private:
  string description;
  string value;
  
};
}
#endif
