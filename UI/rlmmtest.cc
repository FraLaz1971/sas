//
// $Id: rlmmtest.cc,v 1.3 2008/04/04 14:29:43 agile_cvs Exp $ 
//  
//  simple.cc
//  Copyright (C) 2002 Christian Holm Christensen <cholm@nbi.dk> 
//
//  This library is free software; you can redistribute it and/or        pip_idl_batch
//  modify it under the terms of the GNU Lesser General Public License 
//  as published by the Free Software Foundation; either version 2.1 
//  of the License, or (at your option) any later version. 
//
//  This library is distributed in the hope that it will be useful, 
//  but WITHOUT ANY WARRANTY; without even the implied warranty of 
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
//  Lesser General Public License for more details. 
// 
//  You should have received a copy of the GNU Lesser General Public 
//  License along with this library; if not, write to the Free 
//  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
//  02111-1307 USA 
//


/** @file   rlmmtest.cc
    @author Christian Holm
    @date   Mon Oct  7 13:57:07 2002
    @brief  Test of rlmm::readline. */
    

    
#include "rlmmtest.h"

namespace examples{

//____________________________________________________________________
examples::rlmmtest::rlmmtest() 
{
  _prompt  = "sasoa [%d] ";
  _keeper2.read(".rlmmtest_history");
  _key_map.activate();
  _done    = false;
  _line1   = 0;
  _line2   = 0;
}

//____________________________________________________________________
 std::string  examples::rlmmtest::make_prompt(const  std::string & skel, int num)
{
  static char str[16];
  size_t colon = skel.find('%');
  if (colon ==  std::string ::npos) 
    return  std::string (skel);
  
  size_t d = skel.find('d', colon);
   std::string   format = skel.substr(colon, d+1);
      
  sprintf(str, format.c_str(), num);
      
   std::string  p(skel);
  p.replace(colon, d+1, str);
  return p;
}

//____________________________________________________________________
int examples::rlmmtest::run() {
   std::string  line;
   std::string  argument;
  
 do {
     std::string   p;
    int& lineno = _keeper1.is_active() ? _line1 : _line2;
    if (batch){
      line = batchline;
       std::cout << " batchline = " << line << endl;
    } else {
      p = make_prompt(_prompt, lineno);
      if (!read(p, line))      return 0;
    }

    size_t j = line.size();
    size_t i = line.size()-1;
    
    while (i >= 0) {
      if (line[i] != ' ' && line[i] != '\t') break;
      i--;
    }
    if (j != i+1) line.erase(i+1, j - i);

    if (line.empty())  continue;
    lineno++;
//     std::cout << history::active().length() << ": `" << line << "'" <<  endl;
     std::cerr << history::active().length() << ": `" << line << "'" <<  endl;
    
    history::active().add(line);
    argument = line.substr(line.length()-1, 1);
//     std::cout  << "argument = " << line.substr(line.length()-1, 1) << endl;
    int iarg;
    iarg = 999;
//     std::cout << "iarg = " << iarg << endl;
    stringstream isarg; isarg.str("");
    isarg << argument;
//    isarg << argument;
    isarg >> iarg;
//     std::cout << "iarg = " << iarg << endl;
    if ((line == "quit")||(line == "exit")||(line == ".q")||(line == "q")||(line == "stop"))   handle_quit();
    if (line == "which")  handle_which();
    if (line == "showpar")  handle_showparameters();
    if (line == "switch") handle_switch();
    if (line == "dump")   handle_dump();
    if (line == "list")   handle_list();
    if (line == "pointing")   handle_list();    
    if (line == "conf")   handle_conf();
    if (line == "showdef")   handle_showdef();
    if (line == "showconf")   handle_showconf();
    if (line == "showenv")   handle_showenv();
    if (line == "filelist")   handle_filelist();
    if (line == "exp")   handle_exposure();
    if (line == "system")   handle_testsystem();
    if (line == "energy")   handle_energy();
    if (line == "setcontactsdir")   handle_setcontactsdir(); 
    if (line == "gti")   handle_gti();    
    if (line == "autogti")   handle_autogti();    

//    if (line == "launchcor")   handle_launchCorrection();
    if (line == "cutl3")   handle_cutL3();
	if (line == "contactssh") handle_loadContcSSH();
    if (line == "teststage2")   handle_stage2test();
    if (line == "teststage3")   handle_stage3test();    
    if (line == "cutL3file")   handle_cutL3file();      
    if (line == "data")   handle_data();
    if (line == "refresh")   handle_refresh();
    if (line == "syntax")   handle_syntax();
    if (line == "testirosmap")   handle_testirosmap();
    if (line == "testiros")   handle_testiros();    
    if (line == "testrebuilder")   handle_testrebuilder();
    if (line == "testokdaemon")   handle_testokdaemon();
    if (line == "correction")   handle_correction();
    if (line == "testdb") handle_testdb();
    if (line == "loadcontact") handle_loadcontact();
    if (line == "admin")   handle_admin();    
    if (line == "killprocess")   handle_killprocess();
    if (line == "pointing")   handle_pointing();    
    if (line == "l3test")  handle_l3test();
    if (line == "mdimg")  handle_mdimg();
    if (line == "newtest")  handle_newtest();    
    if (line == "gnptest")  handle_testgnuplot();
    if (line == "datetest")  handle_datetest();
    if (line == "otherimg")  handle_otherimage();
    if (line == "detimage")  handle_detimage();
    if (line == "prepare")  handle_prepare();
    if (line == "emidaemon")  handle_EMIDaemon();
    if (line == "newdaemon")  handle_newdaemon();
    if (line == "asdcdaemon")  handle_asdc_daemon();
    if (line == "startok")  handle_startokdaemon();
    if (line == "splitdata")  handle_splitdata();
    if (line == "TDS")  handle_TDS();
    if (line == "allpipe")  handle_allpipe();
    if (line == "unzip")  handle_unzip();
    if (line == "quat_to_sapoi")  handle_quat_to_sapoi();
    if (line == "burst")  burst();
    if (line == "setluts")  handle_setLUTs();
    if (line == "autogti")  handle_autogti();    
    if (line == "attest")  handle_testattitude();        
    if (line == "multicontact")  handle_multicontact();        
    if (line == "cleardata")  handle_cleardata();    
    if (line == "plotallmd")  handle_plotallmdimages();    
    if (line == "testproducts")  handle_testproducts(); 
    if (line == "exposure")  handle_exposure();    
    if (line == "ext_exp")  handle_extract_exposure();    
    if (line == "large")  handle_largefile();    
    if (line == "rm_workenv")   handle_rm_workenv();                    
    if (line.substr(0, 7) == "verbose"){
      try{
        saveCommand(line);
        handle_verbose();
        } catch(const exception &e){
           std::cerr  << "handled exception "<< e.what() << endl;
        }
    }

    if (line.substr(0, 10) == "runcontact")  {
	// extract contact number
	mytempstring  = line.substr(line.find_first_of(",")+1, -1);
	 std::cout << "rlmmtest::run() running sasoa for contact " << mytempstring  << endl;
	 std::cout << "extracted integer = " << atoi(mytempstring.c_str()) << endl;
	exec_runContact(atoi(mytempstring .c_str()));	
	}

    if (line.substr(0, 13) == "runEMIcontact")  {
	// extract contact number
	mytempstring  = line.substr(line.find_first_of(",")+1, -1);
	 std::cout << "rlmmtest::run() running sasoa EMI for contact " << mytempstring  << endl;
	 std::cout << "extracted integer = " << atoi(mytempstring.c_str()) << endl;
	exec_EMI(atoi(mytempstring .c_str()));	
	}
	

    if (line.substr(0, 14) == "runIROScontact")  {
	// extract contact number
	mytempstring  = line.substr(line.find_first_of(",")+1, -1);
	 std::cout << "rlmmtest::run() running sasoa IROS for contact " << mytempstring  << endl;
	 std::cout << "extracted integer = " << atoi(mytempstring.c_str()) << endl;
	exec_runIROSContact(atoi(mytempstring .c_str()));	
	}

    if (line.substr(0, 8) == "attitude")  {
	// extract contact number
	mytempstring  = line.substr(line.find_first_of(",")+1, -1);
	 std::cout << "rlmmtest::run() running attitude correction for contact " << mytempstring  << endl;
	 std::cout << "extracted integer = " << atoi(mytempstring.c_str()) << endl;
	exec_attitude(atoi(mytempstring.c_str()));	
	}
	
    if (line.substr(0, 10) == "instrument"){
        saveCommand(line);
        handle_setInstrument();
    }    
    if (line.substr(0, 7) == "sethome")   {
        saveCommand(line);
        handle_sethome();
    }        
    if (line.substr(0, 14) == "create_irosmap")   {
    //if (line == "create_irosmap")   {
        saveCommand(line);
         std::cout << "rlmmtest::run() EXECUTING"<< endl;
        handle_createirosmap();
    }
    if ((line == "help")||(line == "man"))   handle_help();    
    if (line.substr(0, 10) == "entrystage")   {
      saveCommand(line);
      if(handle_entrystage(iarg)){
       std::cout << "going to throw e "<< e.what() << endl;
      throw(e) ;
      }
      if(batch) handle_quit();
      iarg = 999;
      }
    if (line.substr(0, 9) == "exitstage")   {
      handle_exitstage(iarg);
      if (batch) handle_quit();     
      iarg = 1111;
     }
     if(batch) break; batch = false;
     //else handle_help();      
  }  while (!_done);
  return 0;
}

//____________________________________________________________________
void examples::rlmmtest::handle_help() 
{
   std::cout << "Commands: \n\n" 
       << "\tquit\tQuit the application\n"
//       << "\twhich\tShow which history is in use\n"
//       << "\tswitch\tSwitch which history is in use\n"
//       << "\tdump\tDump key bindings\n" 
//       << "\tlist\tDump current history\n"
       << "\tsyntax\tShow command-line syntax\n"       
//       << "\tshowdef\tShow user defined default\n"
//       << "\tshowconf\tShow the whole configuration\n"
//       << "\tsethome\tSet the sasoa home\n"
       << "\tdata\tShow available input data\n"
//       << "\tinstrument\tSet instrument/prototype name\n"             
//       << "\tverbose\tSet verbose execution messages\n"                         
       << "\thelp\tThis help\n" << endl;
}

//____________________________________________________________________
void examples::rlmmtest::handle_list() 
{
try{
       std::cout << "TO DO implement rlmmtest::handle_list() ... "  << endl;
//  history::entry e;
//    for (int i = 1; i <= history::active().length(); i++) {
//      e = history::active().at(i);
//       std::cout << setw(4) << i << ": " << e.line() << endl;
//    }
  }  catch (const exception &e) {
      std::cerr << "exception " << e.what() << endl;
  }
}

//____________________________________________________________________
void examples::rlmmtest::handle_switch() 
{
  if (_keeper1.is_active()) 
    _keeper2.activate();
  else 
    _keeper1.activate();
}

//____________________________________________________________________
void examples::rlmmtest::handle_which() 
{
   std::cout << "keeper is " 
       << (_keeper1.is_active() ? "1" : "2")  << endl;
}

