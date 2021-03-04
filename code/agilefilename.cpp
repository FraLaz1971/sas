/***************************************************************************
                          agilefilename.cpp  -  description
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

#include "agilefilename.h"

namespace SAarchive{
  
AGILEFileName::AGILEFileName(){
  nameroot = "";
  sapipe = false;
  subextension = false;
  orbdata = false;
  string temp("pkpNNNNNN_C_PP_SS_SUB.ext");
  assignName(temp);
  init();
}

AGILEFileName::AGILEFileName(const AGILEFileName &fn){
  init();
  assignName(fn.total());
}

AGILEFileName::AGILEFileName(const string &sfn){
  init();
  assignName(sfn);
}

AGILEFileName::~AGILEFileName(){

}

/** No descriptions */

string AGILEFileName::getBase(){
  return base;
}

/** No descriptions */
string AGILEFileName::getContact(){
  return contact;
}
/** No descriptions */
string AGILEFileName::getVc(){
  return vc;
}
/** No descriptions */
string AGILEFileName::getType(){
  return type;
}
/** No descriptions */
string AGILEFileName::getSubType(){
  return subtype;
}
/** No descriptions */
string AGILEFileName::total() const{
  return totname;
}
/** No descriptions */
void AGILEFileName::operator<<(const string &n){
  assignName(n);
}
/** No descriptions */
void SAarchive::AGILEFileName::setBase(const string &bs){
  base = bs;
}
/** No descriptions */
void SAarchive::AGILEFileName::setContact(const string &cnt){
   contact = cnt;
}
/** No descriptions */
void SAarchive::AGILEFileName::setType(const string &typ){
  type = typ;
}
/** No descriptions */
void SAarchive::AGILEFileName::setVc(const string &v){
  vc = v;
}
/** No descriptions */
void SAarchive::AGILEFileName::setSequenceNumber(const string &sn){
  seqnum = sn;
}
/** No descriptions */
string SAarchive::AGILEFileName::getSequenceNumber(){
  return seqnum;
}
/** No descriptions */
string SAarchive::AGILEFileName::getSubExtension(){
  return subext;
}
/** No descriptions */
void SAarchive::AGILEFileName::setSubExtension(const string &se){
  subext = se;
}
/** No descriptions */
void SAarchive::AGILEFileName::setExtension(const string &ex){
  ext = ex;
}
/** No descriptions */
string SAarchive::AGILEFileName::getExtension(){
  return ext;
}
/** assign the subparts of the filename extracting them from the input strin (= tot) */
void SAarchive::AGILEFileName::assignName(const string &tot){
  // if required insert other constraints
  if (tot.size()>0){
  try{
    base.assign(tot, 0, 3);
    contact.assign(tot, 3, 6);
    vc.assign(tot, 10, 1);
    type.assign(tot, 12, 2);
    subtype.assign(tot, 14, 2);
    seqnum.assign(tot, 17, 3);
    if (subextension) {
      subext.assign(tot, 21, 3);
      ext.assign(tot, 21, 3);
    }
    else {
      ext.assign(tot, 21, 3);
    }
    if (orbdata){
      orbnum.assign(tot, 21, 6);
    }
    totname.assign(tot);
  } catch (const exception &e){
      cerr << "AGILEFileName::assign() error in assigning the events data file name (not regular)"<< e.what() << endl;
  }
}
}

/** No descriptions */
void SAarchive::AGILEFileName::show(){
  cout << "total name = "<< total() << endl;
  cout << "Base  = " << getBase() << endl;
  cout << "Contact = " << getContact()  << endl;
  cout << "VC number = "<< getVc() << endl;
  cout << "type = " << getType() << endl;
  cout << "subtype = " << getSubType() << endl;
  cout << "sequence number = " << getSequenceNumber() << endl;
  if (orbdata) cout << "orbit number = " << getOrbitNumber() << endl;
  if (subextension) cout << "subextension = " << getSubExtension() << endl;
  cout << "extension = " << getExtension() << endl;
  if (sapipe) {
    cout << "*** specific SA pipeline filename fields ***" << endl;
  }
  cout << endl;
  showTrigger();
}
/** No descriptions */
string SAarchive::AGILEFileName::getOrbitNumber(){
  return orbnum;
}
/** No descriptions */
} // ends namespace SAarchive/** No descriptions */
void SAarchive::AGILEFileName::setOrbitNumber(const string &orb){
  orbnum = orb;
}
/** No descriptions */



