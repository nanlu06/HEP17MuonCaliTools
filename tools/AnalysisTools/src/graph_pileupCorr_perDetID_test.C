#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"
#include "CommonFunc.h"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

        std::cout << "[Usage]: ./graph_pileupCorr-test outputPath outputName\n" << std::endl;
        TString path=argv[1];
        TString outputName=argv[2];
        TString rtfilename = path + outputName;
        TString depths=argv[3];
        TString phis=argv[4];
        TString etas=argv[5];
        int depth = depths.Atoi();
        int phi = phis.Atoi(); 
        int eta = etas.Atoi();
        cout <<" "<<path<< " "<<outputName<<" "<<rtfilename<<" depth: "<<depth<<" phi: "<<phis<<" eta: "<<eta<<endl;

        TFile rtFile(rtfilename);
        TTree* intree = (TTree*)rtFile.Get("outtree");

        long nentries = intree->GetEntries();
        
        int ieta, vtxbin, idepth, iphi;
        float pos_mean, pos_errhigh, pos_errlow, nvtx_mean, nvtx_errhigh, nvtx_errlow;
  
        intree->SetBranchAddress("ieta", &ieta);
        intree->SetBranchAddress("vtxbin", &vtxbin);
        intree->SetBranchAddress("idepth", &idepth);
        intree->SetBranchAddress("iphi", &iphi);
        intree->SetBranchAddress("pos_mean", &pos_mean);
        intree->SetBranchAddress("pos_errhigh", &pos_errhigh);
        intree->SetBranchAddress("pos_errlow", &pos_errlow);
        intree->SetBranchAddress("nvtx_mean", &nvtx_mean);
        intree->SetBranchAddress("nvtx_errhigh", &nvtx_errhigh);
        intree->SetBranchAddress("nvtx_errlow", &nvtx_errlow);

        const Int_t n = 4;
        float xn[n]={0,0,0,0}, xp[n]={0,0,0,0};

