#!/bin/bash
path=`pwd`
echo $path
cd $path/workarea
ieta=$1
iphi=$2
ivtx=$3
echo $ieta $iphi $ivtx
./sig_only_fit_data_perDetID_2018_test /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/May012018/tree_data_2018A_v1_json.root /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-2018A-v1-bsub-v1/ outtree_${ieta}_${iphi}_${ivtx}.root $ieta $iphi $ivtx > /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-2018A-v1-bsub-v1/log_${ieta}_${iphi}_${ivtx}.log
