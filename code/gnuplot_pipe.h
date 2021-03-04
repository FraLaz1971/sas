/***************************************************************************
                          gnuplot_pipe.h  -  description
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

#ifndef GNUPLOT_PIPE_H
#define GNUPLOT_PIPE_H


/**
  *@author Francesco Lazzarotto
  */
#include "gnuplot_base.h"

namespace Graphics  {
    using namespace Graphics;

class Gnuplot_Pipe : public Gnuplot_Base
{
public:
  virtual int begin(const char * cmd_opt=NULL, const char * reserved=NULL)
  {
    if(fp) return GNUPLOT_ALREADY_OPEN;

    cmdline = exec;
    if(cmd_opt)
      {
        cmdline += " ";
        cmdline += cmd_opt;
      }

    fp = ::popen( cmdline.c_str(), "w" );
    if( !fp ) return GNUPLOT_CANNOT_EXEC;

    return GNUPLOT_OK;
  }

  virtual int end()
  {
    if( ! fp ) return GNUPLOT_OK;

    ::fflush(fp);
    ::pclose(fp);
    fp = NULL;

    return GNUPLOT_OK;
  }

};
}
#endif
