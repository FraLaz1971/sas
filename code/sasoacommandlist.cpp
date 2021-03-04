/***************************************************************************
                          sasoacommandlist.cpp  -  description
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

#include "sasoacommandlist.h"
namespace SApipeline{

SasoaCommandList::SasoaCommandList(){
  counter1 = 0;
  tempstring = "false";
  setTempDataMode(tempstring);
  tempstring = ".";
  setDefaultInDir(tempstring);
}

SasoaCommandList::SasoaCommandList(string &line){
     if (verbose) cout <<"executing SasoaCommandList ctor" << endl;
     if (verbose) cout <<"SasoaCommandList() input commandline string = " << line << endl;

    // read the substring til the ", " character  [sub]
     int i=0; // count the characters in a substring
     int k=0;  // count the substrings
    string sing, partial, brick;
    vector<string> subs; // substring to decode
    vector<string>::iterator it;
    it = subs.begin();
    string::iterator siter = line.begin();
    bool condition=0;
    while(siter != line.end()){ /// until the end of the string
        i = (siter)-line.begin(); /// position of the character
        sing = *siter;
        siter++;
        if  ((line.substr(i, 1)==(string)",")||(line.substr(i, 1)==(string)";")){
          condition = 1;
           /** now saving in vector of commands */;
          subs.push_back(partial);
          partial.erase(0);
          it++;
        }
        else {
          condition = 0;
          partial.append(sing);
          }
     }
   string instr, val;
   it = subs.begin();
   string sing2;
  int j=0; // count the space at the beginning of the string
   k=0;
     while(it != subs.end()){
     brick = *it;
   // erase space at the beginning of the [instruction value] string
     j=0;
     while (brick.substr(j, 1)==" ") {
        brick = brick.substr(j+1, -1);
        j++;
    }
        /** if (verbose) cout <<" subs["<< it - subs.begin() << "] = " << *it << endl; */
          k = brick.find((string)" ");
        /** if (verbose) cout <<"position of space = " << k << endl; */
        instr = brick.substr(0, k);
        /**       if (verbose) cout <<"instruction = " << instr << endl; */
        parameter.setDescription(instr);
        val = brick.substr(k+1, 1000);
        /** erase whitespace at the beginning*/
        /**        if (verbose) cout <<"argument = " << val << endl;   */
       while (val.substr(j, 1)==" ") {
          val = val.substr(j+1, -1);
          j++;    
        }
          parameter.setValue(val);
          insertCommand(parameter);
        it++;
    }
    // if not outdir command is not present set the default  creating outdir from infile root
    // if infile is not present create a default value
}

SasoaCommandList::~SasoaCommandList(){
}


}
 /** shows the parameters of the command */
void SApipeline::SasoaCommandList::showCommands(){
 map<string, string>::iterator it;
 it=compars_map.begin();
 if (verbose) cout << "SasoaCommandList::showCommands() begin"<< endl;
 while(it!= compars_map.end()){
    cout << it->first << "\t"<< it->second << endl;
    it++;
 }
 if (verbose) cout << "SasoaCommandList::showCommands() end"<< endl;
}
/** No descriptions */
void SApipeline::SasoaCommandList::show(){
  showCommands();
}
/** No descriptions */
void SApipeline::SasoaCommandList::setDescription(int parnum, string des){
}
/** No descriptions */
void SApipeline::SasoaCommandList::setValue(int parnum, int value){
}
/** No descriptions */
void SApipeline::SasoaCommandList::pushCommand(SasoaCommand par){

}
/** method that set a single command into the commandlist */
void SApipeline::SasoaCommandList::insertCommand( SasoaCommand &par){
  string instr = par.getDescription();
  string val = par.getValue();
  compars_map[instr] = val;
}

string SApipeline::SasoaCommandList::getInputFilename(){
  if(!isInputFileSet()){
    cerr << "SasoaCommandList::getInputFilename() WARNING input file is not set "<< endl;
    //throw e;
     string temps1("");
     compars_map["infile"] = temps1;
  }
    item  = compars_map.find("infile");
    tempstring = item->second;
    return tempstring;
}