/*
//dep1
float x1[n]={ 1.176e+01,1.816e+01,2.467e+01,3.250e+01 };
float x2[n]={ 1.170e+01,1.815e+01,2.464e+01,3.243e+01 };
float x3[n]={ 1.168e+01,1.812e+01,2.464e+01,3.261e+01 };
float x4[n]={ 1.166e+01,1.813e+01,2.463e+01,3.261e+01 };
*/

        int ivtx=0;

        float y1[n], y1p[n], y1n[n];

        float x1[n], x1p[n], x1n[n];

        for(int iEntry=0;iEntry<nentries;iEntry++){
                intree->GetEntry(iEntry);
                if(ieta==eta && iphi==phi && idepth==depth){
                        for(ivtx=1;ivtx<5;ivtx++){
                                if(vtxbin==ivtx){
                                        y1[ivtx-1] = pos_mean;
                                        y1p[ivtx-1] = pos_errhigh;
                                        y1n[ivtx-1] = pos_errlow;
                                        x1[ivtx-1] = nvtx_mean;
                                        x1p[ivtx-1] = nvtx_errhigh;
                                        x1n[ivtx-1] = nvtx_errlow;
                                }
                        }
                }
        }

        cout<< "y1 = " << y1[0] << ", " << y1[1] << ", " << y1[2] << ", " << y1[3] << endl;
        cout<< "y1p = " << y1p[0] << ", " << y1p[1] << ", " << y1p[2] << ", " << y1p[3] << endl;
        cout<< "y1n = " << y1n[0] << ", " << y1n[1] << ", " << y1n[2] << ", " << y1n[3] << endl;
        
        cout <<"ieta=="<<eta<<endl;

        TGraph *gr1 = new TGraphAsymmErrors(n,x1,y1,xn,xp,y1n,y1p);
        gr1->Fit("pol1");
        gr1->GetFunction("pol1")->SetLineColor(4);
        gr1->SetLineColor(4);
        gr1->SetLineWidth(4);
        gr1->SetMarkerColor(4);
        gr1->SetMarkerStyle(21);

        TF1 *myfunc1 = gr1->GetFunction("pol1");
        std::pair<float,float> prod =  CommonFunc::LinearCal(myfunc1);

        TTree *outtree = new TTree("outtree_pileup_corr", "Info");
        cout <<"create tree"<<endl;

        float energy, energy_errhigh, energy_errlow, energy_per_layer, energy_per_layer_errhigh, energy_per_layer_errlow, energy_corr, energy_corr_errhigh, energy_corr_errlow;
        energy = -999, energy_errhigh = 999, energy_errlow = 999, energy_per_layer = -999, energy_per_layer_errlow = 999, energy_per_layer_errhigh = 999, energy_corr = -999, energy_corr_errhigh = 999, energy_corr_errlow = 999;
 
        outtree->Branch("eta", &eta, "eta/I");
        outtree->Branch("phi", &phi, "phi/I");
        outtree->Branch("depth", &depth, "depth/I");
        outtree->Branch("energy", &energy, "energy/F");
        outtree->Branch("energy_errhigh", &energy_errhigh, "energy_errhigh/F");
        outtree->Branch("energy_errlow", &energy_errlow, "energy_errlow/F");
        outtree->Branch("energy_per_layer", &energy_per_layer, "energy_per_layer/F");
        outtree->Branch("energy_per_layer_errhigh", &energy_per_layer_errhigh, "energy_per_layer_errhigh/F");
        outtree->Branch("energy_per_layer_errlow", &energy_per_layer_errlow, "energy_per_layer_errlow/F");
        outtree->Branch("energy_corr", &energy_corr, "energy_corr/F"); 
        outtree->Branch("energy_corr_errhigh", &energy_corr_errhigh, "energy_corr_errhigh/F");
        outtree->Branch("energy_corr_errlow", &energy_corr_errlow, "energy_corr_errlow/F");
        energy = prod.first;
        energy_errhigh = prod.second;
        energy_errlow = prod.second;

        if(eta==16) energy_per_layer = prod.first/3.;
        else if(eta==17) energy_per_layer = prod.first/5.;
        if(eta>17){
           if(depth==2 || depth==4){
              if(eta==26) energy_per_layer = prod.first/2.;
              else energy_per_layer = prod.first/3.;
           }
           else if(depth==3){
              if(eta==26) energy_per_layer = prod.first/2.;
              else if(eta==18) energy_per_layer = prod.first/4.;
              else energy_per_layer = prod.first/3.;
           }
           else if(depth>4){
              energy_per_layer = prod.first/4.;
           }
        }
        
        energy_per_layer_errhigh = energy_per_layer*energy_errhigh/energy;
        energy_per_layer_errlow = energy_per_layer*energy_errlow/energy;

        if(eta==16 && depth==4) energy_corr = prod.first/2.5409214;
        else if(eta==17){
             if(depth==2) energy_corr = prod.first/2.9010239;
             else if(depth==3)  energy_corr = prod.first/2.9010239;
        }  
        else if(eta==18){
             if(depth==2) energy_corr = prod.first/1.2209443;
             else if(depth==3)  energy_corr = prod.first/1.6279258;
             else if(depth==4)  energy_corr = prod.first/1.2209443;
             else if(depth==5)  energy_corr = prod.first/2.4418887;
        }
        else if(eta==19){
             if(depth==1) energy_corr = prod.first/0.9749902;
             else if(depth==2) energy_corr = prod.first/1.2024880;
             else if(depth==3)  energy_corr = prod.first/1.2024880;
             else if(depth==4)  energy_corr = prod.first/1.2024880;
             else if(depth==5)  energy_corr = prod.first/1.6033173;
             else if(depth==6)  energy_corr = prod.first/1.6033173;
        }
        else if(eta==20){
             if(depth==1) energy_corr = prod.first/0.9625976;
             else if(depth==2) energy_corr = prod.first/1.1872037;
             else if(depth==3)  energy_corr = prod.first/1.1872037;
             else if(depth==4)  energy_corr = prod.first/1.1872037;
             else if(depth==5)  energy_corr = prod.first/1.5829383;
             else if(depth==6)  energy_corr = prod.first/1.5829383;
        }
        else if(eta==21){
             if(depth==1) energy_corr = prod.first/0.9521488;
             else if(depth==2) energy_corr = prod.first/1.1743168;
             else if(depth==3)  energy_corr = prod.first/1.1743168;
             else if(depth==4)  energy_corr = prod.first/1.1743168;
             else if(depth==5)  energy_corr = prod.first/1.5657558;
             else if(depth==6)  energy_corr = prod.first/1.565755;
        }
        else if(eta==22){
             if(depth==1) energy_corr = prod.first/0.9429098;
             else if(depth==2) energy_corr = prod.first/1.1629221;
             else if(depth==3)  energy_corr = prod.first/1.1629221;
             else if(depth==4)  energy_corr = prod.first/1.1629221;
             else if(depth==5)  energy_corr = prod.first/1.5505628;
             else if(depth==6)  energy_corr = prod.first/1.5505628;
        }
        else if(eta==23){
             if(depth==1) energy_corr = prod.first/0.9345199;
             else if(depth==2) energy_corr = prod.first/1.1525746;
             else if(depth==3)  energy_corr = prod.first/1.1525746;
             else if(depth==4)  energy_corr = prod.first/1.1525746;
             else if(depth==5)  energy_corr = prod.first/1.5367661;
             else if(depth==6)  energy_corr = prod.first/1.5367661;
        }
        else if(eta==24){
             if(depth==1) energy_corr = prod.first/0.9269888;
             else if(depth==2) energy_corr = prod.first/1.1432862;
             else if(depth==3)  energy_corr = prod.first/1.1432862;
             else if(depth==4)  energy_corr = prod.first/1.1432862;
             else if(depth==5)  energy_corr = prod.first/1.5243816;
             else if(depth==6)  energy_corr = prod.first/1.5243816;
        }
        else if(eta==25){
             if(depth==1) energy_corr = prod.first/0.9203438;
             else if(depth==2) energy_corr = prod.first/1.1350908;
             else if(depth==3)  energy_corr = prod.first/1.1350908;
             else if(depth==4)  energy_corr = prod.first/1.1350908;
             else if(depth==5)  energy_corr = prod.first/1.5134544;
             else if(depth==6)  energy_corr = prod.first/1.5134544;
        }
        else if(eta==26){
             if(depth==1) energy_corr = prod.first/0.9146088;
             else if(depth==2) energy_corr = prod.first/0.7520116;
             else if(depth==3)  energy_corr = prod.first/0.7520116;
             else if(depth==4)  energy_corr = prod.first/0.7520116;
             else if(depth==5)  energy_corr = prod.first/1.1280175;
             else if(depth==6)  energy_corr = prod.first/1.5040233;
             else if(depth==7)  energy_corr = prod.first/1.5040233;
        }
        energy_corr_errhigh = energy_corr*energy_errhigh/energy; 
        energy_corr_errlow = energy_corr*energy_errlow/energy;

        if(depth==4 && eta==16) outtree->Fill();
        else if((depth==2 || depth==3) && eta==17) outtree->Fill();
        else if((depth>1 && depth<6) && eta==18) outtree->Fill();
        else if(depth<7 && (eta>18 || eta<26)) outtree->Fill();
        else if(depth<8 && eta==26) outtree->Fill();

        TCanvas *c1 = new TCanvas("c1","pile up correction plot",200,10,700,500);
        gr1->Draw("AP");
        gr1->GetXaxis()->SetTitle("Average Nvertex");
        gr1->GetYaxis()->SetTitle("Energy [GeV]");
        gr1->GetXaxis()->SetLimits(0.,50.);
        if(depth==1) gr1->GetYaxis()->SetRangeUser(0.,1.0);
        else if(depth==2) gr1->GetYaxis()->SetRangeUser(0.1,1.5);
        else if(depth==3 || depth==4) gr1->GetYaxis()->SetRangeUser(0.2,1.5);
        else if(depth==5) gr1->GetYaxis()->SetRangeUser(0.2,1.5);
        else gr1->GetYaxis()->SetRangeUser(0.2,1.0);

        TLegend *legend = new TLegend(0.15,0.65,0.55,0.90);
        legend->SetBorderSize(0);
        legend->SetTextFont(42);
        legend->SetTextSize(0.04);
        legend->SetFillStyle(0);
        legend->SetFillColor(0);
        legend->SetLineColor(0);
        if(phi!=0) legend->AddEntry(gr1, Form("ieta%d iphi%d depth%d",eta, phi, depth), "L");
        else legend->AddEntry(gr1, Form("ieta%d depth%d collapsed iphi",eta, depth), "L");
        legend->Draw("same");

        system("mkdir -vp "+path);
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d_iphi%d_ieta%d.png", path.Data(), depth, phi, eta));
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d_iphi%d_ieta%d.pdf", path.Data(), depth, phi, eta));
        c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d_iphi%d_ieta%d.eps", path.Data(), depth, phi, eta));

        // TCanvas::Update() draws the frame, after which one can change it
        c1->Update();
        c1->Modified();
         
        TFile* outputFile=TFile::Open(Form("%s/NoIso_test_pileupCorr_depth%d_iphi%d_ieta%d.root", path.Data(), depth, phi, eta),"recreate");
        outtree->Write();
        gr1->SetName(Form("gr_ieta%d_idepth%d",eta,depth));
        gr1->Write();
}
