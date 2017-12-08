#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./graph_pileupCorr-test outputPath outputName\n" << std::endl;
        TString path=argv[1];
        TString outputName=argv[2];
        TString rtfilename = path + outputName;

        TFile rtFile(rtfilename);
        TTree* outtree = (TTree*)rtFile.Get("outtree");

        long nentries = outtree->GetEntries();
        
        int ieta, vtxbin, idepth;
        float pos_mean, pos_errhigh, pos_errlow;
  
        outtree->SetBranchAddress("ieta", &ieta);
        outtree->SetBranchAddress("vtxbin", &vtxbin);
        outtree->SetBranchAddress("idepth", &idepth);
        outtree->SetBranchAddress("pos_mean", &pos_mean);
        outtree->SetBranchAddress("pos_errhigh", &pos_errhigh);
        outtree->SetBranchAddress("pos_errlow", &pos_errlow);

        TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

        const Int_t n = 4;
        float xn[n]={0,0,0,0}, xp[n]={0,0,0,0};

        //choose the idepth you wanna plot
        int d =3; //idepth
        //choose the idepth you wanna start with, if it's 21, you will plot ieta= [21,24]
        int k = 21;


        //dep1
        //float x1[n]={};
        //float x2[n]={};
        //float x3[n]={};
        //float x4[n]={};

        //dep2
        float x1[n]={13.387,20.683,27.647,36.13};
        float x2[n]={13.553,20.671,27.716,35.97};
        float x3[n]={13.583,20.742,27.689,35.92};
        float x4[n]={13.480,20.657,27.634,35.99};

