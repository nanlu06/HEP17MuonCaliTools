#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./sig_only_fit_data signalFile outputPath outputName\n" << std::endl;

        TString signalfile=argv[1];
        TString path=argv[2];
        TString outputName=argv[3];
        TString rtfilename = path + outputName;

        system("mkdir -vp "+path);
        FILE * sFile;
        sFile = fopen (path+"summary_cut10MeV.txt","w");

        TFile sigFile(signalfile);
        TTree* sigTree = (TTree*)sigFile.Get("tree");

        TTree *outtree = new TTree("outtree", "Info");
        cout <<"create tree"<<endl;

        unsigned int num=0;
        int ieta;
        //int iphi;
        int ecal5x5_bin;
        int idepth = 0;
        float pos_mean;
        float pos_errhigh;
        float pos_errlow;

        outtree->Branch("num", &num, "num/I");
        outtree->Branch("ieta", &ieta, "ieta/I");
        //outtree->Branch("iphi", &iphi, "iphi/I");
        outtree->Branch("ecal5x5_bin", &ecal5x5_bin, "ecal5x5_bin/I");
        outtree->Branch("idepth", &idepth, "idepth/I");
        outtree->Branch("pos_mean", &pos_mean, "pos_mean/F");
        outtree->Branch("pos_errhigh", &pos_errhigh, "pos_errhigh/F");
        outtree->Branch("pos_errlow", &pos_errlow, "pos_errlow/F");

        int dephigh = 0;
        int deplow = 0;

        for(int k=16; k<27; k++){ 
                cout <<"ieta="<<k<<endl;
                fprintf(sFile,"//ieta %d \n",k);

                ieta = k;
                TString Nieta;
                Nieta.Form("%d",ieta);

                for(int iecal5x5_bin=0; iecal5x5_bin<5; iecal5x5_bin++){  
                        fprintf(sFile,"//ivertex %d \n",iecal5x5_bin);

                        ecal5x5_bin = iecal5x5_bin;
                        TString Necal5x5_bin;
                        Necal5x5_bin.Form("%d",iecal5x5_bin);

                        if(ieta==16) {deplow=4;dephigh=4;}
                        if(ieta==17) {deplow=2;dephigh=3;}
                        if(ieta==18) {deplow=1;dephigh=5;}
                        if(ieta>=19 && ieta<=25 ) {deplow=1;dephigh=6;}
                        if(ieta==26) {deplow=1;dephigh=7;}

                        for(int d=deplow;d<=dephigh;d++){
                                idepth = d;
                                cout <<"idepth="<<d<<endl;
                                fprintf(sFile,"//depth %d \n",d);
                                TString ecal5x5_bincut = "";
                                if(iecal5x5_bin==1) ecal5x5_bincut = "&& ecal5x5==0";
                                else if(iecal5x5_bin==2) ecal5x5_bincut = "&& ecal5x5>0 && ecal5x5<0.55";
                                else if(iecal5x5_bin==3) ecal5x5_bincut = "&& ecal5x5>0.55 && ecal5x5<1.1";
                                else if(iecal5x5_bin==4) ecal5x5_bincut = "&& ecal5x5>1.1 && ecal5x5<2.7";
                                else if(iecal5x5_bin==5) ecal5x5_bincut = "&& ecal5x5>2.7";

                                //if(k==18 && d>5) continue;
                                //else if(k==17 && (d<2 || d>3)) continue;
                                //else if(k==16 && (d!=4)) continue;
                                //else if(k<26 && d>6) continue;

                                TString Nidep;
                                Nidep.Form("%d",d);

                                FILE * pFile;
                                pFile = fopen (path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iecal5x5_bin_"+Necal5x5_bin+".txt","w");
                                fprintf (pFile, "ieta = %d, idep = %d \n", k, d);
                                cout <<"ieta, idepth: "<<Nieta<<" "<<Nidep<<endl;

                                TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0. && Trkmatch && HCal_ieta=="+Nieta+ecal5x5_bincut);
                                fprintf (pFile, "cut: %s \n",cuttree.Data());
                                cout <<cuttree<<endl;

                                // Declare observable x
                                RooRealVar* p = new RooRealVar("p","p",10,0,5000) ;
                                RooRealVar* nvtx_good = new RooRealVar("nvtx_good","nvtx_good",10,0,1000) ;
                                RooRealVar* iso = new RooRealVar("ISOR04","ISOR04",0,-1000,1000) ;
                                RooRealVar* Trkiso = new RooRealVar("TrkISOR03","TrkISOR03",0,-100,100) ;
                                RooRealVar* pt = new RooRealVar("pt","pt",1,0,500000) ;
                                RooRealVar* isMedium = new RooRealVar("isMedium", "isMedium", 1, 0, 2);
                                RooRealVar* Trkmatch = new RooRealVar("Trkmatch","Trkmatch",1,0,1);
                                RooRealVar* HCal_ieta = new RooRealVar("HCal_ieta","HCal_ieta",10,0,40) ;
                                RooRealVar* HCal_iphi = new RooRealVar("HCal_iphi","HCal_iphi",10,0,40) ;
                                RooRealVar* HCal_cellHot = new RooRealVar("HCal_cellHot","HCal_cellHot",0,0,1) ;
                                RooRealVar* e4 = new RooRealVar("e"+Nidep,"e"+Nidep,1,0,3) ;
                                RooRealVar* e1r = new RooRealVar("e"+Nidep+"r","e"+Nidep+"r",10,0,10) ;
                                RooRealVar* e1s = new RooRealVar("e"+Nidep+"s","e"+Nidep+"s",10,0,10) ;
                                RooRealVar* e12r = new RooRealVar("e12r","e12r",10,0,1000) ;
                                RooRealVar* e23r = new RooRealVar("e23r","e23r",10,0,1000) ;
                                RooRealVar* ecal5x5 = new RooRealVar("ecal5x5","ecal5x5",10,0,50000) ;

                                //RooRealVar* e2r = new RooRealVar("e2r","e2r",10,0,10) ;
                                //RooRealVar* e3r = new RooRealVar("e3r","e3r",10,0,10) ;
                                //RooRealVar* e4r = new RooRealVar("e4r","e4r",10,0,10) ;
                                //RooRealVar* e5r = new RooRealVar("e5r","e5r",10,0,10) ;
                                //RooRealVar* e6r = new RooRealVar("e6r","e6r",10,0,10) ;

                                RooRealVar* mean = new RooRealVar("mean","mean of gaussian",0) ;
                                RooRealVar* sigma = new RooRealVar("sigma","width of gaussian",0.1,0.001,2) ;
                                RooAbsPdf* sig1 = new RooGaussian("sig1","Signal",*e4,*mean,*sigma) ;  
                                //landau
                                RooRealVar* ml = new RooRealVar("ml","mean landau",0.5,0.1,2) ;
                                RooRealVar* sl = new RooRealVar("sl","sigma landau",0.15, 0.01,2) ;
                                RooAbsPdf* landau = new RooLandau("lx","lx",*e4,*ml,*sl) ; 

                                RooRealVar* a0 = new RooRealVar("a0","a0",-3,-100,0.) ;
                                RooAbsPdf* bkg = new RooExponential("bkg","Background",*e4,*a0) ;

                                RooAbsPdf* sig = new RooFFTConvPdf("sig","landau (X) gauss signal",*e4,*landau,*sig1) ;
                                RooRealVar* bkgfrac = new RooRealVar("bkgfrac","fraction of background",0.1,0.0,0.2) ;
                                RooAbsPdf* model = new RooAddPdf("model","g1+g2+a",RooArgList(*bkg,*sig),*bkgfrac) ;
                                RooRealVar* evWeight = new RooRealVar("weight","weight",1,-10,10) ;

                                RooArgSet obsAndWeight;
                                obsAndWeight.add(*e4);
                                obsAndWeight.add(*ecal5x5);
                                /*
                                   obsAndWeight.add(*e3r);
                                   obsAndWeight.add(*e4r);
                                   obsAndWeight.add(*e5r);
                                   obsAndWeight.add(*e6r);
                                   */
                                //obsAndWeight.add(*ecal);
                                //obsAndWeight.add(*pt);
                                //obsAndWeight.add(*iso);
                                //obsAndWeight.add(*HCal_cellHot);
                                obsAndWeight.add(*HCal_ieta);
                                obsAndWeight.add(*Trkmatch);
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

                                pos_mean = ml->getVal();
                                pos_errhigh = ml->getErrorHi();
                                pos_errlow = -ml->getErrorLo();


                                cout << "num=" << num << "\n" <<endl;
                                cout << "ieta=" << ieta << "\n" <<endl;
                                cout << "ecal5x5_bin=" << ecal5x5_bin << "\n" <<endl;
                                cout << "idepth=" << idepth << "\n" <<endl;
                                cout << "pos_mean = " << pos_mean << "\n" <<endl;
                                cout << "pos_errhigh = " << pos_errhigh << "\n" <<endl;
                                cout << "pos_errlow = " << pos_errlow << "\n" <<endl;
                                outtree->Fill();

                                TFile *tout = new TFile( path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iecal5x5_bin_"+Necal5x5_bin+".root", "RECREATE" );
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
                                tbins.addUniform(30,0,Emax) ;
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
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iecal5x5_bin_"+Necal5x5_bin+"_cut10MeV.png");


                                num++;
                        }//end of loop over d
                }//end of loop over iecal5x5_bin
        }//end of loop over k
        fclose (sFile);
        TFile *rtFile = new TFile ( rtfilename, "RECREATE");
        cout <<"create root"<<endl;
        outtree->Write();
        rtFile->Close(); 
}
