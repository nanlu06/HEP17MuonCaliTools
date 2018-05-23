#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"
#include "CommonFunc.h"
#include "CMSLUMI.h"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./sig_only_fit_data signalFile outputPath outputName ieta iphi depth \n" << std::endl;

        TString signalfile=argv[1];
        TString path=argv[2];
        TString outputName=argv[3];
        TString rtfilename = path + outputName;

        TString Nieta=argv[4];
        TString Niphi=argv[5];
        TString Nvtx=argv[6];
      
        CommonFunc::setTDRStyle();
        int W = 800;
        int H = 600;
        int H_ref = 600;
        int W_ref = 800;
        float T = 0.08*H_ref;
        float B = 0.12*H_ref;
        float L = 0.12*W_ref;
        float R = 0.04*W_ref;
 
        cout <<path<<endl; 
        system("mkdir -vp "+path);

        TFile sigFile(signalfile);
        TTree* sigTree = (TTree*)sigFile.Get("tree");

        TTree *outtree = new TTree("outtree", "Info");
        cout <<"create tree"<<endl;

        unsigned int num=0;
        int ieta = Nieta.Atoi();
        int iphi = 0;
        if(!(Niphi.Contains("all"))) iphi = Niphi.Atoi();
        int vtxbin = Nvtx.Atoi();
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

                cout <<"ieta="<<ieta<<endl;

                        if(ieta==16) {deplow=4;dephigh=4;}
                        if(ieta==17) {deplow=2;dephigh=3;}
                        if(ieta==18) {deplow=1;dephigh=5;}
                        if(ieta>=19 && ieta<=25 ) {deplow=1;dephigh=6;}
                        if(ieta==26) {deplow=1;dephigh=7;}

                        for(int d=deplow;d<=dephigh;d++){
                                idepth = d;
                                cout <<"idepth="<<d<<endl;
                                TString nvtxcut = Form("&& nvtx_good == %d",vtxbin);

                                TString Nidep;
                                Nidep.Form("%d",d);

                                FILE * pFile;
                                pFile = fopen (path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+Nvtx+".txt","w");
                                fprintf (pFile, "ieta = %d, idep = %d , nvtx = %d \n", ieta, iphi,vtxbin);
                                cout <<"ieta, idepth: "<<Nieta<<" "<<Nidep<<endl;

                                TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0.0 && pt> 25.0  && Trkmatch && tight1 && ISOR04 <0.15 && HCal_ieta=="+Nieta+nvtxcut + " && HCal_iphi=="+Niphi);
                                if(Niphi.Contains("all")) cuttree = "e"+Nidep+" < 10.0 && e"+Nidep+" > 0.0 && pt> 25.0  && Trkmatch && tight1 && ISOR04 <0.15 && HCal_ieta=="+Nieta+nvtxcut;

                                //TString cuttree("e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 && pt> 25.0  && Trkmatch && tight1 && ISOR04 <0.15 && HCal_ieta=="+Nieta+nvtxcut + " && HCal_iphi=="+Niphi);
                                //if(Niphi.Contains("all")) cuttree = "e"+Nidep+" < 10.0 && e"+Nidep+" > 0.00001 && pt> 25.0  && Trkmatch && tight1 && ISOR04 <0.15 && HCal_ieta=="+Nieta+nvtxcut;
                                fprintf (pFile, "cut: %s \n",cuttree.Data());
                                cout <<cuttree<<endl;

                                // Declare observable x
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
                                //RooRealVar* e1r = new RooRealVar("e"+Nidep+"r","e"+Nidep+"r",10,0,10) ;
                                //RooRealVar* e1s = new RooRealVar("e"+Nidep+"s","e"+Nidep+"s",10,0,10) ;
                                //RooRealVar* e12r = new RooRealVar("e12r","e12r",10,0,1000) ;
                                //RooRealVar* e23r = new RooRealVar("e23r","e23r",10,0,1000) ;
                                //RooRealVar* ecal = new RooRealVar("ecal5x5","ecal5x5",10,0,50000) ;

                                //RooRealVar* e2r = new RooRealVar("e2r","e2r",10,0,10) ;
                                //RooRealVar* e3r = new RooRealVar("e3r","e3r",10,0,10) ;
                                //RooRealVar* e4r = new RooRealVar("e4r","e4r",10,0,10) ;
                                //RooRealVar* e5r = new RooRealVar("e5r","e5r",10,0,10) ;
                                //RooRealVar* e6r = new RooRealVar("e6r","e6r",10,0,10) ;

                                RooRealVar* mean = new RooRealVar("mean","mean of gaussian",0) ;
                                RooRealVar* sigma = new RooRealVar("Gaussian standard deviation","width of gaussian",0.1,0.001,2) ;
                                RooAbsPdf* sig1 = new RooGaussian("sig1","Signal",*e4,*mean,*sigma) ;  
                                //landau
                                RooRealVar* ml = new RooRealVar("Landau location paramter","mean landau",0.5,0.1,2) ;
                                RooRealVar* sl = new RooRealVar("Landau scale parameter","sigma landau",0.15, 0.01,2) ;
                                RooAbsPdf* landau = new RooLandau("lx","lx",*e4,*ml,*sl) ; 

                                //RooRealVar* a0 = new RooRealVar("a0","a0",-3,-100,0.) ;
                                //RooAbsPdf* bkg = new RooExponential("bkg","Background",*e4,*a0) ;

                                RooAbsPdf* sig = new RooFFTConvPdf("sig","landau (X) gauss signal",*e4,*landau,*sig1) ;
                                //RooRealVar* bkgfrac = new RooRealVar("bkgfrac","fraction of background",0.1,0.0,0.2) ;
                                //RooAbsPdf* model = new RooAddPdf("model","g1+g2+a",RooArgList(*bkg,*sig),*bkgfrac) ;
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
                                obsAndWeight.add(*iso);
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
                                if(pos_errlow==0) pos_errlow = pos_errhigh;
                                if(pos_errhigh==0) pos_errhigh = pos_errlow;
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

                                TFile *tout = new TFile( path+"result_depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nvtx+".root", "RECREATE" );
                                tout->cd();
                                RooFitResult *result = minim.save("fitResult","Fit Results");
                                result->Write();

                                //fprintf (pFile," Landau location parameter: %.4e + %.4e - %.4e \n",ml->getVal(), ml->getErrorHi(), ml->getErrorLo());
                                //fprintf (pFile," Landau scale parameter: %.4e + %.4e - %.4e \n",sl->getVal(), sl->getErrorHi(), sl->getErrorLo());
                                //fprintf (pFile," Gaussian sigma: %.4e + %.4e - %.4e \n \n",sigma->getVal(), sigma->getErrorHi(), sigma->getErrorLo());
                                //fprintf (sFile,"ene.push_back(%.4e); ene.push_back( %.4e); ene.push_back(%.4e); \n", ml->getVal(), ml->getErrorHi(), -ml->getErrorLo());
                                fclose (pFile);
                                
                                int Emax = 2.0;
                                RooBinning tbins(0,Emax);
                                tbins.addUniform(40,0,Emax) ;
                                RooPlot* dtframe = e4->frame(Range(0,Emax,kTRUE),Title("energy in ieta "+ Nieta + " iphi " + Niphi + " idepth "+Nidep));
                                data->plotOn(dtframe,Binning(tbins));
                                sig->plotOn(dtframe);
                                //model->plotOn(dtframe, Components(*bkg), LineStyle(kDashed));
                                //model->plotOn(dtframe, Components(*sig), LineColor(kRed));
                                //landau->plotOn(dtframe, LineColor(kRed));
                                sig->paramOn(dtframe,Layout(0.43, 0.93, 0.88), Format("NEU",AutoPrecision(0))) ;
                                data->statOn(dtframe,Layout(0.43,0.93,0.7), Format("NEU",AutoPrecision(0))) ;
                                dtframe->getAttText("sig_paramBox")->SetTextColor(kBlack);
                                dtframe->getAttFill("sig_paramBox")->SetFillStyle(0);
                                //dtframe->getAttText("sig_paramBox")->SetLineWidth(0);
                                dtframe->getAttText("sig_paramBox")->SetTextSize(0.035);
                                TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
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
                                //dtframe->SetXTitle("Reconstructed energy / pathlength [GeV/mm]");
                                dtframe->SetYTitle("Events");
                                dtframe->Draw();
                                CommonFunc::AddCMS(c1);
                                c1->Update();
                                c1->RedrawAxis();
                                c1->GetFrame()->Draw();
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nvtx+".png");
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nvtx+".pdf");
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nvtx+".eps");
                                c1->SaveAs(path+"depth_"+Nidep+"_ieta_"+Nieta+"_iphi_"+Niphi+"_"+Nvtx+".C");

                                num++;
                        }//end of loop over d (depth)
                //}//end of loop over ivtx
        //}//end of loop over k (ieta)
        TFile *rtFile = new TFile ( rtfilename, "RECREATE");
        cout <<"create root"<<endl;
        outtree->Write();
        rtFile->Close(); 
}
