#/usr/bin/env bash
echo "generating total makefile for $(uname) $OS ..." >/dev/stderr
a=0;t=0;TARGETS="";RMTARGETS=""; EEXT="";OEXT=".o";SRCDIR=sas;OBJDIR=sas
OTARGETS=""
echo 'SRCDIR = sas'
echo 'OBJDIR = sas'
echo 'CC=gcc -g '
echo 'CXX=g++ -g '
echo 'LD=gcc '
echo 'CXXFLAGS = '
echo 'CFLAGS = '
echo 'RM = rm -f'
echo 'MV = mv '
echo 'CP = cp '
echo 'MAKE = make'
echo 'SRC = $(wildcard sas/*.cpp)'
echo 'CPPFLAGS = -Isas -Isas/CCfits'
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
#                echo '$(TARGET'$a'): $SRCDIR/$(TARGET'$a')$(EEXT)'
        fi
	a=$(($a+1)) 
done
#handle multifile targets
#echo 'src/analysis$(OEXT): src/analysis.c src/analysis.h src/defines.h'
#echo -e "\t"'$(CC)  $(CPPFLAGS) -c src/analysis.c   -o src/analysis$(OEXT) '
#echo 'src/useanalysis$(OEXT): src/useanalysis.c src/analysis.h src/defines.h '
#echo -e "\t"'$(CC)  $(CPPFLAGS) -c src/useanalysis.c  -o  src/useanalysis$(OEXT) '
#echo 'src/useanalysis$(EEXT): src/analysis$(OEXT) src/useanalysis$(OEXT)'
#echo -e "\t"'$(LD) $? -o src/analysis$(EEXT) $(LDFLAGS)'
#echo 'useanalysis: src/useanalysis$(EEXT)'
#echo 'analysis: useanalysis'
echo 'libsas.a: $(OBJ)'
echo -e '\t $(AR) libsas.a $?'

echo 'echo created all targets' >&2
echo 'install: all'
echo -e '\t $(MV) $(RMTARGETS) bin'
echo '.PHONY: clean distclean '
echo 'clean: '
echo -e "\t"' $(RM) $(OBJ) libsas.a'
echo 'distclean: clean'
echo -e "\t" ' $(RM) bin/* Makefile* *.fit *.fits *.csv *.ssv *.tsv *.dat *.txt *.log'
echo "generating dirs" >&2
if ! test -d bin; then mkdir  bin; fi
if ! test -d obj; then mkdir  obj; fi
