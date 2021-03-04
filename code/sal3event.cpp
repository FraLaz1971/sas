/***************************************************************************
                          sal3event.cpp  -  description
                             -------------------
    begin                : Wed Jun 21 2006
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

#include "sal3event.h"
namespace SAdata{
SAL3Event::SAL3Event(){
}
SAL3Event::~SAL3Event(){
}
/** No descriptions */
float SAL3Event::getAmplitude(){
  return amplitude;
}
/** No descriptions */
void SAL3Event::setAmplitude(float amp){
  amplitude = amp;
}
/** No descriptions */
void SAL3Event::setCount(long int c){
  count = c;
}
/** No descriptions */
long int SAL3Event::getCount(){
  return count;
}
/** No descriptions */
void SAL3Event::setPhotonId(long int pi){
  photon_id = pi; 
}
/** No descriptions */
long int SAL3Event::getPhotonId(){
  return photon_id;
}
/** No descriptions */
void SAL3Event::setPos(int p){
  pos = p; 
}
/** No descriptions */
int SAL3Event::getPos(){
  return pos;
}
/** No descriptions */
unsigned char SAL3Event::getDetector(){
  return detector;
}
/** No descriptions */
void SAL3Event::setDetector(unsigned char det){
  detector = det;
}
/** No descriptions */
void SAL3Event::setPosShift(float ps){
  pos_shift = ps;
}
/** No descriptions */
float SAL3Event::getPosShift(){
  return pos_shift;
}
/** No descriptions */
void SAL3Event::setSsid(unsigned char si){
  ssid = si;
}
/** No descriptions */
unsigned char SAL3Event::getSsid(){
  return ssid;
}
}/** No descriptions */
void SAdata::SAL3Event::setTime(double tm){
  time = tm;
}
/** No descriptions */
double SAdata::SAL3Event::getTime(){
  return time;
}
/** No descriptions */
void SAdata::SAL3Event::show(){
  cout << "#### SAL3Event ####" << endl;
  cout << "Count = " << count << endl;
  cout << "Photon Id = " << photon_id << endl;
  cout << "Time = " << time << endl;
  cout << "Amplitude = " << amplitude << endl;
  cout << "pos = " << pos << endl;  
  cout << "Detector = " << (int) detector << endl;
  cout << "pos_shift = " << pos_shift << endl;
  cout << "SSID = " << (int)ssid << endl;
  cout << "##################" << endl;
}