/** No descriptions */
void SAarchive::AGILEFileName::update(){
  totname.clear();
  totname +=  base;
  totname +=  contact;
  totname +=  "_";
  totname +=  vc;
  totname +=  "_";
  totname +=  type;
  totname +=  subtype;
  totname +=  "_";
  totname +=  seqnum;
  if ((subextension)&&(!orbdata)){
    totname +=  "_";
    totname +=  subext;
  }
  if ((orbdata)&&(subextension)){
    totname +=  "_";
    totname +=  orbnum;
    totname +=  "_";
    totname +=  subext;
  }
    totname +=  ".";
    totname +=  ext;
}
/** No descriptions */
void SAarchive::AGILEFileName::setOrbdata(bool b){
  orbdata = b;
}
/** No descriptions */
void SAarchive::AGILEFileName::setSubExtension(bool b){
  subextension = b;
}
/** No descriptions */
void SAarchive::AGILEFileName::setSapipe(bool b){
  sapipe = b;
}
/** return the (ok)filename to trigger following task */
string SAarchive::AGILEFileName::getTriggerFileName(){
  return triggerfilename;
}

/** returns the total trigger filename */
string SAarchive::AGILEFileName::trigTotal(){
  return triggerfilename;
}
/** No descriptions */
void SAarchive::AGILEFileName::assignTrigger(const string &tn){
  string ts; ts.assign("error in assigning the trigger file name");
  se.setMsg(ts);
//  string p; p.assign("pippo.err");
  int s = tn.size() ;
  try{
   if (verbose) cout << "AGILEFileName::assignTrigger() assigned trigger filename "<< tn << endl;
    if (verbose) cout << "AGILEFileName::assignTrigger() trigger filename size is " << s << endl;
    if (!(s==17)) {
      if (verbose)cout << "AGILEFileName::assignTrigger() trigger filename size is not 17"  << endl;
      if (verbose)cout << "AGILEFileName::assignTrigger() throwing an exception!"  << endl;
      throw se;throw e;
    } else{
    if (verbose)cout << "AGILEFileName::assignTrigger() trigger filename size is " << s << ": correct, going ahead"  << endl;
      trigbase.assign(tn, 0, 3);
      contact.assign(tn, 4, 6);
      corrver.assign(tn, 11, 3);
      trext.assign(tn, 15, 2);
      triggerfilename.assign(tn);
    }
  } catch (const exception &e){
    cerr << "AGILEFileName::assignTrigger() error in assigning the trigger file name (not regular)"<< e.what()<< endl;
  } catch (const SAexception &se){
    cerr << "AGILEFileName::assignTrigger() error in assigning the trigger file name (not regular)"<< se.getMsg() << endl;
  }

}
/** No descriptions */
void SAarchive::AGILEFileName::updateTrigger(){
  triggerfilename.clear();
  triggerfilename +=  trigbase;
  triggerfilename += ".";
  triggerfilename += contact;
  triggerfilename += ".";
  triggerfilename += corrver;
  triggerfilename += ".";
  triggerfilename += trext;
}
/** No descriptions */
void SAarchive::AGILEFileName::showTrigger(){
  cout << "*** Executing  AGILEFileName::showTrigger() START ***" << endl;
  cout << "total trigger filename = "<< getTriggerFileName() << endl;
  cout << "TrigBase  = " << getTrigBase() << endl;
  cout << "Contact = " << getContact()  << endl;
  cout << "Corrector Version = "<< getCorrectorVersion() << endl;
  cout << "trigger filename extension = " << getTriggerExtension() << endl;
  cout << "*** Executing  AGILEFileName::showTrigger() STOP ***" << endl;
  if (sapipe) {
    cout << "*** specific SA pipeline filename fields ***" << endl;
  }
}
/** No descriptions */
void SAarchive::AGILEFileName::setTrigBase(const string &tb){
  trigbase = tb;
}
/** No descriptions */
string SAarchive::AGILEFileName::getTrigBase(){
  return trigbase;
}
/** No descriptions */
void SAarchive::AGILEFileName::setTriggerExtension(const string &te){
  trext = te;
}
/** No descriptions */
string SAarchive::AGILEFileName::getTriggerExtension(){
  return trext;
}
/** No descriptions */
void SAarchive::AGILEFileName::setCorrectorVersion(const string &cv){
  corrver = cv;
}
/** No descriptions */
string SAarchive::AGILEFileName::getCorrectorVersion(){
  return corrver;
}
/** No descriptions */
void SAarchive::AGILEFileName::clear(){
  /** */
  base.clear();
  /** */
  contact.clear();
  /** */
  vc.clear();
  /** */
  type.clear();
  /** */
  subtype.clear();
  /** */
  totname.clear();
  /** */
  seqnum.clear();
  /** */
  orbnum.clear();
  /** */
  subext.clear();
  /** */
  ext.clear();
  /** Trigger filename */
  triggerfilename.clear();
  /** extension of trigger file*/
  trigbase.clear();
  /** extension of trigger file*/
  trext.clear();
  /** version of the corrector*/
  corrver.clear();
}
/** No descriptions */
void SAarchive::AGILEFileName::init(){
  try{
  trigfnamelength=17;
  sapipe = true;
  /** true if is a filename with the subextension   <_sub.ext>  */
  subextension = false;
  /** true if is an orbital data filename*/
  orbdata = false;
  setDefault();
  }catch (const exception &e){
    cerr << "SAarchive::AGILEFileName::init() error"<< e.what()<< endl;
  }
}
/** No descriptions */
void SAarchive::AGILEFileName::setDefault(){
    /** */
try{
  totname.assign("");
    /** */
  base.assign("");
  /** */
  contact.assign("");
  /** */
  vc.assign("");
  /** */
  type.assign("");
  /** */
  subtype.assign("");
  /** */
  totname.assign("");
  /** */
  seqnum.assign("");
  /** */
  orbnum.assign("");
  /** */
  subext.assign("");
  /** */
  ext.assign("");
  /** Trigger filename */
  triggerfilename.assign("");
  /** extension of trigger file*/
  trigbase.assign("");
  /** extension of trigger file*/
  trext.assign("");
  /** version of the corrector*/
  corrver.assign("");
} catch(const exception &e ){
  cerr << "AGILEFileName::setDefault() error in setting default string values" << e.what() << endl;
}
}
/** No descriptions */
void SAarchive::AGILEFileName::setAbsoluteFileName(const string &afn){
  if (verbose)cout << "AGILEFileName::setAbsoluteFileName() setting "<< afn << endl;
  int lpos = afn.find_last_of("/");
  assignName(afn.substr(lpos+1));
  update();
}
/** No descriptions */
void SAarchive::AGILEFileName::setTrigAbsoluteFilename(const string &tafn){
  int lpos = tafn.find_last_of("/");
  assignTrigger(tafn.substr(lpos));
  updateTrigger();
}


/*!
    \fn SAarchive::AGILEFileName::getIrosMapFileName()
 */
string SAarchive::AGILEFileName::getIrosMapFileName()
{
  tempstring = "dat";
  setExtension(tempstring);
  tempstring = total();
  return tempstring;
}
/** returns the "root" of the name -without subsextension and extension-*/
string SAarchive::AGILEFileName::getNameRoot(){
  nameroot.clear();
  nameroot +=  base;
  nameroot +=  contact;
  nameroot +=  (string)"_";
  nameroot +=  vc;
  nameroot +=  (string)"_";
  nameroot +=  type;
  nameroot +=  subtype;
  nameroot +=  (string)"_";
  nameroot +=  seqnum;
  return nameroot;
}


/*!
    \fn SAarchive::AGILEFileName::getContactNumber()
 */
int  SAarchive::AGILEFileName::getContactNumber()
{
    contactnum = atoi(contact.c_str());
    return contactnum;
}
