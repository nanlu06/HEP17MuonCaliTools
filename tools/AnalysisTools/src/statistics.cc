#include "statistics.hh"

using namespace RooFit;
using namespace RooStats;

ClassImp(statistics)

statistics::statistics(){
  defaultMinimizer    = "Minuit2";     // or "Minuit"
  defaultPrintLevel      = -1;             // Minuit print level
  killBelowFatal        = 1;             // In case you want to suppress RooFit warnings further, set to 1
  fRandom=new TRandom3();
  if (killBelowFatal) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer(defaultMinimizer.c_str());
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(defaultStrategy);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(defaultPrintLevel);
}

statistics::~statistics(){
  SafeDelete(fRandom);
}

void statistics::setDefaultMinimize(){
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
}

float statistics::minimizeTest(RooNLLVar* nll,float neps)
{
    nll->enableOffsetting(true);
    int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
    int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();

    RooMinimizer minim(*nll);
    minim.setStrategy(strat);
    minim.setPrintLevel(1);   
    minim.setProfile();
    minim.setEps(neps);
    int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());

    return status;
}

vector<TString> statistics::SplitString(const TString& theOpt, const char separator )
{
   vector<TString> splitV;
   TString splitOpt(theOpt);
   splitOpt.ReplaceAll("\n"," ");
   splitOpt = splitOpt.Strip(TString::kBoth,separator);
   while (splitOpt.Length()>0) {
      if ( !splitOpt.Contains(separator) ) {
         splitV.push_back(splitOpt);
         break;
      }
      else {
         TString toSave = splitOpt(0,splitOpt.First(separator));
         splitV.push_back(toSave);
         splitOpt = splitOpt(splitOpt.First(separator),splitOpt.Length());
      }
      splitOpt = splitOpt.Strip(TString::kLeading,separator);
   }
   return splitV;
}
