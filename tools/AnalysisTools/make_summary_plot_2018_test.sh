#!/bin/bash
#for ieta in {16..26}
#MC
#path='/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-wPU-MuonGun-v1/'
#data
path='/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-2018A-v1-bsub-v2/'
for ieta in {16..26}
do
  ./bin/graph_energy_per_layer_vs_depth $path NoIso_test_pileupCorr.root ${ieta}
done
#rm $path/energy_per_layer.root
#hadd $path/energy_per_layer.root $path/energy_per_layer_*.root
./bin/summary_plot $path energy_per_layer.root 0.3 0.1
