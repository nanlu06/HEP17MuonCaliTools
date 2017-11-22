#ifndef STATISTICS_H
#define STATISTICS_H
#include "CommonHead.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooStats;
using namespace RooFit;

class statistics : public TObject{
public:
  string defaultMinimizer;
  int defaultPrintLevel;
  int defaultStrategy;
  bool killBelowFatal;
  bool doBlind;
  bool conditionalExpected;
  bool doTilde;
  bool doExp;
  bool doObs;
  double precision;
  bool verbose;
  bool usePredictiveFit;
  bool extrapolateSigma;
  int maxRetries;
  TRandom3 *fRandom;
public:
  statistics();
  ~statistics();
  static void setDefaultMinimize();
  static void setDefaultPrintLevel(int printlevel){ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(printlevel);}
  static void setDefaultStrategy(int strategy){ROOT::Math::MinimizerOptions::SetDefaultStrategy(strategy);}
  static float minimizeTest(RooNLLVar* nll,float neps=1.0);
  static std::vector<TString> SplitString(const TString& theOpt, const char separator );
  ClassDef(statistics,1);
};

#endif
