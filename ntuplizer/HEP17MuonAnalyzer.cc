#include <memory>
#include <iostream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include "TPRegexp.h"
#include <TLorentzVector.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"

//////////////trigger info////////////////////////////////////

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTConfigData.h"

#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h" 
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h" 
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgoRcd.h"

#include "CondFormats/HcalObjects/interface/HcalRespCorrs.h"
#include "CondFormats/DataRecord/interface/HcalRespCorrsRcd.h"

#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

#include "Calibration/IsolatedParticles/interface/CaloPropagateTrack.h"
#include "Calibration/IsolatedParticles/interface/eECALMatrix.h" 
#include "Calibration/IsolatedParticles/interface/eHCALMatrix.h" 

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/CaloTopology/interface/CaloSubdetectorTopology.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/HcalCommonData/interface/HcalDDDRecConstants.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#define EDM_ML_DEBUG

class HEP17MuonAnalyzer : public edm::EDAnalyzer {

public:
  explicit HEP17MuonAnalyzer(const edm::ParameterSet&);
  ~HEP17MuonAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
   
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup& );
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void   clearVectors();
  int    matchId(const HcalDetId&, const HcalDetId&);
  double activeLength(const DetId&);
  bool   isGoodVertex(const reco::Vertex& vtx);
  double respCorr(const DetId& id);
  double gainFactor(const edm::ESHandle<HcalDbService>&, const HcalDetId& id);
  int    depth16HE(int ieta, int iphi);

  // ----------member data ---------------------------
  HLTConfigProvider          hltConfig_;
  edm::Service<TFileService> fs;
  edm::InputTag              HLTriggerResults_;
  edm::InputTag              labelHBHERecHit_, labelEBRecHit_, labelEERecHit_;
  std::string                labelVtx_, labelMuon_;
  int                        verbosity_, maxDepth_, kount_;
  bool                       useRaw_;
  const int                  MaxDepth=7;
  const HcalTopology        *theHBHETopology;
  HcalRespCorrs             *respCorrs_;

  edm::EDGetTokenT<edm::TriggerResults>                   tok_trigRes_;
  edm::EDGetTokenT<reco::VertexCollection>                tok_Vtx_;
  edm::EDGetTokenT<EcalRecHitCollection>                  tok_EB_;
  edm::EDGetTokenT<EcalRecHitCollection>                  tok_EE_;
  edm::EDGetTokenT<HBHERecHitCollection>                  tok_HBHE_;
  edm::EDGetTokenT<reco::MuonCollection>                  tok_Muon_;

  //////////////////////////////////////////////////////
  std::vector<double>       ptGlob_, etaGlob_, phiGlob_, chiGlobal_;
  std::vector<double>       globalMuonHits_,matchedStat_,globalTrckPt_;
  std::vector<double>       globalTrckEta_,globalTrckPhi_,trackerLayer_;
  std::vector<double>       innerTrackpt_,innerTracketa_,innerTrackphi_;
  std::vector<int>          matchedId_,numPixelLayers_,muon_tight1_, muon_tight2_;
  std::vector<double>       chiTracker_,dxyTracker_,dzTracker_;
  std::vector<double>       outerTrackPt_,outerTrackEta_,outerTrackPhi_;
  std::vector<double>       outerTrackChi_,outerTrackHits_,outerTrackRHits_;
  std::vector<double>       tight_LongPara_,tight_PixelHits_,tight_TransImpara_;
  std::vector<bool>         innerTrack_, outerTrack_, globalTrack_;
  std::vector<double>       isolationR04_,isolationR03_, TrkisolationR03_;
  std::vector<double>       energyMuon_,hcalEnergy_,ecalEnergy_;//hoEnergy_;
  std::vector<double>       ecal1x1Energy_,ecal3x3Energy_,ecal5x5Energy_,ecal15x15Energy_,ecal25x25Energy_,hcal1x1Energy_, pMuon_, cMuon_, DiMuonM_;
  std::vector<int>          hcalHot_;
  std::vector<unsigned int> ecalDetId_,hcalDetId_,ehcalDetId_;
  std::vector<double>       hcalDepth1Charge_, hcalDepth1UEnergy_, hcalDepth1Energy_, hcalDepth1Energy1_, hcalDepth1Energy2_, hcalDepth1Energy3_, hcalDepth1Energy4_, hcalDepth1Energy5_, hcalDepth1Energy6_, hcalDepth1Energy7_, hcalDepth1Energy8_, hcalDepth1ActiveLength_;
  std::vector<double>       hcalDepth2Charge_, hcalDepth2UEnergy_, hcalDepth2Energy_, hcalDepth2Energy1_, hcalDepth2Energy2_, hcalDepth2Energy3_, hcalDepth2Energy4_, hcalDepth2Energy5_, hcalDepth2Energy6_, hcalDepth2Energy7_, hcalDepth2Energy8_, hcalDepth2ActiveLength_;
  std::vector<double>       hcalDepth3Charge_, hcalDepth3UEnergy_, hcalDepth3Energy_, hcalDepth3Energy1_, hcalDepth3Energy2_, hcalDepth3Energy3_, hcalDepth3Energy4_, hcalDepth3Energy5_, hcalDepth3Energy6_, hcalDepth3Energy7_, hcalDepth3Energy8_, hcalDepth3ActiveLength_;
  std::vector<double>       hcalDepth4Charge_, hcalDepth4UEnergy_, hcalDepth4Energy_, hcalDepth4Energy1_, hcalDepth4Energy2_, hcalDepth4Energy3_, hcalDepth4Energy4_, hcalDepth4Energy5_, hcalDepth4Energy6_, hcalDepth4Energy7_, hcalDepth4Energy8_, hcalDepth4ActiveLength_;
  std::vector<double>       hcalDepth5Charge_, hcalDepth5UEnergy_, hcalDepth5Energy_, hcalDepth5Energy1_, hcalDepth5Energy2_, hcalDepth5Energy3_, hcalDepth5Energy4_, hcalDepth5Energy5_, hcalDepth5Energy6_, hcalDepth5Energy7_, hcalDepth5Energy8_, hcalDepth5ActiveLength_;
  std::vector<double>       hcalDepth6Charge_, hcalDepth6UEnergy_, hcalDepth6Energy_, hcalDepth6Energy1_, hcalDepth6Energy2_, hcalDepth6Energy3_, hcalDepth6Energy4_, hcalDepth6Energy5_, hcalDepth6Energy6_, hcalDepth6Energy7_, hcalDepth6Energy8_, hcalDepth6ActiveLength_;
  std::vector<double>       hcalDepth7Charge_, hcalDepth7UEnergy_, hcalDepth7Energy_, hcalDepth7Energy1_, hcalDepth7Energy2_, hcalDepth7Energy3_, hcalDepth7Energy4_, hcalDepth7Energy5_, hcalDepth7Energy6_, hcalDepth7Energy7_, hcalDepth7Energy8_, hcalDepth7ActiveLength_;
  std::vector<int>          hcal_ieta_, hcal_iphi_, hcal_ieta_hot_, hcal_iphi_hot_;
  std::vector<HcalDDDRecConstants::HcalActiveLength> actHB, actHE;
  std::vector<std::string>  all_triggers;
  ////////////////////////////////////////////////////////////

  TTree                    *tree_;
  std::vector<bool>         muon_is_good_, muon_global_, muon_tracker_;// ismediummuon_; //isloosemuon_, istightmuon_;
  std::vector<int>          hltresults;
  unsigned int              runNumber_, nvtx_, nvtx_notFake_, nvtx_good_,eventNumber_ , lumiNumber_, bxNumber_;
 };

