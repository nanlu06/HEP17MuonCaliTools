#ifndef CMSLUMI_H
#define CMSLUMI_H

#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

namespace CMSLUMI{
/*
TString cmsText     = "CMS";
float cmsTextFont   = 61; 

bool writeExtraText = false;
TString extraText   = "Preliminary";
float extraTextFont = 52; 

float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;

float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;

float extraOverCmsTextSize  = 0.76;

TString lumi_test = "0.87 fb^{-1}";
TString lumi_13TeV = "20.1 fb^{-1}";
TString lumi_8TeV  = "19.7 fb^{-1}";
TString lumi_7TeV  = "5.1 fb^{-1}";
TString lumi_sqrtS = "";

bool drawLogo      = false;
*/
void CMS_lumi( TPad* pad, int iPeriod=3, int iPosX=10 );
};
#endif
