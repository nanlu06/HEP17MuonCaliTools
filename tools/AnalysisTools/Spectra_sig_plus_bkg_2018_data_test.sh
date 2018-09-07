#!/bin/bash
for ieta in 26
#for ieta in 16 17 18 19 20 21 22 23 24 25 26
#for ieta in 16 17 18 19 20 21 22 23 24 25
do
  for iphi in all
  do
       ./bin/sig_plus_bkg_fit_data_perDetID_2018_test /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/Aug152018/tree_data_2018AB_319104-319311_ECAL_nvtx_sel19.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/test/ outtree_${ieta}_${iphi}_19.root $ieta $iphi 19  15
  done
done
