source /cvmfs/cms.cern.ch/crab3/crab.sh
path=/afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali_test/CMSSW_9_4_0_pre3/src/Calibration/HcalCalibAlgos/test/crab_prod
declare -a arr=(
"crab_MIP_DY_NoPU_test_crab_v4"
"crab_MIP_DY_wPU_test_crab_v4"
)
for i in "${arr[@]}"
do
   echo "$i"
   cd $i
   crab report --dir $path/$i
   crab status
   crab resubmit
   crab status
   cd ../ 
done
