/***************************************************************************
                          gnuplot_base.h  -  description
                             -------------------
    begin                : Wed May 17 2006
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

#ifndef GNUPLOT_BASE_H
#define GNUPLOT_BASE_H

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <stdarg.h>
#include <iostream>
#include <string>

/**
  *@author Francesco Lazzarotto
  */

namespace Graphics  {
  using namespace Graphics;
  
class Gnuplot_Base
{
protected:

  std::string exec;
  std::string cmdline;

  FILE * fp;

public:
  explicit Gnuplot_Base(const char * execname=NULL) : fp(NULL)
  {
    if(execname)
      {
        exec = execname;
      }
    else
      {
        exec = "gnuplot";
      }
  }

  virtual ~Gnuplot_Base()
  {
    end();
  }

  enum { GNUPLOT_OK = 0,
         GNUPLOT_NG,
         GNUPLOT_ALREADY_OPEN,
         GNUPLOT_NOT_OPEN,
         GNUPLOT_CANNOT_EXEC
  };

virtual int begin(const char * cmd_opt=NULL, const char * reserved=NULL) = \
    0;
  virtual int end() {return 0;}

  int flush()
  {
    if( fp ) ::fflush(fp);

    return GNUPLOT_OK;
  }

  int begin_data()
  {
    if( ! fp ) return GNUPLOT_NOT_OPEN;
    return flush();
  }

  int end_data()
  {
    if( ! fp ) return GNUPLOT_NOT_OPEN;
    ::fprintf(fp, "e\n");
    return flush();
  }

  int command(const char * cmd, ...)
  {
    if(!fp) return GNUPLOT_NOT_OPEN;
    if(!cmd) return GNUPLOT_OK;

    { va_list ap; va_start(ap, cmd); ::vfprintf(fp, cmd, ap); va_end(ap); }

    return GNUPLOT_OK;
  }

  int commandln(const char * cmd, ...)
  {
    if(!fp) return GNUPLOT_NOT_OPEN;
    if(!cmd) return GNUPLOT_OK;

    { va_list ap; va_start(ap, cmd); ::vfprintf(fp, cmd, ap); va_end(ap); }
    ::fprintf(fp, "\n");

    return GNUPLOT_OK;
  }
};
}
#endif
