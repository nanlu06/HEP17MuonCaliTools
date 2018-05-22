#ifndef _CommonFunc_h_
#define _CommonFunc_h_
#include "CommonHead.h"

namespace CommonFunc{
  void PrintCanvas(TCanvas* c, TString name);
  std::pair<float,float> LinearCal( TF1 *myfunc4);
  bool IsNaN(double var);
  TStyle* AtlasStyle();
  void SetAtlasStyle();
  bool AddCMS( TCanvas* C );
  void setTDRStyle();
};


#endif
