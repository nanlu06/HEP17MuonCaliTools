from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'MIP_DY_wPU_test_crab_v4'
config.General.workArea = 'crab_prod'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'HEP17_cfg.py'

config.Data.inputDataset = '/DYToMuMu_M-20_13TeV_pythia8/RunIISummer17DRPremix-92X_upgrade2017_realistic_v10-v2/GEN-SIM-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/group/dpg_hcal/comm_hcal/nlu'
config.Data.publication = True
config.Data.outputDatasetTag = 'DY_wPU_test_crab_v4'

config.Site.storageSite = 'T2_CH_CERN'
