#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"
#include "CommonFunc.h"
#include "CMSLUMI.h"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./sig_plus_bkg_fit signalFile outputName ieta depth ZmassCut min_depth4 max_depth4 min_depth5 max_depth5 min_depth6 max_depth6 min_depth7 max_depth7 min_depth4r max_depth4r min_depth5r max_depth5r min_depth6r max_depth6r \n" << std::endl;

        TString signalfile=argv[1];
        TString outputName=argv[2];
        TString Nieta=argv[3];
        TString Ndepth=argv[4];
        TString ZmassCut=argv[5];
        TString StrMin4=argv[6];
        TString StrMax4=argv[7];
	TString StrMin5=argv[8];
        TString StrMax5=argv[9];
	TString StrMin6=argv[10];
        TString StrMax6=argv[11]; 
        TString StrMin7=argv[12];
        TString StrMax7=argv[13];
	TString StrMin4r=argv[14];
        TString StrMax4r=argv[15];
        TString StrMin5r=argv[16];
        TString StrMax5r=argv[17];
        TString StrMin6r=argv[18];
        TString StrMax6r=argv[19];


        int ieta = Nieta.Atoi();
        int depth = Ndepth.Atoi();
        float Emax = StrMax6.Atof();
        float Emin = StrMin6.Atof();
	float Emax4 = StrMax4.Atof();
        float Emin4 = StrMin4.Atof();
        float Emax5 = StrMax5.Atof();
        float Emin5 = StrMin5.Atof();
        float Emax6 = StrMax6.Atof();
        float Emin6 = StrMin6.Atof();
        float Emax7 = StrMax7.Atof();
        float Emin7 = StrMin7.Atof();
	float Emax4r = StrMax4r.Atof();
        float Emin4r = StrMin4r.Atof();
        float Emax5r = StrMax5r.Atof();
        float Emin5r = StrMin5r.Atof();
        float Emax6r = StrMax6r.Atof();
        float Emin6r = StrMin6r.Atof();

	//cout<<Emax5<<" "<<Emin5<<endl;
        if(depth==7){
           Emax = StrMax7.Atof();
           Emin = StrMin7.Atof();
        }
	else if(depth==5){
	  Emax = StrMax5.Atof();
	  Emin = StrMin5.Atof();
        }
	else if(depth==4){
	  Emax = StrMax4.Atof();
	  Emin = StrMin4.Atof();
        }
	else if(depth==6){
	  Emax = StrMax6.Atof();
	  Emin = StrMin6.Atof();
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

        double pos_mean = -999.;
        double pos_errhigh = -999.;
        double pos_errlow = -999.;
        double sigfrac = -999.;
        double bkgcoef = -999.;
        double norm = -999.;
        outtree->Branch("ieta", &ieta, "ieta/I");
        outtree->Branch("depth", &depth, "depth/I");
        outtree->Branch("pos_mean", &pos_mean, "pos_mean/D");
        outtree->Branch("pos_errhigh", &pos_errhigh, "pos_errhigh/D");
        outtree->Branch("pos_errlow", &pos_errlow, "pos_errlow/D");
        outtree->Branch("sigfrac", &sigfrac, "sigfrac/D");
        outtree->Branch("bkgcoef", &bkgcoef, "bkgcoef/D");
        outtree->Branch("norm", &norm, "norm/D");

        // Declare observable x
        RooRealVar* evWeight = new RooRealVar("weight","weight",1,-10,10) ;
        RooRealVar* HCAL_energy = new RooRealVar("e"+Ndepth+"_o","e"+Ndepth+"_o",0.4,Emin,Emax) ;
	RooRealVar* HCAL_energy_e4 = new RooRealVar("e4_o","e4_o",0.4,Emin4,Emax4) ;
        RooRealVar* HCAL_energy_e5 = new RooRealVar("e5_o","e5_o",0.4,Emin5,Emax5) ;
        RooRealVar* HCAL_energy_e6 = new RooRealVar("e6_o","e6_o",0.4,Emin6,Emax6) ;
        RooRealVar* HCAL_energy_e7 = new RooRealVar("e7_o","e7_o",0.4,Emin7,Emax7) ;
        RooRealVar* Z_mass = new RooRealVar("Z_mass","Z_mass",91,0,1000) ;
	RooRealVar* IsMuonRec = new RooRealVar("IsMuonRec","IsMuonRec",0,0,2) ;
	//RooRealVar* HCAL_energy_e4r = new RooRealVar("e4r_o","e4r_o",1.,Emin4r,Emax4r) ;
	//RooRealVar* HCAL_energy_e5r = new RooRealVar("e5r_o","e5r_o",1.,Emin5r,Emax5r) ;
	//RooRealVar* HCAL_energy_e6r = new RooRealVar("e6r_o","e6r_o",1.,Emin6r,Emax6r) ;
	RooRealVar* phi_probe = new RooRealVar("phi_probe","phi_probe",-0.005,-2000.,2000.) ;
	//RooRealVar* phi_calc = new RooRealVar("phi_calc","phi_calc",-0.005,-3.,3.) ;
	//RooRealVar* DelPhi_probe = new RooRealVar("DelPhi_probe","DelPhi_probe",-0.005,-4.,4.) ;
	//RooRealVar* nMuon_probe = new RooRealVar("nMuon_probe","nMuon_probe",0,0,5) ;
	//RooRealVar* MuonIsMed_probe = new RooRealVar("MuonIsMed_probe","MuonIsMed_probe",0,0,2) ;
        //Gaussian
        RooRealVar* mean = new RooRealVar("mean","mean of gaussian",0) ;
        RooRealVar* sigma = new RooRealVar("Gaussian #sigma","width of gaussian",0.2,0.001,2) ;
        RooAbsPdf* gausSig = new RooGaussian("gausSig","gausSig",*HCAL_energy,*mean,*sigma) ;  
        //Landau
        RooRealVar* ml = new RooRealVar("Landau location","mean landau",0.6,0.1,2.) ;
	//RooRealVar* ml = new RooRealVar("Landau location","mean landau",0.36,0.1,2) ;
        RooRealVar* sl = new RooRealVar("Landau scale","sigma landau",0.097,0.00,2) ;
        RooAbsPdf* landauSig = new RooLandau("lx","lx",*HCAL_energy,*ml,*sl) ; 
        //bkg
	RooRealVar* a0 = new RooRealVar("a0","a0",-3,-100,0.) ;
        RooAbsPdf* bkgPdf = new RooExponential("bkg","Background",*HCAL_energy,*a0) ;

        RooAbsPdf* sigPdf = new RooFFTConvPdf("sigPdf","landau (X) gauss signal",*HCAL_energy,*landauSig,*gausSig) ;
        RooRealVar* bkgfrac = new RooRealVar("bkgfrac","fraction of background",0.2,0.01,1.0) ;
        RooAbsPdf* sigbkg = new RooAddPdf("sigbkg","signal + bkg",RooArgList(*bkgPdf,*sigPdf),*bkgfrac) ;
        RooRealVar* nevents = new RooRealVar("nevents","number of fitted events",500,0,100000) ;
        RooExtendPdf* model = new RooExtendPdf("model","extended signal p.d.f",*sigbkg,*nevents,"sigRange") ;

        RooArgSet obsAndWeight;
        obsAndWeight.add(*HCAL_energy);
        obsAndWeight.add(*Z_mass);
	obsAndWeight.add(*IsMuonRec);
	obsAndWeight.add(*phi_probe);
	//obsAndWeight.add(*phi_calc);
	//obsAndWeight.add(*DelPhi_probe);
	//obsAndWeight.add(*nMuon_probe);
	//obsAndWeight.add(*HCAL_energy_e4r);
	//obsAndWeight.add(*HCAL_energy_e6r);
	//obsAndWeight.add(*HCAL_energy_e5r);
	//obsAndWeight.add(*MuonIsMed_probe);
	//obsAndWeight.add(*HCAL_energy_e4);
	//obsAndWeight.add(*HCAL_energy_e5);
	//obsAndWeight.add(*HCAL_energy_e6);
	//obsAndWeight.add(*HCAL_energy_e7);
        if(depth==6){
	  //obsAndWeight.add(*HCAL_energy_e7);
	  obsAndWeight.add(*HCAL_energy_e4);
	  obsAndWeight.add(*HCAL_energy_e5);
	}
        else if(depth==7){
	  obsAndWeight.add(*HCAL_energy_e6);
	  obsAndWeight.add(*HCAL_energy_e4);
          obsAndWeight.add(*HCAL_energy_e5);
	}
	else if(depth==5){
	  obsAndWeight.add(*HCAL_energy_e4);
	  obsAndWeight.add(*HCAL_energy_e6);
          //obsAndWeight.add(*HCAL_energy_e7);
	}
	else if(depth==4){
	  obsAndWeight.add(*HCAL_energy_e5);
	  obsAndWeight.add(*HCAL_energy_e6);
          //obsAndWeight.add(*HCAL_energy_e7);
	}
        //obsAndWeight.add(*evWeight);

        cout <<"before dataset"<<endl;
	//TString cuttree = " Z_mass > "+ZmassCut+" && e6_o < " + StrMax6 + " && e6_o > " + StrMin6+/* " && e7_o < " + StrMax7 + " && e7_o > " + StrMin7+*/" && e4_o < " + StrMax4 + " && e4_o > " + StrMin4+ " && e5_o < " + StrMax5 + " && e5_o > " + StrMin5+" && ((!IsMuonRec && nMuon_probe==0.) || (IsMuonRec && phi_probe>-10. && nMuon_probe>0 && abs(DelPhi_probe)>0.2))";// && e6r_o < " + StrMax6r+ " && e6r_o > " + StrMin6r+" && e4r_o < " + StrMax4r + " && e4r_o > " + StrMin4r+ " && e5r_o < " + StrMax5r + " && e5r_o > " + StrMin5r;
	TString cuttree = " Z_mass > "+ZmassCut+" && e6_o < " + StrMax6 + " && e6_o > " + StrMin6/*+ " && e7_o < " + StrMax7 + " && e7_o > " + StrMin7*/+" && e4_o < " + StrMax4 + " && e4_o > " + StrMin4+ " && e5_o < " + StrMax5 + " && e5_o > " + StrMin5+" && IsMuonRec && phi_probe>-10.";// && nMuon_probe>0 ";//&& abs(DelPhi_probe)<0.2";//  && e6r_o <" + StrMax6r+ " && e6r_o > " + StrMin6r+" && e4r_o < " + StrMax4r + " && e4r_o > " + StrMin4r+ " && e5r_o < " + StrMax5r + " && e5r_o > " + StrMin5r;
	//TString cuttree = " Z_mass > "+ZmassCut+" && e6_o < " + StrMax6 + " && e6_o > " + StrMin6/*+ " && e7_o < " + StrMax7 + " && e7_o > " + StrMin7*/+" && e4_o < " + StrMax4 + " && e4_o > " + StrMin4+ " && e5_o < " + StrMax5 + " && e5_o > " + StrMin5+" && IsMuonRec && phi_probe<-10. && nMuon_probe>0 && e6r_o <" + StrMax6r+ " && e6r_o > " + StrMin6r+" && e4r_o < " + StrMax4r + " && e4r_o > " + StrMin4r+ " && e5r_o < " + StrMax5r + " && e5r_o > " + StrMin5r;
        cout <<"selection cuts: "<<cuttree<<endl;

        //RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut(cuttree)) ;
	RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),Import(*sigTree),Cut(cuttree)) ;
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
        sigfrac = 1.-bkgfrac->getVal();
        bkgcoef = a0->getVal();
        norm = nevents->getVal();
        outtree->Fill();

        RooBinning tbins(Emin,Emax);
        tbins.addUniform(40,Emin,Emax) ;
        RooPlot* dtframe = HCAL_energy->frame(Range(Emin,Emax,kTRUE),Title("energy in ieta "+ Nieta  + " idepth "+Ndepth));
        data->plotOn(dtframe,Binning(tbins));
        model->plotOn(dtframe);
        model->plotOn(dtframe, Components(*bkgPdf), LineStyle(kDashed));
        model->plotOn(dtframe, Components(*sigPdf), LineColor(kRed));
        model->paramOn(dtframe,Layout(0.60, 0.95, 0.90), Format("NEU",AutoPrecision(0))) ;
        data->statOn(dtframe,Layout(0.65,0.95,0.5), Format("NEU",AutoPrecision(0))) ;
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
