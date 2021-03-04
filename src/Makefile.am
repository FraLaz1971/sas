#~/serenhello % cat src/Makefile.am
bin_PROGRAMS = amhello
libamhello_a_SOURCES = amhellofunc.c ../include/amhellofunc.h
amhello_SOURCES = amhello.c
instdir = ${HOME}/Software/amhello/lib
inst_LIBRARIES = libamhello.a
amhello_LDADD = libamhello.a
