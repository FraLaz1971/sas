/***************************************************************************
                          saevent.cpp  -  description
                             -------------------
    begin                : Tue Jul 25 2006
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
namespace SAdata{

using namespace SAdata;
using namespace std;
class SAEvent {
  public:
  /** No descriptions */
	SAEvent();
  /** No descriptions */
	SAEvent(const SAEvent &sev);
  /** No descriptions */
	~SAEvent();
  /** No descriptions */
double time;
};
}