  /** handles entrystage command */
 int examples::rlmmtest::handle_entrystage(int stagenum){
       std::cout << "rlmmtest:: executing handle_entrystage" << endl;
      return status;
 }
  /** handles existage command */
  void examples::rlmmtest::handle_exitstage(int stagenum){
       std::cout << "rlmmtest::  executing handle_exitstage" << endl;    
  }


}
//____________________________________________________________________

//____________________________________________________________________
//
// EOF
//


/** pass commandline to the pipeline handler */
void examples::rlmmtest::saveCommand( std::string  line){
  sasoa_command = line;
}
/** No descriptions */
void examples::rlmmtest::setBatch(bool val){
  batch = val;
}
/** No descriptions */
void examples::rlmmtest::setBatchCommand( std::string  line){
  batchline = line;
}
/** No descriptions */
void examples::rlmmtest::handle_showcommandlist(){
  
}
/** configure default values for the pipeline */
void examples::rlmmtest::handle_conf(){
       std::cout << "rlmmtest::  executing handle_conf" << endl;
}
/** No descriptions */
void examples::rlmmtest::handle_showdef(){
       std::cout << "rlmmtest::  executing handle_def" << endl;
}
/** No descriptions */
void examples::rlmmtest::handle_syntax(){
     std::cout << "rlmmtest::  executing handle_syntax" << endl;
}
/** No descriptions */
void examples::rlmmtest::handle_showconf(){
}
/** No descriptions */
void examples::rlmmtest::handle_sethome(){
  std::cout << "rlmmtest::  executing handle_sethome" << endl;
}
/** No descriptions */
void examples::rlmmtest::handle_showenv(){
}
/** No descriptions */
void examples::rlmmtest::handle_verbose(){
}
/** No descriptions */
void examples::rlmmtest::handle_rm_workenv(){
}
/** No descriptions */
void examples::rlmmtest::handle_data(){
}
/** No descriptions */
void examples::rlmmtest::handle_setInstrument(){
}
/** No descriptions */
void examples::rlmmtest::handle_refresh(){
}
/** No descriptions */
void examples::rlmmtest::handle_testirosmap(){
}
/** No descriptions */
void examples::rlmmtest::handle_correction(){
}
/** No descriptions */
void examples::rlmmtest::handle_testrebuilder(){
}
/** No descriptions */
void examples::rlmmtest::handle_testokdaemon(){
}
/** No descriptions */
void examples::rlmmtest::handle_testdb(){
}
/** No descriptions */
void examples::rlmmtest::handle_killprocess(){
}
/** No descriptions */
void examples::rlmmtest::handle_admin(){
}
/** No descriptions */
void examples::rlmmtest::handle_testiros(){
}
/** No descriptions */
void examples::rlmmtest::handle_l3test(){
}
/** No descriptions */
void examples::rlmmtest::handle_pointing(){
}
/** No descriptions */
void examples::rlmmtest::handle_testgnuplot(){
}
/** No descriptions */
void examples::rlmmtest::handle_mdimg(){
}
/** No descriptions */
void examples::rlmmtest::handle_newtest(){
}
/** No descriptions */
void examples::rlmmtest::handle_datetest(){
}
/** No descriptions */
void examples::rlmmtest::handle_testproducts(){
}
/** No descriptions */
void examples::rlmmtest::handle_detimage(){
}