HEP17MuonAnalyzer::HEP17MuonAnalyzer(const edm::ParameterSet& iConfig): theHBHETopology(nullptr), respCorrs_(nullptr) {
  //now do what ever initialization is needed
  kount_            = 0;
  HLTriggerResults_ = iConfig.getParameter<edm::InputTag>("HLTriggerResults");
  labelVtx_         = iConfig.getParameter<std::string>("LabelVertex");
  //labelEBRecHit_    = iConfig.getParameter<std::string>("LabelEBRecHit");
  //labelEERecHit_    = iConfig.getParameter<std::string>("LabelEERecHit");
  //labelHBHERecHit_  = iConfig.getParameter<std::string>("LabelHBHERecHit");
  labelEBRecHit_    = iConfig.getParameter<edm::InputTag>("LabelEBRecHit");
  labelEERecHit_    = iConfig.getParameter<edm::InputTag>("LabelEERecHit");
  labelHBHERecHit_  = iConfig.getParameter<edm::InputTag>("LabelHBHERecHit");
  labelMuon_        = iConfig.getParameter<std::string>("LabelMuon");
  verbosity_        = iConfig.getUntrackedParameter<int>("Verbosity",0);
  maxDepth_         = iConfig.getUntrackedParameter<int>("MaxDepth",4);
  if (maxDepth_ > MaxDepth) maxDepth_ = MaxDepth;
  else if (maxDepth_ < 1)   maxDepth_ = 4;
  std::string modnam = iConfig.getUntrackedParameter<std::string>("ModuleName","");
  std::string procnm = iConfig.getUntrackedParameter<std::string>("ProcessName","");
  useRaw_            = iConfig.getParameter<bool>("UseRaw");

  tok_trigRes_  = consumes<edm::TriggerResults>(HLTriggerResults_);
  tok_EB_       = consumes<EcalRecHitCollection>(labelEBRecHit_);
  tok_EE_       = consumes<EcalRecHitCollection>(labelEERecHit_);
  tok_HBHE_     = consumes<HBHERecHitCollection>(labelHBHERecHit_);

  if (modnam == "") {
    tok_Vtx_      = consumes<reco::VertexCollection>(labelVtx_);
    tok_Muon_     = consumes<reco::MuonCollection>(labelMuon_);
    edm::LogVerbatim("HBHEMuon")  << "Labels used " << HLTriggerResults_ << " "
                                  << labelVtx_ << " " << labelEBRecHit_ << " "
                                  << labelEERecHit_ << " " << labelHBHERecHit_
                                  << " " << labelMuon_;
  } else {
    tok_Vtx_      = consumes<reco::VertexCollection>(edm::InputTag(modnam,labelVtx_,procnm));
    tok_Muon_     = consumes<reco::MuonCollection>(edm::InputTag(modnam,labelMuon_,procnm));
    edm::LogVerbatim("HBHEMuon")   << "Labels used "   << HLTriggerResults_
                                   << "\n            " << edm::InputTag(modnam,labelVtx_,procnm)
                                   << "\n            " << labelEBRecHit_
                                   << "\n            " << labelEERecHit_
                                   << "\n            " << labelHBHERecHit_
                                   << "\n            " << edm::InputTag(modnam,labelMuon_,procnm);
  }

}

HEP17MuonAnalyzer::~HEP17MuonAnalyzer() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called for each event  ------------
void HEP17MuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  ++kount_;
  clearVectors();
  // depthHE is the first depth index for HE for |ieta| = 16
  // It used to be 3 for all runs preceding 2017 and 4 beyond that
  int depthHE = (maxDepth_ <= 6) ? 3 : 4;
  runNumber_   = iEvent.id().run();
  eventNumber_ = iEvent.id().event();
  lumiNumber_  = iEvent.id().luminosityBlock();
  bxNumber_    = iEvent.bunchCrossing();
#ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "Run " << runNumber_ << " Event " << eventNumber_
			   << " Lumi " << lumiNumber_ << " BX " << bxNumber_
			   << std::endl;
#endif  
  edm::Handle<edm::TriggerResults> _Triggers;
  iEvent.getByToken(tok_trigRes_, _Triggers); 
#ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "Size of all triggers "  
			   << all_triggers.size() << std::endl;
#endif
  int Ntriggers = all_triggers.size();
#ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "Size of HLT MENU: " << _Triggers->size()
			   << std::endl;
