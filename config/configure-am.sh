#/usr/$(bin)/env bash
echo "generating total makefile for $(uname) $OS ..." >&2
a=0;t=0;TARGETS="";RMTARGETS=""; EEXT="";OEXT=".o";SRCDIR=.;OBJDIR=.
OTARGETS="";BINDIR='../bin';LIBDIR='../lib'
echo 'SRCDIR = .'
echo 'BINDIR = ../bin'
echo 'LIBDIR = ../lib'
echo 'OBJDIR = .'
echo 'CC=gcc -g '
echo 'CXX=g++ -g '
echo 'LD=gcc '
echo 'CXXFLAGS = '
echo 'CFLAGS = '
echo 'RM = rm -f'
echo 'MV = mv '
echo 'CP = cp '
echo 'MAKE = make'
echo 'SRC = $(wildcard ./*.cpp)'
echo 'CPPFLAGS = -I. -I./CCfits'
echo 'LIBS = '
echo 'LDFLAGS = -lm'
echo 'EEXT='
echo 'OEXT=.o'
echo 'AR=ar rcs'

for t in $(ls -1 $SRCDIR/*.cpp)
do
	TARGET=$(basename ${t%.*})
	echo 'TARGET'$a = $TARGET
	echo 'OTARGET'$a = $SRCDIR/$TARGET$OEXT
	TARGETS="$TARGET $TARGETS"
	OTARGETS="$SRCDIR/$TARGET$OEXT $OTARGETS"
	if [[ ( $TARGET != "useanalysis" ) && ($TARGET != "useanalysis") ]]
	then
        RMTARGETS="$SRCDIR/$TARGET$EEXT $RMTARGETS"
	fi
	a=$(($a+1))
done
echo 'TARGETS' = $TARGETS
echo 'RMTARGETS' = $RMTARGETS
echo 'OTARGETS' = $OTARGETS
echo 'OBJ = $(OTARGETS)'
echo 'all: $(OBJ) libsas.a'
a=0
for s in $(ls -1 $SRCDIR/*.cpp)
do
	TARGET=$(basename ${s%.*})
        if [[ ($TARGET != "analysis") && ($TARGET != "useanalysis") ]]
        then
                echo '$(SRCDIR)/$(TARGET'$a')$(OEXT): $(SRCDIR)/$(TARGET'$a')'.cpp
                echo -e "\t"'$(CXX) $(CPPFLAGS) -c $(SRCDIR)/$(TARGET'$a').cpp  -o $(SRCDIR)/'$TARGET$OEXT
        fi
	a=$(($a+1)) 
done
echo 'libsas.a: $(OBJ)'
echo -e '\t $(AR) libsas.a $?'
echo 'echo created all targets' >&2
echo 'install: all'
echo -e '\t $(MV) libsas.a $(LIBDIR)'
echo '.PHONY: clean distclean '
echo 'clean: '
echo -e "\t"' $(RM) $(OBJ) libsas.a'
echo 'distclean: clean'
echo -e "\t" ' $(RM) $(BINDIR)/* Makefile* *.fit *.fits *.csv *.ssv *.tsv *.dat *.txt *.log'
echo "generating dirs" >&2
if ! test -d $BINDIR; then mkdir $BINDIR; fi
if ! test -d $LIBDIR; then mkdir $LIBDIR; fi
if ! test -d $OBJDIR; then mkdir $OBJDIR; fi
