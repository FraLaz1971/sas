/***************************************************************************
                          agilefilename.h  -  description
                             -------------------
    begin                : Mon Sep 18 2006
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

#ifndef AGILEFILENAME_H
#define AGILEFILENAME_H


/**
  *@author Francesco Lazzarotto
  */
  
#include <string>
#include <iostream>
#include "archivemodule.h"

using namespace std;

namespace SAarchive{
using namespace SAarchive;

class AGILEFileName : public ArchiveModule {
  
public:
 
  /** No descriptions */
  AGILEFileName();

  /** No descriptions */
  AGILEFileName(const AGILEFileName &fn);

  /** No descriptions */
  AGILEFileName(const string &sfn);

  /** No descriptions */
  ~AGILEFileName();
  /** No descriptions */
  string getBase();
  /** No descriptions */
  string getContact();
  /** No descriptions */
  string getExtension();
  /** No descriptions */
  string getSubType();
  /** No descriptions */
  string getType();
  /** No descriptions */
  string getVc();
  /** No descriptions */
  void setType(const string &stype);
  /** No descriptions */
  void setContact(const string &cnt);
  /** No descriptions */
  void setBase(const string &bs);
  /** No descriptions */
  void operator<<(const string &fn);
  /** No descriptions */
  string total() const;
  /** No descriptions */
  void setVc(const string &v);
  /** No descriptions */
  void setSubExtension(const string &se);
  /** No descriptions */
  string getSubExtension();
  /** No descriptions */
  string getSequenceNumber();
  /** No descriptions */
  void setSequenceNumber(const string &sn);
  /** No descriptions */
  void setExtension(const string &ex);
  /** assign the subparts of the filename extracting them from the input strin (= tot) */
  void assignName(const string &tot);
  /** No descriptions */
  void show();
  /** No descriptions */
  string getOrbitNumber();
  /** No descriptions */
  void setOrbitNumber(const string &orb);
  /** No descriptions */
  void update();
  /** No descriptions */
  void setSubExtension(bool b);
  /** No descriptions */
  void setOrbdata(bool b);
  /** No descriptions */
  void setSapipe(bool b);
  /** return the (ok)filename to trigger following task */
  string getTriggerFileName();
  /** No descriptions */
  void assignTrigger(const string &tn);
  /** returns the total trigger filename */
  string trigTotal();
  /** No descriptions */
  void updateTrigger();
  /** No descriptions */
  void showTrigger();
  /** No descriptions */
  string getCorrectorVersion();
  /** No descriptions */
  void setCorrectorVersion(const string &cv);
  /** No descriptions */
  string getTriggerExtension();
  /** No descriptions */
  void setTriggerExtension(const string &te);
  /** No descriptions */
  string getTrigBase();
  /** No descriptions */
  void setTrigBase(const string &tb);
  /** No descriptions */
  void clear();
  /** No descriptions */
  void init();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  void setTrigAbsoluteFilename(const string &tafn);
  /** No descriptions */
  void setAbsoluteFileName(const string &afn);

  string getIrosMapFileName();
  /** No descriptions */
  string getNameRoot();

  /** No descriptions */
  int  getContactNumber();

  protected:

  /** Events data filename fields */
  string base;
  /** */
  int contactnum;
  /** */
  string contact;
  /** */
  string vc;
  /** */
  string type;
  /** */
  string subtype;
  /** */
  string totname;
  /** */
  string seqnum;
  /** string saving the orbit number string*/
  string orbnum;
  /** string saving the orbit part number */
  string orbpart;
  /** */
  string subext;
  /** */
  string ext;
  /** Trigger filename */
  string triggerfilename;
  /** extension of trigger file*/
  string trigbase;
  /** extension of trigger file*/
  string trext; 
  /** version of the corrector*/
  string corrver;
  /** the contact number is the same of the events data file */
  //string trigcnt (= contact);  
  /** */
  bool sapipe;
  /** true if is a filename with the subextension   <_sub.ext>  */
  bool subextension;
  /** true if is an orbital data filename*/
  bool orbdata;
  /** */
  string nameroot;
  /** */  
  int datafnamelength;
  /** */
  int trigfnamelength;
  // this is a comment to test cvs 13-11-2006 Francesco Lazzarotto
  // and this is another comment for use of TAG by Francesco Lazzarotto
  // this comment was written on 17-11-2006
  // stop with comments!


};

}
#endif
