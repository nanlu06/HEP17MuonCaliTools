#ifndef _CommonFunc_h_
#define _CommonFunc_h_
#include "CommonHead.h"

namespace CommonFunc{
  void PrintCanvas(TCanvas* c, TString name);
  bool IsNaN(double var);
  TStyle* AtlasStyle();
  void SetAtlasStyle();
  bool AddCMS( TCanvas* C );
};


#endif
