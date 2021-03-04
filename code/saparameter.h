/***************************************************************************
                          saparameter.h  -  description
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

#ifndef SAPARAMETER_H
#define SAPARAMETER_H

#include <utility>
#include <iostream>
#include <string>
#include "hertagbase.h"


/**
  *@author Francesco Lazzarotto
  */
using namespace std;

namespace SApipeline{
class SAParameter : public pair<string, string>, public HertagBase  {
public: 
  SAParameter();

  SAParameter(const string &parandval);

  SAParameter(const SAParameter &par);

  ~SAParameter();
  
  /** No descriptions */
  string getValue() const;
  /** No descriptions */
  string getDescription() const;
  /** No descriptions */
  void setValue(const string &parval);
  /** No descriptions */
  void setDescription(const string &des);
  /** No descriptions */
  void setTotalString(const string &parandval);
    private:
  string description;
  string value; 
};
}
#endif
