/***************************************************************************
                          sal3event.h  -  description
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

#ifndef SAL3EVENT_H
#define SAL3EVENT_H

#include <iostream>
/**
  *@author Francesco Lazzarotto
  */
namespace SAdata{

using namespace SAdata;
using namespace std;
class SAL3Event {
public: 
	SAL3Event();
	~SAL3Event();
  /** No descriptions */
  void setPhotonId(long int pi);
  /** No descriptions */
  long int getCount();
  /** No descriptions */
  void setCount(long int c);
  /** No descriptions */
  void setAmplitude(float amp);
  /** No descriptions */
  float getAmplitude();
  /** No descriptions */
  float getPosShift();
  /** No descriptions */
  void setPosShift(float ps);
  /** No descriptions */
  void setDetector(unsigned char det);
  /** No descriptions */
  unsigned char getDetector();
  /** No descriptions */
  int getPos();
  /** No descriptions */
  void setPos(int p);
  /** No descriptions */
  long int getPhotonId();
  /** No descriptions */
  unsigned char getSsid();
  /** No descriptions */
  void setSsid(unsigned char si);
  /** No descriptions */
  double getTime();
  /** No descriptions */
  void setTime(double);
  /** No descriptions */
  void show();
private:

        long int count;
        long int photon_id;
        double time;
        float amplitude;
        int pos;
        unsigned char detector;
        float pos_shift;
        unsigned char ssid; 
};
}
#endif