#endif
  if (_Triggers.isValid()) {
    const edm::TriggerNames &triggerNames_ = iEvent.triggerNames(*_Triggers);
    std::vector<int> index;
    for (int i=0; i<Ntriggers; i++) {
      index.push_back(triggerNames_.triggerIndex(all_triggers[i]));
      int triggerSize = int( _Triggers->size());
#ifdef EDM_ML_DEBUG
      edm::LogInfo("HBHEMuon") << "outside loop " << index[i]
			       << "\ntriggerSize " << triggerSize
			       << std::endl;
#endif
      if (index[i] < triggerSize) {
	hltresults.push_back(_Triggers->accept(index[i]));
#ifdef EDM_ML_DEBUG
	edm::LogInfo("HBHEMuon") << "Trigger_info " << triggerSize
				 << " triggerSize " << index[i]
				 << " trigger_index " << hltresults.at(i)
				 << " hltresult" << std::endl;
#endif
      } else {
	edm::LogInfo("HBHEMuon") << "Requested HLT path \"" 
				 << "\" does not exist\n";
      }
    }
  }

  #ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "after trigger ------------ " << std::endl;
  #endif

  edm::ESHandle<CaloGeometry> pG;
  iSetup.get<CaloGeometryRecord>().get(pG);
  const CaloGeometry* geo = pG.product();
  
  edm::ESHandle<MagneticField> bFieldH;
  iSetup.get<IdealMagneticFieldRecord>().get(bFieldH);
  const MagneticField* bField = bFieldH.product();
  
  edm::ESHandle<EcalChannelStatus> ecalChStatus;
  iSetup.get<EcalChannelStatusRcd>().get(ecalChStatus);
  const EcalChannelStatus* theEcalChStatus = ecalChStatus.product();
  
  edm::ESHandle<EcalSeverityLevelAlgo> sevlv;
  iSetup.get<EcalSeverityLevelAlgoRcd>().get(sevlv);
  
  edm::ESHandle<CaloTopology> theCaloTopology;
  iSetup.get<CaloTopologyRecord>().get(theCaloTopology);
  const CaloTopology *caloTopology = theCaloTopology.product();
 
  /* 
  edm::ESHandle<HcalTopology> htopo;
  iSetup.get<HcalRecNumberingRecord>().get(htopo);
  const HcalTopology* theHBHETopology = htopo.product();
  */

  edm::ESHandle<HcalDbService> conditions;
  iSetup.get<HcalDbRecord>().get(conditions);

  // Relevant blocks from iEvent
  edm::Handle<reco::VertexCollection> vtx;
  iEvent.getByToken(tok_Vtx_, vtx);
  
  edm::Handle<EcalRecHitCollection> barrelRecHitsHandle;
  iEvent.getByToken(tok_EB_, barrelRecHitsHandle);
  edm::Handle<EcalRecHitCollection> endcapRecHitsHandle;
  iEvent.getByToken(tok_EE_, endcapRecHitsHandle);
  
  edm::Handle<HBHERecHitCollection> hbhe;
  iEvent.getByToken(tok_HBHE_, hbhe);
  
  edm::Handle<reco::MuonCollection> _Muon;
  iEvent.getByToken(tok_Muon_, _Muon);
  // get handles to calogeometry and calotopology
  #ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "before checking vtx.isValid() ------------ " << std::endl;
  #endif

  if (!(vtx.isValid()))                  return;
  reco::VertexCollection::const_iterator firstGoodVertex = vtx->end();
  for (reco::VertexCollection::const_iterator it = vtx->begin(); it != firstGoodVertex; it++) {
    if (isGoodVertex(*it)) {
      firstGoodVertex = it;
      break;
    }
  }

  #ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "before vertex: ------------ " << std::endl;
  #endif

  // require a good vertex
  if (firstGoodVertex == vtx->end())     return;
  #ifdef EDM_ML_DEBUG
  edm::LogInfo("HBHEMuon") << "after vertex: ------------ " << std::endl;
  #endif

   nvtx_=0; nvtx_notFake_=0; nvtx_good_=0;
   for (reco::VertexCollection::const_iterator it = vtx->begin(); it != vtx->end(); it++) {
    nvtx_++;
    if (!it->isFake()) nvtx_notFake_++;
    if (isGoodVertex(*it)) nvtx_good_++;
   }


  bool accept(false);
  
  #ifdef EDM_ML_DEBUG
  //edm::LogInfo("HBHEMuon") << "accept: " << accept<<std::endl;
  #endif
  //std::cout << "check before muon loop"<<std::endl;
  if (_Muon.isValid() && barrelRecHitsHandle.isValid() && 
      endcapRecHitsHandle.isValid() && hbhe.isValid()) { 
      //std::cout << "before loop into muons"<<std::endl;
    for (reco::MuonCollection::const_iterator RecMuon = _Muon->begin(); RecMuon!= _Muon->end(); ++RecMuon)  {
      
      double eEcal(-10000.0), eEcal3x3(-10000.0), eEcal5x5(-10000.0), eEcal15x15(-10000.0), eEcal25x25(-10000.0),eHcal(-10000.0);
      int ieta(-1000), iphi(-1000), ietahot(-1000), iphihot(-1000);
      double chgHcalDepth[MaxDepth], ueHcalDepth[MaxDepth], eHcalDepth[MaxDepth], eHcalDepth1[MaxDepth], eHcalDepth2[MaxDepth], eHcalDepth3[MaxDepth], eHcalDepth4[MaxDepth], eHcalDepth5[MaxDepth], eHcalDepth6[MaxDepth], eHcalDepth7[MaxDepth], eHcalDepth8[MaxDepth];
      double activeL[MaxDepth];
      int isHot(0);
      int tmpmatch(0);

      for (int i=0; i<MaxDepth; ++i){
        chgHcalDepth[i] = ueHcalDepth[i] = eHcalDepth[i] = activeL[i] = eHcalDepth1[i] = eHcalDepth2[i] = eHcalDepth3[i] = eHcalDepth4[i] = eHcalDepth5[i] = eHcalDepth6[i] = eHcalDepth7[i] = eHcalDepth8[i] = -10000.0;
      }

      if (RecMuon->innerTrack().isNonnull()) {
	const reco::Track* pTrack = (RecMuon->innerTrack()).get();
	spr::propagatedTrackID trackID = spr::propagateCALO(pTrack, geo, bField, (((verbosity_/100)%10>0)));
	
	ecalDetId_.push_back((trackID.detIdECAL)()); 
	hcalDetId_.push_back((trackID.detIdHCAL)());  
	ehcalDetId_.push_back((trackID.detIdEHCAL)());
  
	HcalDetId check;
	std::pair<bool,HcalDetId> info = spr::propagateHCALBack(pTrack,  geo, bField, (((verbosity_/100)%10>0)));
	if (info.first) { 
	  check = info.second;
	}	

	if (trackID.okHCAL) {
	  const DetId closestCell(trackID.detIdHCAL);
	  HcalDetId hcidt(closestCell.rawId());  
	  if ((hcidt.ieta() == check.ieta()) && (hcidt.iphi() == check.iphi()))
	    tmpmatch= 1;

	  HcalSubdetector subdet = HcalDetId(closestCell).subdet();
	  ieta   = HcalDetId(closestCell).ieta();
	  iphi   = HcalDetId(closestCell).iphi();
	  bool            hborhe = (std::abs(ieta) == 16);

          bool muon_1 = RecMuon->pt()>20.0;
          bool muon_2 = muon::isMediumMuon(*RecMuon);
          bool muon_3 = (RecMuon->pfIsolationR04().sumChargedHadronPt + std::max(0.,RecMuon->pfIsolationR04().sumNeutralHadronEt + RecMuon->pfIsolationR04().sumPhotonEt - (0.5 *RecMuon->pfIsolationR04().sumPUPt))) / RecMuon->pt()<0.15;

          //if (ieta< 30 && ieta>15 && iphi>62 && iphi<67 && muon_1 && muon_2 && muon_3){
          if (ieta< 30 && ieta>15 && muon_1 && muon_2 && muon_3){
          //if (ieta< 28 && ieta>19 && iphi>62 && iphi<67){
              accept = true;
              int tight1 = 0;
              if(muon::isTightMuon(*RecMuon,*firstGoodVertex)) tight1 = 1;
              muon_tight1_.push_back(tight1);
      // this part is moved from before to here to save time
      muon_is_good_.push_back(RecMuon->isPFMuon());
      muon_global_.push_back(RecMuon->isGlobalMuon());
      muon_tracker_.push_back(RecMuon->isTrackerMuon());
      ptGlob_.push_back((RecMuon)->pt());
      etaGlob_.push_back(RecMuon->eta());
      phiGlob_.push_back(RecMuon->phi());
      energyMuon_.push_back(RecMuon->energy());
      pMuon_.push_back(RecMuon->p());
      cMuon_.push_back(RecMuon->charge());
      TLorentzVector lvMuon;
      lvMuon.SetPtEtaPhiM(RecMuon->pt(), RecMuon->eta(), RecMuon->phi(), 0.10566);
             
      double dimuon_M_tmp=-999.;
      int tight2 = 0;
      for (reco::MuonCollection::const_iterator iMuon = _Muon->begin(); iMuon!= _Muon->end(); ++iMuon)  {
         if(iMuon!=RecMuon && (iMuon->charge()!=RecMuon->charge())){
           bool muon1 = iMuon->pt()>20.0 && fabs(iMuon->eta())<2.5;
           bool muon2 = muon::isMediumMuon(*iMuon);
           bool muon3 = (iMuon->pfIsolationR04().sumChargedHadronPt + std::max(0.,iMuon->pfIsolationR04().sumNeutralHadronEt + iMuon->pfIsolationR04().sumPhotonEt - (0.5 *iMuon->pfIsolationR04().sumPUPt))) / iMuon->pt()<0.15;
           if(muon1 && muon2 && muon3){ 
            TLorentzVector Muon_tmp;
            Muon_tmp.SetPtEtaPhiM(iMuon->pt(), iMuon->eta(), iMuon->phi(), 0.10566);
            double dimuon_M = (Muon_tmp + lvMuon).M();
             if(fabs(dimuon_M-91.188)<fabs(dimuon_M_tmp-91.188)){
                  dimuon_M_tmp = dimuon_M;
                  if(muon::isTightMuon(*iMuon,*firstGoodVertex)) tight2 = 1;
             }
           }
         }
      }
      DiMuonM_.push_back(dimuon_M_tmp);
      muon_tight2_.push_back(tight2);
#ifdef EDM_ML_DEBUG
      edm::LogInfo("HBHEMuon") << "Energy:" << RecMuon->energy() << " P:"
                               << RecMuon->p() << std::endl;
#endif
      //isloosemuon_.push_back(muon::isLooseMuon(*RecMuon));
      //ismediummuon_.push_back(muon::isMediumMuon(*RecMuon));

      if (RecMuon->track().isNonnull()) {
        trackerLayer_.push_back(RecMuon->track()->hitPattern().trackerLayersWithMeasurement());
      } else {
        trackerLayer_.push_back(-1);
      }
      if (RecMuon->innerTrack().isNonnull()) {
        innerTrack_.push_back(true);
        numPixelLayers_.push_back(RecMuon->innerTrack()->hitPattern().pixelLayersWithMeasurement());
        chiTracker_.push_back(RecMuon->innerTrack()->normalizedChi2());
        dxyTracker_.push_back(fabs(RecMuon->innerTrack()->dxy((*firstGoodVertex).position())));
        dzTracker_.push_back(fabs(RecMuon->innerTrack()->dz((*firstGoodVertex).position())));
        innerTrackpt_.push_back(RecMuon->innerTrack()->pt());
        innerTracketa_.push_back(RecMuon->innerTrack()->eta());
        innerTrackphi_.push_back(RecMuon->innerTrack()->phi());
        tight_PixelHits_.push_back(RecMuon->innerTrack()->hitPattern().numberOfValidPixelHits());
      } else {
        innerTrack_.push_back(false);
        numPixelLayers_.push_back(0);
        chiTracker_.push_back(0);
        dxyTracker_.push_back(0);
        dzTracker_.push_back(0);
        innerTrackpt_.push_back(0);
        innerTracketa_.push_back(0);
        innerTrackphi_.push_back(0);
        tight_PixelHits_.push_back(0);
      }
      if (RecMuon->outerTrack().isNonnull()) {
        outerTrack_.push_back(true);
        outerTrackPt_.push_back(RecMuon->outerTrack()->pt());
        outerTrackEta_.push_back(RecMuon->outerTrack()->eta());
        outerTrackPhi_.push_back(RecMuon->outerTrack()->phi());
        outerTrackChi_.push_back(RecMuon->outerTrack()->normalizedChi2());
        outerTrackHits_.push_back(RecMuon->outerTrack()->numberOfValidHits());
        outerTrackRHits_.push_back(RecMuon->outerTrack()->recHitsSize());
      } else {
        outerTrack_.push_back(false);
        outerTrackPt_.push_back(0);
        outerTrackEta_.push_back(0);
        outerTrackPhi_.push_back(0);
        outerTrackChi_.push_back(0);
        outerTrackHits_.push_back(0);
        outerTrackRHits_.push_back(0);
      }
      if (RecMuon->globalTrack().isNonnull())  {

        globalTrack_.push_back(true);
        chiGlobal_.push_back(RecMuon->globalTrack()->normalizedChi2());
        globalMuonHits_.push_back(RecMuon->globalTrack()->hitPattern().numberOfValidMuonHits());
        matchedStat_.push_back(RecMuon->numberOfMatchedStations());
        globalTrckPt_.push_back(RecMuon->globalTrack()->pt());
        globalTrckEta_.push_back(RecMuon->globalTrack()->eta());
        globalTrckPhi_.push_back(RecMuon->globalTrack()->phi());
        tight_TransImpara_.push_back(fabs(RecMuon->muonBestTrack()->dxy((*firstGoodVertex).position())));
        tight_LongPara_.push_back(fabs(RecMuon->muonBestTrack()->dz((*firstGoodVertex).position())));
      } else {
        globalTrack_.push_back(false);
        chiGlobal_.push_back(0);
        globalMuonHits_.push_back(0);
        matchedStat_.push_back(0);
        globalTrckPt_.push_back(0);
        globalTrckEta_.push_back(0);
        globalTrckPhi_.push_back(0);
        tight_TransImpara_.push_back(0);
        tight_LongPara_.push_back(0);
      }

      isolationR04_.push_back(((RecMuon->pfIsolationR04().sumChargedHadronPt + std::max(0.,RecMuon->pfIsolationR04().sumNeutralHadronEt + RecMuon->pfIsolationR04().sumPhotonEt - (0.5 *RecMuon->pfIsolationR04().sumPUPt))) / RecMuon->pt()) );

      isolationR03_.push_back(((RecMuon->pfIsolationR03().sumChargedHadronPt + std::max(0.,RecMuon->pfIsolationR03().sumNeutralHadronEt + RecMuon->pfIsolationR03().sumPhotonEt - (0.5 * RecMuon->pfIsolationR03().sumPUPt))) / RecMuon->pt()));

      TrkisolationR03_.push_back( RecMuon->isolationR03().sumPt/RecMuon->pt());

      ecalEnergy_.push_back(RecMuon->calEnergy().emS9);
      hcalEnergy_.push_back(RecMuon->calEnergy().hadS9);
      //hoEnergy_.push_back(RecMuon->calEnergy().hoS9);


          //get Ecal energy
          bool okE = trackID.okECAL;
          if (okE) {
            const DetId isoCell(trackID.detIdECAL);
            std::pair<double,bool> e1x1 = spr::eECALmatrix(isoCell,barrelRecHitsHandle,endcapRecHitsHandle,*theEcalChStatus,geo,caloTopology,sevlv.product(),0,0,-100.0,-100.0,-500.0,500.0,false);
            eEcal = e1x1.first;
            std::pair<double,bool> e3x3 = spr::eECALmatrix(isoCell,barrelRecHitsHandle,endcapRecHitsHandle,*theEcalChStatus,geo,caloTopology,sevlv.product(),1,1,-100.0,-100.0,-500.0,500.0,false);
            eEcal3x3 = e3x3.first;
            std::pair<double,bool> e5x5 = spr::eECALmatrix(isoCell,barrelRecHitsHandle,endcapRecHitsHandle,*theEcalChStatus,geo,caloTopology,sevlv.product(),2,2,-100.0,-100.0,-500.0,500.0,false);
            eEcal5x5 = e5x5.first;
            std::pair<double,bool> e15x15 = spr::eECALmatrix(isoCell,barrelRecHitsHandle,endcapRecHitsHandle,*theEcalChStatus,geo,caloTopology,sevlv.product(),7,7,-100.0,-100.0,-500.0,500.0,false);
            eEcal15x15 = e15x15.first;
            std::pair<double,bool> e25x25 = spr::eECALmatrix(isoCell,barrelRecHitsHandle,endcapRecHitsHandle,*theEcalChStatus,geo,caloTopology,sevlv.product(),12,12,-100.0,-100.0,-500.0,500.0,false);
            eEcal25x25 = e25x25.first;
            okE   = e3x3.second;
          }
#ifdef EDM_ML_DEBUG
          edm::LogInfo("HBHEMuon") << "Propagate Track to ECAL: " << okE << ":"
                                 << trackID.okECAL << " E "
                                 << eEcal << std::endl;
#endif

	  eHcal = spr::eHCALmatrix(theHBHETopology, closestCell, hbhe,0,0, false, true, -100.0, -100.0, -100.0, -100.0, -500.,500.,useRaw_);
	  std::vector<std::pair<double,int> > ehdepth;
	  spr::energyHCALCell((HcalDetId) closestCell, hbhe, ehdepth, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          
          HcalDetId hcid1(subdet,ieta-1,iphi-1,1);
          HcalDetId hcid2(subdet,ieta-1,iphi,1);
          HcalDetId hcid3(subdet,ieta-1,iphi+1,1);

          int ieta_temp = ieta+1;
          //if(ieta==28 || ieta==29) ieta_temp = ieta;
          HcalDetId hcid4(subdet,ieta_temp,iphi-1,1);
          HcalDetId hcid5(subdet,ieta_temp,iphi,1);
          HcalDetId hcid6(subdet,ieta_temp,iphi+1,1);

          HcalDetId hcid7(subdet,ieta,iphi-1,1);
          HcalDetId hcid8(subdet,ieta,iphi+1,1);

          std::vector<std::pair<double,int> > ehdepth1, ehdepth2, ehdepth3, ehdepth4, ehdepth5, ehdepth6, ehdepth7, ehdepth8;
          spr::energyHCALCell((HcalDetId)hcid1, hbhe, ehdepth1, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid2, hbhe, ehdepth2, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid3, hbhe, ehdepth3, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid4, hbhe, ehdepth4, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid5, hbhe, ehdepth5, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid6, hbhe, ehdepth6, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid7, hbhe, ehdepth7, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));
          spr::energyHCALCell((HcalDetId)hcid8, hbhe, ehdepth8, maxDepth_, -100.0, -100.0, -100.0, -100.0, -500.0, 500.0, useRaw_, (((verbosity_/1000)%10)>0));

          
          for (unsigned int i=0; i<ehdepth1.size(); ++i) {
            eHcalDepth1[ehdepth1[i].second-1] = ehdepth1[i].first;
          }

          for (unsigned int i=0; i<ehdepth2.size(); ++i) {
            eHcalDepth2[ehdepth2[i].second-1] = ehdepth2[i].first;
          }
 
          for (unsigned int i=0; i<ehdepth3.size(); ++i) {
            eHcalDepth3[ehdepth3[i].second-1] = ehdepth3[i].first;
          }

          for (unsigned int i=0; i<ehdepth4.size(); ++i) {
            eHcalDepth4[ehdepth4[i].second-1] = ehdepth4[i].first;
          }

          for (unsigned int i=0; i<ehdepth5.size(); ++i) {
            eHcalDepth5[ehdepth5[i].second-1] = ehdepth5[i].first;
          }

          for (unsigned int i=0; i<ehdepth6.size(); ++i) {
            eHcalDepth6[ehdepth6[i].second-1] = ehdepth6[i].first;
          }

          for (unsigned int i=0; i<ehdepth7.size(); ++i) {
            eHcalDepth7[ehdepth7[i].second-1] = ehdepth7[i].first;
          }

          for (unsigned int i=0; i<ehdepth8.size(); ++i) {
            eHcalDepth8[ehdepth8[i].second-1] = ehdepth8[i].first;
          }

	  for (unsigned int i=0; i<ehdepth.size(); ++i) {
	    eHcalDepth[ehdepth[i].second-1] = ehdepth[i].first;

            //HcalSubdetector subdet0 = (hborhe) ? ((ehdepth[i].second >= depth16HE(ieta, iphi)) ? HcalEndcap : HcalBarrel) : subdet;
            HcalSubdetector subdet0 = (hborhe) ? ((ehdepth[i].second >= depthHE) ? HcalEndcap : HcalBarrel) : subdet;

            HcalDetId hcid0(subdet0,ieta,iphi,ehdepth[i].second);
            double actL = activeLength(DetId(hcid0));
            activeL[ehdepth[i].second-1] = actL;
            //get charge 
            double ene  = ehdepth[i].first;
            double chg(ene), enec(ene);
            double corr = respCorr(DetId(hcid0));
            if (corr != 0) {enec /= corr;}
            double gain = gainFactor(conditions,hcid0);
            if (gain  != 0) chg  /= gain;
            chgHcalDepth[ehdepth[i].second-1] = chg;
            ueHcalDepth[ehdepth[i].second-1] = enec;
          }

	  HcalDetId           hotCell;
	  spr::eHCALmatrix(geo, theHBHETopology, closestCell, hbhe, 1,1, hotCell, false, useRaw_, false);
	  isHot = matchId(closestCell,hotCell);

      matchedId_.push_back(tmpmatch);
      ecal25x25Energy_.push_back(eEcal25x25);
      ecal15x15Energy_.push_back(eEcal15x15);
      ecal5x5Energy_.push_back(eEcal5x5);
      ecal3x3Energy_.push_back(eEcal3x3);
      ecal1x1Energy_.push_back(eEcal);
      hcal1x1Energy_.push_back(eHcal);
      hcal_ieta_.push_back(ieta);
      hcal_iphi_.push_back(iphi);
      hcal_ieta_hot_.push_back(ietahot);
      hcal_iphi_hot_.push_back(iphihot);

      hcalDepth1UEnergy_.push_back(ueHcalDepth[0]);
      hcalDepth2UEnergy_.push_back(ueHcalDepth[1]);
      hcalDepth3UEnergy_.push_back(ueHcalDepth[2]);
      hcalDepth4UEnergy_.push_back(ueHcalDepth[3]);
      hcalDepth5UEnergy_.push_back(ueHcalDepth[4]);
      hcalDepth6UEnergy_.push_back(ueHcalDepth[5]);
      hcalDepth7UEnergy_.push_back(ueHcalDepth[6]);

      hcalDepth1Charge_.push_back(chgHcalDepth[0]);
      hcalDepth2Charge_.push_back(chgHcalDepth[1]);
      hcalDepth3Charge_.push_back(chgHcalDepth[2]);
      hcalDepth4Charge_.push_back(chgHcalDepth[3]);
      hcalDepth5Charge_.push_back(chgHcalDepth[4]);
      hcalDepth6Charge_.push_back(chgHcalDepth[5]);
      hcalDepth7Charge_.push_back(chgHcalDepth[6]);

      hcalDepth1Energy_.push_back(eHcalDepth[0]);
      hcalDepth2Energy_.push_back(eHcalDepth[1]);
      hcalDepth3Energy_.push_back(eHcalDepth[2]);
      hcalDepth4Energy_.push_back(eHcalDepth[3]);
      hcalDepth5Energy_.push_back(eHcalDepth[4]);
      hcalDepth6Energy_.push_back(eHcalDepth[5]);
      hcalDepth7Energy_.push_back(eHcalDepth[6]);

      hcalDepth1Energy1_.push_back(eHcalDepth1[0]);
      hcalDepth2Energy1_.push_back(eHcalDepth1[1]);
      hcalDepth3Energy1_.push_back(eHcalDepth1[2]);
      hcalDepth4Energy1_.push_back(eHcalDepth1[3]);
      hcalDepth5Energy1_.push_back(eHcalDepth1[4]);
      hcalDepth6Energy1_.push_back(eHcalDepth1[5]);
      hcalDepth7Energy1_.push_back(eHcalDepth1[6]);

      hcalDepth1Energy2_.push_back(eHcalDepth2[0]);
      hcalDepth2Energy2_.push_back(eHcalDepth2[1]);
      hcalDepth3Energy2_.push_back(eHcalDepth2[2]);
      hcalDepth4Energy2_.push_back(eHcalDepth2[3]);
      hcalDepth5Energy2_.push_back(eHcalDepth2[4]);
      hcalDepth6Energy2_.push_back(eHcalDepth2[5]);
      hcalDepth7Energy2_.push_back(eHcalDepth2[6]);

      hcalDepth1Energy3_.push_back(eHcalDepth3[0]);
      hcalDepth2Energy3_.push_back(eHcalDepth3[1]);
      hcalDepth3Energy3_.push_back(eHcalDepth3[2]);
      hcalDepth4Energy3_.push_back(eHcalDepth3[3]);
      hcalDepth5Energy3_.push_back(eHcalDepth3[4]);
      hcalDepth6Energy3_.push_back(eHcalDepth3[5]);
      hcalDepth7Energy3_.push_back(eHcalDepth3[6]);         

      hcalDepth1Energy4_.push_back(eHcalDepth4[0]);
      hcalDepth2Energy4_.push_back(eHcalDepth4[1]);
      hcalDepth3Energy4_.push_back(eHcalDepth4[2]);
      hcalDepth4Energy4_.push_back(eHcalDepth4[3]);
      hcalDepth5Energy4_.push_back(eHcalDepth4[4]);
      hcalDepth6Energy4_.push_back(eHcalDepth4[5]);
      hcalDepth7Energy4_.push_back(eHcalDepth4[6]);

      hcalDepth1Energy5_.push_back(eHcalDepth5[0]);
      hcalDepth2Energy5_.push_back(eHcalDepth5[1]);
      hcalDepth3Energy5_.push_back(eHcalDepth5[2]);
      hcalDepth4Energy5_.push_back(eHcalDepth5[3]);
      hcalDepth5Energy5_.push_back(eHcalDepth5[4]);
      hcalDepth6Energy5_.push_back(eHcalDepth5[5]);
      hcalDepth7Energy5_.push_back(eHcalDepth5[6]);

      hcalDepth1Energy6_.push_back(eHcalDepth6[0]);
      hcalDepth2Energy6_.push_back(eHcalDepth6[1]);
      hcalDepth3Energy6_.push_back(eHcalDepth6[2]);
      hcalDepth4Energy6_.push_back(eHcalDepth6[3]);
      hcalDepth5Energy6_.push_back(eHcalDepth6[4]);
      hcalDepth6Energy6_.push_back(eHcalDepth6[5]);
      hcalDepth7Energy6_.push_back(eHcalDepth6[6]);

      hcalDepth1Energy7_.push_back(eHcalDepth7[0]);
      hcalDepth2Energy7_.push_back(eHcalDepth7[1]);
      hcalDepth3Energy7_.push_back(eHcalDepth7[2]);
      hcalDepth4Energy7_.push_back(eHcalDepth7[3]);
      hcalDepth5Energy7_.push_back(eHcalDepth7[4]);
      hcalDepth6Energy7_.push_back(eHcalDepth7[5]);
      hcalDepth7Energy7_.push_back(eHcalDepth7[6]);

      hcalDepth1Energy8_.push_back(eHcalDepth8[0]);
      hcalDepth2Energy8_.push_back(eHcalDepth8[1]);
      hcalDepth3Energy8_.push_back(eHcalDepth8[2]);
      hcalDepth4Energy8_.push_back(eHcalDepth8[3]);
      hcalDepth5Energy8_.push_back(eHcalDepth8[4]);
      hcalDepth6Energy8_.push_back(eHcalDepth8[5]);
      hcalDepth7Energy8_.push_back(eHcalDepth8[6]);

      hcalDepth1ActiveLength_.push_back(activeL[0]);
      hcalDepth2ActiveLength_.push_back(activeL[1]);
      hcalDepth3ActiveLength_.push_back(activeL[2]);
      hcalDepth4ActiveLength_.push_back(activeL[3]);
      hcalDepth5ActiveLength_.push_back(activeL[4]);
      hcalDepth6ActiveLength_.push_back(activeL[5]);
      hcalDepth7ActiveLength_.push_back(activeL[6]);

      hcalHot_.push_back(isHot);

         }
	}
#ifdef EDM_ML_DEBUG
	edm::LogInfo("HBHEMuon") << "Propagate Track to HCAL: " 
				 << trackID.okHCAL << " Match " << tmpmatch
				 << " Hot " << isHot << " Energy "
				 << eHcal << std::endl;
#endif
	
      }
    }
  }
  if (accept) tree_->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void HEP17MuonAnalyzer::beginJob() {
  
  tree_ = fs->make<TTree>("TREE", "TREE");
  tree_->Branch("Event_No",          &eventNumber_);
  tree_->Branch("Run_No",            &runNumber_);
  tree_->Branch("LumiNumber",        &lumiNumber_);
  tree_->Branch("BXNumber",          &bxNumber_);
  tree_->Branch("nvtx",              &nvtx_);
  tree_->Branch("nvtx_notFake",      &nvtx_notFake_);
  tree_->Branch("nvtx_good",         &nvtx_good_);
  tree_->Branch("pt_of_muon",        &ptGlob_);
  tree_->Branch("eta_of_muon",       &etaGlob_);
  tree_->Branch("phi_of_muon",       &phiGlob_);
  tree_->Branch("energy_of_muon",    &energyMuon_);
  tree_->Branch("p_of_muon",         &pMuon_);
  tree_->Branch("charge_of_muon",    &cMuon_);
  tree_->Branch("DiMuon_Mass",      &DiMuonM_);
  tree_->Branch("istight1",         &muon_tight1_);
  tree_->Branch("istight2",         &muon_tight2_);
  tree_->Branch("PF_Muon",           &muon_is_good_);
  tree_->Branch("Global_Muon",       &muon_global_);
  tree_->Branch("Tracker_muon",      &muon_tracker_);
  //tree_->Branch("isloosemuon",       &isloosemuon_);
  //tree_->Branch("ismediummuon",      &ismediummuon_);
  //tree_->Branch("istightmuon",       &istightmuon_);
  
  tree_->Branch("hcal_3into3",      &hcalEnergy_);
  tree_->Branch("hcal_1x1",         &hcal1x1Energy_);
  tree_->Branch("hcal_detID",       &hcalDetId_);
  tree_->Branch("hcal_cellHot",     &hcalHot_);
  tree_->Branch("hcal_ieta",        &hcal_ieta_);
  tree_->Branch("hcal_iphi",        &hcal_iphi_);
  tree_->Branch("hcal_ieta_hot",    &hcal_ieta_hot_);
  tree_->Branch("hcal_iphi_hot",    &hcal_iphi_hot_);
  tree_->Branch("hcal_chgdepth1",    &hcalDepth1Charge_);
  tree_->Branch("hcal_chgdepth2",    &hcalDepth2Charge_);
  tree_->Branch("hcal_chgdepth3",    &hcalDepth3Charge_);
  tree_->Branch("hcal_chgdepth4",    &hcalDepth4Charge_);
  tree_->Branch("hcal_uedepth1",     &hcalDepth1UEnergy_);
  tree_->Branch("hcal_uedepth2",     &hcalDepth2UEnergy_);
  tree_->Branch("hcal_uedepth3",     &hcalDepth3UEnergy_);
  tree_->Branch("hcal_uedepth4",     &hcalDepth4UEnergy_);
  tree_->Branch("hcal_edepth1",     &hcalDepth1Energy_);
  tree_->Branch("hcal_edepth2",     &hcalDepth2Energy_);
  tree_->Branch("hcal_edepth3",     &hcalDepth3Energy_);
  tree_->Branch("hcal_edepth4",     &hcalDepth4Energy_);
  
  //1
  tree_->Branch("hcal_edepth11",     &hcalDepth1Energy1_);
  tree_->Branch("hcal_edepth12",     &hcalDepth2Energy1_);
  tree_->Branch("hcal_edepth13",     &hcalDepth3Energy1_);
  tree_->Branch("hcal_edepth14",     &hcalDepth4Energy1_);
  //2
  tree_->Branch("hcal_edepth21",     &hcalDepth1Energy2_);
  tree_->Branch("hcal_edepth22",     &hcalDepth2Energy2_);
  tree_->Branch("hcal_edepth23",     &hcalDepth3Energy2_);
  tree_->Branch("hcal_edepth24",     &hcalDepth4Energy2_);
  //3
  tree_->Branch("hcal_edepth31",     &hcalDepth1Energy3_);
  tree_->Branch("hcal_edepth32",     &hcalDepth2Energy3_);
  tree_->Branch("hcal_edepth33",     &hcalDepth3Energy3_);
  tree_->Branch("hcal_edepth34",     &hcalDepth4Energy3_);
  //4
  tree_->Branch("hcal_edepth41",     &hcalDepth1Energy4_);
  tree_->Branch("hcal_edepth42",     &hcalDepth2Energy4_);
  tree_->Branch("hcal_edepth43",     &hcalDepth3Energy4_);
  tree_->Branch("hcal_edepth44",     &hcalDepth4Energy4_);
  //5
  tree_->Branch("hcal_edepth51",     &hcalDepth1Energy5_);
  tree_->Branch("hcal_edepth52",     &hcalDepth2Energy5_);
  tree_->Branch("hcal_edepth53",     &hcalDepth3Energy5_);
  tree_->Branch("hcal_edepth54",     &hcalDepth4Energy5_);
  //6
  tree_->Branch("hcal_edepth61",     &hcalDepth1Energy6_);
  tree_->Branch("hcal_edepth62",     &hcalDepth2Energy6_);
  tree_->Branch("hcal_edepth63",     &hcalDepth3Energy6_);
  tree_->Branch("hcal_edepth64",     &hcalDepth4Energy6_);
  //7
  tree_->Branch("hcal_edepth71",     &hcalDepth1Energy7_);
  tree_->Branch("hcal_edepth72",     &hcalDepth2Energy7_);
  tree_->Branch("hcal_edepth73",     &hcalDepth3Energy7_);
  tree_->Branch("hcal_edepth74",     &hcalDepth4Energy7_);
  //8
  tree_->Branch("hcal_edepth81",     &hcalDepth1Energy8_);
  tree_->Branch("hcal_edepth82",     &hcalDepth2Energy8_);
  tree_->Branch("hcal_edepth83",     &hcalDepth3Energy8_);
  tree_->Branch("hcal_edepth84",     &hcalDepth4Energy8_);

  tree_->Branch("hcal_activeL1",    &hcalDepth1ActiveLength_);
  tree_->Branch("hcal_activeL2",    &hcalDepth2ActiveLength_);
  tree_->Branch("hcal_activeL3",    &hcalDepth3ActiveLength_);
  tree_->Branch("hcal_activeL4",    &hcalDepth4ActiveLength_);
  
  if (maxDepth_ > 4) {
    tree_->Branch("hcal_chgdepth5",   &hcalDepth5Charge_);
    tree_->Branch("hcal_uedepth5",    &hcalDepth5UEnergy_);
    tree_->Branch("hcal_edepth5",     &hcalDepth5Energy_);
    tree_->Branch("hcal_edepth15",    &hcalDepth5Energy1_);
    tree_->Branch("hcal_edepth25",    &hcalDepth5Energy2_);
    tree_->Branch("hcal_edepth35",    &hcalDepth5Energy3_);
    tree_->Branch("hcal_edepth45",    &hcalDepth5Energy4_);
    tree_->Branch("hcal_edepth55",    &hcalDepth5Energy5_);
    tree_->Branch("hcal_edepth65",    &hcalDepth5Energy6_);
    tree_->Branch("hcal_edepth75",    &hcalDepth5Energy7_);
    tree_->Branch("hcal_edepth85",    &hcalDepth5Energy8_);

    tree_->Branch("hcal_activeL5",    &hcalDepth5ActiveLength_);
    if (maxDepth_ > 5) {
      tree_->Branch("hcal_chgdepth6",   &hcalDepth6Charge_);
      tree_->Branch("hcal_uedepth6",    &hcalDepth6UEnergy_);
      tree_->Branch("hcal_edepth6",     &hcalDepth6Energy_);
      tree_->Branch("hcal_edepth16",    &hcalDepth6Energy1_);
      tree_->Branch("hcal_edepth26",    &hcalDepth6Energy2_);
      tree_->Branch("hcal_edepth36",    &hcalDepth6Energy3_);
      tree_->Branch("hcal_edepth46",    &hcalDepth6Energy4_);
      tree_->Branch("hcal_edepth56",    &hcalDepth6Energy5_);
      tree_->Branch("hcal_edepth66",    &hcalDepth6Energy6_);
      tree_->Branch("hcal_edepth76",    &hcalDepth6Energy7_);
      tree_->Branch("hcal_edepth86",    &hcalDepth6Energy8_);

      tree_->Branch("hcal_activeL6",    &hcalDepth6ActiveLength_);
      if (maxDepth_ > 6) {
        tree_->Branch("hcal_chgdepth7",   &hcalDepth7Charge_);
        tree_->Branch("hcal_uedepth7",    &hcalDepth7UEnergy_);
	tree_->Branch("hcal_edepth7",     &hcalDepth7Energy_);
        tree_->Branch("hcal_edepth17",    &hcalDepth7Energy1_);
        tree_->Branch("hcal_edepth27",    &hcalDepth7Energy2_);
        tree_->Branch("hcal_edepth37",    &hcalDepth7Energy3_);
        tree_->Branch("hcal_edepth47",    &hcalDepth7Energy4_);
        tree_->Branch("hcal_edepth57",    &hcalDepth7Energy5_);
        tree_->Branch("hcal_edepth67",    &hcalDepth7Energy6_);
        tree_->Branch("hcal_edepth77",    &hcalDepth7Energy7_);
        tree_->Branch("hcal_edepth87",    &hcalDepth7Energy8_);

	tree_->Branch("hcal_activeL7",    &hcalDepth7ActiveLength_);
      }
    }
  }
  

  tree_->Branch("TrackerLayer",                     &trackerLayer_);
  tree_->Branch("matchedId",                        &matchedId_);
  tree_->Branch("innerTrack",                       &innerTrack_);
  tree_->Branch("innerTrackpt",                     &innerTrackpt_);
  tree_->Branch("innerTracketa",                    &innerTracketa_);
  tree_->Branch("innerTrackphi",                    &innerTrackphi_);
  tree_->Branch("MatchedStat",                      &matchedStat_);
  tree_->Branch("GlobalTrckPt",                     &globalTrckPt_);
  tree_->Branch("GlobalTrckEta",                    &globalTrckEta_);
  tree_->Branch("GlobalTrckPhi",                    &globalTrckPhi_);
  tree_->Branch("NumPixelLayers",                   &numPixelLayers_);
  tree_->Branch("chiTracker",                       &chiTracker_);
  tree_->Branch("DxyTracker",                       &dxyTracker_);
  tree_->Branch("DzTracker",                        &dzTracker_);
  tree_->Branch("OuterTrack",                       &outerTrack_);
  tree_->Branch("OuterTrackPt",                     &outerTrackPt_);
  tree_->Branch("OuterTrackEta",                    &outerTrackEta_);
  tree_->Branch("OuterTrackPhi",                    &outerTrackPhi_);
  tree_->Branch("OuterTrackHits",                   &outerTrackHits_);
  tree_->Branch("OuterTrackRHits",                  &outerTrackRHits_);
  tree_->Branch("OuterTrackChi",                    &outerTrackChi_);
  tree_->Branch("GlobalTrack",                      &globalTrack_);
  tree_->Branch("GlobTrack_Chi",                    &chiGlobal_);
  tree_->Branch("Global_Muon_Hits",                 &globalMuonHits_);
  tree_->Branch("MatchedStations",                  &matchedStat_);
  tree_->Branch("Global_Track_Pt",                  &globalTrckPt_);
  tree_->Branch("Global_Track_Eta",                 &globalTrckEta_);
  tree_->Branch("Global_Track_Phi",                 &globalTrckPhi_);
  ///////////////////////////////
  tree_->Branch("Tight_LongitudinalImpactparameter",&tight_LongPara_);
  tree_->Branch("Tight_TransImpactparameter",       &tight_TransImpara_);
  tree_->Branch("InnerTrackPixelHits",              &tight_PixelHits_);
  tree_->Branch("IsolationR04",                     &isolationR04_);
  tree_->Branch("IsolationR03",                     &isolationR03_);
  tree_->Branch("TrkIsolationR03",                  &TrkisolationR03_);

  tree_->Branch("ecal_3into3",                      &ecalEnergy_);
  tree_->Branch("ecal_3x3",                         &ecal3x3Energy_);
  tree_->Branch("ecal_1x1",                         &ecal1x1Energy_);
  tree_->Branch("ecal_5x5",                         &ecal5x5Energy_);
  tree_->Branch("ecal_15x15",                       &ecal15x15Energy_);
  tree_->Branch("ecal_25x25",                       &ecal25x25Energy_);
  tree_->Branch("ecal_detID",                       &ecalDetId_);
  tree_->Branch("ehcal_detID",                      &ehcalDetId_);
  //tree_->Branch("tracker_3into3",                   &hoEnergy_);
  
  ///////////////////////////////
  tree_->Branch("hltresults",                       &hltresults);
  tree_->Branch("all_triggers",                     &all_triggers);

}

