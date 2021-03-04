/***************************************************************************
                          rlmmtest.h  -  description
                             -------------------
    begin                : Tue Mar 21 2006
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
#ifdef HAVE_CONFIG_H
# include <config.hh>
#endif
#ifndef rlmm_readline_hh
# include <rlmm/readline.hh>
#endif
#ifndef rlmm_history_hh
# include <rlmm/history.hh>
#endif
#ifndef rlmm_key_map_hh
# include <rlmm/key_map.hh>
#endif
#ifndef rlmm_function_map_hh
# include <rlmm/function_map.hh>
#endif
#ifndef __IOSTREAM__
# include <iostream>
#endif
#ifndef __IOMANIP__
# include <iomanip>
#endif
#ifndef __CSTDIO__
# include <cstdio>
#endif
#include <sstream>
using namespace std;
using namespace rlmm;
#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <stdexcept>


//#include <string>

//____________________________________________________________________
namespace examples
{
  /** Test of rlmm::readline.
      This example shows how to change histories in mid-stream. */
  class rlmmtest : public rlmm::readline
  {
  private:
    typedef rlmm::readline base_type;
    /// First history.
    rlmm::history _keeper1;
    /// Second history.
    rlmm::history _keeper2;
    /// key map
    rlmm::key_map _key_map;

    /// Line number when using the first history
    int _line1;
    /// Line number when usign the second history
    int _line2;
    /// Flag to set when done.
    bool     _done;
    /// The prompt
    string _prompt;    /** save the command line for sasoa */

    string batchline;
    
  protected:
    /// save batch execution selection
    exception e;
    bool batch;
  string sasoa_command;
  int status;
  public:
    /// CTOR.
    rlmmtest();
    /** Utility member function to make a prompt.
	A occurence of a integer format specifier is substituted with
	the current history number.  E.g., if the @p skel parameter is
	@c "prompt [%d] " and the current history number is 10, then
	the @c %d will be replaced by the 10, and the prompt is
	@c "prompt [10] ".  All normal integer format specifiers can
	be used e.g., if @p skel is @c "prompt [%03d]" and the current
	history line is 10, then the output will be
	@c "prompt [010] ".
	@param skel Skeleton for prompt.
	@param num history number.
	@return new prompt with substitutions. */
    string make_prompt(const string& skel, int num);
    /// Run this example.
    int run();
    /// Handle an input of @c "quit".
  virtual    void handle_quit() { _done = true; }
    /// Handle an input of @c "which".
    void handle_which();
    /// Handle an input of @c "switch".
    void handle_switch();
    /// Handle an input of @c "dump".
    void handle_dump() {key_map::active().list_bindings(); }
    /// Handle an input of @c "list".
    void handle_list();
    /// Handle an input of @c "help".
    void handle_help();

  /** handles entrystage command */
  virtual int handle_entrystage(int stagenum);
  /** handles existage command */
  virtual void handle_exitstage(int stagenum);
  /** pass commandline to the pipeline handler */
  void saveCommand(string line);
  /** No descriptions */
  void setBatch(bool val);
  /** No descriptions */
  void setBatchCommand(string line);
  /** No descriptions */
  virtual  void handle_showparameters();
  /** No descriptions */
  virtual  void handle_EMIDaemon();
  /** No descriptions */
  virtual  void handle_showcommandlist();
  /** configure default values for the pipeline */
  virtual void handle_conf();
  /** No descriptions */
  virtual void handle_showdef();
  /** No descriptions */
  virtual void handle_syntax();
  /** No descriptions */
  virtual void handle_showconf();
  /** No descriptions */
  virtual void handle_sethome();
  /** No descriptions */
  virtual void handle_showenv();
  /** No descriptions */
  virtual void handle_verbose();
  /** No descriptions */
  virtual void handle_rm_workenv();
    /// Handle an input of @c "data".
    ///  listing available input data in the default directory 
  virtual void handle_data();
  /** No descriptions */
  virtual void handle_setInstrument();
  /** No descriptions */
  virtual void handle_refresh();
  /** No descriptions */
  virtual void handle_cutL3();
  /** No descriptions */
  virtual void handle_testiros();
  /** No descriptions */
  virtual void handle_testirosmap();
  /** No descriptions */
  virtual void handle_correction();
  /** No descriptions */
  virtual void handle_testrebuilder();
  /** No descriptions */
  virtual void handle_testokdaemon();
  /** No descriptions */
  virtual void handle_testdb();
  /** No descriptions */
  virtual void handle_killprocess();
  /** No descriptions */
  virtual void handle_admin();
  /** No descriptions */
  virtual void handle_l3test();
  /** No descriptions */
  virtual void handle_pointing();
  /** No descriptions */
  virtual void handle_testgnuplot();
  /** No descriptions */
  virtual void handle_mdimg();
  /** No descriptions */
  virtual void handle_newtest();
  /** No descriptions */
  virtual void handle_datetest();
  /** No descriptions */
  virtual void handle_testproducts();
  /** No descriptions */
  virtual void handle_detimage();
  /** No descriptions */
  virtual void handle_otherimage();
  /** No descriptions */
  virtual void handle_plotallmdimages();
  /** No descriptions */
   virtual void handle_cutL3file();
   /** No descriptions */
   virtual void handle_cleardata();
   /** No descriptions */
   virtual  void handle_startokdaemon();
   /** No descriptions */
   virtual  void handle_testattitude();
  /** No descriptions */
  virtual void handle_testsystem();
  /** No descriptions */
  virtual void handle_stage3test();
  /** No descriptions */
  virtual void handle_stage2test();
  /** No descriptions */
  virtual void handle_createirosmap();
  /** No descriptions */
  virtual void handle_filelist();
  /** clear gti filtering */
  virtual void handle_gti();
  /** handle multi contact run */
  virtual void handle_multicontact();
  /** handle energy filter */
  virtual void handle_energy();
  /** split detector data */
  virtual void handle_splitdata();
  /** load contact data*/
  virtual void handle_loadcontact();
  /** */
  virtual void handle_unzip();
  /** */
  virtual void handle_autogti();
  /** */
  virtual void handle_setcontactsdir();  
  /** No descriptions */
  virtual void handle_allpipe();  
  /** No descriptions */
  virtual void handle_prepare();
  /** No descriptions */
  virtual void handle_newdaemon();

  /** No descriptions 
  void handle_runcontact(){
  }
  /** No descriptions */
  virtual void exec_runContact(int contactnum);
  /** No descriptions */
  virtual void exec_EMI(int contactnum);
  /** No descriptions */
  virtual void exec_runEMIContact(int contactnum);
  /** No descriptions */
  virtual void exec_runIROSContact(int contactnum);
  /** No descriptions */
  virtual void exec_allpipe(int contactnum);
  /** No descriptions */
  virtual void handle_setLUTs();
  /** No descriptions */
  virtual void handle_quat_to_sapoi();
  /** No descriptions */
  virtual void handle_extract_exposure();
  /** No descriptions */
  virtual void handle_loadContcSSH();
  /** No descriptions */
  virtual void handle_asdc_daemon();
  /** No descriptions */
  virtual void handle_exposure();
  /** No descriptions */
  virtual void handle_largefile();
  /** No descriptions */
  virtual void burst();
  /** No descriptions */
  virtual void handle_TDS();
  /** No descriptions */
  virtual void exec_attitude(int contactnum);
  /** No descriptions */
  string mytempstring;

  };
}


