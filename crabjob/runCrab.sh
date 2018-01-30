#cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.sh
voms-proxy-init --voms cms
crab submit -c scrabconfig_data.py