// ------------ method called once each job just after ending the event loop  ------------
void HEP17MuonAnalyzer::endJob() {}

// ------------ method called when starting to processes a run  ------------
void HEP17MuonAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {

  edm::ESHandle<HcalDDDRecConstants> pHRNDC;
  iSetup.get<HcalRecNumberingRecord>().get(pHRNDC);
  const HcalDDDRecConstants & hdc = (*pHRNDC);
  actHB.clear();
  actHE.clear();
  actHB = hdc.getThickActive(0);
  actHE = hdc.getThickActive(1);
   
  bool changed = true;
  all_triggers.clear();
  if (hltConfig_.init(iRun, iSetup,"HLT" , changed)) {
    // if init returns TRUE, initialisation has succeeded!
#ifdef EDM_ML_DEBUG
    edm::LogInfo("HBHEMuon") << "HLT config with process name " 
			     << "HLT" << " successfully extracted"
			     << std::endl;
#endif
//  std::string string_search[5]={"HLT_IsoMu_","HLT_L1SingleMu_","HLT_L2Mu","HLT_Mu","HLT_RelIso1p0Mu"};
    std::string string_search[6]={"HLT_IsoMu17","HLT_IsoMu20","HLT_IsoMu24","HLT_IsoMu27","HLT_Mu45","HLT_Mu50"};
  
    unsigned int ntriggers = hltConfig_.size();
    for (unsigned int t=0;t<ntriggers;++t) {
      std::string hltname(hltConfig_.triggerName(t));
      for (unsigned int ik=0; ik<6; ++ik) {
	if (hltname.find(string_search[ik])!=std::string::npos ){
	  all_triggers.push_back(hltname);
	  break;
	}
      }
    }//loop over ntriggers
    edm::LogInfo("HBHEMuon") << "All triggers size in begin run " 
			     << all_triggers.size() << std::endl;
  } else {
    edm::LogError("HBHEMuon") << "Error! HLT config extraction with process name " 
			      << "HLT" << " failed";
  }

  edm::ESHandle<HcalTopology> htopo;
  iSetup.get<HcalRecNumberingRecord>().get(htopo);
  theHBHETopology = htopo.product();

  edm::ESHandle<HcalRespCorrs> resp;
  iSetup.get<HcalRespCorrsRcd>().get(resp);
  respCorrs_ = new HcalRespCorrs(*resp.product());
  respCorrs_->setTopo(theHBHETopology);
  
}


