/***************************************************************************
                          filelist.h  -  description
                             -------------------
    begin                : Wed May 9 2007
    copyright            : (C) 2007 by Francesco Lazzarotto
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

#ifndef FILELIST_H
#define FILELIST_H

#include <list>

#include "systemconnector.h"


/**
  *@author Francesco Lazzarotto
  */
namespace System{
  
  using namespace System;
  using namespace std;
  
class FileList : public list<string>, public HertagBase  {
public: 
	FileList();
	FileList(string shellcommand);
	~FileList();
  /** No descriptions */
  /** No descriptions */
  void show();
  void changeBodytoAll(string newbody);

  protected:

  list<string>::iterator myit;

  SystemConnector mysyscon;
};
}
#endif
/** No descriptions */

