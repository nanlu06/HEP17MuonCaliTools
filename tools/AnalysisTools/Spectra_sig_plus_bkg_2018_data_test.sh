#!/bin/bash
#cd /afs/cern.ch/user/j/jmao/work/public/releases/HCalCalibration/CMSSW_9_3_1/src/HEP17MuonCaliTools/tools/AnalysisTools
#eval `scramv1 runtime -sh`
#./bin/sig_only_fit_data /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/tree_HCalMIP_test4_data_PR2017BC-HcalCalHBHEMuonFilter-ReReco.root /afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/test/ outtree.root

#for ieta in 16 17 18 19 20
#for ieta in 20
#do
  #for iphi in 63 64 65 66
  #for iphi in 65
  #do
#for ieta in 21 22 23 24 25 26
#for ieta in 23 24 25 26
#do
#  for iphi in 63 65
#  do
for ieta in 26
#for ieta in 16 17 18 19 20 21 22 23 24 25 26
#for ieta in 16 17 18 19 20 21 22 23 24 25
#for ieta in 19 20 21 22 23
do
  for iphi in all
  do
        #./bin/sig_only_fit_data_perDetID_2018_pileuptest /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/May012018/tree_data_2018A_v2.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v2_pileuptest/ outtree_${ieta}_${iphi}.root $ieta $iphi > /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v2_pileuptest/log_${ieta}_${iphi}.log
        #./bin/sig_only_fit_data_perDetID_2018 /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/May012018/tree_data_2018A_v2.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v2/ outtree_${ieta}_${iphi}.root $ieta $iphi > /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v2/log_${ieta}_${iphi}.log
        #./bin/sig_only_fit_data_perDetID_2018_pileuptest /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/May012018/tree_data_2018A_v1.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v1_test/ outtree_${ieta}_${iphi}.root $ieta $iphi > /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May2-2018A-v1_test/log_${ieta}_${iphi}.log

       #./bin/sig_only_fit_data_perDetID_2018_test /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/July142018/tree_data_2018A_v1_v2_v3_ECAL_json.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-Aug15-v1/ outtree_${ieta}_${iphi}_20.root $ieta $iphi 20
       ./bin/sig_plus_bkg_fit_data_perDetID_2018_test /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/Aug152018/tree_data_2018AB_319104-319311_ECAL_nvtx_sel19.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/test/ outtree_${ieta}_${iphi}_19.root $ieta $iphi 19  15
  done
done
#./bin/sig_only_fit_data tree_test_code.root /afs/cern.ch/user/j/jmao/public/HCalMipCali/Plots/test_tree9/ out.root
