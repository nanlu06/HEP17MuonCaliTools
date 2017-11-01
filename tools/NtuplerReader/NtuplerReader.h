//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Oct 21 23:09:55 2017 by ROOT version 6.08/07
// from TTree TREE/TREE
// found on file: /eos/cms/store/group/dpg_hcal/comm_hcal/nlu/DoubleMuon/HCalMIPCali_test3_data_PromptReco2017_Run2017B-PromptReco-v1_v5_v1/170926_144546/0000/Validation_test_10.root
//////////////////////////////////////////////////////////

#ifndef NtuplerReader_h
#define NtuplerReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class NtuplerReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          Event_No;
   UInt_t          Run_No;
   UInt_t          LumiNumber;
   UInt_t          BXNumber;
   UInt_t          nvtx;
   UInt_t          nvtx_notFake;
   vector<double>  *pt_of_muon;
   vector<double>  *eta_of_muon;
   vector<double>  *phi_of_muon;
   vector<double>  *energy_of_muon;
   vector<double>  *p_of_muon;
   vector<bool>    *PF_Muon;
   vector<bool>    *Global_Muon;
   vector<bool>    *Tracker_muon;
   vector<bool>    *isloosemuon;
   vector<bool>    *ismediummuon;
   vector<double>  *hcal_3into3;
   vector<double>  *hcal_1x1;
   vector<unsigned int> *hcal_detID;
   vector<double>  *hcal_cellHot;
   vector<int>     *hcal_ieta;
   vector<int>     *hcal_iphi;
   vector<int>     *hcal_ieta_hot;
   vector<int>     *hcal_iphi_hot;
   vector<double>  *hcal_edepth1;
   vector<double>  *hcal_edepth2;
   vector<double>  *hcal_edepth3;
   vector<double>  *hcal_edepth4;
   vector<double>  *hcal_edepth11;
   vector<double>  *hcal_edepth12;
   vector<double>  *hcal_edepth13;
   vector<double>  *hcal_edepth14;
   vector<double>  *hcal_edepth21;
   vector<double>  *hcal_edepth22;
   vector<double>  *hcal_edepth23;
   vector<double>  *hcal_edepth24;
   vector<double>  *hcal_edepth31;
   vector<double>  *hcal_edepth32;
   vector<double>  *hcal_edepth33;
   vector<double>  *hcal_edepth34;
   vector<double>  *hcal_edepth41;
   vector<double>  *hcal_edepth42;
   vector<double>  *hcal_edepth43;
   vector<double>  *hcal_edepth44;
   vector<double>  *hcal_edepth51;
   vector<double>  *hcal_edepth52;
   vector<double>  *hcal_edepth53;
   vector<double>  *hcal_edepth54;
   vector<double>  *hcal_edepth61;
   vector<double>  *hcal_edepth62;
   vector<double>  *hcal_edepth63;
   vector<double>  *hcal_edepth64;
   vector<double>  *hcal_edepth71;
   vector<double>  *hcal_edepth72;
   vector<double>  *hcal_edepth73;
   vector<double>  *hcal_edepth74;
   vector<double>  *hcal_edepth81;
   vector<double>  *hcal_edepth82;
   vector<double>  *hcal_edepth83;
   vector<double>  *hcal_edepth84;
   vector<double>  *hcal_activeL1;
   vector<double>  *hcal_activeL2;
   vector<double>  *hcal_activeL3;
   vector<double>  *hcal_activeL4;
   vector<double>  *hcal_edepthHot1;
   vector<double>  *hcal_edepthHot2;
   vector<double>  *hcal_edepthHot3;
   vector<double>  *hcal_edepthHot4;
   vector<double>  *hcal_activeHotL1;
   vector<double>  *hcal_activeHotL2;
   vector<double>  *hcal_activeHotL3;
   vector<double>  *hcal_activeHotL4;
   vector<double>  *hcal_edepth5;
   vector<double>  *hcal_edepth15;
   vector<double>  *hcal_edepth25;
   vector<double>  *hcal_edepth35;
   vector<double>  *hcal_edepth45;
   vector<double>  *hcal_edepth55;
   vector<double>  *hcal_edepth65;
   vector<double>  *hcal_edepth75;
   vector<double>  *hcal_edepth85;
   vector<double>  *hcal_activeL5;
   vector<double>  *hcal_edepthHot5;
   vector<double>  *hcal_activeHotL5;
   vector<double>  *hcal_edepth6;
   vector<double>  *hcal_edepth16;
   vector<double>  *hcal_edepth26;
   vector<double>  *hcal_edepth36;
   vector<double>  *hcal_edepth46;
   vector<double>  *hcal_edepth56;
   vector<double>  *hcal_edepth66;
   vector<double>  *hcal_edepth76;
   vector<double>  *hcal_edepth86;
   vector<double>  *hcal_activeL6;
   vector<double>  *hcal_edepthHot6;
   vector<double>  *hcal_activeHotL6;
   vector<double>  *hcal_edepth7;
   vector<double>  *hcal_edepth17;
   vector<double>  *hcal_edepth27;
   vector<double>  *hcal_edepth37;
   vector<double>  *hcal_edepth47;
   vector<double>  *hcal_edepth57;
   vector<double>  *hcal_edepth67;
   vector<double>  *hcal_edepth77;
   vector<double>  *hcal_edepth87;
   vector<double>  *hcal_activeL7;
   vector<double>  *hcal_edepthHot7;
   vector<double>  *hcal_activeHotL7;
   vector<double>  *TrackerLayer;
   vector<double>  *matchedId;
   vector<bool>    *innerTrack;
   vector<double>  *innerTrackpt;
   vector<double>  *innerTracketa;
   vector<double>  *innerTrackphi;
   vector<double>  *MatchedStat;
   vector<double>  *GlobalTrckPt;
   vector<double>  *GlobalTrckEta;
   vector<double>  *GlobalTrckPhi;
   vector<double>  *NumPixelLayers;
   vector<double>  *chiTracker;
   vector<double>  *DxyTracker;
   vector<double>  *DzTracker;
   vector<bool>    *OuterTrack;
   vector<double>  *OuterTrackPt;
   vector<double>  *OuterTrackEta;
   vector<double>  *OuterTrackPhi;
   vector<double>  *OuterTrackHits;
   vector<double>  *OuterTrackRHits;
   vector<double>  *OuterTrackChi;
   vector<bool>    *GlobalTrack;
   vector<double>  *GlobTrack_Chi;
   vector<double>  *Global_Muon_Hits;
   vector<double>  *MatchedStations;
   vector<double>  *Global_Track_Pt;
   vector<double>  *Global_Track_Eta;
   vector<double>  *Global_Track_Phi;
   vector<double>  *Tight_LongitudinalImpactparameter;
   vector<double>  *Tight_TransImpactparameter;
   vector<double>  *InnerTrackPixelHits;
   vector<double>  *IsolationR04;
   vector<double>  *IsolationR03;
   vector<double>  *TrkIsolationR03;
   vector<double>  *ecal_3into3;
   vector<double>  *ecal_3x3;
   vector<double>  *ecal_1x1;
   vector<double>  *ecal_5x5;
   vector<unsigned int> *ecal_detID;
   vector<unsigned int> *ehcal_detID;
   vector<int>     *hltresults;
   vector<string>  *all_triggers;

   // List of branches
   TBranch        *b_Event_No;   //!
   TBranch        *b_Run_No;   //!
   TBranch        *b_LumiNumber;   //!
   TBranch        *b_BXNumber;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_nvtx_notFake;   //!
   TBranch        *b_pt_of_muon;   //!
   TBranch        *b_eta_of_muon;   //!
   TBranch        *b_phi_of_muon;   //!
   TBranch        *b_energy_of_muon;   //!
   TBranch        *b_p_of_muon;   //!
   TBranch        *b_PF_Muon;   //!
   TBranch        *b_Global_Muon;   //!
   TBranch        *b_Tracker_muon;   //!
   TBranch        *b_isloosemuon;   //!
   TBranch        *b_ismediummuon;   //!
   TBranch        *b_hcal_3into3;   //!
   TBranch        *b_hcal_1x1;   //!
   TBranch        *b_hcal_detID;   //!
   TBranch        *b_hcal_cellHot;   //!
   TBranch        *b_hcal_ieta;   //!
   TBranch        *b_hcal_iphi;   //!
   TBranch        *b_hcal_ieta_hot;   //!
   TBranch        *b_hcal_iphi_hot;   //!
   TBranch        *b_hcal_edepth1;   //!
   TBranch        *b_hcal_edepth2;   //!
   TBranch        *b_hcal_edepth3;   //!
   TBranch        *b_hcal_edepth4;   //!
   TBranch        *b_hcal_edepth11;   //!
   TBranch        *b_hcal_edepth12;   //!
   TBranch        *b_hcal_edepth13;   //!
   TBranch        *b_hcal_edepth14;   //!
   TBranch        *b_hcal_edepth21;   //!
   TBranch        *b_hcal_edepth22;   //!
   TBranch        *b_hcal_edepth23;   //!
   TBranch        *b_hcal_edepth24;   //!
   TBranch        *b_hcal_edepth31;   //!
   TBranch        *b_hcal_edepth32;   //!
   TBranch        *b_hcal_edepth33;   //!
   TBranch        *b_hcal_edepth34;   //!
   TBranch        *b_hcal_edepth41;   //!
   TBranch        *b_hcal_edepth42;   //!
   TBranch        *b_hcal_edepth43;   //!
   TBranch        *b_hcal_edepth44;   //!
   TBranch        *b_hcal_edepth51;   //!
   TBranch        *b_hcal_edepth52;   //!
   TBranch        *b_hcal_edepth53;   //!
   TBranch        *b_hcal_edepth54;   //!
   TBranch        *b_hcal_edepth61;   //!
   TBranch        *b_hcal_edepth62;   //!
   TBranch        *b_hcal_edepth63;   //!
   TBranch        *b_hcal_edepth64;   //!
   TBranch        *b_hcal_edepth71;   //!
   TBranch        *b_hcal_edepth72;   //!
   TBranch        *b_hcal_edepth73;   //!
   TBranch        *b_hcal_edepth74;   //!
   TBranch        *b_hcal_edepth81;   //!
   TBranch        *b_hcal_edepth82;   //!
   TBranch        *b_hcal_edepth83;   //!
   TBranch        *b_hcal_edepth84;   //!
   TBranch        *b_hcal_activeL1;   //!
   TBranch        *b_hcal_activeL2;   //!
   TBranch        *b_hcal_activeL3;   //!
   TBranch        *b_hcal_activeL4;   //!
   TBranch        *b_hcal_edepthHot1;   //!
   TBranch        *b_hcal_edepthHot2;   //!
   TBranch        *b_hcal_edepthHot3;   //!
   TBranch        *b_hcal_edepthHot4;   //!
   TBranch        *b_hcal_activeHotL1;   //!
   TBranch        *b_hcal_activeHotL2;   //!
   TBranch        *b_hcal_activeHotL3;   //!
   TBranch        *b_hcal_activeHotL4;   //!
   TBranch        *b_hcal_edepth5;   //!
   TBranch        *b_hcal_edepth15;   //!
   TBranch        *b_hcal_edepth25;   //!
   TBranch        *b_hcal_edepth35;   //!
   TBranch        *b_hcal_edepth45;   //!
   TBranch        *b_hcal_edepth55;   //!
   TBranch        *b_hcal_edepth65;   //!
   TBranch        *b_hcal_edepth75;   //!
   TBranch        *b_hcal_edepth85;   //!
   TBranch        *b_hcal_activeL5;   //!
   TBranch        *b_hcal_edepthHot5;   //!
   TBranch        *b_hcal_activeHotL5;   //!
   TBranch        *b_hcal_edepth6;   //!
   TBranch        *b_hcal_edepth16;   //!
   TBranch        *b_hcal_edepth26;   //!
   TBranch        *b_hcal_edepth36;   //!
   TBranch        *b_hcal_edepth46;   //!
   TBranch        *b_hcal_edepth56;   //!
   TBranch        *b_hcal_edepth66;   //!
   TBranch        *b_hcal_edepth76;   //!
   TBranch        *b_hcal_edepth86;   //!
   TBranch        *b_hcal_activeL6;   //!
   TBranch        *b_hcal_edepthHot6;   //!
   TBranch        *b_hcal_activeHotL6;   //!
   TBranch        *b_hcal_edepth7;   //!
   TBranch        *b_hcal_edepth17;   //!
   TBranch        *b_hcal_edepth27;   //!
   TBranch        *b_hcal_edepth37;   //!
   TBranch        *b_hcal_edepth47;   //!
   TBranch        *b_hcal_edepth57;   //!
   TBranch        *b_hcal_edepth67;   //!
   TBranch        *b_hcal_edepth77;   //!
   TBranch        *b_hcal_edepth87;   //!
   TBranch        *b_hcal_activeL7;   //!
   TBranch        *b_hcal_edepthHot7;   //!
   TBranch        *b_hcal_activeHotL7;   //!
   TBranch        *b_TrackerLayer;   //!
   TBranch        *b_matchedId;   //!
   TBranch        *b_innerTrack;   //!
   TBranch        *b_innerTrackpt;   //!
   TBranch        *b_innerTracketa;   //!
   TBranch        *b_innerTrackphi;   //!
   TBranch        *b_MatchedStat;   //!
   TBranch        *b_GlobalTrckPt;   //!
   TBranch        *b_GlobalTrckEta;   //!
   TBranch        *b_GlobalTrckPhi;   //!
   TBranch        *b_NumPixelLayers;   //!
   TBranch        *b_chiTracker;   //!
   TBranch        *b_DxyTracker;   //!
   TBranch        *b_DzTracker;   //!
   TBranch        *b_OuterTrack;   //!
   TBranch        *b_OuterTrackPt;   //!
   TBranch        *b_OuterTrackEta;   //!
   TBranch        *b_OuterTrackPhi;   //!
   TBranch        *b_OuterTrackHits;   //!
   TBranch        *b_OuterTrackRHits;   //!
   TBranch        *b_OuterTrackChi;   //!
   TBranch        *b_GlobalTrack;   //!
   TBranch        *b_GlobTrack_Chi;   //!
   TBranch        *b_Global_Muon_Hits;   //!
   TBranch        *b_MatchedStations;   //!
   TBranch        *b_Global_Track_Pt;   //!
   TBranch        *b_Global_Track_Eta;   //!
   TBranch        *b_Global_Track_Phi;   //!
   TBranch        *b_Tight_LongitudinalImpactparameter;   //!
   TBranch        *b_Tight_TransImpactparameter;   //!
   TBranch        *b_InnerTrackPixelHits;   //!
   TBranch        *b_IsolationR04;   //!
   TBranch        *b_IsolationR03;   //!
   TBranch        *b_TrkIsolationR03;   //!
   TBranch        *b_ecal_3into3;   //!
   TBranch        *b_ecal_3x3;   //!
   TBranch        *b_ecal_1x1;   //!
   TBranch        *b_ecal_5x5;   //!
   TBranch        *b_ecal_detID;   //!
   TBranch        *b_ehcal_detID;   //!
   TBranch        *b_hltresults;   //!
   TBranch        *b_all_triggers;   //!

   NtuplerReader(TTree *tree=0);
   virtual ~NtuplerReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NtuplerReader_cxx
