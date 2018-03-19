TStyle* AtlasStyle()
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);

  atlasStyle->SetPaperSize(20,26);

  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);

  atlasStyle->SetTitleXOffset(1.1);
  atlasStyle->SetTitleYOffset(1.3);

  Int_t font=42; // Helvetica
  Double_t tsize=0.05; // originally 0.05
  atlasStyle->SetTextFont(font);
  
  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth((Width_t)3.0);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  atlasStyle->SetEndErrorSize(0.);
  atlasStyle->SetOptTitle(0);
  atlasStyle->SetOptStat(0);
  atlasStyle->SetOptFit(0);
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  return atlasStyle;

}

void SetAtlasStyle()
{
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  TStyle* atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}


void graph_per_layer_test_Feb22() {
   
   SetAtlasStyle();

   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   const Int_t n =6;
   Double_t x[n], y1[n], y2[n], y4[n],y5[n],y6[n],y7[n],y8[n],y9[n],y10[n],y11[n];

   const Int_t m =7;
   Double_t xm[m], ym[m];

   const Int_t n18 = 4;
   Double_t x3[n18], y3[n18];

   //depth1
   y1[0] = -2999998.000000, y2[0] = -2946.621826, y4[0] = 0.144841, y5[0] = 0.156267, y6[0] = 0.131563, y7[0] = 0.122599, y8[0] = 0.093577, y9[0] = 0.082760, y10[0] = 0.050602, ym[0] = 0.025158;
   //depth2
   y1[1] = 1.000000, y2[1] = 1.062333, y3[0] = 0.505896, y4[1] = 0.408559, y5[1] = 0.466166, y6[1] = 0.440973, y7[1] = 0.467808, y8[1] = 0.448070, y9[1] = 0.459642, y10[1] = 0.340445, ym[1] = 0.096546;
   //depth3
   y1[2] = -2999998.000000, y2[2] = 1.395339, y3[1] = 0.557048, y4[2] = 0.418555, y5[2] = 0.344068, y6[2] = 0.422190, y7[2] = 0.441046, y8[2] = 0.420124, y9[2] = 0.396128, y10[2] = 0.402273, ym[2] = 0.395470;
   //depth4
   y1[3] = 0.892387, y2[3] = -144115188075855872.000000, y3[2] = 0.431076, y4[3] = 0.442900, y5[3] = 0.416255, y6[3] = 0.381097, y7[3] = 0.396434, y8[3] = 0.423470, y9[3] = 0.402216, y10[3] = 0.439992, ym[3] = 0.275581;
   //depth5
   y1[4] = 38.536072, y2[4] = 74.461861, y3[3] = 1.074531, y4[4] = 0.637447, y5[4] = 0.621429, y6[4] = 0.615442, y7[4] = 0.639832, y8[4] = 0.597628, y9[4] = 0.661244, y10[4] = 0.660990, ym[4] = 0.458974;
   //depth6
   y1[5] = 29792605436903424.000000, y2[5] = 1084058752.000000, y4[5] = 0.566675, y5[5] = 0.554790, y6[5] = 0.582538, y7[5] = 0.533868, y8[5] = 0.619946, y9[5] = 0.589297, y10[5] = 0.610568, ym[5] = 0.719757;
   //depth7
   ym[6] = 0.608352;

   for (Int_t i=0;i<n;i++) { 
     x[i] = 1 +i;   
     if(i==0){
       y3[i] = y3[i]/3.0; 
       x3[i] = 2 +i;
     }
     if(i!=0 && i<4){
       x3[i] = 2 +i;
       if(i==1) y3[i] = y3[i]/4.0;  
       else if(i==3) y3[i] = y3[i]/4.5;
       else y3[i] = y3[i]/3.0;
        y4[i] = y4[i]/3.0;
        y5[i] = y5[i]/3.0;
        y6[i] = y6[i]/3.0;
        y7[i] = y7[i]/3.0;
        y8[i] = y8[i]/3.0;
        y9[i] = y9[i]/3.0;
        y10[i] = y10[i]/3.0;
     }
     else if(i>3){
        y4[i] = y4[i]/4.0;
        y5[i] = y5[i]/4.0;
        y6[i] = y6[i]/4.0;
        y7[i] = y7[i]/4.0;
        y8[i] = y8[i]/4.0;
        y9[i] = y9[i]/4.0;
        y10[i] = y10[i]/4.0;
     }
   }

   for (Int_t i=0;i<m;i++) {
        xm[i] = 1 +i;
     	if(i!=0 && i<4) ym[i] = ym[i]/2.0;
     	else if(i==4) ym[i] = ym[i]/3.0;
        else if(i>4) ym[i] = ym[i]/4.0;
   }

   //19
   TGraph *gr3 = new TGraph(n18,x3,y3);
   gr3->SetLineColor(3);
   gr3->SetLineWidth(4);
   gr3->SetMarkerColor(3);
   gr3->SetMarkerStyle(21);
   //20
   TGraph *gr4 = new TGraph(n,x,y4);
   gr4->SetLineColor(1);
   gr4->SetLineWidth(4);
   gr4->SetMarkerColor(1);
   gr4->SetMarkerStyle(21);
   //21
   TGraph *gr5 = new TGraph(n,x,y5);
   gr5->SetLineColor(2);
   gr5->SetLineWidth(4);
   gr5->SetMarkerColor(2);
   gr5->SetMarkerStyle(21);
   //22
   TGraph *gr6 = new TGraph(n,x,y6);
   gr6->SetLineColor(6);
   gr6->SetLineWidth(4);
   gr6->SetMarkerColor(6);
   gr6->SetMarkerStyle(21);

        cout <<"ieta==22"<<endl;
        TGraph *gr7 = new TGraph(n,x,y7);
        gr7->SetLineColor(7);
        gr7->SetLineWidth(4);
        gr7->SetMarkerColor(7);
        gr7->SetMarkerStyle(21);

        cout <<"ieta==23"<<endl;
        TGraph *gr8 = new TGraph(n,x,y8);
        gr8->SetLineColor(8);
        gr8->SetLineWidth(4);
        gr8->SetMarkerColor(8);
        gr8->SetMarkerStyle(21);

cout <<"ieta==24"<<endl;
        TGraph *gr9 = new TGraph(n,x,y9);
        gr9->SetLineColor(9);
        gr9->SetLineWidth(4);
        gr9->SetMarkerColor(9);
        gr9->SetMarkerStyle(21);

        cout <<"ieta==25"<<endl;
        TGraph *gr10 = new TGraph(n,x,y10);
        gr10->SetLineColor(kRed+2);
        gr10->SetLineWidth(4);
        gr10->SetMarkerColor(kRed+2);
        gr10->SetMarkerStyle(21);

        cout <<"ieta==26"<<endl;
        TGraph *gr11 = new TGraph(m,xm,ym);
        gr11->SetLineColor(kGreen+2);
        gr11->SetLineWidth(4);
        gr11->SetMarkerColor(kGreen+2);
        gr11->SetMarkerStyle(21);

   TMultiGraph *mg = new TMultiGraph();
   mg->Add(gr3);
   mg->Add(gr4);
   mg->Add(gr5);
   mg->Add(gr6);
   mg->Add(gr7);
   mg->Add(gr8);
   mg->Add(gr9);
   mg->Add(gr10);
   mg->Add(gr11);
   mg->Draw("APL");
   mg->GetXaxis()->SetTitle("Depth");
   //mg->GetYaxis()->SetTitle("pe/MIP/layer");
   mg->GetYaxis()->SetTitle("Energy [GeV]/layer");
   //mg->GetXaxis()->SetRangeUser(1,6);
   //mg->SetMinimum(3.);
   //mg->SetMaximum(6.5);
   mg->SetMinimum(0.);
   mg->SetMaximum(0.3);

  TLegend *legend = new TLegend(0.55,0.20,0.95,0.40);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->AddEntry(gr3, "ieta = 18", "L");
    legend->AddEntry(gr4, "ieta = 19", "L");
    legend->AddEntry(gr5, "ieta = 20", "L");
    legend->AddEntry(gr6, "ieta = 21", "L");
    legend->AddEntry(gr7, "ieta = 22", "L");
    legend->AddEntry(gr8, "ieta = 23", "L");
    legend->AddEntry(gr9, "ieta = 24", "L");
    legend->AddEntry(gr10, "ieta = 25", "L");
    legend->AddEntry(gr11, "ieta = 26", "L");
    legend->Draw("same");


  c1->SaveAs("pe_per_layer_Feb22.png");
  c1->SaveAs("pe_per_depth_Feb22.pdf");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->Modified();
}
