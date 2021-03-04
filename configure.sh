CFLAGS=""; CPPFLAGS="";LDFLAGS="";CXXFLAGS=""
CC=gcc
CXX=g++
CPPFLAGS="-Wall"
PKGHOME=$(pwd)
PKGNAME=sas
export CFLAGS="-std=c99 -I$PKGHOME/include"
echo CFLAGS = $CFLAGS
LDFLAGS="-Llib"
autoreconf
autoconf
automake --add-missing
./configure --prefix=$HOME/Software/$PKGNAME
cd $PKGNAME
../config/configure-am.sh > Makefile
cd $OLDPWD

