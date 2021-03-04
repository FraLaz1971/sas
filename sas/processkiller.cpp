/***************************************************************************
                          processkiller.cpp  -  description
                             -------------------
    begin                : Wed Oct 18 2006
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

#include "processkiller.h"

ProcessKiller::ProcessKiller(){
  cout << "ProcessKiller()" << endl;
  pname = "";
}
ProcessKiller::ProcessKiller(const string &pn){
    cout << "ProcessKiller() " << pn << endl;
    pname = pn;
    system("rm out.txt");
    system("mkfifo out.txt");
}

ProcessKiller::~ProcessKiller(){
      system("rm out.txt");
}
/** No descriptions */
vector<int> ProcessKiller::getPIDs(){
  //tempstring = "xterm -e ps -u | grep "+pname+" > out.txt & ";
  tempstring2 = "ps -Alf | grep "+pname+" > out.txt & ";  
  cout << "executing "<< tempstring2 << endl;
   system(tempstring2.c_str());
  // extract pids
  ifstream ifile("out.txt");
  string pp;  
    try{
      getline(ifile, pp);
      cout << pp << endl;
      if (pp.size()>0) substring = pp.substr(9, 9);
      cout << "ProcessKiller::getPIDs() extracted "<< substring << endl;
      pids.push_back(atoi(tempstring.c_str()));
      } catch (const exception &e){
        cerr << "handling exception "<< e.what() << endl;
      }
  while (ifile){
    try{
      getline(ifile, pp);
      cout << pp << endl;
      if (pp.size()>0) substring = pp.substr(9, 9);
      cout << "ProcessKiller::getPIDs() extracted "<< substring << endl;
      pids.push_back(atoi(substring.c_str()));
      } catch (const exception &e){
        cerr << "handling exceptions "<< e.what() << endl;
      }
  }
  return  pids;
}
/** No descriptions */
string ProcessKiller::getProcessName(){
  tempstring = "process to kill unknown";
  if (pname=="") throw logic_error(tempstring);
  return pname;
}
/** No descriptions */
void ProcessKiller::test(){
  vector<int> a = getPIDs();
  vector<int>::iterator ia = a.begin();
  for(ia; ia<a.end(); ia++){
    cout << "ProcessKiller::killProcs() proc num = "<< *ia << endl;
  }
  killall();
}
/** No descriptions */
void ProcessKiller::killall(){
  vector<int>::iterator i = pids.begin();
  for(; i<pids.end(); i++) {
    killProcess(*i);
    }
}
/** No descriptions */
void ProcessKiller::killProcess(int a){
     stringstream ss;  string s;
     ss << a;     s = ss.str();    
     tempstring2  = "kill -9 "+s;
     system(tempstring2.c_str());
}
/** No descriptions */
void ProcessKiller::setProcessName(const string &pn){
   pname = pn;
}
/** No descriptions */
void ProcessKiller::killProcs(){
  vector<int> a = getPIDs();
  vector<int>::iterator ia = a.begin();
  for(ia; ia<a.end(); ia++){
    cout << "ProcessKiller::killProcs() proc num = "<< *ia << endl;
  }
  killall();
}