void examples::rlmmtest::handle_startokdaemon(){
}

void examples::rlmmtest::handle_cutL3(){
  
}

void examples::rlmmtest::handle_cutL3file(){
  
}
void examples::rlmmtest::handle_plotallmdimages(){
}

/** No descriptions */
void examples::rlmmtest::handle_otherimage(){
}

/** No descriptions */
void examples::rlmmtest::handle_testattitude(){
}
/** clear all temporary data */
void examples::rlmmtest::handle_cleardata(){
}
/** No descriptions */
void examples::rlmmtest::handle_testsystem(){
}
/** No descriptions */
void examples::rlmmtest::handle_showparameters(){  
}
/** No descriptions */
void examples::rlmmtest::handle_stage2test(){
}
/** No descriptions */
void examples::rlmmtest::handle_stage3test(){
}
/** No descriptions */
void examples::rlmmtest::handle_createirosmap(){
}
/** No descriptions */
void examples::rlmmtest::handle_filelist(){
}
/** No descriptions */
void examples::rlmmtest::handle_gti(){
}
/** No descriptions */
void examples::rlmmtest::handle_multicontact(){
}
/** No descriptions */
void examples::rlmmtest::handle_energy(){
}
/** No descriptions */
void examples::rlmmtest::handle_splitdata(){
}
/** No descriptions */
void examples::rlmmtest::handle_loadcontact(){
}
/** No descriptions */
void examples::rlmmtest::handle_unzip(){
}
/** No descriptions */
void examples::rlmmtest::handle_autogti(){
}
/** No descriptions */
void examples::rlmmtest::handle_setcontactsdir(){
}
/** No descriptions */
void examples::rlmmtest::handle_allpipe(){

}
/** No descriptions */
void examples::rlmmtest::handle_prepare(){

}
void examples::rlmmtest::handle_newdaemon(){

}
void examples::rlmmtest::handle_setLUTs(){

}
/** No descriptions */
void examples::rlmmtest::exec_allpipe(int contactnum){

}
/** No descriptions */
void examples::rlmmtest::exec_runContact(int contactnum){

}

/** No descriptions */
void examples::rlmmtest::exec_EMI(int contactnum){

}
/** No descriptions */
void examples::rlmmtest::exec_runEMIContact(int contactnum){

}
/** No descriptions */
void examples::rlmmtest::exec_runIROSContact(int contactnum){

}
/** No descriptions */
void examples::rlmmtest::handle_quat_to_sapoi(){

}

/** No descriptions */
void examples::rlmmtest::handle_extract_exposure(){

}
void examples::rlmmtest::handle_exposure(){

}

/** No descriptions */
void examples::rlmmtest::handle_loadContcSSH(){

}

/** No descriptions */
void examples::rlmmtest::handle_asdc_daemon(){
}

/** No descriptions */
void examples::rlmmtest::handle_largefile(){

}
/** No descriptions */
void examples::rlmmtest::handle_EMIDaemon(){
}
/** No descriptions */
void examples::rlmmtest::burst(){
}
/** No descriptions */
void examples::rlmmtest::handle_TDS(){
}

void examples::rlmmtest::exec_attitude(int contactnum){
}

