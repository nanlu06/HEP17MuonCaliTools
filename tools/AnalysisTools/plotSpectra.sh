#!/bin/bash
cd /afs/cern.ch/user/j/jmao/work/public/releases/HCalCalibration/CMSSW_9_3_1/src/HEP17MuonCaliTools/tools/AnalysisTools
eval `scramv1 runtime -sh`
./bin/sig_only_fit_data tree_test_code.root /afs/cern.ch/user/j/jmao/public/HCalMipCali/Plots/test_tree9/ out.root
