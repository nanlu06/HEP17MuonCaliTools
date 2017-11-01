# Use the following on IRIX 6.5 and Linux 2.4
# Last tested with p15.06.01
#

ROOTLIBS = `/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.08.07/bin/root-config --libs`
OPTCOMP  = `/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.08.07/bin/root-config --cflags`

SPECIALFLAGS= --exceptions
CFLAGS = -I. 
LFLAGS =

RCXX = $(CFLAGS) $(ROOTCFLAGS)
DBG = -g -L -O
CC = g++ ${DBG} $(RCXX) $(OPTCOMP) 
F77 = f77

all: run

run:  readMC.C   NtuplerReader.C   NtuplerReader.h 
	$(CC) readMC.C  NtuplerReader.C  $(ROOTLIBS) -o readMC

clean:
	\rm -f *.o

