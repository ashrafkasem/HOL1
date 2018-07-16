#!/bin/bash

# Without extension. So if the file is file.cc: ./<scriptname> file
FILE=$1

eval `scramv1 runtime -sh`

ROOT_FLAGS=`root-config --libs --cflags --ldflags`
CLHEP_FLAGS="-I/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/include -L/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/lib -lCLHEP -ldl -Wl,-rpath /cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/lib"

g++ -std=c++11 -O2 $FILE.cc -o $FILE $ROOT_FLAGS $CLHEP_FLAGS
