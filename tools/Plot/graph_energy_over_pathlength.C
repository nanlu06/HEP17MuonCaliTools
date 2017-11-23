//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Internal";
//TString extraText   = "Preliminary";
TString lumiText = "5.9 fb^{-1} (13 TeV)";
//TString lumiText = "35.9 fb^{-1} (13 TeV)";
//TString lumiText = "Simulation (13 TeV)";

bool AddCMS( TCanvas* C );

void graph_energy_over_pathlength() {
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   const Int_t n = 6;
   Double_t x[n], y[n], y1[n],y2[n],y3[n];

   //Oct19
   //no Iso with 10MeV cut
   y[0] = 1.390E-01;
   y1[0] = 1.219E-01;
   y2[0] = 1.339E-01;
   y3[0] = 1.220E-01;

   y[1] = 4.581E-01;
   y1[1] = 4.878E-01;
   y2[1] = 4.510E-01;
   y3[1] = 4.653E-01;
/*
   //with iso
   y[0] = 1.423E-01;
   y1[0] = 1.553E-01;
   y2[0] = 1.289E-01;
   y3[0] = 6.920E-02;

   y[1] = 4.59E-01;
   y1[1] = 4.72E-01;
   y2[1] = 4.52E-01;
   y3[1] = 4.35E-01;
*/
   y[2] = 4.507E-01;
   y1[2] = 4.838E-01;
   y2[2] = 4.570E-01;
   y3[2] = 4.371E-01;

   y[3] = 4.427E-01;
   y1[3] = 4.116E-01;
   y2[3] = 4.428E-01;
   y3[3] = 4.682E-01;

   y[4] = 7.000E-01;
   y1[4] = 6.656E-01;
   y2[4] = 6.772E-01;
   y3[4] = 7.245E-01;

   y[5] = 6.135E-01;
   y1[5] = 5.832E-01;
   y2[5] = 6.427E-01;
   y3[5] = 6.242E-01;

   float activeL1[4]={0.9521488,0.9429098,0.9345199,0.926988};
   float activeL2[4]={1.1743168,1.1629221,1.1525746,1.1432862};
   float activeL3[4]={1.174316,1.1629221,1.1525746,1.1432862};
   float activeL4[4]={1.1743168,1.1629221,1.1525746,1.1432862};
   float activeL5[4]={1.5657558,1.5505628,1.5367661,1.5243816};
   float activeL6[4]={1.5657558,1.5505628,1.5367661,1.5243816};

   for (Int_t i=0;i<n;i++) {
     x[i] = 1 +i;
     if(i==0){
        y[i] = y[i]*9./(activeL1[0]*3.7);
        y1[i] = y1[i]*9./(activeL1[1]*3.7);
        y2[i] = y2[i]*9./(activeL1[2]*3.7);
        y3[i] = y3[i]*9./(activeL1[3]*3.7);
     }
     else if(i==1){
        y[i] = y[i]/activeL2[0];
        y1[i] = y1[i]/activeL2[1];
        y2[i] = y2[i]/activeL2[2];
        y3[i] = y3[i]/activeL2[3];
     }
     else if(i==2){
        y[i] = y[i]/activeL3[0];
        y1[i] = y1[i]/activeL3[1];
        y2[i] = y2[i]/activeL3[2];
        y3[i] = y3[i]/activeL3[3];
     }
     else if(i==3){
        y[i] = y[i]/activeL4[0];
        y1[i] = y1[i]/activeL4[1];
        y2[i] = y2[i]/activeL4[2];
        y3[i] = y3[i]/activeL4[3];
     }
     else if(i==4){
        y[i] = y[i]/activeL5[0];
        y1[i] = y1[i]/activeL5[1];
        y2[i] = y2[i]/activeL5[2];
        y3[i] = y3[i]/activeL5[3];
     }
    else if(i==5){
        y[i] = y[i]/activeL6[0];
        y1[i] = y1[i]/activeL6[1];
        y2[i] = y2[i]/activeL6[2];
        y3[i] = y3[i]/activeL6[3];
     }
     printf(" %i %f %f %f %f %f \n",i,x[i],y[i], y1[i], y2[i], y3[i]);
   }
   TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(4);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);

   TGraph *gr1 = new TGraph(n,x,y1);
   gr1->SetLineColor(3);
   gr1->SetLineWidth(4);
   gr1->SetMarkerColor(3);
   gr1->SetMarkerStyle(21);

   TGraph *gr2 = new TGraph(n,x,y2);
   gr2->SetLineColor(1);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(1);
   gr2->SetMarkerStyle(21);

   TGraph *gr3 = new TGraph(n,x,y3);
   gr3->SetLineColor(2);
   gr3->SetLineWidth(4);
   gr3->SetMarkerColor(2);
   gr3->SetMarkerStyle(21);


   TMultiGraph *mg = new TMultiGraph();
   mg->Add(gr1);
   mg->Add(gr2);
   mg->Add(gr3);
   mg->Add(gr);
   mg->Draw("APL");
   mg->GetXaxis()->SetTitle("Depth");
   mg->GetYaxis()->SetTitle("Energy / pathlength [GeV/cm]");
   mg->SetMinimum(0.);
   mg->SetMaximum(0.6);

  TLegend *legend = new TLegend(0.55,0.20,0.95,0.40);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->AddEntry(gr, "ieta = 21", "L");
    legend->AddEntry(gr1, "ieta = 22", "L");
    legend->AddEntry(gr2, "ieta = 23", "L");
    legend->AddEntry(gr3, "ieta = 24", "L");
    legend->Draw("same");

  AddCMS(c1);
  c1->SaveAs("test_per_path_Oct19_v0_Cut10MeV.png");
  c1->SaveAs("test_per_path_Oct19_v0_Cut10MeV.pdf");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->Modified();
}

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.905;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.185;
  float cmsy = 0.940;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.118;
  float extray = cmsy;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);
   
  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};
