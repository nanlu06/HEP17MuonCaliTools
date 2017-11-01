#define NtuplerReader_cxx
#include "NtuplerReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

void NtuplerReader::Loop()
{

   TFile* outputFile=TFile::Open("/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/tree_data3_v5BCD_Cert_294927-302654_phi_pathlength.root","recreate");

   TTree *tree = new TTree("tree","tree");

   double ecal1x1, ecal3x3,ecal5x5, weight, ISOR04, TrkISOR03, p, energy, pt, eta, phi, e1dx, e2dx, e3dx, e4dx, e5dx, e6dx, e7dx, e1, e2, e3, e4, e5, e6, e7;
   double activeL1[4]={0.9521488,0.9429098,0.9345199,0.926988};
   double activeL2[4]={1.1743168,1.1629221,1.1525746,1.1432862};
   double activeL3[4]={1.174316,1.1629221,1.1525746,1.1432862};
   double activeL4[4]={1.1743168,1.1629221,1.1525746,1.1432862};
   double activeL5[4]={1.5657558,1.5505628,1.5367661,1.5243816};
   double activeL6[4]={1.5657558,1.5505628,1.5367661,1.5243816};
   double activeL7[4]={1,1,1,1};
   double e1r, e12r, e123r, e23r, e1s, e15, e2r, e2s, e25, e3r, e3s, e35, e4r, e4s, e45, e5r, e5s, e55, e6r, e6s, e65, e7r, e7s, e75;
   int run, event, n_vtx, isMedium, isLoose, HCal_cellHot, HCal_ieta, HCal_iphi;
   int isZmumu;
   double Mmumu;
   tree->Branch("run", &run, "run/I");
   tree->Branch("nvtx", &n_vtx, "nvtx/I");
   tree->Branch("event", &event, "event/I");
   tree->Branch("isZmumu", &isZmumu, "isZmumu/I");
   tree->Branch("Mmumu", &Mmumu, "Mmumu/D"); 
   tree->Branch("weight", &weight, "weight/D");  
   tree->Branch("HCal_cellHot", &HCal_cellHot, "HCal_cellHot/I");
   tree->Branch("ecal1x1", &ecal1x1, "ecal1x1/D");
   tree->Branch("ecal3x3", &ecal3x3, "ecal3x3/D");
   tree->Branch("ecal5x5", &ecal5x5, "ecal5x5/D");
   tree->Branch("ISOR04", &ISOR04, "ISOR04/D");
   tree->Branch("TrkISOR03", &TrkISOR03, "TrkISOR03/D");
   tree->Branch("isMedium", &isMedium, "isMedium/I");
   tree->Branch("isLoose", &isLoose, "isLoose/I");
   tree->Branch("HCal_ieta", &HCal_ieta, "HCal_ieta/I");
   tree->Branch("HCal_iphi", &HCal_iphi, "HCal_iphi/I");
   tree->Branch("eta", &eta, "eta/D");
   tree->Branch("pt", &pt, "pt/D");
   tree->Branch("energy", &energy, "energy/D");
   tree->Branch("phi", &phi, "phi/D");
   tree->Branch("p", &p, "p/D");
   tree->Branch("e1", &e1, "e1/D");
   tree->Branch("e2", &e2, "e2/D");
   tree->Branch("e3", &e3, "e3/D");
   tree->Branch("e4", &e4, "e4/D");
   tree->Branch("e5", &e5, "e5/D");
   tree->Branch("e6", &e6, "e6/D");
   tree->Branch("e7", &e7, "e7/D");
   tree->Branch("e1dx", &e1dx, "e1dx/D");
   tree->Branch("e2dx", &e2dx, "e2dx/D");
   tree->Branch("e3dx", &e3dx, "e3dx/D");
   tree->Branch("e4dx", &e4dx, "e4dx/D");
   tree->Branch("e5dx", &e5dx, "e5dx/D");
   tree->Branch("e6dx", &e6dx, "e6dx/D");
   tree->Branch("e7dx", &e7dx, "e7dx/D");

   tree->Branch("e1r", &e1r, "e1r/D");
   tree->Branch("e12r", &e12r, "e12r/D");
   tree->Branch("e123r", &e123r, "e123r/D");
   tree->Branch("e23r", &e23r, "e23r/D");
   tree->Branch("e2r", &e2r, "e2r/D");
   tree->Branch("e3r", &e3r, "e3r/D");
   tree->Branch("e4r", &e4r, "e4r/D");
   tree->Branch("e5r", &e5r, "e5r/D");
   tree->Branch("e6r", &e6r, "e6r/D");
   tree->Branch("e7r", &e7r, "e7r/D");
   tree->Branch("e1s", &e1s, "e1s/D");
   tree->Branch("e2s", &e2s, "e2s/D");
   tree->Branch("e3s", &e3s, "e3s/D");
   tree->Branch("e4s", &e4s, "e4s/D");
   tree->Branch("e5s", &e5s, "e5s/D");
   tree->Branch("e6s", &e6s, "e6s/D");
   tree->Branch("e7s", &e7s, "e7s/D");
   //what happend to depth 5
   tree->Branch("e15", &e15, "e15/D");
   tree->Branch("e25", &e25, "e25/D");
   tree->Branch("e35", &e35, "e35/D");
   tree->Branch("e45", &e45, "e45/D");
   tree->Branch("e55", &e55, "e55/D");
   tree->Branch("e65", &e65, "e65/D");
   tree->Branch("e75", &e75, "e75/D");
/*
   tree->Branch("activeL1", &activeL1, "activeL1/D");
   tree->Branch("activeL2", &activeL2, "activeL2/D");
   tree->Branch("activeL3", &activeL3, "activeL3/D");
   tree->Branch("activeL4", &activeL4, "activeL4/D");
   tree->Branch("activeL5", &activeL5, "activeL5/D");
   tree->Branch("activeL6", &activeL6, "activeL6/D");
   tree->Branch("activeL7", &activeL7, "activeL7/D");
*/
   double mmu = 0.10566; 

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   //Long64_t nentries = 50000;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%5000==0) std::cout <<"events: "<<jentry<<std::endl;

      int nmuon = IsolationR04->size();

      /*
      vector<TLorentzVector> muon_fv;
      muon_fv.clear();

      for(int k = 0; k<nmuon; k ++){
           pt = pt_of_muon->at(k);
           phi = phi_of_muon->at(k);
           eta = eta_of_muon->at(k);
 
           TLorentzVector muon_tmp;
           muon_tmp.SetPtEtaPhiM(pt,eta,phi,0.10566);
           muon_fv.push_back(muon_tmp);
      }


      double dimuon_M_tmp=-999.;
      int mi=-999, mj=-999;
      if(nmuon>1){
        for(int i = 0; i<nmuon; i ++){
          for(int j = i+1; j<nmuon; j ++){
              double dimuon_M = (muon_fv.at(i) + muon_fv.at(j)).M();
              if(fabs(dimuon_M-91.188)<fabs(dimuon_M_tmp-91.188)){
                  dimuon_M_tmp = dimuon_M;
                  mi = i; mj = j; 
              }
          }
        }
      }
       
      */

      for(int k = 0; k<nmuon; k ++){
           HCal_iphi = hcal_iphi->at(k);
           HCal_ieta = hcal_ieta->at(k);
           //if(HCal_ieta<20 || HCal_ieta>25) continue;
           if(HCal_ieta<20 || HCal_ieta>27) continue;
           if(HCal_iphi<=63 || HCal_iphi>=66) continue;

           isMedium = ismediummuon->at(k);
           if(!isMedium) continue;
           HCal_cellHot = hcal_cellHot->at(k);
           if(!HCal_cellHot) continue;

           run = Run_No;
           event = Event_No;
           n_vtx = nvtx;
           weight = 1.0;
           Mmumu = dimuon_M_tmp;
           ISOR04 = IsolationR04->at(k);
           TrkISOR03 = TrkIsolationR03->at(k);
           if((k==mi) || (k==mj)) isZmumu = 1;
           else isZmumu = 0;
           pt = pt_of_muon->at(k); 
           phi = phi_of_muon->at(k); 
           eta = eta_of_muon->at(k);
           energy = energy_of_muon->at(k);
           p = p_of_muon->at(k);

           ecal1x1 = ecal_1x1->at(k);
           ecal3x3 = ecal_3x3->at(k);
           ecal5x5 = ecal_5x5->at(k);
           e1 = hcal_edepth1->at(k);
           e2 = hcal_edepth2->at(k);
           e3 = hcal_edepth3->at(k);
           e4 = hcal_edepth4->at(k);
           e5 = hcal_edepth5->at(k);
           e6 = hcal_edepth6->at(k);
           e7 = hcal_edepth7->at(k);

           e15 = hcal_edepth51->at(k); // the second one is depth 
           e25 = hcal_edepth52->at(k);
           e35 = hcal_edepth53->at(k); 
           e45 = hcal_edepth54->at(k);
           e55 = hcal_edepth55->at(k); 
           e65 = hcal_edepth56->at(k);
           e75 = hcal_edepth57->at(k);

           
           double en11(0.), en21(0.), en31(0.), en41(0.), en51(0.), en61(0.), en71(0.), en81(0.);
           double en12(0.), en22(0.), en32(0.), en42(0.), en52(0.), en62(0.), en72(0.), en82(0.); 
           double en13(0.), en23(0.), en33(0.), en43(0.), en53(0.), en63(0.), en73(0.), en83(0.);
           double en14(0.), en24(0.), en34(0.), en44(0.), en54(0.), en64(0.), en74(0.), en84(0.);
           double en15(0.), en25(0.), en35(0.), en45(0.), en55(0.), en65(0.), en75(0.), en85(0.);
           double en16(0.), en26(0.), en36(0.), en46(0.), en56(0.), en66(0.), en76(0.), en86(0.);
           double en17(0.), en27(0.), en37(0.), en47(0.), en57(0.), en67(0.), en77(0.), en87(0.);
           if(hcal_edepth11->at(k) != -10000){ en11 = hcal_edepth11->at(k);} //cout <<en11<<endl;}
           if(hcal_edepth12->at(k) != -10000){ en12 = hcal_edepth12->at(k);} //cout <<en12<<endl;}
           if(hcal_edepth13->at(k) != -10000) en13 = hcal_edepth13->at(k);
           if(hcal_edepth14->at(k) != -10000) en14 = hcal_edepth14->at(k);
           if(hcal_edepth15->at(k) != -10000) en15 = hcal_edepth15->at(k);
           if(hcal_edepth16->at(k) != -10000) en16 = hcal_edepth16->at(k);
           if(hcal_edepth17->at(k) != -10000) en17 = hcal_edepth17->at(k);

           if(hcal_edepth21->at(k) != -10000) en21 = hcal_edepth21->at(k);
           if(hcal_edepth22->at(k) != -10000) en22 = hcal_edepth22->at(k);
           if(hcal_edepth23->at(k) != -10000) en23 = hcal_edepth23->at(k);
           if(hcal_edepth24->at(k) != -10000) en24 = hcal_edepth24->at(k);
           if(hcal_edepth25->at(k) != -10000) en25 = hcal_edepth25->at(k);
           if(hcal_edepth26->at(k) != -10000) en26 = hcal_edepth26->at(k);
           if(hcal_edepth27->at(k) != -10000) en27 = hcal_edepth27->at(k);

           if(hcal_edepth31->at(k) != -10000) en31 = hcal_edepth31->at(k);
           if(hcal_edepth32->at(k) != -10000) en32 = hcal_edepth32->at(k);
           if(hcal_edepth33->at(k) != -10000) en33 = hcal_edepth33->at(k);
           if(hcal_edepth34->at(k) != -10000) en34 = hcal_edepth34->at(k);
           if(hcal_edepth35->at(k) != -10000) en35 = hcal_edepth35->at(k);
           if(hcal_edepth36->at(k) != -10000) en36 = hcal_edepth36->at(k);
           if(hcal_edepth37->at(k) != -10000) en37 = hcal_edepth37->at(k);

           if(hcal_edepth41->at(k) != -10000) en41 = hcal_edepth41->at(k);
           if(hcal_edepth42->at(k) != -10000) en42 = hcal_edepth42->at(k);
           if(hcal_edepth43->at(k) != -10000) en43 = hcal_edepth43->at(k);
           if(hcal_edepth44->at(k) != -10000) en44 = hcal_edepth44->at(k);
           if(hcal_edepth45->at(k) != -10000) en45 = hcal_edepth45->at(k);
           if(hcal_edepth46->at(k) != -10000) en46 = hcal_edepth46->at(k);
           if(hcal_edepth47->at(k) != -10000) en47 = hcal_edepth47->at(k);
 
           if(hcal_edepth51->at(k) != -10000) en51 = hcal_edepth51->at(k);
           if(hcal_edepth52->at(k) != -10000) en52 = hcal_edepth52->at(k);
           if(hcal_edepth53->at(k) != -10000) en53 = hcal_edepth53->at(k);
           if(hcal_edepth54->at(k) != -10000) en54 = hcal_edepth54->at(k);
           if(hcal_edepth55->at(k) != -10000) en55 = hcal_edepth55->at(k);
           if(hcal_edepth56->at(k) != -10000) en56 = hcal_edepth56->at(k);
           if(hcal_edepth57->at(k) != -10000) en57 = hcal_edepth57->at(k);

           if(hcal_edepth61->at(k) != -10000) en61 = hcal_edepth61->at(k);
           if(hcal_edepth62->at(k) != -10000) en62 = hcal_edepth62->at(k);
           if(hcal_edepth63->at(k) != -10000) en63 = hcal_edepth63->at(k);
           if(hcal_edepth64->at(k) != -10000) en64 = hcal_edepth64->at(k);
           if(hcal_edepth65->at(k) != -10000) en65 = hcal_edepth65->at(k);
           if(hcal_edepth66->at(k) != -10000) en66 = hcal_edepth66->at(k);
           if(hcal_edepth67->at(k) != -10000) en67 = hcal_edepth67->at(k);

           if(hcal_edepth71->at(k) != -10000) en71 = hcal_edepth71->at(k);
           if(hcal_edepth72->at(k) != -10000) en72 = hcal_edepth72->at(k);
           if(hcal_edepth73->at(k) != -10000) en73 = hcal_edepth73->at(k);
           if(hcal_edepth74->at(k) != -10000) en74 = hcal_edepth74->at(k);
           if(hcal_edepth75->at(k) != -10000) en75 = hcal_edepth75->at(k);
           if(hcal_edepth76->at(k) != -10000) en76 = hcal_edepth76->at(k);
           if(hcal_edepth77->at(k) != -10000) en77 = hcal_edepth77->at(k);

           if(hcal_edepth81->at(k) != -10000) en81 = hcal_edepth81->at(k);
           if(hcal_edepth82->at(k) != -10000) en82 = hcal_edepth82->at(k);
           if(hcal_edepth83->at(k) != -10000) en83 = hcal_edepth83->at(k);
           if(hcal_edepth84->at(k) != -10000) en84 = hcal_edepth84->at(k);
           if(hcal_edepth85->at(k) != -10000) en85 = hcal_edepth85->at(k);
           if(hcal_edepth86->at(k) != -10000) en86 = hcal_edepth86->at(k);
           if(hcal_edepth87->at(k) != -10000) en87 = hcal_edepth87->at(k);

           if(HCal_ieta<26 || HCal_ieta==27){
              if(HCal_iphi==63){
                  e1s = en21 + en31 + en51 + en61 + en81 ;       
                  //cout <<"En "<<en11<<" "<<en21<<" "<< en31<<" "<<en41<<" "<<en51<<" "<<en61<<" "<<en71<< " "<<en81<<endl;
                  //cout <<"Depth 1 "<<e1s<<endl;
                  e2s = en22 + en32 + en52 + en62 + en82 ;
                  e3s = en23 + en33 + en53 + en63 + en83 ;
                  e4s = en24 + en34 + en54 + en64 + en84 ;
                  e5s = en25 + en35 + en55 + en65 + en85 ;
                  e6s = en26 + en36 + en56 + en66 + en86 ;
                  e7s = en27 + en37 + en57 + en67 + en87 ;
              }
              else if(HCal_iphi==66){
                  e1s = en11 + en21 + en41 + en51 + en71 ;
                  e2s = en12 + en22 + en42 + en52 + en72 ;
                  e3s = en13 + en23 + en43 + en53 + en73 ;
                  e4s = en14 + en24 + en44 + en54 + en74 ;
                  e5s = en15 + en25 + en45 + en55 + en75 ;
                  e6s = en16 + en26 + en46 + en56 + en76 ;
                  e7s = en17 + en27 + en47 + en57 + en77 ;
              }
              else{  
                  e1s = en11 + en21 + en31 + en41 + en51 + en61 + en71 + en81 ;
                  e2s = en12 + en22 + en32 + en42 + en52 + en62 + en72 + en82 ;
                  e3s = en13 + en23 + en33 + en43 + en53 + en63 + en73 + en83 ;
                  e4s = en14 + en24 + en34 + en44 + en54 + en64 + en74 + en84 ;
                  e5s = en15 + en25 + en35 + en45 + en55 + en65 + en75 + en85 ;
                  e6s = en16 + en26 + en36 + en46 + en56 + en66 + en76 + en86 ;
                  e7s = en17 + en27 + en37 + en47 + en57 + en67 + en77 + en87 ;
              }
           }
           
           else if(HCal_ieta== 26){
           e1s = (hcal_edepth11->at(k) + hcal_edepth21->at(k) + hcal_edepth31->at(k) + hcal_edepth41->at(k) + hcal_edepth51->at(k) + hcal_edepth61->at(k) + hcal_edepth71->at(k) + hcal_edepth81->at(k));
           e2s = (hcal_edepth12->at(k) + hcal_edepth22->at(k) + hcal_edepth32->at(k) + hcal_edepth42->at(k) + hcal_edepth52->at(k) + hcal_edepth62->at(k) + hcal_edepth72->at(k) + hcal_edepth82->at(k));
           e3s = (hcal_edepth13->at(k) + hcal_edepth23->at(k) + hcal_edepth33->at(k) + hcal_edepth12->at(k) + hcal_edepth22->at(k) + hcal_edepth32->at(k) + hcal_edepth43->at(k) + hcal_edepth53->at(k) + hcal_edepth63->at(k) + hcal_edepth73->at(k) + hcal_edepth83->at(k));
           e4s = (hcal_edepth13->at(k) + hcal_edepth23->at(k) + hcal_edepth33->at(k) + hcal_edepth44->at(k) + hcal_edepth54->at(k) + hcal_edepth64->at(k) + hcal_edepth74->at(k) + hcal_edepth84->at(k));
           e5s = (hcal_edepth14->at(k) + hcal_edepth24->at(k) + hcal_edepth34->at(k) + hcal_edepth45->at(k) + hcal_edepth55->at(k) + hcal_edepth65->at(k) + hcal_edepth75->at(k) + hcal_edepth85->at(k));
           e6s = (hcal_edepth15->at(k) + hcal_edepth25->at(k) + hcal_edepth35->at(k) + hcal_edepth46->at(k) + hcal_edepth56->at(k) + hcal_edepth66->at(k) + hcal_edepth76->at(k) + hcal_edepth86->at(k));
           e7s = (hcal_edepth16->at(k) + hcal_edepth26->at(k) + hcal_edepth36->at(k) + hcal_edepth47->at(k) + hcal_edepth57->at(k) + hcal_edepth67->at(k) + hcal_edepth77->at(k) + hcal_edepth87->at(k));

           }
           else if(HCal_ieta==28){
           e1s = (hcal_edepth11->at(k) + hcal_edepth21->at(k) + hcal_edepth31->at(k) + hcal_edepth71->at(k) + hcal_edepth81->at(k));         
           e2s = (hcal_edepth12->at(k) + hcal_edepth22->at(k) + hcal_edepth32->at(k) + hcal_edepth72->at(k) + hcal_edepth82->at(k));
           e3s = (hcal_edepth13->at(k) + hcal_edepth23->at(k) + hcal_edepth33->at(k) + hcal_edepth73->at(k) + hcal_edepth83->at(k));
           e4s = (hcal_edepth14->at(k) + hcal_edepth24->at(k) + hcal_edepth34->at(k) + hcal_edepth74->at(k) + hcal_edepth84->at(k));
           e5s = (hcal_edepth15->at(k) + hcal_edepth25->at(k) + hcal_edepth35->at(k) + hcal_edepth75->at(k) + hcal_edepth85->at(k));
           e6s = (hcal_edepth16->at(k) + hcal_edepth26->at(k) + hcal_edepth36->at(k) + hcal_edepth76->at(k) + hcal_edepth86->at(k));
           e7s = (hcal_edepth17->at(k) + hcal_edepth27->at(k) + hcal_edepth37->at(k) + hcal_edepth77->at(k) + hcal_edepth87->at(k));
           }

           e1r = e1s/e1;
           e12r =( e1s+e2s)/e1;
           e123r =( e1s+e2s+e3s)/e1;
           e23r =(e2s+e3s)/e2;
           //cout <<"en "<<en11<<" "<<en21<<" "<< en31<<" "<<en41<<" "<<en51<<" "<<en61<<" "<<en71<< " "<<en81<<endl; 
           //cout <<"depth 1 "<<e1r<<" "<<e1s<<" "<<e1<<endl; 
           e2r = e2s/e2;
           e3r = e3s/e3;
           e4r = e4s/e4;
           e5r = e5s/e5;
           e6r = e6s/e6;
           e7r = e7s/e7;

           e1dx = e1/activeL1[HCal_ieta-21];
           e2dx = e2/activeL2[HCal_ieta-21];
           e3dx = e3/activeL3[HCal_ieta-21];
           e4dx = e4/activeL4[HCal_ieta-21];
           e5dx = e5/activeL5[HCal_ieta-21];
           e6dx = e6/activeL6[HCal_ieta-21];
           e7dx = e7/activeL7[HCal_ieta-21];
           tree->Fill();
      }
   }
   outputFile->cd();
   tree->Write();
   outputFile->Close();
}
