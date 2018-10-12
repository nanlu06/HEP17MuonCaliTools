#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"
#include "CommonFunc.h"
#include "CMSLUMI.h"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./sig_plus_bkg_fit signalFile outputName ieta depth ZmassCut min_depth6 max_depth6 min_depth7 max_depth7 \n" << std::endl;

        TString signalfile=argv[1];
        TString outputName=argv[2];
        TString Nieta=argv[3];
        TString Ndepth=argv[4];
        TString ZmassCut=argv[5];
        TString StrMin6=argv[6];
        TString StrMax6=argv[7]; 
        TString StrMin7=argv[8];
        TString StrMax7=argv[9];

        int ieta = Nieta.Atoi();
        int depth = Ndepth.Atoi();
        float Emax = StrMax6.Atof();
        float Emin = StrMin6.Atof();
        if(depth==7){
           Emax = StrMax7.Atof();
           Emin = StrMin7.Atof();
        }

        CommonFunc::setTDRStyle();
        int W = 800;
        int H = 600;
        int H_ref = 600;
        int W_ref = 800;
        float T = 0.08*H_ref;
        float B = 0.12*H_ref;
        float L = 0.12*W_ref;
        float R = 0.04*W_ref;
 
        TFile sigFile(signalfile);
        TTree* sigTree = (TTree*)sigFile.Get("tree");

        TTree *outtree = new TTree("outtree", "Info");

        float pos_mean = -999.;
        float pos_errhigh = -999.;
        float pos_errlow = -999.;
        float sigfrac = -999.;
        float bkgcoef = -999.;
        float norm = -999.;
        outtree->Branch("ieta", &ieta, "ieta/I");
        outtree->Branch("depth", &depth, "depth/I");
        outtree->Branch("pos_mean", &pos_mean, "pos_mean/F");
        outtree->Branch("pos_errhigh", &pos_errhigh, "pos_errhigh/F");
        outtree->Branch("pos_errlow", &pos_errlow, "pos_errlow/F");
        outtree->Branch("sigfrac", &sigfrac, "sigfrac/F");
        outtree->Branch("bkgcoef", &bkgcoef, "bkgcoef/F");
        outtree->Branch("norm", &norm, "norm/F");

        // Declare observable x
        RooRealVar* evWeight = new RooRealVar("weight","weight",1,-10,10) ;
        RooRealVar* HCAL_energy = new RooRealVar("e"+Ndepth+"_o","e"+Ndepth+"_o",0.4,Emin,Emax) ;
        RooRealVar* HCAL_energy_e6 = new RooRealVar("e6_o","e6_o",0.4,Emin,Emax) ;
        RooRealVar* HCAL_energy_e7 = new RooRealVar("e7_o","e7_o",0.4,Emin,Emax) ;
        RooRealVar* Z_mass = new RooRealVar("Z_mass","Z_mass",91,0,500) ;
        //Gaussian
        RooRealVar* mean = new RooRealVar("mean","mean of gaussian",0) ;
        RooRealVar* sigma = new RooRealVar("Gaussian #sigma","width of gaussian",0.11,0.05,2) ;
        RooAbsPdf* gausSig = new RooGaussian("gausSig","gausSig",*HCAL_energy,*mean,*sigma) ;  
        //Landau
        RooRealVar* ml = new RooRealVar("Landau location","mean landau",0.588,0.1,2) ;
        RooRealVar* sl = new RooRealVar("Landau scale","sigma landau",0.097,0.01,2) ;
        RooAbsPdf* landauSig = new RooLandau("lx","lx",*HCAL_energy,*ml,*sl) ; 
        //bkg
        RooRealVar* a0 = new RooRealVar("a0","a0",-3,-100,0.) ;
        RooAbsPdf* bkgPdf = new RooExponential("bkg","Background",*HCAL_energy,*a0) ;

        RooAbsPdf* sigPdf = new RooFFTConvPdf("sigPdf","landau (X) gauss signal",*HCAL_energy,*landauSig,*gausSig) ;
        RooRealVar* bkgfrac = new RooRealVar("bkgfrac","fraction of background",0.1,0.0,1.0) ;
        RooAbsPdf* model = new RooAddPdf("model","signal + bkg",RooArgList(*bkgPdf,*sigPdf),*bkgfrac) ;

        RooArgSet obsAndWeight;
        obsAndWeight.add(*HCAL_energy);
        obsAndWeight.add(*Z_mass);
        if(depth==6) obsAndWeight.add(*HCAL_energy_e7);
        else if(depth==7) obsAndWeight.add(*HCAL_energy_e6);
        obsAndWeight.add(*evWeight);

        cout <<"before dataset"<<endl;
        TString cuttree = " Z_mass > "+ZmassCut+" && e6_o < " + StrMax6 + " && e6_o > " + StrMin6+ " && e7_o < " + StrMax7 + " && e7_o > " + StrMin7;
        cout <<"selection cuts: "<<cuttree<<endl;

        RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut(cuttree)) ;
        data->Print() ;
        cout <<"after dataset"<<endl;

        RooNLLVar* nll = (RooNLLVar*)model->createNLL(*data);
        //RooArgSet POIs(*ml, *sl, *sigma);
        RooArgSet POIs(*ml);
        RooMinuit minim(*nll);
        minim.migrad() ;
        minim.minos(POIs) ;

        pos_mean = ml->getVal();
        pos_errhigh = ml->getErrorHi();
        pos_errlow = -ml->getErrorLo();
        if(pos_errlow==0) pos_errlow = pos_errhigh;
        if(pos_errhigh==0) pos_errhigh = pos_errlow;
        sigfrac = 1-bkgfrac->getVal();
        bkgcoef = a0->getVal();
        outtree->Fill();

        RooBinning tbins(Emin,Emax);
        tbins.addUniform(40,Emin,Emax) ;
        RooPlot* dtframe = HCAL_energy->frame(Range(Emin,Emax,kTRUE),Title("energy in ieta "+ Nieta  + " idepth "+Ndepth));
        data->plotOn(dtframe,Binning(tbins));
        model->plotOn(dtframe);
        model->plotOn(dtframe, Components(*bkgPdf), LineStyle(kDashed));
        model->plotOn(dtframe, Components(*sigPdf), LineColor(kRed));
        model->paramOn(dtframe,Layout(0.60, 0.95, 0.90), Format("NEU",AutoPrecision(0))) ;
        data->statOn(dtframe,Layout(0.65,0.95,0.6), Format("NEU",AutoPrecision(0))) ;
        dtframe->getAttText("model_paramBox")->SetTextColor(kBlack);
        dtframe->getAttFill("model_paramBox")->SetFillStyle(0);
        //dtframe->getAttText("sig_paramBox")->SetLineWidth(0);
        dtframe->getAttText("model_paramBox")->SetTextSize(0.032);

        TCanvas *c1 = new TCanvas("c1","Muon energy spectrum in HCAL",200,10,700,500);
        c1->SetFillColor(0);
        c1->SetBorderMode(0);
        c1->SetFrameFillStyle(0);
        c1->SetFrameBorderMode(0);
        c1->SetLeftMargin( L/W );
        c1->SetRightMargin( R/W );
        c1->SetTopMargin( T/H );
        c1->SetBottomMargin( B/H );
        c1->SetTickx(0);
        c1->SetTicky(0);

        dtframe->SetXTitle("Energy [GeV]");
        dtframe->SetYTitle("Events");
        dtframe->Draw();
        //CommonFunc::AddCMS(c1);
        c1->Update();
        c1->RedrawAxis();
        c1->GetFrame()->Draw();
        c1->SaveAs("depth_"+Ndepth+"_ieta_"+Nieta+".png");
        c1->SaveAs("depth_"+Ndepth+"_ieta_"+Nieta+".pdf");
        c1->SaveAs("depth_"+Ndepth+"_ieta_"+Nieta+".eps");
        c1->SaveAs("depth_"+Ndepth+"_ieta_"+Nieta+".C");

        TFile *rtFile = new TFile ( outputName, "RECREATE");
        cout <<"create root"<<endl;
        outtree->Write();
        rtFile->Close(); 
}
