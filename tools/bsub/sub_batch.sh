#!/bin/bash
for ieta in {16..26}
#for ieta in 26
do
  for iphi in all
  do
    #for ivtx  in 10
    for ivtx  in {10..35}
    do
    echo $ivtx
    bsub -R "pool>30000" -q 8nh run_test.sh $ieta $iphi $ivtx
    done
  done
done       
