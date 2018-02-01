from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'MIP_DY_wPU_test_crab_v4'  #change name
config.General.workArea = 'crab_prod'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'HEP17_cfg.py'

config.Data.inputDataset = '/DYToMuMu_M-20_13TeV_pythia8/RunIISummer17DRPremix-92X_upgrade2017_realistic_v10-v2/GEN-SIM-RECO'#change the name of the dataset
config.Data.inputDBS = 'global'
config.Data.lumiMask = 'dataJSON/Cert_294927-302654_13TeV_PromptReco_Collisions17_JSON.txt'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/group/dpg_hcal/comm_hcal/nlu' #change user name
config.Data.publication = True
config.Data.outputDatasetTag = 'DY_wPU_test_crab_v4' #change name

config.Site.storageSite = 'T2_CH_CERN'
