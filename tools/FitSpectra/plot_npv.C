/////////////////////////////////////////////////////////////////////////
//
// 'ORGANIZATION AND SIMULTANEOUS FITS' RooFit tutorial macro #502
// 
// Creating and writing a workspace
//
//
// 07/2008 - Wouter Verkerke 
//
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
using namespace RooFit ;
using namespace std ;


void plot_npv()
{
  TString path="/afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/";
  TString filename = "data3_v5BCD_Cert_294927-302654_phi6465/split_nvtx/"; //"data3_v5BCD_Cert_294927-302654_phi6465_Isoe12_ecal5x5/";

  //for(int k=18; k<29; k++){ //loop over ieta
  for(int k=21; k<25; k++){ //ieta
    for(int ivtx=0; ivtx<5; ivtx++){  //vertex
     for(int d=1; d<7; d++){
      TString nvtxcut = "";
      if(ivtx==1) nvtxcut = "&& nvtx<16.75";
      else if(ivtx==2) nvtxcut = "&& nvtx>16.75 && nvtx<24.06";
      else if(ivtx==3) nvtxcut = "&& nvtx>24.06 && nvtx<31.37";
      else if(ivtx==4) nvtxcut = "&& nvtx>31.37";
      if(k==18 && d>5) continue; 
      else if(k<26 && d>6) continue;

      TString Nieta, Nidep, Nnvtx;
      Nieta.Form("%d",k);
      Nidep.Form("%d",d);
      Nnvtx.Form("%d",ivtx);
 
      cout <<"ieta, idepth: "<<Nieta<<" "<<Nidep<<endl;
      TString cuttree("e"+Nidep+" < 3.0 && e"+Nidep+" > 0.00001 && isMedium && ISOR04< 0.15 && pt > 20.0 && HCal_cellHot==1 && HCal_ieta=="+Nieta+nvtxcut);

     cout <<cuttree<<endl;
 
 // Declare observable x
  RooRealVar* nvtx = new RooRealVar("nvtx","nvtx",10,0,50000) ;
  RooRealVar* iso = new RooRealVar("ISOR04","ISOR04",0,-50000,50000) ;
  RooRealVar* Trkiso = new RooRealVar("TrkISOR03","TrkISOR03",0,-50000,50000) ;
  RooRealVar* pt = new RooRealVar("pt","pt",1,0,50000) ;
  RooRealVar* isMedium = new RooRealVar("isMedium", "isMedium", 1, 0, 2);
  RooRealVar* HCal_ieta = new RooRealVar("HCal_ieta","HCal_ieta",10,0,40) ;
  RooRealVar* HCal_iphi = new RooRealVar("HCal_iphi","HCal_iphi",10,0,40) ;
  RooRealVar* HCal_cellHot = new RooRealVar("HCal_cellHot","HCal_cellHot",0,0,1) ;
  RooRealVar* e4 = new RooRealVar("e"+Nidep,"e"+Nidep,1,0,3) ;
  RooRealVar* ecal = new RooRealVar("ecal5x5","ecal5x5",10,0,50000) ;
  //RooRealVar* e2r = new RooRealVar("e2r","e2r",10,0,10) ;
  //RooRealVar* e3r = new RooRealVar("e3r","e3r",10,0,10) ;
  //RooRealVar* e4r = new RooRealVar("e4r","e4r",10,0,10) ;
  //RooRealVar* e5r = new RooRealVar("e5r","e5r",10,0,10) ;
  //RooRealVar* e6r = new RooRealVar("e6r","e6r",10,0,10) ;

  TString signalfile = "/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/tree_data3_v5BCD_Cert_294927-302654_phi_pathlength.root";
 
  TFile sigFile(signalfile);
  TTree* sigTree = (TTree*)sigFile.Get("tree");
  RooRealVar* evWeight = new RooRealVar("weight","weight",1,-10,10) ;

  RooArgSet obsAndWeight;
  obsAndWeight.add(*e4);
  obsAndWeight.add(*nvtx);
  //obsAndWeight.add(*e1r);
  //obsAndWeight.add(*e1s);
  //obsAndWeight.add(*e23r);
  //obsAndWeight.add(*ecal);
/*
  obsAndWeight.add(*e3r);
  obsAndWeight.add(*e4r);
  obsAndWeight.add(*e5r);
  obsAndWeight.add(*e6r);
*/
  obsAndWeight.add(*pt);
  obsAndWeight.add(*iso);
  //obsAndWeight.add(*Trkiso);
  obsAndWeight.add(*HCal_cellHot);
  obsAndWeight.add(*HCal_ieta);
  obsAndWeight.add(*isMedium);
  obsAndWeight.add(*evWeight);

  RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut(cuttree)) ;
  data->Print() ;


  int Emax = 50.0;
  RooBinning tbins(0,Emax);
  tbins.addUniform(50,0,Emax) ;
  RooPlot* dtframe = nvtx->frame(Range(0,Emax,kTRUE),Title("#vtx in ieta "+ Nieta +" idepth "+Nidep));
  data->plotOn(dtframe,Binning(tbins));
  data->statOn(dtframe,Layout(0.55,0.99,0.75)) ;
  TCanvas* c1 = new TCanvas();
  dtframe->Draw();
  c1->SaveAs(path+filename+"nvtx_depth_"+Nidep+"_ieta_"+Nieta+"_"+Nnvtx+"_Cut10MeV_check.png");
    }
   }
  }
}
