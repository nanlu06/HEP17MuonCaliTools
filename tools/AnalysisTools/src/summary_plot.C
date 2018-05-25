#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"
#include "CommonFunc.h"
#include "CMSLUMI.h"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

   std::cout << "[Usage]: ./graph_energy_vs_depth Path inputName\n" << std::endl;
   TString path=argv[1];
   TString outputName=argv[2];
   TString filename = path + outputName;
   TString ymaxs = argv[3];
   TString ymins = argv[4];
   float ymax = ymaxs.Atof();
   float ymin = ymins.Atof();

   cout <<" "<<path<< " "<<outputName<<" "<<filename<<endl;
   cout <<"max min "<<ymax<<" "<<ymin<<endl;

   CommonFunc::setTDRStyle();

   /*
   bool writeExtraText = true;       // if extra text
   TString extraText  = "Preliminary";  // default extra text is "Preliminary"
   lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
   lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
   lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
   */

   int iPeriod = 3;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)


   TFile rtFile(filename);
   TGraphAsymmErrors* gr16 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta16");
   TGraphAsymmErrors* gr17 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta17");
   TGraphAsymmErrors* gr18 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta18");
   TGraphAsymmErrors* gr19 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta19");
   TGraphAsymmErrors* gr20 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta20");
   TGraphAsymmErrors* gr21 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta21");
   TGraphAsymmErrors* gr22 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta22");
   TGraphAsymmErrors* gr23 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta23");
   TGraphAsymmErrors* gr24 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta24"); 
   TGraphAsymmErrors* gr25 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta25");
   TGraphAsymmErrors* gr26 = (TGraphAsymmErrors*)rtFile.Get("gr_energy_per_layer_ieta26");

   int W = 800;
   int H = 600;
   int H_ref = 600; 
   int W_ref = 800; 
   float T = 0.08*H_ref;
   float B = 0.12*H_ref; 
   float L = 0.12*W_ref;
   float R = 0.04*W_ref;

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

   gr16->SetLineColor(4);
   gr16->SetLineWidth(2);
   gr16->SetMarkerColor(4);
   gr16->SetMarkerStyle(21);

   gr17->SetLineColor(3);
   gr17->SetLineWidth(2);
   gr17->SetMarkerColor(3);
   gr17->SetMarkerStyle(21);

   gr18->SetLineColor(1);
   gr18->SetLineWidth(2);
   gr18->SetMarkerColor(1);
   gr18->SetMarkerStyle(21);
   
   gr19->SetLineColor(2);
   gr19->SetLineWidth(2);
   gr19->SetMarkerColor(2);
   gr19->SetMarkerStyle(21);

   gr20->SetLineColor(kGreen+3);
   gr20->SetLineWidth(2);
   gr20->SetMarkerColor(kGreen+3);
   gr20->SetMarkerStyle(21);

   gr21->SetLineColor(kMagenta);
   gr21->SetLineWidth(2);
   gr21->SetMarkerColor(kMagenta);
   gr21->SetMarkerStyle(21);

   gr22->SetLineColor(kViolet+2);
   gr22->SetLineWidth(2);
   gr22->SetMarkerColor(kViolet+2);
   gr22->SetMarkerStyle(21);
 
   gr23->SetLineColor(kBlue);
   gr23->SetLineWidth(2);
   gr23->SetMarkerColor(kBlue);
   gr23->SetMarkerStyle(21);

   gr24->SetLineColor(kBlack);
   gr24->SetLineWidth(2);
   gr24->SetMarkerColor(kBlack);
   gr24->SetMarkerStyle(21);

   gr25->SetLineColor(kGreen+2);
   gr25->SetLineWidth(2);
   gr25->SetMarkerColor(kGreen+2);
   gr25->SetMarkerStyle(21);

   gr26->SetLineColor(kPink-9);
   gr26->SetLineWidth(2);
   gr26->SetMarkerColor(kPink-9);
   gr26->SetMarkerStyle(21);

   TMultiGraph *mg = new TMultiGraph();
   //mg->Add(gr16);
   //mg->Add(gr17);
   //mg->Add(gr18);
   mg->Add(gr19);
   mg->Add(gr20);
   mg->Add(gr21);
   mg->Add(gr22);
   mg->Add(gr23);
   mg->Add(gr24);
   mg->Add(gr25);
   mg->Add(gr26);
   mg->Draw("APL");
   mg->GetXaxis()->SetTitle("Depth");
   //mg->GetYaxis()->SetTitle("pe/MIP/layer");
   mg->GetYaxis()->SetTitle("Energy / Layer [GeV]");
   //mg->GetYaxis()->SetTitle("Reconstructed energy / layer [GeV]");
   //mg->GetYaxis()->SetTitle("Energy / pathlength [GeV/cm]");
   //mg->GetXaxis()->SetRangeUser(1,7);
   mg->SetMaximum(ymax);
   mg->SetMinimum(ymin);
   //mg->SetMaximum(0.3);

  TLegend *legend = new TLegend(0.55,0.7,0.95,0.90);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    //legend->AddEntry(gr16, "ieta = 16", "L");
    //legend->AddEntry(gr17, "ieta = 17", "L");
    //legend->AddEntry(gr18, "ieta = 18", "L");
    legend->AddEntry(gr22, "ieta = 22", "L");
    legend->AddEntry(gr23, "ieta = 23", "L");
    legend->AddEntry(gr24, "ieta = 24", "L");
    legend->AddEntry(gr25, "ieta = 25", "L");
    legend->AddEntry(gr26, "ieta = 26", "L");
    legend->Draw("same");

   TLegend *legend2 = new TLegend(0.25,0.7,0.55,0.90);
   legend2->SetBorderSize(0);
   legend2->SetTextFont(42);
   legend2->SetTextSize(0.04);
   legend2->SetFillStyle(0);
   legend2->SetFillColor(0);
   legend2->SetLineColor(0);
   legend2->AddEntry(gr19, "ieta = 19", "L");
   legend2->AddEntry(gr20, "ieta = 20", "L");
   legend2->AddEntry(gr21, "ieta = 21", "L");
   legend2->Draw("same");
   //CMSLUMI::CMS_lumi( c1, -1, 33 );
   //CommonFunc::AddCMS(c1);
   c1->Update();
   c1->RedrawAxis();
   c1->GetFrame()->Draw();

   c1->SaveAs("muon_energy_per_layer_05252018_v2.png");
   c1->SaveAs("muon_energy_per_layer_05252018_v2.pdf");
   c1->SaveAs("muon_energy_per_layer_05252018_v2.C");
   c1->SaveAs("muon_energy_per_layer_05252018_v2.eps");
}
