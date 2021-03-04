/***************************************************************************
                          sanominalpointing.h  -  description
                             -------------------
    begin                : Tue Jun 20 2006
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

#ifndef SANOMINALPOINTING_H
#define SANOMINALPOINTING_H


/**
  *@author Francesco Lazzarotto
  */
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
namespace SAdata{
using namespace SAdata;

class SANominalPointing {
public: 
	SANominalPointing();
	~SANominalPointing();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  string getRoll();
  /** No descriptions */
  string getDelta();
  /** No descriptions */
  string getAlfa();
  /** No descriptions */
  void setRoll(string rol);
  /** No descriptions */
  void setDelta(string del);
  /** No descriptions */
  void setAlfa(string al);
  /** No descriptions */
  void setCatalogName(const string &cn);
  /** No descriptions */
  void setCatalogDir(const string &cd);
  /** No descriptions */
  string getCatalogName();
  /** No descriptions */
  string getCatalogDir();
  /** No descriptions */
  void write();
private:
string catalog_dir;    ///   ; Catalog repository
string catalog_name; ///  ; Catalog Name
string alfa; /// ; Alfa 2000 in radians
string delta; /// ; Delta 2000 in radians
string roll; /// ; Roll in radians
string outfilename;
};
}
#endif
