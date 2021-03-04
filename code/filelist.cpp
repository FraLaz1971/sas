/***************************************************************************
                          filelist.cpp  -  description
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

#include "filelist.h"

namespace System{
  
FileList::FileList(){
  
}
FileList::FileList(string shellcommand){
    vector<string> tempv = mysyscon.dumpCommand(shellcommand);
    vector<string>::iterator vit;
    myit = begin();  vit = tempv.begin();
    while(vit!=tempv.end()){
       push_back(*vit++);
    }
}
FileList::~FileList(){
}

}
void System::FileList::changeBodytoAll(string newbody){
}

/** No descriptions */
void System::FileList::show(){
  myit = begin();
  while(myit!=end()){
    cout << "FileList::show() " << *myit++<< endl;
  }
}
