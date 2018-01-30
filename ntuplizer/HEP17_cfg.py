import FWCore.ParameterSet.Config as cms

process = cms.Process("RaddamMuon")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("RecoJets.Configuration.CaloTowersES_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag='92X_dataRun2_Prompt_v9'

process.load("RecoLocalCalo.EcalRecAlgos.EcalSeverityLevelESProducer_cfi")
process.load("Calibration.HcalCalibAlgos.hep17Muon_cfi")

#if 'MessageLogger' in process.__dict__:
#    process.MessageLogger.categories.append('HBHEMuon')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd.unl.edu//store/data/Run2017B/SingleMuon/RECO/PromptReco-v2/000/298/678/00000/C0C0C0B0-A466-E711-AE46-02163E019E8C.root'
#        'root://xrootd.unl.edu//store/mc/Phys14DR/DYToMuMu_M-50_Tune4C_13TeV-pythia8/GEN-SIM-RECO/PU20bx25_tsg_castor_PHYS14_25_V1-v1/10000/184C1AC9-A775-E411-9196-002590200824.root'
        )
                            )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("Validation_test.root")
)

#process.hep17Muon.UseRaw = False
#process.hep17Muon.UnCorrect = False
#process.hep17Muon.GetCharge = True
#process.hep17Muon.CollapseDepth = False
#process.hep17Muon.IsItPlan1 = True
#process.hep17Muon.IgnoreHECorr = False
#process.hep17Muon.IsItPreRecHit = True
process.hep17Muon.MaxDepth = 7
process.hep17Muon.LabelHBHERecHit = cms.InputTag("hbheprereco")
process.hep17Muon.Verbosity = 0

process.p = cms.Path(process.hep17Muon)
