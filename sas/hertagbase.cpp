/***************************************************************************
                          hertagbase.cpp  -  description
                             -------------------
    begin                : Wed Oct 11 2006
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

#include "hertagbase.h"

HertagBase::HertagBase(){
  verbose = false;
}
HertagBase::~HertagBase(){
}
/** No descriptions */
int HertagBase::process(){
}
/** No descriptions */
void HertagBase::test(){
}
void HertagBase::report(){
}
/** No descriptions */
void HertagBase::setVerbose(bool v){
  verbose = v;
}
/** No descriptions */
void HertagBase::setEnvVar(const string &varname, const string &varvalue, int overwrite){
  int erval;
  try{
      if( setenv(varname.c_str(), varvalue.c_str(), overwrite)) throw e;      
  } catch(const exception &e){
    cout << "HertagBase::setEnvVar() error in setting the environment variable" << endl; 
  }
}                                                                                                          
/** No descriptions */
void HertagBase::exportEnvVar(const string &varname, const string &varvalue){
  ofstream of;  string fn;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
            fn = "exportvar.sh";
            of.open (fn.c_str(), ofstream::out | ofstream::trunc);
            of << "#!/bin/sh" << endl;
            of << "echo export "+varname+"="+varvalue << endl;
            of << "export "+varname+"="+varvalue;
            of.close();
      } catch (ofstream::failure e)      {
        cout << "HertagBase::exportEnvVar() error writing export var bash script file"<< endl;
      }
     system("./exportvar.sh");
     system(". exportvar.sh");
}


/*!
    \fn HertagBase::showAlert()
 */
void HertagBase::showAlert()
{
  for (i=0;i<20; i++ ){
    cout << "##############################################"<< endl;
  }
}

/*!
    \fn HertagBase::showAlert()
 */
void HertagBase::showAlert(int nr, const string &c)
{
    for (i=0;i<nr; i++ ){
    cout << "##############################################"<< endl;
    }
    cout << "#   "<< c << endl;
    for (i=0;i<nr; i++ ){
	cout << "##############################################"<< endl;
    }
  }
/** returns a vector of strings each element of the vector containing a word of the
line */
void HertagBase::tokenizeLine(const string &linestring, vector<string> *restoken){
  int b = linestring.size(); int h=0;  string currentstring(linestring), token("");
  int csp=0; // current delimitator (space) position
   stringstream ss;
   try{
  while (currentstring.size()>0){
    if (verbose) cout << "currentstring =  " << currentstring << endl;
    if (verbose) cout << "currentstring.find_first_of(" ") =  " << currentstring.find_first_of(" ") << endl;
    if (verbose) cout << "string::npos =  " << string::npos << endl;
    token = currentstring.substr(0, currentstring.find_first_of(" "));
    if  (currentstring.find_first_of(" ") == string::npos){
          currentstring = "" ;
    } else {
      currentstring = currentstring.substr(currentstring.find_first_of(" ")+1);
      currentstring = currentstring.substr(currentstring.find_first_not_of(" "));
    }
    if (verbose) cout << "currentstring =  " << currentstring << endl;    
    if (verbose) cout << "HertagBase::tokenizeLine() read " << token << endl;
    restoken->push_back(token);

  }                                                                                        
  vector<string>::iterator stit = restoken->begin();
  if (verbose)  {
      while(stit !=  restoken->end()){
        cout << "token n. " <<  stit - restoken->begin() << " value = " << *stit++ << endl;
      }
  }
            } catch (const exception &e) {
            cerr<< "HertagBase::tokenizeLine() Exception tokenizing the line"<< e.what() << endl;
          } 
}