/*
        //dep3
        float x1[n]={13.564,20.689,27.659,36.13};
        float x2[n]={13.541,20.697,27.733,35.94};
        float x3[n]={13.593,20.736,27.675,35.94};
        float x4[n]={13.516,20.649,27.617,35.96};

        //dep4
        float x1[n]={13.553,20.686,27.667,36.2};
        float x2[n]={13.536,20.698,27.729,35.96};
        float x3[n]={13.584,20.754,27.677,35.94};
        float x4[n]={13.503,20.675,27.626,36.00};

        //dep5
        float x1[n]={13.525,20.69,27.66,36.14};
        float x2[n]={13.548,20.704,27.738,35.93};
        float x3[n]={13.624,20.729,27.685,35.94};
        float x4[n]={13.485,20.664,27.628,35.95};
        */

        int ivtx=0;

        float y1[n], y1p[n], y1n[n];
        float y2[n], y2p[n], y2n[n];
        float y3[n], y3p[n], y3n[n];
        float y4[n], y4p[n], y4n[n];
        
           memset(y1,0.,sizeof(y1));
           memset(y1p,0.,sizeof(y1p));
           memset(y1n,0.,sizeof(y1n));

           memset(y2,0.,sizeof(y2));
           memset(y2p,0.,sizeof(y2p));
           memset(y2n,0.,sizeof(y2n));

           memset(y3,0.,sizeof(y3));
           memset(y3p,0.,sizeof(y3p));
           memset(y3n,0.,sizeof(y3n));

           memset(y4,0.,sizeof(y4));
           memset(y4p,0.,sizeof(y4p));
           memset(y4n,0.,sizeof(y4n));
           
        for(int iEntry=0;iEntry<nentries;iEntry++){

                outtree->GetEntry(iEntry);
                
                if(idepth!=d) continue;
                if(ieta<k || ieta>k+3) continue;

                //ieta==21;
                if(ieta==k && idepth==d){
                        for(ivtx=1;ivtx<5;ivtx++){
                                if(vtxbin==ivtx){
                                        y1[ivtx-1] = pos_mean;
                                        y1p[ivtx-1] = pos_errhigh;
                                        y1n[ivtx-1] = pos_errlow;
                                }
                        }
                }

                //ieta==22;
                if(ieta==k+1 && idepth==d){
                        for(ivtx=1;ivtx<5;ivtx++){
                                if(vtxbin==ivtx){
                                        y2[ivtx-1] = pos_mean;
                                        y2p[ivtx-1] = pos_errhigh;
                                        y2n[ivtx-1] = pos_errlow;
                                }
                        }
                } 

                //ieta==23;
                if(ieta==k+2 && idepth==d){
                        for(ivtx=1;ivtx<5;ivtx++){
                                if(vtxbin==ivtx){
                                        y3[ivtx-1] = pos_mean;
                                        y3p[ivtx-1] = pos_errhigh;
                                        y3n[ivtx-1] = pos_errlow;
                                }
                        }
                } 

                //ieta==24;
                if(ieta==k+3 && idepth==d){
                        for(ivtx=1;ivtx<5;ivtx++){
                                if(vtxbin==ivtx){
                                        y4[ivtx-1] = pos_mean;
                                        y4p[ivtx-1] = pos_errhigh;
                                        y4n[ivtx-1] = pos_errlow;
                                }
                        }
                } 

        }
        cout<< "y1 = " << y1[0] << ", " << y1[1] << ", " << y1[2] << ", " << y1[3] << endl;
        cout<< "y1p = " << y1p[0] << ", " << y1p[1] << ", " << y1p[2] << ", " << y1p[3] << endl;
        cout<< "y1n = " << y1n[0] << ", " << y1n[1] << ", " << y1n[2] << ", " << y1n[3] << endl;
        cout<< "y2 = " << y2[0] << ", " << y2[1] << ", " << y2[2] << ", " << y2[3] << endl;
        cout<< "y2p = " << y2p[0] << ", " << y2p[1] << ", " << y2p[2] << ", " << y2p[3] << endl;
        cout<< "y2n = " << y2n[0] << ", " << y2n[1] << ", " << y2n[2] << ", " << y2n[3] << endl;
        cout<< "y3 = " << y3[0] << ", " << y3[1] << ", " << y3[2] << ", " << y3[3] << endl;
        cout<< "y3p = " << y3p[0] << ", " << y3p[1] << ", " << y3p[2] << ", " << y3p[3] << endl;
        cout<< "y3n = " << y3n[0] << ", " << y3n[1] << ", " << y3n[2] << ", " << y3n[3] << endl;
        cout<< "y4 = " << y4[0] << ", " << y4[1] << ", " << y4[2] << ", " << y4[3] << endl;
        cout<< "y4p = " << y4p[0] << ", " << y4p[1] << ", " << y4p[2] << ", " << y4p[3] << endl;
        cout<< "y4n = " << y4n[0] << ", " << y4n[1] << ", " << y4n[2] << ", " << y4n[3] << endl;

        
           TF1 *f1 = new TF1("f1","pol1",0,40);

           TGraph *gr4 = new TGraphAsymmErrors(n,x4,y4,xn,xp,y4n,y4p);
           gr4->Fit("f1","R");
           gr4->GetFunction("f1")->SetLineColor(2);
           gr4->SetLineColor(2);
           gr4->SetLineWidth(4);
           gr4->SetMarkerColor(2);
           gr4->SetMarkerStyle(21);
        //gr->GetXaxis()->SetTitle("depth");
        //gr->GetYaxis()->SetTitle("energy [GeV]");
        //gr->Draw("P");


        TGraph *gr1 = new TGraphAsymmErrors(n,x1,y1,xn,xp,y1n,y1p);
        gr1->Fit("f1","R");
        gr1->GetFunction("f1")->SetLineColor(4);
        gr1->SetLineColor(4);
        gr1->SetLineWidth(4);
        gr1->SetMarkerColor(4);
        gr1->SetMarkerStyle(21);

        TGraph *gr2 = new TGraphAsymmErrors(n,x2,y2,xn,xp,y2n,y2p);
        gr2->Fit("f1","R");
        gr2->GetFunction("f1")->SetLineColor(3);
        gr2->SetLineColor(3);
        gr2->SetLineWidth(4);
        gr2->SetMarkerColor(3);
        gr2->SetMarkerStyle(21);

        TGraph *gr3 = new TGraphAsymmErrors(n,x3,y3,xn,xp,y3n,y3p);
        gr3->Fit("f1","R");
        gr3->GetFunction("f1")->SetLineColor(1);
        gr3->SetLineColor(1);
        gr3->SetLineWidth(4);
        gr3->SetMarkerColor(1);
        gr3->SetMarkerStyle(21);


        TMultiGraph *mg = new TMultiGraph();
        mg->Add(gr1);
        mg->Add(gr2);
        mg->Add(gr3);
        mg->Add(gr4);
        mg->Draw("AP");
  
        mg->GetXaxis()->SetTitle("Average Nvertex");
        mg->GetYaxis()->SetTitle("Energy [GeV]");
        mg->GetXaxis()->SetLimits(0.,40.);
        if(d==1) mg->GetYaxis()->SetRangeUser(0.0,0.5);
        else if(d==2) mg->GetYaxis()->SetRangeUser(0.3,1.);
        else if(d==3 || d==4) mg->GetYaxis()->SetRangeUser(0.2,0.8);
        else mg->GetYaxis()->SetRangeUser(0.5,1.0);
        //depth2
        //mg->GetYaxis()->SetRangeUser(0.4,1.2);
        //depth1
        //mg->GetYaxis()->SetRangeUser(0.,0.8);

        TLegend *legend = new TLegend(0.15,0.65,0.55,0.90);
        legend->SetBorderSize(0);
        legend->SetTextFont(42);
        legend->SetTextSize(0.04);
        legend->SetFillStyle(0);
        legend->SetFillColor(0);
        legend->SetLineColor(0);
        legend->AddEntry(gr1, "ieta = 21", "L");
        legend->AddEntry(gr2, "ieta = 22", "L");
        legend->AddEntry(gr3, "ieta = 23", "L");
        legend->AddEntry(gr4, "ieta = 24", "L");
        legend->Draw("same");

        system("mkdir -vp "+path);
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.png", path.Data(), d));
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.pdf", path.Data(), d));
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.eps", path.Data(), d));

        // TCanvas::Update() draws the frame, after which one can change it
        c1->Update();
        c1->Modified();
         
}
