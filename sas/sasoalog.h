/***************************************************************************
                          sasoalog.h  -  description
                             -------------------
    begin                : Thu May 11 2006
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

#ifndef SASOALOG_H
#define SASOALOG_H


/**
  *@author Francesco Lazzarotto
  */
#include <string>

using namespace std;
namespace SApipeline{
  using namespace SApipeline;
  
class SasoaLog {
public: 
	SasoaLog();
	~SasoaLog();
  /** No descriptions */
  void setScreen();
  /** No descriptions */
  void setFile(const string &filename);
  /** No descriptions */
  void writeLine(const string &line);
};
}
#endif
