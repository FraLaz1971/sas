#!/bin/sh
/bin/sh /home/agile/projects/sasoa/libtool --silent --tag=CXX --mode=link g++  -Wnon-virtual-dtor -Wno-long-long -Wundef -Wall -pedantic -W -Wpointer-arith -Wwrite-strings -ansi -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -Wcast-align -Wconversion -O2  -DQT_THREAD_SUPPORT -D_REENTRANT   -L/usr/local/headas-6.1.2/i686-pc-linux-gnu-libc2.4/lib/ -L/home/agile/lib -L/usr/X11/lib/ -L/usr/lib/qt3/lib/  -lreadline -lqt-mt -lCCfits -lcfitsio -lncurses -lsas -o $1 $1.o