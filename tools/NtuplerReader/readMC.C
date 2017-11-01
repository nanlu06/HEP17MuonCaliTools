#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>

#include "NtuplerReader.h"

int main(int argc, const char* argv[]) {

       TChain *mc = new TChain("HcalHBHEMuonAnalyzer/TREE");

       TString listname = "preselection_data.list";
       ifstream listfile;
       listfile.open(listname);
       if (! listfile.good()) {
          std::cerr << "Error: " << listname << " cannot be opened." << std::endl;
       return -1;
       }

       std::string filename;
       while (getline(listfile, filename)) {
       mc->Add(filename.c_str());
       }
       NtuplerReader *readMC = new NtuplerReader(mc);
       readMC->Loop();
       listfile.close();

        //char file[100];
        //        //sprintf(file, "%s", argv[1]);
        //                //cout << "read file: " << file << " ... " << endl;
        //
       return 1;
}
