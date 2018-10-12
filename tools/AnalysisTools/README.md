1) setup root
2) make clean; make
3) make bin/sig_only_fit_data
4) make bin/graph_pileupCorr_test
5) source plotSpectra.sh | tee -a runSpectra.log
6) source pileup-correction.sh | tee -a runSpectra.log



How to perform the fit signal+bkg for region outside of tracker coverage?

[Usage]: ./bin/sig_plus_bkg_fit signalFile outputName ieta depth ZmassCut min_depth6 max_depth6 min_depth7 max_depth7 
./bin/sig_plus_bkg_fit /afs/cern.ch/work/i/idutta/public/tree_ieta27_data2018_ABCD_plots_v3.root outcome.root 27 7 80 0.2 1.0 0.1 2.0
