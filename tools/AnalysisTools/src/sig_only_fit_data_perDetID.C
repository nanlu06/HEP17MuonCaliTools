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

        TString Nieta=argv[4];
        TString Niphi=argv[5];
       
        cout <<path<<endl; 
        system("mkdir -vp "+path);
        FILE * sFile;
        sFile = fopen (path+"summary_cut10MeV.txt","w");

        TFile sigFile(signalfile);
        TTree* sigTree = (TTree*)sigFile.Get("tree");

        TTree *outtree = new TTree("outtree", "Info");
        cout <<"create tree"<<endl;

        unsigned int num=0;
        int ieta = Nieta.Atoi();
        int iphi = 0;
        if(!(Niphi.Contains("all"))) iphi = Niphi.Atoi();
        int vtxbin;
        int idepth = 0;
        float pos_mean;
        float pos_errhigh;
        float pos_errlow;
        float nvtx_mean;
        float nvtx_errhigh;
        float nvtx_errlow;
        outtree->Branch("num", &num, "num/I");
        outtree->Branch("ieta", &ieta, "ieta/I");
        outtree->Branch("iphi", &iphi, "iphi/I");
        outtree->Branch("vtxbin", &vtxbin, "vtxbin/I");
        outtree->Branch("idepth", &idepth, "idepth/I");
        outtree->Branch("pos_mean", &pos_mean, "pos_mean/F");
        outtree->Branch("pos_errhigh", &pos_errhigh, "pos_errhigh/F");
        outtree->Branch("pos_errlow", &pos_errlow, "pos_errlow/F");
        outtree->Branch("nvtx_mean", &nvtx_mean, "nvtx_mean/F");
        outtree->Branch("nvtx_errhigh", &nvtx_errhigh, "nvtx_errhigh/F");
        outtree->Branch("nvtx_errlow", &nvtx_errlow, "nvtx_errlow/F");
        int dephigh = 0;
        int deplow = 0;

        //for(int k=21; k<24; k++){ //loop over ieta 
                cout <<"ieta="<<ieta<<endl;
                fprintf(sFile,"//ieta %d \n",ieta);

                //ieta = k;
                //TString Nieta;
                //Nieta.Form("%d",ieta);

                for(int ivtx=0; ivtx<5; ivtx++){  
                        fprintf(sFile,"//ivertex %d \n",ivtx);

                        vtxbin = ivtx;
                        TString Nnvtx;
                        Nnvtx.Form("%d",ivtx);

                        if(ieta==16) {deplow=4;dephigh=4;}
                        if(ieta==17) {deplow=2;dephigh=3;}
                        if(ieta==18) {deplow=1;dephigh=5;}
                        if(ieta>=19 && ieta<=25 ) {deplow=1;dephigh=6;}
                        if(ieta==26) {deplow=1;dephigh=7;}

                        for(int d=deplow;d<=dephigh;d++){
                                idepth = d;
                                cout <<"idepth="<<d<<endl;
                                fprintf(sFile,"//depth %d \n",d);
                                TString nvtxcut = "";
                                /*
                                //period E:
                                if(ivtx==1) nvtxcut = "&& nvtx<20";
                                else if(ivtx==2) nvtxcut = "&& nvtx>=20 && nvtx<26";
                                else if(ivtx==3) nvtxcut = "&& nvtx>=26 && nvtx<33";
                                else if(ivtx==4) nvtxcut = "&& nvtx>=33";
                                
                                //period F:
                                if(ivtx==1) nvtxcut = "&& nvtx_good<20";
                                else if(ivtx==2) nvtxcut = "&& nvtx_good>=20 && nvtx_good<28";
                                else if(ivtx==3) nvtxcut = "&& nvtx_good>=28 && nvtx_good<35";
                                else if(ivtx==4) nvtxcut = "&& nvtx_good>=35";
                                */
                                //Over all
                                if(ivtx==1) nvtxcut = "&& nvtx_good<18";
                                else if(ivtx==2) nvtxcut = "&& nvtx_good>=18 && nvtx_good<24";
                                else if(ivtx==3) nvtxcut = "&& nvtx_good>=24 && nvtx_good<31";
                                else if(ivtx==4) nvtxcut = "&& nvtx_good>=31";

                                TString Nidep;
                                Nidep.Form("%d",d);

                                FILE * pFile;
                                pFile = fopen (path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+Nnvtx+".txt","w");
                                fprintf (pFile, "ieta = %d, idep = %d \n", ieta, iphi);
                                cout <<"ieta, idepth: "<<Nieta<<" "<<Nidep<<endl;

                                TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 && pt> 25.0  && Trkmatch && tight1 && HCal_ieta=="+Nieta+nvtxcut + " && HCal_iphi=="+Niphi);
                                if(Niphi.Contains("all")) cuttree = "e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 && pt> 25.0  && Trkmatch && tight1 && HCal_ieta=="+Nieta+nvtxcut;
                                fprintf (pFile, "cut: %s \n",cuttree.Data());
                                cout <<cuttree<<endl;

                                // Declare observable x
                                //RooRealVar* nvtx = new RooRealVar("nvtx","nvtx",10,0,1000) ;
                                RooRealVar* nvtx = new RooRealVar("nvtx_good","nvtx_good",10,0,1000) ;
                                RooRealVar* iso = new RooRealVar("ISOR04","ISOR04",0,-1000,1000) ;
                                RooRealVar* Trkiso = new RooRealVar("TrkISOR03","TrkISOR03",0,-100,100) ;
                                RooRealVar* pt = new RooRealVar("pt","pt",1,0,500000) ;
                                RooRealVar* tight = new RooRealVar("tight1", "tight1", 1, 0, 2);
                                RooRealVar* Trkmatch = new RooRealVar("Trkmatch","Trkmatch",1,0,1);
                                RooRealVar* HCal_ieta = new RooRealVar("HCal_ieta","HCal_ieta",10,0,40) ;
                                RooRealVar* HCal_iphi = new RooRealVar("HCal_iphi","HCal_iphi",10,0,100) ;
                                RooRealVar* HCal_cellHot = new RooRealVar("HCal_cellHot","HCal_cellHot",0,0,1) ;
                                RooRealVar* e4 = new RooRealVar("e"+Nidep,"e"+Nidep,1,0,4) ;
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
                                obsAndWeight.add(*nvtx);
                                /*
                                   obsAndWeight.add(*e3r);
                                   obsAndWeight.add(*e4r);
                                   obsAndWeight.add(*e5r);
                                   obsAndWeight.add(*e6r);
                                   */
                                //obsAndWeight.add(*ecal);
                                obsAndWeight.add(*tight);
                                obsAndWeight.add(*pt);
                                //obsAndWeight.add(*iso);
                                obsAndWeight.add(*HCal_iphi);
                                obsAndWeight.add(*HCal_ieta);
                                obsAndWeight.add(*Trkmatch);
                                obsAndWeight.add(*evWeight);

                                RooDataSet* data = new RooDataSet("ggfmc","ggfmc",RooArgSet(obsAndWeight),RooFit::WeightVar(*evWeight),Import(*sigTree),Cut(cuttree)) ;
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
                                nvtx_mean = data->mean(*nvtx);
                                nvtx_errhigh = data->sigma(*nvtx);
                                nvtx_errlow = data->sigma(*nvtx);

                                cout << "num=" << num << "\n" <<endl;
                                cout << "ieta=" << ieta << "\n" <<endl;
                                cout << "iphi=" << iphi << "\n" <<endl;
                                cout << "vtxbin=" << vtxbin << "\n" <<endl;
                                cout << "idepth=" << idepth << "\n" <<endl;
                                cout << "pos_mean = " << pos_mean << "\n" <<endl;
                                cout << "pos_errhigh = " << pos_errhigh << "\n" <<endl;
                                cout << "pos_errlow = " << pos_errlow << "\n" <<endl;
                                cout << "nvtx = " << nvtx_mean << " "<<nvtx_errhigh<<"\n" <<endl;
                                outtree->Fill();

                                TFile *tout = new TFile( path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nnvtx+".root", "RECREATE" );
                                tout->cd();
                                RooFitResult *result = minim.save("fitResult","Fit Results");
                                result->Write();

                                //fprintf (pFile," Landau location parameter: %.4e + %.4e - %.4e \n",ml->getVal(), ml->getErrorHi(), ml->getErrorLo());
                                //fprintf (pFile," Landau scale parameter: %.4e + %.4e - %.4e \n",sl->getVal(), sl->getErrorHi(), sl->getErrorLo());
                                //fprintf (pFile," Gaussian sigma: %.4e + %.4e - %.4e \n \n",sigma->getVal(), sigma->getErrorHi(), sigma->getErrorLo());
                                //fprintf (sFile,"ene.push_back(%.4e); ene.push_back( %.4e); ene.push_back(%.4e); \n", ml->getVal(), ml->getErrorHi(), -ml->getErrorLo());
                                fclose (pFile);
                                
                                int Emax = 4.0;
                                RooBinning tbins(0,Emax);
                                tbins.addUniform(40,0,Emax) ;
                                RooPlot* dtframe = e4->frame(Range(0,Emax,kTRUE),Title("energy in ieta "+ Nieta + " iphi " + Niphi + " idepth "+Nidep));
                                data->plotOn(dtframe,Binning(tbins));
                                sig->plotOn(dtframe);
                                //model->plotOn(dtframe, Components(*bkg), LineStyle(kDashed));
                                //model->plotOn(dtframe, Components(*sig), LineColor(kRed));
                                //landau->plotOn(dtframe, LineColor(kRed));
                                sig->paramOn(dtframe,Layout(0.55)) ;
                                data->statOn(dtframe,Layout(0.55,0.99,0.75)) ;
                                TCanvas* c1 = new TCanvas();
                                dtframe->Draw();
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nnvtx+"_cut10keV.png");


                                num++;
                        }//end of loop over d (depth)
                }//end of loop over ivtx
        //}//end of loop over k (ieta)
        fclose (sFile);
        TFile *rtFile = new TFile ( rtfilename, "RECREATE");
        cout <<"create root"<<endl;
        outtree->Write();
        rtFile->Close(); 
}