NtuplerReader::NtuplerReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/DoubleMuon/HCalMIPCali_test3_data_PromptReco2017_Run2017B-PromptReco-v1_v5_v1/170926_144546/0000/Validation_test_10.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/DoubleMuon/HCalMIPCali_test3_data_PromptReco2017_Run2017B-PromptReco-v1_v5_v1/170926_144546/0000/Validation_test_10.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/DoubleMuon/HCalMIPCali_test3_data_PromptReco2017_Run2017B-PromptReco-v1_v5_v1/170926_144546/0000/Validation_test_10.root:/HcalHBHEMuonAnalyzer");
      dir->GetObject("TREE",tree);

   }
   Init(tree);
}

NtuplerReader::~NtuplerReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NtuplerReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NtuplerReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NtuplerReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pt_of_muon = 0;
   eta_of_muon = 0;
   phi_of_muon = 0;
   energy_of_muon = 0;
   p_of_muon = 0;
   PF_Muon = 0;
   Global_Muon = 0;
   Tracker_muon = 0;
   isloosemuon = 0;
   ismediummuon = 0;
   hcal_3into3 = 0;
   hcal_1x1 = 0;
   hcal_detID = 0;
   hcal_cellHot = 0;
   hcal_ieta = 0;
   hcal_iphi = 0;
   hcal_ieta_hot = 0;
   hcal_iphi_hot = 0;
   hcal_edepth1 = 0;
   hcal_edepth2 = 0;
   hcal_edepth3 = 0;
   hcal_edepth4 = 0;
   hcal_edepth11 = 0;
   hcal_edepth12 = 0;
   hcal_edepth13 = 0;
   hcal_edepth14 = 0;
   hcal_edepth21 = 0;
   hcal_edepth22 = 0;
   hcal_edepth23 = 0;
   hcal_edepth24 = 0;
   hcal_edepth31 = 0;
   hcal_edepth32 = 0;
   hcal_edepth33 = 0;
   hcal_edepth34 = 0;
   hcal_edepth41 = 0;
   hcal_edepth42 = 0;
   hcal_edepth43 = 0;
   hcal_edepth44 = 0;
   hcal_edepth51 = 0;
   hcal_edepth52 = 0;
   hcal_edepth53 = 0;
   hcal_edepth54 = 0;
   hcal_edepth61 = 0;
   hcal_edepth62 = 0;
   hcal_edepth63 = 0;
   hcal_edepth64 = 0;
   hcal_edepth71 = 0;
   hcal_edepth72 = 0;
   hcal_edepth73 = 0;
   hcal_edepth74 = 0;
   hcal_edepth81 = 0;
   hcal_edepth82 = 0;
   hcal_edepth83 = 0;
   hcal_edepth84 = 0;
   hcal_activeL1 = 0;
   hcal_activeL2 = 0;
   hcal_activeL3 = 0;
   hcal_activeL4 = 0;
   hcal_edepthHot1 = 0;
   hcal_edepthHot2 = 0;
   hcal_edepthHot3 = 0;
   hcal_edepthHot4 = 0;
   hcal_activeHotL1 = 0;
   hcal_activeHotL2 = 0;
   hcal_activeHotL3 = 0;
   hcal_activeHotL4 = 0;
   hcal_edepth5 = 0;
   hcal_edepth15 = 0;
   hcal_edepth25 = 0;
   hcal_edepth35 = 0;
   hcal_edepth45 = 0;
   hcal_edepth55 = 0;
   hcal_edepth65 = 0;
   hcal_edepth75 = 0;
   hcal_edepth85 = 0;
   hcal_activeL5 = 0;
   hcal_edepthHot5 = 0;
   hcal_activeHotL5 = 0;
   hcal_edepth6 = 0;
   hcal_edepth16 = 0;
   hcal_edepth26 = 0;
   hcal_edepth36 = 0;
   hcal_edepth46 = 0;
   hcal_edepth56 = 0;
   hcal_edepth66 = 0;
   hcal_edepth76 = 0;
   hcal_edepth86 = 0;
   hcal_activeL6 = 0;
   hcal_edepthHot6 = 0;
   hcal_activeHotL6 = 0;
   hcal_edepth7 = 0;
   hcal_edepth17 = 0;
   hcal_edepth27 = 0;
   hcal_edepth37 = 0;
   hcal_edepth47 = 0;
   hcal_edepth57 = 0;
   hcal_edepth67 = 0;
   hcal_edepth77 = 0;
   hcal_edepth87 = 0;
   hcal_activeL7 = 0;
   hcal_edepthHot7 = 0;
   hcal_activeHotL7 = 0;
   TrackerLayer = 0;
   matchedId = 0;
   innerTrack = 0;
   innerTrackpt = 0;
   innerTracketa = 0;
   innerTrackphi = 0;
   MatchedStat = 0;
   GlobalTrckPt = 0;
   GlobalTrckEta = 0;
   GlobalTrckPhi = 0;
   NumPixelLayers = 0;
   chiTracker = 0;
   DxyTracker = 0;
   DzTracker = 0;
   OuterTrack = 0;
   OuterTrackPt = 0;
   OuterTrackEta = 0;
   OuterTrackPhi = 0;
   OuterTrackHits = 0;
   OuterTrackRHits = 0;
   OuterTrackChi = 0;
   GlobalTrack = 0;
   GlobTrack_Chi = 0;
   Global_Muon_Hits = 0;
   MatchedStations = 0;
   Global_Track_Pt = 0;
   Global_Track_Eta = 0;
   Global_Track_Phi = 0;
   Tight_LongitudinalImpactparameter = 0;
   Tight_TransImpactparameter = 0;
   InnerTrackPixelHits = 0;
   IsolationR04 = 0;
   IsolationR03 = 0;
   TrkIsolationR03 = 0;
   ecal_3into3 = 0;
   ecal_3x3 = 0;
   ecal_1x1 = 0;
   ecal_5x5 = 0;
   ecal_detID = 0;
   ehcal_detID = 0;
   hltresults = 0;
   all_triggers = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event_No", &Event_No, &b_Event_No);
   fChain->SetBranchAddress("Run_No", &Run_No, &b_Run_No);
   fChain->SetBranchAddress("LumiNumber", &LumiNumber, &b_LumiNumber);
   fChain->SetBranchAddress("BXNumber", &BXNumber, &b_BXNumber);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("nvtx_notFake", &nvtx_notFake, &b_nvtx_notFake);
   fChain->SetBranchAddress("pt_of_muon", &pt_of_muon, &b_pt_of_muon);
   fChain->SetBranchAddress("eta_of_muon", &eta_of_muon, &b_eta_of_muon);
   fChain->SetBranchAddress("phi_of_muon", &phi_of_muon, &b_phi_of_muon);
   fChain->SetBranchAddress("energy_of_muon", &energy_of_muon, &b_energy_of_muon);
   fChain->SetBranchAddress("p_of_muon", &p_of_muon, &b_p_of_muon);
   fChain->SetBranchAddress("PF_Muon", &PF_Muon, &b_PF_Muon);
   fChain->SetBranchAddress("Global_Muon", &Global_Muon, &b_Global_Muon);
   fChain->SetBranchAddress("Tracker_muon", &Tracker_muon, &b_Tracker_muon);
   fChain->SetBranchAddress("isloosemuon", &isloosemuon, &b_isloosemuon);
   fChain->SetBranchAddress("ismediummuon", &ismediummuon, &b_ismediummuon);
   fChain->SetBranchAddress("hcal_3into3", &hcal_3into3, &b_hcal_3into3);
   fChain->SetBranchAddress("hcal_1x1", &hcal_1x1, &b_hcal_1x1);
   fChain->SetBranchAddress("hcal_detID", &hcal_detID, &b_hcal_detID);
   fChain->SetBranchAddress("hcal_cellHot", &hcal_cellHot, &b_hcal_cellHot);
   fChain->SetBranchAddress("hcal_ieta", &hcal_ieta, &b_hcal_ieta);
   fChain->SetBranchAddress("hcal_iphi", &hcal_iphi, &b_hcal_iphi);
   fChain->SetBranchAddress("hcal_ieta_hot", &hcal_ieta_hot, &b_hcal_ieta_hot);
   fChain->SetBranchAddress("hcal_iphi_hot", &hcal_iphi_hot, &b_hcal_iphi_hot);
   fChain->SetBranchAddress("hcal_edepth1", &hcal_edepth1, &b_hcal_edepth1);
   fChain->SetBranchAddress("hcal_edepth2", &hcal_edepth2, &b_hcal_edepth2);
   fChain->SetBranchAddress("hcal_edepth3", &hcal_edepth3, &b_hcal_edepth3);
   fChain->SetBranchAddress("hcal_edepth4", &hcal_edepth4, &b_hcal_edepth4);
   fChain->SetBranchAddress("hcal_edepth11", &hcal_edepth11, &b_hcal_edepth11);
   fChain->SetBranchAddress("hcal_edepth12", &hcal_edepth12, &b_hcal_edepth12);
   fChain->SetBranchAddress("hcal_edepth13", &hcal_edepth13, &b_hcal_edepth13);
   fChain->SetBranchAddress("hcal_edepth14", &hcal_edepth14, &b_hcal_edepth14);
   fChain->SetBranchAddress("hcal_edepth21", &hcal_edepth21, &b_hcal_edepth21);
   fChain->SetBranchAddress("hcal_edepth22", &hcal_edepth22, &b_hcal_edepth22);
   fChain->SetBranchAddress("hcal_edepth23", &hcal_edepth23, &b_hcal_edepth23);
   fChain->SetBranchAddress("hcal_edepth24", &hcal_edepth24, &b_hcal_edepth24);
   fChain->SetBranchAddress("hcal_edepth31", &hcal_edepth31, &b_hcal_edepth31);
   fChain->SetBranchAddress("hcal_edepth32", &hcal_edepth32, &b_hcal_edepth32);
   fChain->SetBranchAddress("hcal_edepth33", &hcal_edepth33, &b_hcal_edepth33);
   fChain->SetBranchAddress("hcal_edepth34", &hcal_edepth34, &b_hcal_edepth34);
   fChain->SetBranchAddress("hcal_edepth41", &hcal_edepth41, &b_hcal_edepth41);
   fChain->SetBranchAddress("hcal_edepth42", &hcal_edepth42, &b_hcal_edepth42);
   fChain->SetBranchAddress("hcal_edepth43", &hcal_edepth43, &b_hcal_edepth43);
   fChain->SetBranchAddress("hcal_edepth44", &hcal_edepth44, &b_hcal_edepth44);
   fChain->SetBranchAddress("hcal_edepth51", &hcal_edepth51, &b_hcal_edepth51);
   fChain->SetBranchAddress("hcal_edepth52", &hcal_edepth52, &b_hcal_edepth52);
   fChain->SetBranchAddress("hcal_edepth53", &hcal_edepth53, &b_hcal_edepth53);
   fChain->SetBranchAddress("hcal_edepth54", &hcal_edepth54, &b_hcal_edepth54);
   fChain->SetBranchAddress("hcal_edepth61", &hcal_edepth61, &b_hcal_edepth61);
   fChain->SetBranchAddress("hcal_edepth62", &hcal_edepth62, &b_hcal_edepth62);
   fChain->SetBranchAddress("hcal_edepth63", &hcal_edepth63, &b_hcal_edepth63);
   fChain->SetBranchAddress("hcal_edepth64", &hcal_edepth64, &b_hcal_edepth64);
   fChain->SetBranchAddress("hcal_edepth71", &hcal_edepth71, &b_hcal_edepth71);
   fChain->SetBranchAddress("hcal_edepth72", &hcal_edepth72, &b_hcal_edepth72);
   fChain->SetBranchAddress("hcal_edepth73", &hcal_edepth73, &b_hcal_edepth73);
   fChain->SetBranchAddress("hcal_edepth74", &hcal_edepth74, &b_hcal_edepth74);
   fChain->SetBranchAddress("hcal_edepth81", &hcal_edepth81, &b_hcal_edepth81);
   fChain->SetBranchAddress("hcal_edepth82", &hcal_edepth82, &b_hcal_edepth82);
   fChain->SetBranchAddress("hcal_edepth83", &hcal_edepth83, &b_hcal_edepth83);
   fChain->SetBranchAddress("hcal_edepth84", &hcal_edepth84, &b_hcal_edepth84);
   fChain->SetBranchAddress("hcal_activeL1", &hcal_activeL1, &b_hcal_activeL1);
   fChain->SetBranchAddress("hcal_activeL2", &hcal_activeL2, &b_hcal_activeL2);
   fChain->SetBranchAddress("hcal_activeL3", &hcal_activeL3, &b_hcal_activeL3);
   fChain->SetBranchAddress("hcal_activeL4", &hcal_activeL4, &b_hcal_activeL4);
   fChain->SetBranchAddress("hcal_edepthHot1", &hcal_edepthHot1, &b_hcal_edepthHot1);
   fChain->SetBranchAddress("hcal_edepthHot2", &hcal_edepthHot2, &b_hcal_edepthHot2);
   fChain->SetBranchAddress("hcal_edepthHot3", &hcal_edepthHot3, &b_hcal_edepthHot3);
   fChain->SetBranchAddress("hcal_edepthHot4", &hcal_edepthHot4, &b_hcal_edepthHot4);
   fChain->SetBranchAddress("hcal_activeHotL1", &hcal_activeHotL1, &b_hcal_activeHotL1);
   fChain->SetBranchAddress("hcal_activeHotL2", &hcal_activeHotL2, &b_hcal_activeHotL2);
   fChain->SetBranchAddress("hcal_activeHotL3", &hcal_activeHotL3, &b_hcal_activeHotL3);
   fChain->SetBranchAddress("hcal_activeHotL4", &hcal_activeHotL4, &b_hcal_activeHotL4);
   fChain->SetBranchAddress("hcal_edepth5", &hcal_edepth5, &b_hcal_edepth5);
   fChain->SetBranchAddress("hcal_edepth15", &hcal_edepth15, &b_hcal_edepth15);
   fChain->SetBranchAddress("hcal_edepth25", &hcal_edepth25, &b_hcal_edepth25);
   fChain->SetBranchAddress("hcal_edepth35", &hcal_edepth35, &b_hcal_edepth35);
   fChain->SetBranchAddress("hcal_edepth45", &hcal_edepth45, &b_hcal_edepth45);
   fChain->SetBranchAddress("hcal_edepth55", &hcal_edepth55, &b_hcal_edepth55);
   fChain->SetBranchAddress("hcal_edepth65", &hcal_edepth65, &b_hcal_edepth65);
   fChain->SetBranchAddress("hcal_edepth75", &hcal_edepth75, &b_hcal_edepth75);
   fChain->SetBranchAddress("hcal_edepth85", &hcal_edepth85, &b_hcal_edepth85);
   fChain->SetBranchAddress("hcal_activeL5", &hcal_activeL5, &b_hcal_activeL5);
   fChain->SetBranchAddress("hcal_edepthHot5", &hcal_edepthHot5, &b_hcal_edepthHot5);
   fChain->SetBranchAddress("hcal_activeHotL5", &hcal_activeHotL5, &b_hcal_activeHotL5);
   fChain->SetBranchAddress("hcal_edepth6", &hcal_edepth6, &b_hcal_edepth6);
   fChain->SetBranchAddress("hcal_edepth16", &hcal_edepth16, &b_hcal_edepth16);
   fChain->SetBranchAddress("hcal_edepth26", &hcal_edepth26, &b_hcal_edepth26);
   fChain->SetBranchAddress("hcal_edepth36", &hcal_edepth36, &b_hcal_edepth36);
   fChain->SetBranchAddress("hcal_edepth46", &hcal_edepth46, &b_hcal_edepth46);
   fChain->SetBranchAddress("hcal_edepth56", &hcal_edepth56, &b_hcal_edepth56);
   fChain->SetBranchAddress("hcal_edepth66", &hcal_edepth66, &b_hcal_edepth66);
   fChain->SetBranchAddress("hcal_edepth76", &hcal_edepth76, &b_hcal_edepth76);
   fChain->SetBranchAddress("hcal_edepth86", &hcal_edepth86, &b_hcal_edepth86);
   fChain->SetBranchAddress("hcal_activeL6", &hcal_activeL6, &b_hcal_activeL6);
   fChain->SetBranchAddress("hcal_edepthHot6", &hcal_edepthHot6, &b_hcal_edepthHot6);
   fChain->SetBranchAddress("hcal_activeHotL6", &hcal_activeHotL6, &b_hcal_activeHotL6);
   fChain->SetBranchAddress("hcal_edepth7", &hcal_edepth7, &b_hcal_edepth7);
   fChain->SetBranchAddress("hcal_edepth17", &hcal_edepth17, &b_hcal_edepth17);
   fChain->SetBranchAddress("hcal_edepth27", &hcal_edepth27, &b_hcal_edepth27);
   fChain->SetBranchAddress("hcal_edepth37", &hcal_edepth37, &b_hcal_edepth37);
   fChain->SetBranchAddress("hcal_edepth47", &hcal_edepth47, &b_hcal_edepth47);
   fChain->SetBranchAddress("hcal_edepth57", &hcal_edepth57, &b_hcal_edepth57);
   fChain->SetBranchAddress("hcal_edepth67", &hcal_edepth67, &b_hcal_edepth67);
   fChain->SetBranchAddress("hcal_edepth77", &hcal_edepth77, &b_hcal_edepth77);
   fChain->SetBranchAddress("hcal_edepth87", &hcal_edepth87, &b_hcal_edepth87);
   fChain->SetBranchAddress("hcal_activeL7", &hcal_activeL7, &b_hcal_activeL7);
   fChain->SetBranchAddress("hcal_edepthHot7", &hcal_edepthHot7, &b_hcal_edepthHot7);
   fChain->SetBranchAddress("hcal_activeHotL7", &hcal_activeHotL7, &b_hcal_activeHotL7);
   fChain->SetBranchAddress("TrackerLayer", &TrackerLayer, &b_TrackerLayer);
   fChain->SetBranchAddress("matchedId", &matchedId, &b_matchedId);
   fChain->SetBranchAddress("innerTrack", &innerTrack, &b_innerTrack);
   fChain->SetBranchAddress("innerTrackpt", &innerTrackpt, &b_innerTrackpt);
   fChain->SetBranchAddress("innerTracketa", &innerTracketa, &b_innerTracketa);
   fChain->SetBranchAddress("innerTrackphi", &innerTrackphi, &b_innerTrackphi);
   fChain->SetBranchAddress("MatchedStat", &MatchedStat, &b_MatchedStat);
   fChain->SetBranchAddress("GlobalTrckPt", &GlobalTrckPt, &b_GlobalTrckPt);
   fChain->SetBranchAddress("GlobalTrckEta", &GlobalTrckEta, &b_GlobalTrckEta);
   fChain->SetBranchAddress("GlobalTrckPhi", &GlobalTrckPhi, &b_GlobalTrckPhi);
   fChain->SetBranchAddress("NumPixelLayers", &NumPixelLayers, &b_NumPixelLayers);
   fChain->SetBranchAddress("chiTracker", &chiTracker, &b_chiTracker);
   fChain->SetBranchAddress("DxyTracker", &DxyTracker, &b_DxyTracker);
   fChain->SetBranchAddress("DzTracker", &DzTracker, &b_DzTracker);
   fChain->SetBranchAddress("OuterTrack", &OuterTrack, &b_OuterTrack);
   fChain->SetBranchAddress("OuterTrackPt", &OuterTrackPt, &b_OuterTrackPt);
   fChain->SetBranchAddress("OuterTrackEta", &OuterTrackEta, &b_OuterTrackEta);
   fChain->SetBranchAddress("OuterTrackPhi", &OuterTrackPhi, &b_OuterTrackPhi);
   fChain->SetBranchAddress("OuterTrackHits", &OuterTrackHits, &b_OuterTrackHits);
   fChain->SetBranchAddress("OuterTrackRHits", &OuterTrackRHits, &b_OuterTrackRHits);
   fChain->SetBranchAddress("OuterTrackChi", &OuterTrackChi, &b_OuterTrackChi);
   fChain->SetBranchAddress("GlobalTrack", &GlobalTrack, &b_GlobalTrack);
   fChain->SetBranchAddress("GlobTrack_Chi", &GlobTrack_Chi, &b_GlobTrack_Chi);
   fChain->SetBranchAddress("Global_Muon_Hits", &Global_Muon_Hits, &b_Global_Muon_Hits);
   fChain->SetBranchAddress("MatchedStations", &MatchedStations, &b_MatchedStations);
   fChain->SetBranchAddress("Global_Track_Pt", &Global_Track_Pt, &b_Global_Track_Pt);
   fChain->SetBranchAddress("Global_Track_Eta", &Global_Track_Eta, &b_Global_Track_Eta);
   fChain->SetBranchAddress("Global_Track_Phi", &Global_Track_Phi, &b_Global_Track_Phi);
   fChain->SetBranchAddress("Tight_LongitudinalImpactparameter", &Tight_LongitudinalImpactparameter, &b_Tight_LongitudinalImpactparameter);
   fChain->SetBranchAddress("Tight_TransImpactparameter", &Tight_TransImpactparameter, &b_Tight_TransImpactparameter);
   fChain->SetBranchAddress("InnerTrackPixelHits", &InnerTrackPixelHits, &b_InnerTrackPixelHits);
   fChain->SetBranchAddress("IsolationR04", &IsolationR04, &b_IsolationR04);
   fChain->SetBranchAddress("IsolationR03", &IsolationR03, &b_IsolationR03);
   fChain->SetBranchAddress("TrkIsolationR03", &TrkIsolationR03, &b_TrkIsolationR03);
   fChain->SetBranchAddress("ecal_3into3", &ecal_3into3, &b_ecal_3into3);
   fChain->SetBranchAddress("ecal_3x3", &ecal_3x3, &b_ecal_3x3);
   fChain->SetBranchAddress("ecal_1x1", &ecal_1x1, &b_ecal_1x1);
   fChain->SetBranchAddress("ecal_5x5", &ecal_5x5, &b_ecal_5x5);
   fChain->SetBranchAddress("ecal_detID", &ecal_detID, &b_ecal_detID);
   fChain->SetBranchAddress("ehcal_detID", &ehcal_detID, &b_ehcal_detID);
   fChain->SetBranchAddress("hltresults", &hltresults, &b_hltresults);
   fChain->SetBranchAddress("all_triggers", &all_triggers, &b_all_triggers);
   Notify();
}

Bool_t NtuplerReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NtuplerReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NtuplerReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NtuplerReader_cxx