// ------------ method called when ending the processing of a run  ------------
void HEP17MuonAnalyzer::endRun(edm::Run const&, edm::EventSetup const&) { }

// ------------ method called when starting to processes a luminosity block  ------------
void HEP17MuonAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) { }

// ------------ method called when ending the processing of a luminosity block  ------------
void HEP17MuonAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) { }

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void HEP17MuonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
    desc.add<edm::InputTag>("HLTriggerResults",edm::InputTag("TriggerResults","","HLT"));
  //desc.add<std::string>("LabelBeamSpot","offlineBeamSpot");
  desc.add<bool>("UseRaw",false);
  desc.add<std::string>("LabelVertex","offlinePrimaryVertices");
  desc.add<edm::InputTag>("LabelEBRecHit",edm::InputTag("ecalRecHit","EcalRecHitsEB"));
  desc.add<edm::InputTag>("LabelEERecHit",edm::InputTag("ecalRecHit","EcalRecHitsEE"));
  desc.add<edm::InputTag>("LabelHBHERecHit",edm::InputTag("hbheprereco"));
  desc.add<std::string>("LabelMuon","muons");
  desc.addUntracked<int>("Verbosity",0);
  desc.addUntracked<int>("MaxDepth",4);
  descriptions.add("hep17Muon",desc);
  //desc.setUnknown();
  //descriptions.addDefault(desc);
}

