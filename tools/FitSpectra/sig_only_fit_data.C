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


void sig_only_fit_data()
{
  TString path="/afs/cern.ch/user/n/nlu/work/private/CMS/HCal/MIPCali/plots/"; //output path directory
  TString filename =  "data3_v5BCD_Cert_294927-302654_phi6465/"; //"data3_v5BCD_Cert_294927-302654_phi6465_Isoe12_ecal5x5/";

  FILE * sFile;
  sFile = fopen (path+filename+"summary_cut10MeV.txt","w");

  //for(int k=18; k<29; k++){ //loop over ieta
  for(int k=21; k<25; k++){ //ieta
    fprintf(sFile,"//ieta %d \n",k);
    for(int ivtx=0; ivtx<5; ivtx++){  //vertex
      fprintf(sFile,"//ivertex %d \n",ivtx);
      for (int d=1; d<7; d++){ 
      fprintf(sFile,"//depth %d \n",d);
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
 
      FILE * pFile;
      pFile = fopen (path+filename+"result_depth_"+Nidep+"_ieta_"+Nieta+"_"+Nnvtx+".txt","w");
      fprintf (pFile, "ieta = %d, idep = %d \n", k, d);
      cout <<"ieta, idepth: "<<Nieta<<" "<<Nidep<<endl;

      TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 &&  isMedium && ISOR04< 0.15 && pt > 20.0 && HCal_cellHot==1 && HCal_ieta=="+Nieta+nvtxcut);
      //TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 && ecal5x5 <0.5 &&  isMedium && ISOR04< 0.15 && pt > 20.0 && HCal_cellHot==1 && HCal_ieta=="+Nieta+nvtxcut);
      fprintf (pFile, "cut: %s \n",cuttree.Data());
      cout <<cuttree<<endl;

  // Declare observable x
  RooRealVar* nvtx = new RooRealVar("nvtx","nvtx",10,0,1000) ;
  RooRealVar* iso = new RooRealVar("ISOR04","ISOR04",0,-1000,1000) ;
  RooRealVar* Trkiso = new RooRealVar("TrkISOR03","TrkISOR03",0,-100,100) ;
  RooRealVar* pt = new RooRealVar("pt","pt",1,0,500000) ;
  RooRealVar* isMedium = new RooRealVar("isMedium", "isMedium", 1, 0, 2);
  RooRealVar* HCal_ieta = new RooRealVar("HCal_ieta","HCal_ieta",10,0,40) ;
  RooRealVar* HCal_iphi = new RooRealVar("HCal_iphi","HCal_iphi",10,0,40) ;
  RooRealVar* HCal_cellHot = new RooRealVar("HCal_cellHot","HCal_cellHot",0,0,1) ;
  RooRealVar* e4 = new RooRealVar("e"+Nidep,"e"+Nidep,1,0,3) ;
  RooRealVar* e1r = new RooRealVar("e"+Nidep+"r","e"+Nidep+"r",10,0,10) ;
  RooRealVar* e1s = new RooRealVar("e"+Nidep+"s","e"+Nidep+"s",10,0,10) ;
  RooRealVar* e12r = new RooRealVar("e12r","e12r",10,0,1000) ;
  RooRealVar* e23r = new RooRealVar("e23r","e23r",10,0,1000) ;
  RooRealVar* ecal = new RooRealVar("ecal5x5","ecal5x5",10,0,50000) ;

  //RooRealVar* e2r = new RooRealVar("e2r","e2r",10,0,10) ;
  //RooRealVar* e3r = new RooRealVar("e3r","e3r",10,0,10) ;
  //RooRealVar* e4r = new RooRealVar("e4r","e4r",10,0,10) ;
  //RooRealVar* e5r = new RooRealVar("e5r","e5r",10,0,10) ;
  //RooRealVar* e6r = new RooRealVar("e6r","e6r",10,0,10) ;

   //muon pdf
   RooRealVar* mean = new RooRealVar("mean","mean of gaussian",0) ;
   RooRealVar* sigma = new RooRealVar("sigma","width of gaussian",0.1,0.001,2) ;
   RooAbsPdf* sig1 = new RooGaussian("sig1","Signal",*e4,*mean,*sigma) ;  
   //landau
   RooRealVar* ml = new RooRealVar("ml","mean landau",0.5,0.1,2) ;
   RooRealVar* sl = new RooRealVar("sl","sigma landau",0.15, 0.01,2) ;
   RooAbsPdf* landau = new RooLandau("lx","lx",*e4,*ml,*sl) ; 
 
   RooRealVar* a0 = new RooRealVar("a0","a0",-3,-100,0.) ;
   RooAbsPdf* bkg = new RooExponential("bkg","Background",*e4,*a0) ;

   // Construct landau (x) gauss
   RooAbsPdf* sig = new RooFFTConvPdf("sig","landau (X) gauss signal",*e4,*landau,*sig1) ;
   //
   RooRealVar* bkgfrac = new RooRealVar("bkgfrac","fraction of background",0.1,0.0,0.2) ;
   RooAbsPdf* model = new RooAddPdf("model","g1+g2+a",RooArgList(*bkg,*sig),*bkgfrac) ;

  TString signalfile = "/eos/cms/store/group/dpg_hcal/comm_hcal/nlu/ntuples/tree_data3_v5BCD_Cert_294927-302654_phi_pathlength.root";
 
  //TString signalfile = "/eos/cms/store/user/nlu/DoubleMuon/tree_mc3_phi.root";

  TFile sigFile(signalfile);
  TTree* sigTree = (TTree*)sigFile.Get("tree");
  RooRealVar* evWeight = new RooRealVar("weight","weight",1,-10,10) ;

  RooArgSet obsAndWeight;
  obsAndWeight.add(*e4);
  obsAndWeight.add(*nvtx);
/*
  obsAndWeight.add(*e3r);
  obsAndWeight.add(*e4r);
  obsAndWeight.add(*e5r);
  obsAndWeight.add(*e6r);
*/
  obsAndWeight.add(*ecal);
  obsAndWeight.add(*pt);
  obsAndWeight.add(*iso);
  obsAndWeight.add(*HCal_cellHot);
  obsAndWeight.add(*HCal_ieta);
  obsAndWeight.add(*isMedium);
  obsAndWeight.add(*evWeight);

  RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut(cuttree)) ;
  //RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut("e4> 0 && e4<2 && isMedium==1 && ISOR04< 0.15 && pt > 5.0 && HCal_ieta==25")) ;
  data->Print() ;

  //RooFitResult* r = ggfpdf->fitTo(*data,Save()) ;
  //r->Print() ;

  RooNLLVar* nll = (RooNLLVar*)sig->createNLL(*data);
  /*
  RooMinimizer minim_fix(*nll);
  minim_fix.setStrategy(1);
  minim_fix.setPrintLevel(1);
  minim_fix.setEps(1);
  int status = minim_fix.minimize("Minuit2", "Migrad");
  */
  RooArgSet POIs(*ml, *sl, *sigma);
  RooMinuit minim(*nll);
  minim.migrad() ;
  minim.minos(POIs) ;
  TFile *tout = new TFile( path+filename+"result_depth_"+Nidep+"_ieta_"+Nieta+"_"+Nnvtx+".root", "RECREATE" );
  tout->cd();
  RooFitResult *result = minim.save("fitResult","Fit Results");
  result->Write();
  
  fprintf (pFile," Landau location parameter: %.4e + %.4e - %.4e \n",ml->getVal(), ml->getErrorHi(), ml->getErrorLo());
  fprintf (pFile," Landau scale parameter: %.4e + %.4e - %.4e \n",sl->getVal(), sl->getErrorHi(), sl->getErrorLo());
  fprintf (pFile," Gaussian sigma: %.4e + %.4e - %.4e \n \n",sigma->getVal(), sigma->getErrorHi(), sigma->getErrorLo());
  fprintf (sFile,"ene.push_back(%.4e); ene.push_back( %.4e); ene.push_back(%.4e); \n", ml->getVal(), ml->getErrorHi(), -ml->getErrorLo());
  fclose (pFile);

  int Emax = 3.0;
  RooBinning tbins(0,Emax);
  tbins.addUniform(120,0,Emax) ;
  RooPlot* dtframe = e4->frame(Range(0,Emax,kTRUE),Title("energy in ieta "+ Nieta +" idepth "+Nidep));
  data->plotOn(dtframe,Binning(tbins));
  sig->plotOn(dtframe);
  //model->plotOn(dtframe, Components(*bkg), LineStyle(kDashed));
  //model->plotOn(dtframe, Components(*sig), LineColor(kRed));
  //landau->plotOn(dtframe, LineColor(kRed));
  sig->paramOn(dtframe,Layout(0.55)) ;
  //data->statOn(dtframe,Layout(0.55,0.99,0.75)) ;
  TCanvas* c1 = new TCanvas();
  dtframe->Draw();
  c1->SaveAs(path+filename+"depth_"+Nidep+"_ieta_"+Nieta+"_"+Nnvtx+"_cut10MeV.png");
      }
    }
  }
  fclose (sFile);
}
