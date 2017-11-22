#include "CommonFunc.h"

using namespace std;

const double epsilon=1e-6;

bool CommonFunc::IsNaN(double var){volatile double d=var;return d!=d;}

void CommonFunc::PrintCanvas(TCanvas *c, TString name){
  c->Print(Form("%s.root",name.Data()));
  c->Print(Form("%s.eps",name.Data()));
  c->Print(Form("%s.png",name.Data()));
  c->Print(Form("%s.pdf",name.Data()));
  c->Print(Form("%s.C",name.Data()));
}

TStyle* CommonFunc::AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);
  //
  atlasStyle->SetPalette(57); 
  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.08);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.1);
  atlasStyle->SetTitleYOffset(1.1);

  // use large fonts
  //Int_t font=72; // Helvetica italics
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

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth((Width_t)3.0);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  return atlasStyle;

}

void CommonFunc::SetAtlasStyle()
{
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  TStyle* atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}
