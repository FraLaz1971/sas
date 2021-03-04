#!/bin/sh
echo compiling file $1.cpp
g++ -DHAVE_CONFIG_H -I/home/agile/projects/sasoa/sasoa_0_0_6 -I/home/agile/projects/sasoa/ -I$HEADAS/include -I$HEADAS/include/CCfits -I$QTDIR/include -I. -I. -I.. -Wnon-virtual-dtor -Wno-long-long -Wundef -Wall -pedantic -W -Wpointer-arith -Wwrite-strings -ansi -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -Wcast-align -Wconversion -O2 -DQT_THREAD_SUPPORT -D_REENTRANT -I/usr/local/headas-6.1.2/i686-pc-linux-gnu-libc2.4/include/ -fno-check-new -fexceptions -g -c $1.cpp -o $1.o 
