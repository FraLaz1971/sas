#!/bin/sh
aclocal
autoconf
automake
cp support/rlmm.m4 support/rlmm.m4.temp
mv support/rlmm.m4.temp support/rlmm.m4
cp aclocal.m4 aclocal.m4.temp
mv aclocal.m4.temp aclocal.m4
cp configure.ac configure.ac.temp
mv configure.ac.temp configure.ac
cp acinclude.m4 acinclude.m4.temp
mv acinclude.m4.temp acinclude.m4
cp Makefile.am Makefile.temp
mv Makefile.temp Makefile.am
cp configure configure_temp
mv configure_temp configure
./configure
make
