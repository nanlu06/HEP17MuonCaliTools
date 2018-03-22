#!/bin/bash
rm /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/tree_HcalCalHBHEMuonFilter-NovReReco_March5/NoIso_test_pileupCorr_depth*_iphi0_ieta*.root
for idepth in {1..7}
do
  for iphi in 0
  do
    for ieta in {16..26}
    do
    ./bin/graph_pileupCorr_perDetID_test /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/tree_HcalCalHBHEMuonFilter-NovReReco_March5/ outtree_all.root ${idepth} ${iphi} ${ieta}
    done
  done
done
rm /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/tree_HcalCalHBHEMuonFilter-NovReReco_March5/NoIso_test_pileupCorr_det.root
hadd /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/tree_HcalCalHBHEMuonFilter-NovReReco_March5/NoIso_test_pileupCorr_det.root /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/tree_HcalCalHBHEMuonFilter-NovReReco_March5/NoIso_test_pileupCorr_depth*_iphi0_ieta*.root