void HEP17MuonAnalyzer::clearVectors() {
  ///clearing vectots
  eventNumber_ = -99999;
  runNumber_   = -99999;
  lumiNumber_  = -99999;
  bxNumber_    = -99999;
  muon_is_good_.clear();
  muon_global_.clear();
  muon_tracker_.clear();
  DiMuonM_.clear();
  muon_tight1_.clear();
  muon_tight2_.clear();
  cMuon_.clear();
  //isloosemuon_.clear();
  //ismediummuon_.clear();
  //istightmuon_.clear();
  ptGlob_.clear();
  etaGlob_.clear(); 
  phiGlob_.clear(); 
  energyMuon_.clear();
  pMuon_.clear();
  trackerLayer_.clear();
  matchedId_.clear();
  innerTrack_.clear();
  numPixelLayers_.clear();
  chiTracker_.clear();
  dxyTracker_.clear();
  dzTracker_.clear();
  innerTrackpt_.clear();
  innerTracketa_.clear();
  innerTrackphi_.clear();
  tight_PixelHits_.clear();
  outerTrack_.clear();
  outerTrackPt_.clear();
  outerTrackEta_.clear();
  outerTrackPhi_.clear();
  outerTrackHits_.clear();
  outerTrackRHits_.clear();
  outerTrackChi_.clear();
  globalTrack_.clear();
  chiGlobal_.clear();
  globalMuonHits_.clear();
  matchedStat_.clear();
  globalTrckPt_.clear();
  globalTrckEta_.clear();
  globalTrckPhi_.clear();
  tight_TransImpara_.clear();
  tight_LongPara_.clear();

  isolationR04_.clear();
  isolationR03_.clear();
  TrkisolationR03_.clear();
  ecalEnergy_.clear();
  hcalEnergy_.clear();
  //hoEnergy_.clear();
  ecalDetId_.clear();
  hcalDetId_.clear();
  ehcalDetId_.clear();
  ecal1x1Energy_.clear();
  ecal3x3Energy_.clear();
  ecal5x5Energy_.clear();
  ecal15x15Energy_.clear();
  ecal25x25Energy_.clear();
  hcal1x1Energy_.clear();
  hcalHot_.clear();
  hcal_ieta_.clear();
  hcal_iphi_.clear();
  hcal_ieta_hot_.clear();
  hcal_iphi_hot_.clear();
  hcalDepth1UEnergy_.clear();
  hcalDepth2UEnergy_.clear();
  hcalDepth3UEnergy_.clear();
  hcalDepth4UEnergy_.clear();
  hcalDepth5UEnergy_.clear();
  hcalDepth6UEnergy_.clear();
  hcalDepth7UEnergy_.clear();

  hcalDepth1Charge_.clear();
  hcalDepth2Charge_.clear();
  hcalDepth3Charge_.clear();
  hcalDepth4Charge_.clear();
  hcalDepth5Charge_.clear();
  hcalDepth6Charge_.clear();
  hcalDepth7Charge_.clear();

  hcalDepth1Energy_.clear();
  hcalDepth2Energy_.clear();
  hcalDepth3Energy_.clear();
  hcalDepth4Energy_.clear();
  hcalDepth5Energy_.clear();
  hcalDepth6Energy_.clear();
  hcalDepth7Energy_.clear();
  //1-8
  hcalDepth1Energy1_.clear();
  hcalDepth2Energy1_.clear();
  hcalDepth3Energy1_.clear();
  hcalDepth4Energy1_.clear();
  hcalDepth5Energy1_.clear();
  hcalDepth6Energy1_.clear();
  hcalDepth7Energy1_.clear();
  hcalDepth1Energy2_.clear();
  hcalDepth2Energy2_.clear();
  hcalDepth3Energy2_.clear();
  hcalDepth4Energy2_.clear();
  hcalDepth5Energy2_.clear();
  hcalDepth6Energy2_.clear();
  hcalDepth7Energy2_.clear();
  hcalDepth1Energy3_.clear();
  hcalDepth2Energy3_.clear();
  hcalDepth3Energy3_.clear();
  hcalDepth4Energy3_.clear();
  hcalDepth5Energy3_.clear();
  hcalDepth6Energy3_.clear();
  hcalDepth7Energy3_.clear();
  hcalDepth1Energy4_.clear();
  hcalDepth2Energy4_.clear();
  hcalDepth3Energy4_.clear();
  hcalDepth4Energy4_.clear();
  hcalDepth5Energy4_.clear();
  hcalDepth6Energy4_.clear();
  hcalDepth7Energy4_.clear();
  hcalDepth1Energy5_.clear();
  hcalDepth2Energy5_.clear();
  hcalDepth3Energy5_.clear();
  hcalDepth4Energy5_.clear();
  hcalDepth5Energy5_.clear();
  hcalDepth6Energy5_.clear();
  hcalDepth7Energy5_.clear();
  hcalDepth1Energy6_.clear();
  hcalDepth2Energy6_.clear();
  hcalDepth3Energy6_.clear();
  hcalDepth4Energy6_.clear();
  hcalDepth5Energy6_.clear();
  hcalDepth6Energy6_.clear();
  hcalDepth7Energy6_.clear();
  hcalDepth1Energy7_.clear();
  hcalDepth2Energy7_.clear();
  hcalDepth3Energy7_.clear();
  hcalDepth4Energy7_.clear();
  hcalDepth5Energy7_.clear();
  hcalDepth6Energy7_.clear();
  hcalDepth7Energy7_.clear();
  hcalDepth1Energy8_.clear();
  hcalDepth2Energy8_.clear();
  hcalDepth3Energy8_.clear();
  hcalDepth4Energy8_.clear();
  hcalDepth5Energy8_.clear();
  hcalDepth6Energy8_.clear();
  hcalDepth7Energy8_.clear();

  hcalDepth1ActiveLength_.clear();
  hcalDepth2ActiveLength_.clear();
  hcalDepth3ActiveLength_.clear();
  hcalDepth4ActiveLength_.clear();
  hcalDepth5ActiveLength_.clear();
  hcalDepth6ActiveLength_.clear();
  hcalDepth7ActiveLength_.clear();
  hltresults.clear();
}

