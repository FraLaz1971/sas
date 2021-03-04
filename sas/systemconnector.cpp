/***************************************************************************
                          systemconnector.cpp  -  description
                             -------------------
    begin                : Fri Mar 30 2007
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

#include "systemconnector.h"
namespace System {
SystemConnector::SystemConnector(){
  shell = false;
  verbose = false;
}
SystemConnector::~SystemConnector(){
}
}/** No descriptions */
string System::SystemConnector::getEnvVar(const string & evn){
    tempstring.clear();
    if (verbose) cout << "SystemConnector::getEnvVar() getting value of " << evn << endl;
    if(shell){      
      saveEnvVar(evn);
      tempstring = retrieveEnvVar();
    } else {
      t  =  evn.c_str();
      ee = getenv(t);
      tempstring.assign((const char *) ee);      
    }
    return  tempstring;
}

void System::SystemConnector::setEnvVar(const string & evn, const string &vv, int ow){
  //HertagBase::setEnvVar(evn);
}
  
void System::SystemConnector::exportEnvVar(const string & evn, const string &vv){
   //HertagBase::exportEnvVar(evn);

}
  /** No descriptions */
void System::SystemConnector::test(){
  if (shell){
    int    Count; char   *Line;
    while(Line = *(environ+Count))
    {
      printf("%s \n", Line);
      Count++;
    }
}
  
}
/** No descriptions */
void System::SystemConnector::setShellMode(bool sm){
  shell = sm;
}
/** No descriptions */
void System::SystemConnector::saveEnvVar(const string &evn){
      ofstream of;  string fn;
      of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
            system("touch def/envarval.txt");
            fn = "getenvar.sh";
            of.open (fn.c_str(), ofstream::out | ofstream::trunc);
            of << "#!/bin/sh" << endl;
            of << "echo ---> This is a Bash shell script !" << endl;            
            of << "echo executing \"echo $"+evn+">"+" def/envarval.txt \"" << endl;
            of << "echo $"+evn+"> def/envarval.txt";
            of.close();
      } catch (ofstream::failure e)      {
        cout << "HertagBase::exportEnvVar() error writing export var bash script file"<< endl;
      }
     string temps("./getenvar.sh");
     execCommand(temps);
}
/** No descriptions */
string System::SystemConnector::retrieveEnvVar(){
     if (verbose) cout << "Started execution of SystemConnector::retrieveEnvVar()" << endl;
    ifstream ninfile;
    string fn;
    char buf[256]; // read lines of maximun 256 characters
    int mlinelen = 256;
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        fn = "def/envarval.txt";
        ninfile.open (fn.c_str(), ifstream::in);
        if (verbose) cout << "il file e' aperto, dovrei leggere ..." << endl;
        ninfile.getline(buf, mlinelen) ;
        ss << buf;
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      } catch (const exception &e) {
         if (verbose) cout << "Exception opening/writing file"<< e.what() << endl;
      } catch (...) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }

     if (verbose) cout << "Finished execution of SystemConnector::retrieveEnvVar()" << endl;  
  return ss.str();
}
/** No descriptions */
void System::SystemConnector::execCommand(const string &c){
  if (verbose) cout << "SystemConnector::execCommand() executing command " << c << endl;
  system(c.c_str());
}
/** exec system (i.e. unix shell)  command and return as result an array of strings */
vector<string> System::SystemConnector::dumpCommand(const string &c){
  try{
    tempstring1 = ".myfile.txt";
    saveCommandResult(c, tempstring1);
    results1 = getCommandResult(tempstring1);
  } catch (...){
    cerr << "SystemConnector::dumpCommand() exception caught! " << endl;
    
  }
  return results1;
}
/** No descriptions */                             
void System::SystemConnector::saveCommandResult(const string &command, const string &dumpfile){
    tempstring2 = command + " > "+dumpfile;
    execCommand(tempstring2.c_str());
}

/** No descriptions */
vector<string> System::SystemConnector::getCommandResult(const string &dumpfile){
    results.clear();
    if (verbose) cout << "Started execution of SystemConnector::getCommandResult()" << endl;
    if (verbose) cout << "SystemConnector::getCommandResult() going to open filename " << dumpfile << endl;
    ifstream ninfile;
    string fn;
    ninfile.exceptions (ifstream::failbit | ifstream::badbit );
      try {
        fn = dumpfile;                                
        ninfile.open (fn.c_str(), ifstream::in);
        if (verbose) cout << "SystemConnector::getCommandResult() the file is open, i should read ..." << endl;
        i = 0;        b = 0;
        if (verbose) cout << "SystemConnector::getCommandResult() ifstream::eofbit = "<< ifstream::eofbit << endl;
        while(!ninfile.eof()){
          ninfile >> tempstring;
          results.push_back(tempstring);
           if (verbose) cout << "SystemConnector::getCommandResult() ninfile.eof() = " << ninfile.eof() << endl;
           if (verbose) cout << "SystemConnector::getCommandResult() output = "<< tempstring << endl;
           if  (ninfile.eof()) break;
        }
     } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      } catch (const exception &e) {
         if (verbose) cout << "Exception opening/writing file"<< e.what() << endl;
      } catch (...) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }
     if (verbose) cout << "Finished execution of SystemConnector::getCommandResult() " << endl;

        if (verbose) cout << "SystemConnector::getCommandResult() going to return ...." << endl;
  return results;  
}
/** No descriptions */
void System::SystemConnector::testCommand(){
    string tt("ls .");
    results = dumpCommand(tt);
      vector<string>::iterator it;
      it = results.begin();
      i = 0;
    while (it!=results.end()){
         cout << "SystemConnector::test() read results ["<< i++ << "] = " << *it++ << endl;
  }

}
