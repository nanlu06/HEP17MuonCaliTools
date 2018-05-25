#!/bin/bash
#muon gun sample with pileup
#path='/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-wPU-MuonGun-v1'
#data
path='/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-2018A-v1-bsub-v2'
#rm $path/NoIso_test_pileupCorr_depth*_iphi0_ieta*.root
for idepth in {1..7}
#for idepth in {1..2}
do
  for iphi in 0
  do
    for ieta in {16..26}
    do
    ./bin/graph_pileupCorr_perDetID_2018_test $path/ outtree_all.root ${idepth} ${iphi} ${ieta}
    done
  done
done
rm $path/NoIso_test_pileupCorr.root
hadd $path/NoIso_test_pileupCorr.root $path/NoIso_test_pileupCorr_depth*_iphi0_ieta*.root
