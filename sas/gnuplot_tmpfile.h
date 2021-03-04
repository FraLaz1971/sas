/***************************************************************************
                          gnuplot_tmpfile.h  -  description
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

#ifndef GNUPLOT_TMPFILE_H
#define GNUPLOT_TMPFILE_H


/**
  *@author Francesco Lazzarotto
  */

#include "gnuplot_base.h"
namespace Graphics  {
  using namespace Graphics;

class Gnuplot_Tmpfile : public Gnuplot_Base
{
protected:
  std::string tmpfilename;
  bool remove_file;

public:
  virtual int begin(const char * cmd_opt=NULL, const char * filename=NULL)
  {
    if(fp) return GNUPLOT_ALREADY_OPEN;

    cmdline = exec;
    if(cmd_opt)
      {
        cmdline += " ";
        cmdline += cmd_opt;
      }

    if(filename)
      {
        fp = ::fopen(filename, "w");
        tmpfilename = filename;
        remove_file = false;
      }
    else
      {
        char buf[] = "/tmp/gnuplot_XXXXXX";
        int fd = ::mkstemp(buf);
        if( fd == -1 ) return GNUPLOT_NG;
        fp = ::fdopen( fd, "w" );
        tmpfilename = buf;
        remove_file = true;
      }

    if( !fp )
      {
        tmpfilename.clear();
        return GNUPLOT_CANNOT_EXEC;
      }

    return GNUPLOT_OK;
  }

  virtual int end()
  {
    if( ! fp ) return GNUPLOT_OK;

    ::fflush(fp);
    ::fclose(fp);
    fp = NULL;

    ::system( (cmdline + " " + tmpfilename).c_str() );
    if( remove_file ) ::remove( tmpfilename.c_str() );

    return GNUPLOT_OK;
  }
};
}
#endif