int HEP17MuonAnalyzer::matchId(const HcalDetId& id1, const HcalDetId& id2) {

  HcalDetId kd1(id1.subdet(),id1.ieta(),id1.iphi(),1);
  HcalDetId kd2(id2.subdet(),id2.ieta(),id2.iphi(),1);
  int match = ((kd1 == kd2) ? 1 : 0);
  return match;
}

double HEP17MuonAnalyzer::activeLength(const DetId& id_) {
  HcalDetId id(id_);
  int ieta = id.ietaAbs();
  int zside= id.zside();
  int iphi = id.iphi();
  std::vector<int> dpths;
  /*
  if (mergedDepth_) {
    std::vector<HcalDetId> ids;
    hdc_->unmergeDepthDetId(id,ids);
    for (auto idh : ids) 
      dpths.emplace_back(idh.depth());
  } else {
  */
    dpths.emplace_back(id.depth());
  //}
  double lx(0);
  if (id.subdet() == HcalBarrel) {
    for (unsigned int i=0; i<actHB.size(); ++i) {
      if ((ieta == actHB[i].ieta) && (zside == actHB[i].zside) &&
          (std::find(dpths.begin(),dpths.end(),actHB[i].depth) != dpths.end())&&
          (std::find(actHB[i].iphis.begin(),actHB[i].iphis.end(),iphi) !=
           actHB[i].iphis.end())) {
        lx += actHB[i].thick;
      }
    }
  } else {
    for (unsigned int i=0; i<actHE.size(); ++i) {
      if ((ieta == actHE[i].ieta) && (zside == actHE[i].zside) && 
          (std::find(dpths.begin(),dpths.end(),actHE[i].depth) != dpths.end())&&
          (std::find(actHE[i].iphis.begin(),actHE[i].iphis.end(),iphi) !=
           actHE[i].iphis.end())) {
        lx += actHE[i].thick;
      }
    }
  }
  return lx;
}