string SApipeline::SasoaCommandList::getInputdir(){
  if((!isInDirSet())||(compars_map["path"]=="absolute")){
    compars_map["indir"] = "";
  }
    item  = compars_map.find("indir");
  return item->second;
}
string SApipeline::SasoaCommandList::getOutputDir(){
   if(compars_map["outdir"]=="temp"){
     compars_map["outdir"]="";
  }
  else{
     item  = compars_map.find("outdir");
  }
  return item->second;
}
/** No descriptions */
void SApipeline::SasoaCommandList::setDefault(){
    stringstream ts;
    ts << counter1;
    compars_map["outdir"] = "temp"+ts.str();
    counter1++;
}
/** No descriptions */
string SApipeline::SasoaCommandList::getInfileRoot(){
    int pos = getInputFilename().find_last_of(".");
    if (verbose) cout << "SasoaCommandList::getInfileRoot() pos = " << pos << "  extracted infile root  string " <<  getInputFilename().substr(0, pos) << endl;
    return getInputFilename().substr(0, pos);
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isOutDirSet(){
    item = compars_map.find("outdir");
    if(item == compars_map.end()) {
      cout << "outdir is not set : using default value" << endl;
      return false;
    }
    else  {                   
        cout << "outdir set : using user defined value" << endl;
         return true;
    } 
}
/** No descriptions */
void SApipeline::SasoaCommandList::reset(){
      map<string, string >::iterator head, tail;      
      head = compars_map.begin(); tail  = compars_map.end();
      compars_map.erase(head, tail);
      tempstring = "false";
      setTempDataMode(tempstring);
}
/** No descriptions */
void SApipeline::SasoaCommandList::setDefaultOutDir(){
  compars_map["outdir"] = getInfileRoot();
   item  = compars_map.find("outdir");
   if (verbose) cout << "set default outdir, now is" << item->second << endl;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isPathAbsolute(){
    item = compars_map.find("path"); // default path is relative and auto-determined
    if(item == compars_map.end()) {
        if (verbose) cout << "SasoaCommandList::isPathAbsolute() path type is not set : using default value " << endl;
        absolute_path = false;
    }
    else  {
        if (verbose) cout << "SasoaCommandList::isPathAbsolute() path option is "<< item->second << endl;
        if (item->second=="absolute") absolute_path = true;
        else  {
          if (item->second=="auto") absolute_path = false;
        //          else  throw("unknown parameter option");
        }
    }
    return absolute_path;
}
/** No descriptions */
void SApipeline::SasoaCommandList::setAbsolutePath(bool val){
  absolute_path = val;
  if (val) compars_map["path"] = "absolute";
  else  compars_map["path"] = "auto";
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isIDL_DisplayOn(){
    item = compars_map.find("idl_display");
    if(item == compars_map.end()) { 
        if (verbose) cout << "idl display on/off is not set : using default value [off]" << endl;
        return false;
    }
    else  {
        if (verbose) cout << "idl display set : using user defined value" << endl;
        if  (compars_map["idl_display"] == "false") {
              if (verbose) cout << "idl display user defined value is false " << endl;
              return false;
        }
        if  (compars_map["idl_display"] == "true")  {
              if (verbose) cout << "idl display user defined value is true " << endl;
              return true;
        }
        else return false;
    }
}
/** No descriptions */
string SApipeline::SasoaCommandList::getSasoaHome(){
  string msg("home is not set");
  runtime_error e(msg);
  item  = compars_map.find("sethome");
   if (item==compars_map.end())   {
       cerr << "the value for parameter sethome is not set  "<< endl;
       throw e;
    }  else {
      tempstring = item->second;
  }
  return tempstring;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::getVerboseState(){
  string msg("verbose not set");
  runtime_error e(msg);
  map<string, string >::iterator item  = compars_map.find("verbose");
  if (item==compars_map.end())   {
       cerr << "the value for parameter verbose is not set  "<< endl;
       throw e;
    }  else {
  if (item->second=="true") verbose = true;
  if (item->second=="false") verbose = false;  
  }
  return verbose;
}
/** No descriptions */
string SApipeline::SasoaCommandList::getInstrument(){
   item  = compars_map.find("instrument");
  return item->second;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isInputFileSet(){
   item  = compars_map.find("infile");
  if(item == compars_map.end()) {
       if (verbose)  cout << "input file is not set" << endl;
        tempbool =  false;
    }
    else  {
       if (verbose) cout << "input file is set and is " <<  item->second <<  endl;
        tempbool =  true;
    }
    return tempbool;
}
/** No descriptions */
void SApipeline::SasoaCommandList::setDefaultOutDir(const string &fn){
//  if (!isInputFileSet()) compars_map["infile"] = fn;
  setDefaultOutDir();  
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isInDirSet(){
   item  = compars_map.find("indir");
  if(item == compars_map.end()) {
       if (verbose) cout << "input directory is not set" << endl;
        return false;
    }
    else  {
       if (verbose) cout << "input directory is set" << endl;
       return true;
    }
}
/** No descriptions */
void SApipeline::SasoaCommandList::setDefaultInDir(const string &id){
  compars_map["indir"] = id;
}
/** No descriptions */
string SApipeline::SasoaCommandList::getValue(const string &keyword){
  tempstring = "requested parameter is not set";
  runtime_error e(tempstring);
     item  = compars_map.find(keyword.c_str());
    if(item == compars_map.end()) {
       cerr << "the value for parameter '" << keyword <<"' is not set  "<< endl;
       throw(e);
    }
    return  item->second;
}
/** No descriptions */
string SApipeline::SasoaCommandList::getAttitudeFileName(){
 string msg("attitude file name is not set");
  runtime_error e(msg);
  item  = compars_map.find("attfile");
   if (item==compars_map.end())   {
       cerr << "SasoaCommandList::getAttitudeFileName() the value for parameter attfile is not set  "<< endl;
       throw e;
    }  else {
      tempstring = item->second;
  }
  return tempstring;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isDebugSet(){
     item  = compars_map.find("debug");
    if(item == compars_map.end()) {
        if (verbose) cout << "SasoaCommandList::isDebugSet() debug value is not set (returning false)" << endl;
        return false;
    }  else  {
        return true;
    }   
}
/** No descriptions */
bool SApipeline::SasoaCommandList::getDebugValue(){
    item  = compars_map.find("debug");
    if(!isDebugSet()) {
        if (verbose) cout << "SasoaCommandList::getDebugValue() debug value is not set (returning false)" << endl;
        return false;
    }
    else  {
        tempstring = item->second;
        if (tempstring == "true"){
            if (verbose) cout << "SasoaCommandList::getDebugValue() debug option set" << endl;
            tempbool = true;
        }
        if (tempstring == "false"){
            if (verbose) cout << "SasoaCommandList::getDebugValue() debug option not set" << endl;
            tempbool = false;
        }
        else{
            cerr << "SasoaCommandList::getDebugValue() debug option determination error" << endl;
            throw e;
        }
       if (verbose) cout << "SasoaCommandList::getDebugValue() debug option value is set" << endl;
    }
        return tempbool;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::getIrosMode(){
    item  = compars_map.find("iros");
    if(!isIrosModeSet()) {
        if (verbose) cout << "SasoaCommandList::getIrosMode() iros value is not set (returning true)" << endl;
        return true;
    }
    else  {
        tempstring = item->second;
        if (tempstring == "true"){
            if (verbose) cout << "SasoaCommandList::getIrosMode() debug option set" << endl;
            tempbool = true;
        }
        if (tempstring == "false"){
            if (verbose) cout << "SasoaCommandList::getIrosMode() debug option not set" << endl;
            tempbool = false;
        }
        else{
            cerr << "SasoaCommandList::getIrosMode() iros mode option determination error" << endl;
            throw e;
        }
       if (verbose) cout << "SasoaCommandList::getIrosMode() iros mode option value is set" << endl;
    }
        return tempbool;
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isIrosModeSet(){
       item  = compars_map.find("iros");
    if(item == compars_map.end()) {
        if (verbose) cout << "SasoaCommandList::isIrosModeSet() iros mode value is not set (returning false)" << endl;
        return false;
    }  else  {
        return true;
    }
}
/** No descriptions */
bool SApipeline::SasoaCommandList::isAttFileSet(){
       item  = compars_map.find("attfile");
    if(item == compars_map.end()) {
        if (verbose) cout << "SasoaCommandList::isAttFileSet() attitude file name string is not set (returning false)" << endl;
        return false;
    }  else  {
        return true;
    }
}
/** No descriptions */
void SApipeline::SasoaCommandList::setInputFileName(const string &ifn){
  compars_map["infile"] = ifn;
}
/** No descriptions */
void SApipeline::SasoaCommandList::setAuto(const string & val){
  compars_map["auto"] = val;  
}

bool SApipeline::SasoaCommandList::isAuto(){
    item  = compars_map.find("auto");
    if(item == compars_map.end()) {
        if (verbose) cout << "SasoaCommandList::isAuto() automatic option string is not set (returning false)" << endl;
        return false;
    }  else  {
        tempstring = item->second;
        if (tempstring == "true"){
            if (verbose) cout << "auto option set" << endl;
            tempbool = true;
        }
        if (tempstring == "false"){
            if (verbose) cout << "auto option not set" << endl;
            tempbool = false;
        }
        else{
            cerr << " error in getting auto mode value" << endl;
            throw e;
        }
    }
    return tempbool;
}    /** No descriptions */
bool SApipeline::SasoaCommandList::getTempDataMode(){
  string msg("tempdata is not set!");
  runtime_error e(msg);
  map<string, string >::iterator item = compars_map.find("tempdata");
  if (item==compars_map.end())   {
       cerr << "SasoaCommandList::getTempDataMode() the value for parameter tempdata is not set  "<< endl;
       throw e;
    }  else {
  if (item->second==(string)"true") tempbool = true;
  if (item->second==(string)"false") tempbool = false;
  }
  return tempbool;
}
/** No descriptions */
void SApipeline::SasoaCommandList::setTempDataMode(const string &tdm){
  compars_map["tempdata"] = tdm;  
}

/** No descriptions */
void SApipeline::SasoaCommandList::setVerbose(bool v){
  verbose = v;
}