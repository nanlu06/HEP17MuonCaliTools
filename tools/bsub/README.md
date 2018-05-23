1. This folder has to be under the same CMSSW environment where the executable was compiled.
2. a few things that is handwritten for the moment (should be improved in the future, e.g. move to sub_batch.sh as inputs to the job):

in run_test.sh the last line

the directory where the code is run is specified in here:
path='/afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/CMSSW_9_2_6/src/bsub/new'

the input ntuple is specified /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/May012018/tree_data_2018A_v1_json.root

the output path is specified as /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/plots/tree_HcalCalHBHEMuonFilter-May23-2018A-v1-bsub-v1/
this folder has to be existed already before submitting bash jobs.