double HEP17MuonAnalyzer::respCorr(const DetId& id) {
  double cfac(1.0);
  /*
  if (useMyCorr_) {
    auto itr = corrValue_.find(id);
    if (itr != corrValue_.end()) cfac = itr->second;
  } else*/
  if (respCorrs_ != nullptr) {
    cfac = (respCorrs_->getValues(id))->getValue();
  }
  return cfac;
}

double HEP17MuonAnalyzer::gainFactor(const edm::ESHandle<HcalDbService>& conditions, const HcalDetId& id) {
  double gain(0.0);
  const HcalCalibrations& calibs=conditions->getHcalCalibrations(id);
  for (int capid=0; capid<4; ++capid)
    gain += (0.25*calibs.respcorrgain(capid));
  return gain;
}

int HEP17MuonAnalyzer::depth16HE(int ieta, int iphi) {

  int depth = (maxDepth_ <= 6) ? 3 : 4;
  if ((ieta < 0) || (iphi < 62) || (iphi > 66)) depth = 3;
  return depth;
}


/*
double HEP17MuonAnalyzer::activeLength(const DetId& id_) {
  HcalDetId id(id_);
  int ieta = id.ietaAbs();
  int depth= id.depth();
  double lx(0);
  if (id.subdet() == HcalBarrel) {
    for (unsigned int i=0; i<actHB.size(); ++i) {
      if (ieta == actHB[i].ieta && depth == actHB[i].depth) {
	lx = actHB[i].thick;
	break;
      }
    }
  } else {
    for (unsigned int i=0; i<actHE.size(); ++i) {
      if (ieta == actHE[i].ieta && depth == actHE[i].depth) {
	lx = actHE[i].thick;
	break;
      }
    }
  }
  return lx;
}
*/
bool HEP17MuonAnalyzer::isGoodVertex(const reco::Vertex& vtx) {
  if (vtx.isFake())                   return false;
  if (vtx.ndof() < 4)                 return false;
  if (vtx.position().Rho() > 2.)      return false;
  if (fabs(vtx.position().Z()) > 24.) return false;
  return true;
}

//define this as a plug-in
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(HEP17MuonAnalyzer);

