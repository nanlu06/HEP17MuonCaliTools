#include "CommonHead.h"
#include "RooFitHead.h"
#include "statistics.hh"

using namespace RooFit ;
using namespace std ;

int main(int argc, char**argv){

  TString path=argv[1];

   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   const Int_t n = 4;
   float xn[n]={0,0,0,0}, xp[n]={0,0,0,0};
  
   vector<float> ene;//ieta, idepth, ivertx

//ieta 21
//ivertex 0
//depth 1
ene.push_back(1.7181e-01); ene.push_back( 1.7875e-03); ene.push_back(1.8084e-03);
//depth 2
ene.push_back(5.2866e-01); ene.push_back( 4.2419e-03); ene.push_back(4.2365e-03);
//depth 3
ene.push_back(5.0004e-01); ene.push_back( 3.4194e-03); ene.push_back(3.4038e-03);
//depth 4
ene.push_back(4.5041e-01); ene.push_back( 2.8911e-03); ene.push_back(2.8790e-03);
//depth 5
ene.push_back(6.9601e-01); ene.push_back( 3.9630e-03); ene.push_back(3.9434e-03);
//depth 6
ene.push_back(6.2347e-01); ene.push_back( 3.9474e-03); ene.push_back(3.8814e-03);
//ivertex 1
//depth 1
ene.push_back(1.6172e-01); ene.push_back( 4.1694e-03); ene.push_back(4.1714e-03);
//depth 2
ene.push_back(5.0344e-01); ene.push_back( 1.0758e-02); ene.push_back(1.0679e-02);
//depth 3
ene.push_back(4.7537e-01); ene.push_back( 8.6417e-03); ene.push_back(8.3952e-03);
//depth 4
ene.push_back(4.6379e-01); ene.push_back( 8.4561e-03); ene.push_back(8.2473e-03);
//depth 5
ene.push_back(6.8495e-01); ene.push_back( 1.0407e-02); ene.push_back(1.0307e-02);
//depth 6
ene.push_back(6.1406e-01); ene.push_back( 1.0532e-02); ene.push_back(1.0368e-02);
//ivertex 2
//depth 1
ene.push_back(1.6811e-01); ene.push_back( 2.7332e-03); ene.push_back(2.7979e-03);
//depth 2
ene.push_back(5.1460e-01); ene.push_back( 6.3499e-03); ene.push_back(6.3189e-03);
//depth 3
ene.push_back(4.9484e-01); ene.push_back( 5.1997e-03); ene.push_back(5.1553e-03);
//depth 4
ene.push_back(4.4147e-01); ene.push_back( 4.2955e-03); ene.push_back(4.2664e-03);
//depth 5
ene.push_back(7.0217e-01); ene.push_back( 6.2346e-03); ene.push_back(6.1829e-03);
//depth 6
ene.push_back(6.2008e-01); ene.push_back( 5.9462e-03); ene.push_back(5.9225e-03);
//ivertex 3
//depth 1
ene.push_back(1.7673e-01); ene.push_back( 3.2796e-03); ene.push_back(3.2813e-03);
//depth 2
ene.push_back(5.4792e-01); ene.push_back( 8.1735e-03); ene.push_back(8.2366e-03);
//depth 3
ene.push_back(5.0561e-01); ene.push_back( 6.4634e-03); ene.push_back(6.3692e-03);
//depth 4
ene.push_back(4.5430e-01); ene.push_back( 5.3881e-03); ene.push_back(5.3427e-03);
//depth 5
ene.push_back(6.9706e-01); ene.push_back( 7.3103e-03); ene.push_back(7.2594e-03);
//depth 6
ene.push_back(6.3886e-01); ene.push_back( 7.3871e-03); ene.push_back(7.2784e-03);
//ivertex 4
//depth 1
ene.push_back(1.9981e-01); ene.push_back( 5.5126e-03); ene.push_back(5.6337e-03);
//depth 2
ene.push_back(5.6529e-01); ene.push_back( 1.2211e-02); ene.push_back(1.2040e-02);
//depth 3
ene.push_back(5.3006e-01); ene.push_back( 9.7223e-03); ene.push_back(9.6417e-03);
//depth 4
ene.push_back(4.5953e-01); ene.push_back( 7.9492e-03); ene.push_back(7.8584e-03);
//depth 5
ene.push_back(6.8698e-01); ene.push_back( 1.0101e-02); ene.push_back(9.9718e-03);
//depth 6
ene.push_back(6.1401e-01); ene.push_back( 1.0709e-02); ene.push_back(1.0578e-02);
//ieta 22
//ivertex 0
//depth 1
ene.push_back(1.8307e-01); ene.push_back( 1.8309e-03); ene.push_back(1.8274e-03);
//depth 2
ene.push_back(5.8076e-01); ene.push_back( 4.9126e-03); ene.push_back(4.8902e-03);
//depth 3
ene.push_back(4.9511e-01); ene.push_back( 3.3626e-03); ene.push_back(3.3555e-03);
//depth 4
ene.push_back(4.2388e-01); ene.push_back( 2.7814e-03); ene.push_back(2.7688e-03);
//depth 5
ene.push_back(6.6660e-01); ene.push_back( 3.7861e-03); ene.push_back(3.7677e-03);
//depth 6
ene.push_back(5.5564e-01); ene.push_back( 3.2746e-03); ene.push_back(3.2519e-03);
//ivertex 1
//depth 1
ene.push_back(1.5762e-01); ene.push_back( 4.3533e-03); ene.push_back(4.5363e-03);
//depth 2
ene.push_back(5.3495e-01); ene.push_back( 1.1606e-02); ene.push_back(1.1529e-02);
//depth 3
ene.push_back(4.8899e-01); ene.push_back( 8.0274e-03); ene.push_back(7.9334e-03);
//depth 4
ene.push_back(4.2408e-01); ene.push_back( 6.8676e-03); ene.push_back(6.7965e-03);
//depth 5
ene.push_back(6.6316e-01); ene.push_back( 9.4164e-03); ene.push_back(9.3348e-03);
//depth 6
ene.push_back(5.7208e-01); ene.push_back( 8.8477e-03); ene.push_back(8.6473e-03);
//ivertex 2
//depth 1
ene.push_back(1.7485e-01); ene.push_back( 2.7892e-03); ene.push_back(2.8333e-03);
//depth 2
ene.push_back(5.7632e-01); ene.push_back( 7.3405e-03); ene.push_back(7.3537e-03);
//depth 3
ene.push_back(4.9296e-01); ene.push_back( 5.3764e-03); ene.push_back(5.3075e-03);
//depth 4
ene.push_back(4.1824e-01); ene.push_back( 4.2237e-03); ene.push_back(4.2042e-03);
//depth 5
ene.push_back(6.6647e-01); ene.push_back( 5.9384e-03); ene.push_back(5.9225e-03);
//depth 6
ene.push_back(5.5131e-01); ene.push_back( 5.0009e-03); ene.push_back(4.9657e-03);
//ivertex 3
//depth 1
ene.push_back(1.9431e-01); ene.push_back( 4.0777e-03); ene.push_back(4.2496e-03);
//depth 2
ene.push_back(5.9018e-01); ene.push_back( 9.4495e-03); ene.push_back(9.2843e-03);
//depth 3
ene.push_back(5.0055e-01); ene.push_back( 6.2699e-03); ene.push_back(6.2301e-03);
//depth 4
ene.push_back(4.2929e-01); ene.push_back( 5.4073e-03); ene.push_back(5.3900e-03);
//depth 5
ene.push_back(6.7098e-01); ene.push_back( 6.9079e-03); ene.push_back(6.8298e-03);
//depth 6
ene.push_back(5.5360e-01); ene.push_back( 6.0409e-03); ene.push_back(5.9836e-03);
//ivertex 4
//depth 1
ene.push_back(2.1964e-01); ene.push_back( 7.4032e-03); ene.push_back(7.5699e-03);
//depth 2
ene.push_back(6.4085e-01); ene.push_back( 1.5744e-02); ene.push_back(1.5142e-02);
//depth 3
ene.push_back(4.9870e-01); ene.push_back( 9.1188e-03); ene.push_back(9.0299e-03);
//depth 4
ene.push_back(4.3236e-01); ene.push_back( 7.7063e-03); ene.push_back(7.6693e-03);
//depth 5
ene.push_back(6.6139e-01); ene.push_back( 1.0499e-02); ene.push_back(1.0363e-02);
//depth 6
ene.push_back(5.5551e-01); ene.push_back( 8.9580e-03); ene.push_back(8.9023e-03);
//ieta 23
//ivertex 0
//depth 1
ene.push_back(1.9218e-01); ene.push_back( 2.3292e-03); ene.push_back(2.3695e-03);
//depth 2
ene.push_back(6.1133e-01); ene.push_back( 5.5962e-03); ene.push_back(5.5229e-03);
//depth 3
ene.push_back(4.9202e-01); ene.push_back( 3.7098e-03); ene.push_back(3.6726e-03);
//depth 4
ene.push_back(4.6940e-01); ene.push_back( 3.1488e-03); ene.push_back(3.1702e-03);
//depth 5
ene.push_back(6.7002e-01); ene.push_back( 3.8521e-03); ene.push_back(3.8387e-03);
//depth 6
ene.push_back(6.6905e-01); ene.push_back( 3.8649e-03); ene.push_back(3.8418e-03);
//ivertex 1
//depth 1
ene.push_back(1.6630e-01); ene.push_back( 4.2125e-03); ene.push_back(4.3149e-03);
//depth 2
ene.push_back(5.3562e-01); ene.push_back( 1.0855e-02); ene.push_back(1.0825e-02);
//depth 3
ene.push_back(4.6660e-01); ene.push_back( 8.2019e-03); ene.push_back(8.1413e-03);
//depth 4
ene.push_back(4.4810e-01); ene.push_back( 7.5194e-03); ene.push_back(7.4301e-03);
//depth 5
ene.push_back(6.6990e-01); ene.push_back( 9.4357e-03); ene.push_back(9.3605e-03);
//depth 6
ene.push_back(6.5374e-01); ene.push_back( 9.6273e-03); ene.push_back(9.5155e-03);
//ivertex 2
//depth 1
ene.push_back(1.8613e-01); ene.push_back( 4.6278e-03); ene.push_back(3.0811e-03);
//depth 2
ene.push_back(6.0094e-01); ene.push_back( 8.5456e-03); ene.push_back(8.5106e-03);
//depth 3
ene.push_back(4.9387e-01); ene.push_back( 5.7906e-03); ene.push_back(5.7070e-03);
//depth 4
ene.push_back(4.6719e-01); ene.push_back( 4.8771e-03); ene.push_back(4.8483e-03);
//depth 5
ene.push_back(6.7074e-01); ene.push_back( 5.9787e-03); ene.push_back(5.9411e-03);
//depth 6
ene.push_back(6.6992e-01); ene.push_back( 5.9654e-03); ene.push_back(5.9168e-03);
//ivertex 3
//depth 1
ene.push_back(2.0867e-01); ene.push_back( 5.5712e-03); ene.push_back(6.0534e-03);
//depth 2
ene.push_back(6.4580e-01); ene.push_back( 1.1241e-02); ene.push_back(1.1268e-02);
//depth 3
ene.push_back(5.0341e-01); ene.push_back( 7.3320e-03); ene.push_back(7.2650e-03);
//depth 4
ene.push_back(4.8772e-01); ene.push_back( 6.1542e-03); ene.push_back(6.1297e-03);
//depth 5
ene.push_back(6.7440e-01); ene.push_back( 7.3993e-03); ene.push_back(7.3447e-03);
//depth 6
ene.push_back(6.6710e-01); ene.push_back( 7.3139e-03); ene.push_back(7.2447e-03);
//ivertex 4
//depth 1
ene.push_back(2.2114e-01); ene.push_back( 8.0180e-03); ene.push_back(8.2558e-03);
//depth 2
ene.push_back(6.9496e-01); ene.push_back( 1.8100e-02); ene.push_back(1.7677e-02);
//depth 3
ene.push_back(4.9987e-01); ene.push_back( 1.0404e-02); ene.push_back(1.0293e-02);
//depth 4
ene.push_back(4.6578e-01); ene.push_back( 8.5463e-03); ene.push_back(8.4526e-03);
//depth 5
ene.push_back(6.5965e-01); ene.push_back( 1.0244e-02); ene.push_back(1.0002e-02);
//depth 6
ene.push_back(6.8714e-01); ene.push_back( 1.0403e-02); ene.push_back(1.0288e-02);
//ieta 24
//ivertex 0
//depth 1
ene.push_back(2.2882e-01); ene.push_back( 2.9411e-03); ene.push_back(2.9589e-03);
//depth 2
ene.push_back(6.7929e-01); ene.push_back( 7.2940e-03); ene.push_back(7.1889e-03);
//depth 3
ene.push_back(4.7442e-01); ene.push_back( 3.8384e-03); ene.push_back(3.8097e-03);
//depth 4
ene.push_back(4.7041e-01); ene.push_back( 3.3683e-03); ene.push_back(3.3683e-03);
//depth 5
ene.push_back(7.2271e-01); ene.push_back( 4.4949e-03); ene.push_back(4.4782e-03);
//depth 6
ene.push_back(6.3470e-01); ene.push_back( 3.8669e-03); ene.push_back(3.8558e-03);
//ivertex 1
//depth 1
ene.push_back(1.8308e-01); ene.push_back( 4.9813e-03); ene.push_back(4.9792e-03);
//depth 2
ene.push_back(5.9776e-01); ene.push_back( 1.3858e-02); ene.push_back(1.3716e-02);
//depth 3
ene.push_back(4.4848e-01); ene.push_back( 8.6933e-03); ene.push_back(8.5996e-03);
//depth 4
ene.push_back(4.6715e-01); ene.push_back( 7.7841e-03); ene.push_back(7.6905e-03);
//depth 5
ene.push_back(7.2879e-01); ene.push_back( 1.1151e-02); ene.push_back(1.1052e-02);
//depth 6
ene.push_back(6.3796e-01); ene.push_back( 9.8741e-03); ene.push_back(9.7525e-03);
//ivertex 2
//depth 1
ene.push_back(2.1574e-01); ene.push_back( 4.1258e-03); ene.push_back(4.3443e-03);
//depth 2
ene.push_back(6.4539e-01); ene.push_back( 1.0220e-02); ene.push_back(1.0127e-02);
//depth 3
ene.push_back(4.7498e-01); ene.push_back( 5.7873e-03); ene.push_back(5.6853e-03);
//depth 4
ene.push_back(4.6583e-01); ene.push_back( 5.1178e-03); ene.push_back(5.1006e-03);
//depth 5
ene.push_back(7.2258e-01); ene.push_back( 6.8532e-03); ene.push_back(6.8242e-03);
//depth 6
ene.push_back(6.2864e-01); ene.push_back( 5.9861e-03); ene.push_back(5.9512e-03);
//ivertex 3
//depth 1
ene.push_back(2.5223e-01); ene.push_back( 0.0000e+00); ene.push_back(7.6029e-03);
//depth 2
ene.push_back(7.4729e-01); ene.push_back( 1.5624e-02); ene.push_back(1.5340e-02);
//depth 3
ene.push_back(4.8441e-01); ene.push_back( 7.6727e-03); ene.push_back(7.5631e-03);
//depth 4
ene.push_back(4.8299e-01); ene.push_back( 6.8829e-03); ene.push_back(6.8329e-03);
//depth 5
ene.push_back(7.1288e-01); ene.push_back( 8.5845e-03); ene.push_back(8.6164e-03);
//depth 6
ene.push_back(6.3665e-01); ene.push_back( 7.1406e-03); ene.push_back(7.0906e-03);
//ivertex 4
//depth 1
ene.push_back(3.1056e-01); ene.push_back( 1.0767e-02); ene.push_back(-0.0000e+00);
//depth 2
ene.push_back(7.9668e-01); ene.push_back( 2.6972e-02); ene.push_back(-0.0000e+00);
//depth 3
ene.push_back(4.9208e-01); ene.push_back( 1.1854e-02); ene.push_back(1.1700e-02);
//depth 4
ene.push_back(4.6334e-01); ene.push_back( 9.0559e-03); ene.push_back(8.9726e-03);
//depth 5
ene.push_back(7.3515e-01); ene.push_back( 1.2245e-02); ene.push_back(1.2126e-02);
//depth 6
ene.push_back(6.4450e-01); ene.push_back( 1.0759e-02); ene.push_back(1.0681e-02);

/*    
    //ieta 21
    //ivertex 0
    //depth 1
    ene.push_back(1.2983e-01); ene.push_back( 3.5394e-03); ene.push_back(3.6486e-03);
    //depth 2
    ene.push_back(5.1839e-01); ene.push_back( 4.6375e-03); ene.push_back(4.6444e-03);
    //depth 3
    ene.push_back(4.9995e-01); ene.push_back( 3.4921e-03); ene.push_back(3.4351e-03);
    //depth 4
    ene.push_back(4.5068e-01); ene.push_back( 2.9124e-03); ene.push_back(2.8988e-03);
    //depth 5
    ene.push_back(6.9610e-01); ene.push_back( 3.9662e-03); ene.push_back(3.9454e-03);
    //depth 6
    ene.push_back(6.2338e-01); ene.push_back( 3.9660e-03); ene.push_back(3.9114e-03);
    //ivertex 1
    //depth 1
    ene.push_back(1.2935e-01); ene.push_back( 7.2845e-03); ene.push_back(7.9562e-03);
    //depth 2
    ene.push_back(4.9898e-01); ene.push_back( 1.1345e-02); ene.push_back(1.1241e-02);
    //depth 3
    ene.push_back(4.7654e-01); ene.push_back( 8.8864e-03); ene.push_back(8.6008e-03);
    //depth 4
    ene.push_back(4.6432e-01); ene.push_back( 8.5630e-03); ene.push_back(8.3411e-03);
    //depth 5
    ene.push_back(6.8533e-01); ene.push_back( 1.0502e-02); ene.push_back(1.0306e-02);
    //depth 6
    ene.push_back(6.1386e-01); ene.push_back( 1.0673e-02); ene.push_back(1.0477e-02);
    //ivertex 2
    //depth 1
    ene.push_back(1.3023e-01); ene.push_back( 5.0871e-03); ene.push_back(5.2690e-03);
    //depth 2
    ene.push_back(5.0257e-01); ene.push_back( 7.0669e-03); ene.push_back(7.0755e-03);
    //depth 3
    ene.push_back(4.9491e-01); ene.push_back( 5.2554e-03); ene.push_back(5.1946e-03);
    //depth 4
    ene.push_back(4.4185e-01); ene.push_back( 4.3270e-03); ene.push_back(4.2983e-03);
    //depth 5
    ene.push_back(7.0217e-01); ene.push_back( 6.2346e-03); ene.push_back(6.1829e-03);
    //depth 6
    ene.push_back(6.1991e-01); ene.push_back( 6.0120e-03); ene.push_back(5.9810e-03);
    //ivertex 3
    //depth 1
    ene.push_back(1.3205e-01); ene.push_back( 7.1386e-03); ene.push_back(7.6333e-03);
    //depth 2
    ene.push_back(5.3594e-01); ene.push_back( 9.0427e-03); ene.push_back(9.0713e-03);
    //depth 3
    ene.push_back(5.0536e-01); ene.push_back( 6.5718e-03); ene.push_back(6.5204e-03);
    //depth 4
    ene.push_back(4.5442e-01); ene.push_back( 5.4184e-03); ene.push_back(5.3736e-03);
    //depth 5
    ene.push_back(6.9706e-01); ene.push_back( 7.3103e-03); ene.push_back(7.2594e-03);
    //depth 6
    ene.push_back(6.3886e-01); ene.push_back( 7.3871e-03); ene.push_back(7.2784e-03);
    //ivertex 4
    //depth 1
    ene.push_back(1.5632e-01); ene.push_back( 2.0395e-02); ene.push_back(8.6295e-03);
    //depth 2
    ene.push_back(5.5780e-01); ene.push_back( 1.2656e-02); ene.push_back(1.2596e-02);
    //depth 3
    ene.push_back(5.2933e-01); ene.push_back( 9.8608e-03); ene.push_back(9.8081e-03);
    //depth 4
    ene.push_back(4.5960e-01); ene.push_back( 7.9881e-03); ene.push_back(7.8838e-03);
    //depth 5
    ene.push_back(6.8698e-01); ene.push_back( 1.0101e-02); ene.push_back(9.9718e-03);
    //depth 6
    ene.push_back(6.1401e-01); ene.push_back( 1.0709e-02); ene.push_back(1.0578e-02);
    //ieta 22
    //ivertex 0
    //depth 1
    ene.push_back(1.3356e-01); ene.push_back( 4.0103e-03); ene.push_back(4.0874e-03);
    //depth 2
    ene.push_back(5.6582e-01); ene.push_back( 5.3580e-03); ene.push_back(5.3677e-03);
    //depth 3
    ene.push_back(4.9375e-01); ene.push_back( 3.4625e-03); ene.push_back(3.4389e-03);
    //depth 4
    ene.push_back(4.2379e-01); ene.push_back( 2.8151e-03); ene.push_back(2.7876e-03);
    //depth 5
    ene.push_back(6.6681e-01); ene.push_back( 3.8090e-03); ene.push_back(3.7794e-03);
    //depth 6
    ene.push_back(5.5573e-01); ene.push_back( 3.2783e-03); ene.push_back(3.2591e-03);
    //ivertex 1
    //depth 1
    ene.push_back(1.2467e-01); ene.push_back( 7.7192e-03); ene.push_back(8.5047e-03);
    //depth 2
    ene.push_back(5.2773e-01); ene.push_back( 1.2419e-02); ene.push_back(1.2350e-02);
    //depth 3
    ene.push_back(4.8864e-01); ene.push_back( 8.1983e-03); ene.push_back(8.0615e-03);
    //depth 4
    ene.push_back(4.2404e-01); ene.push_back( 6.8962e-03); ene.push_back(6.8328e-03);
    //depth 5
    ene.push_back(6.6364e-01); ene.push_back( 9.5321e-03); ene.push_back(9.3932e-03);
    //depth 6
    ene.push_back(5.9056e-01); ene.push_back( 8.8984e-03); ene.push_back(8.7155e-03);
    //ivertex 2
    //depth 1
    ene.push_back(1.3301e-01); ene.push_back( 5.7399e-03); ene.push_back(5.9295e-03);
    //depth 2
    ene.push_back(5.6357e-01); ene.push_back( 7.9370e-03); ene.push_back(7.9730e-03);
    //depth 3
    ene.push_back(4.9207e-01); ene.push_back( 5.4616e-03); ene.push_back(5.4218e-03);
    //depth 4
    ene.push_back(4.1856e-01); ene.push_back( 4.2924e-03); ene.push_back(4.2661e-03);
    //depth 5
    ene.push_back(6.6647e-01); ene.push_back( 5.9384e-03); ene.push_back(5.9225e-03);
    //depth 6
    ene.push_back(5.5143e-01); ene.push_back( 5.0111e-03); ene.push_back(4.9740e-03);
    //ivertex 3
    //depth 1
    ene.push_back(1.6385e-01); ene.push_back( 4.9067e-03); ene.push_back(5.1188e-03);
    //depth 2
    ene.push_back(5.7078e-01); ene.push_back( 1.0508e-02); ene.push_back(1.0652e-02);
    //depth 3
    ene.push_back(4.9801e-01); ene.push_back( 6.5378e-03); ene.push_back(6.4809e-03);
    //depth 4
    ene.push_back(4.2912e-01); ene.push_back( 5.4405e-03); ene.push_back(5.4085e-03);
    //depth 5
    ene.push_back(6.7145e-01); ene.push_back( 6.9906e-03); ene.push_back(6.9117e-03);
    //depth 6
    ene.push_back(5.5360e-01); ene.push_back( 6.0409e-03); ene.push_back(5.9836e-03);
    //ivertex 4
    //depth 1
    ene.push_back(1.4536e-01); ene.push_back( 1.3324e-02); ene.push_back(1.3580e-02);
    //depth 2
    ene.push_back(6.1765e-01); ene.push_back( 1.7099e-02); ene.push_back(1.9083e-02);
    //depth 3
    ene.push_back(4.9662e-01); ene.push_back( 9.3746e-03); ene.push_back(9.3009e-03);
    //depth 4
    ene.push_back(4.3197e-01); ene.push_back( 7.7812e-03); ene.push_back(7.7301e-03);
    //depth 5
    ene.push_back(6.6139e-01); ene.push_back( 1.0499e-02); ene.push_back(1.0363e-02);
    //depth 6
    ene.push_back(5.5551e-01); ene.push_back( 8.9580e-03); ene.push_back(8.9023e-03);
    //ieta 23
    //ivertex 0
    //depth 1
    ene.push_back(1.2360e-01); ene.push_back( 4.3636e-03); ene.push_back(4.4105e-03);
    //depth 2
    ene.push_back(5.8318e-01); ene.push_back( 6.4897e-03); ene.push_back(6.5699e-03);
    //depth 3
    ene.push_back(4.9047e-01); ene.push_back( 3.7691e-03); ene.push_back(3.7553e-03);
    //depth 4
    ene.push_back(4.6917e-01); ene.push_back( 3.1850e-03); ene.push_back(3.1834e-03);
    //depth 5
    ene.push_back(6.7043e-01); ene.push_back( 3.8703e-03); ene.push_back(3.8508e-03);
    //depth 6
    ene.push_back(6.6916e-01); ene.push_back( 3.8567e-03); ene.push_back(3.8607e-03);
    //ivertex 1
    //depth 1
    ene.push_back(1.1193e-01); ene.push_back( 9.1165e-03); ene.push_back(9.4330e-03);
    //depth 2
    ene.push_back(5.1730e-01); ene.push_back( 1.2383e-02); ene.push_back(1.2483e-02);
    //depth 3
    ene.push_back(4.6636e-01); ene.push_back( 8.3686e-03); ene.push_back(8.2802e-03);
    //depth 4
    ene.push_back(4.4799e-01); ene.push_back( 7.5750e-03); ene.push_back(7.5085e-03);
    //depth 5
    ene.push_back(6.7044e-01); ene.push_back( 9.4598e-03); ene.push_back(9.4155e-03);
    //depth 6
    ene.push_back(6.5374e-01); ene.push_back( 9.6273e-03); ene.push_back(9.5155e-03);
    //ivertex 2
    //depth 1
    ene.push_back(1.2275e-01); ene.push_back( 6.6428e-03); ene.push_back(6.7433e-03);
    //depth 2
    ene.push_back(5.7733e-01); ene.push_back( 9.6898e-03); ene.push_back(9.8479e-03);
    //depth 3
    ene.push_back(4.9207e-01); ene.push_back( 5.9006e-03); ene.push_back(5.8732e-03);
    //depth 4
    ene.push_back(4.6692e-01); ene.push_back( 4.9068e-03); ene.push_back(4.8971e-03);
    //depth 5
    ene.push_back(6.7111e-01); ene.push_back( 5.9974e-03); ene.push_back(5.9571e-03);
    //depth 6
    ene.push_back(6.6992e-01); ene.push_back( 5.9654e-03); ene.push_back(5.9168e-03);
    //ivertex 3
    //depth 1
    ene.push_back(1.5762e-01); ene.push_back( 7.3522e-03); ene.push_back(7.8811e-03);
    //depth 2
    ene.push_back(6.1223e-01); ene.push_back( 1.3306e-02); ene.push_back(1.3586e-02);
    //depth 3
    ene.push_back(5.0162e-01); ene.push_back( 7.4325e-03); ene.push_back(7.3905e-03);
    //depth 4
    ene.push_back(4.8738e-01); ene.push_back( 6.2263e-03); ene.push_back(6.1688e-03);
    //depth 5
    ene.push_back(6.7440e-01); ene.push_back( 7.3993e-03); ene.push_back(7.3447e-03);
    //depth 6
    ene.push_back(6.6730e-01); ene.push_back( 7.3483e-03); ene.push_back(7.2826e-03);
    //ivertex 4
    //depth 1
    ene.push_back(1.2399e-01); ene.push_back( 1.6173e-02); ene.push_back(1.7963e-02);
    //depth 2
    ene.push_back(6.4707e-01); ene.push_back( 2.1552e-02); ene.push_back(2.2071e-02);
    //depth 3
    ene.push_back(4.9804e-01); ene.push_back( 1.0596e-02); ene.push_back(1.0502e-02);
    //depth 4
    ene.push_back(4.6574e-01); ene.push_back( 8.5811e-03); ene.push_back(8.4858e-03);
    //depth 5
    ene.push_back(6.6031e-01); ene.push_back( 1.0324e-02); ene.push_back(1.0238e-02);
    //depth 6
    ene.push_back(6.8714e-01); ene.push_back( 1.0403e-02); ene.push_back(1.0288e-02);
    //ieta 24
    //ivertex 0
    //depth 1
    ene.push_back(1.5459e-01); ene.push_back( 5.4168e-03); ene.push_back(5.5115e-03);
    //depth 2
    ene.push_back(6.3607e-01); ene.push_back( 8.6977e-03); ene.push_back(8.7687e-03);
    //depth 3
    ene.push_back(4.6781e-01); ene.push_back( 4.0465e-03); ene.push_back(4.0432e-03);
    //depth 4
    ene.push_back(4.6881e-01); ene.push_back( 3.4607e-03); ene.push_back(3.4301e-03);
    //depth 5
    ene.push_back(7.2288e-01); ene.push_back( 4.5422e-03); ene.push_back(4.5962e-03);
    //depth 6
    ene.push_back(6.3479e-01); ene.push_back( 3.8705e-03); ene.push_back(3.8641e-03);
    //ivertex 1
    //depth 1
    ene.push_back(1.1779e-01); ene.push_back( 1.0520e-02); ene.push_back(1.1135e-02);
    //depth 2
    ene.push_back(5.5115e-01); ene.push_back( 1.7596e-02); ene.push_back(1.8135e-02);
    //depth 3
    ene.push_back(4.4734e-01); ene.push_back( 8.9101e-03); ene.push_back(8.7614e-03);
    //depth 4
    ene.push_back(4.6908e-01); ene.push_back( 7.8157e-03); ene.push_back(7.7352e-03);
    //depth 5
    ene.push_back(7.2896e-01); ene.push_back( 1.1259e-02); ene.push_back(1.1164e-02);
    //depth 6
    ene.push_back(6.3796e-01); ene.push_back( 9.8741e-03); ene.push_back(9.7525e-03);
    //ivertex 2
    //depth 1
    ene.push_back(1.4223e-01); ene.push_back( 7.6162e-03); ene.push_back(7.8441e-03);
    //depth 2
    ene.push_back(6.1036e-01); ene.push_back( 1.1930e-02); ene.push_back(1.2123e-02);
    //depth 3
    ene.push_back(4.7031e-01); ene.push_back( 6.0917e-03); ene.push_back(6.0606e-03);
    //depth 4
    ene.push_back(4.6465e-01); ene.push_back( 5.2209e-03); ene.push_back(5.2044e-03);
    //depth 5
    ene.push_back(7.2302e-01); ene.push_back( 6.9529e-03); ene.push_back(6.9167e-03);
    //depth 6
    ene.push_back(6.2880e-01); ene.push_back( 5.9732e-03); ene.push_back(5.9883e-03);
    //ivertex 3
    //depth 1
    ene.push_back(1.8548e-01); ene.push_back( 1.0116e-02); ene.push_back(1.0454e-02);
    //depth 2
    ene.push_back(7.0781e-01); ene.push_back( 1.7842e-02); ene.push_back(1.7846e-02);
    //depth 3 
    ene.push_back(4.7179e-01); ene.push_back( 8.3048e-03); ene.push_back(8.3049e-03); 
    //depth 4 
    ene.push_back(4.7947e-01); ene.push_back( 7.1061e-03); ene.push_back(7.0903e-03); 
    //depth 5 
    ene.push_back(7.1288e-01); ene.push_back( 8.8044e-03); ene.push_back(8.7301e-03); 
    //depth 6 
    ene.push_back(6.3690e-01); ene.push_back( 7.1564e-03); ene.push_back(7.1121e-03); 
    //ivertex 4 
    //depth 1 
    ene.push_back(2.3373e-01); ene.push_back( 1.9061e-02); ene.push_back(1.9153e-02); 
    //depth 2 
    ene.push_back(7.2940e-01); ene.push_back( 3.6432e-02); ene.push_back(3.8235e-02); 
    //depth 3 
    ene.push_back(4.8215e-01); ene.push_back( 1.2419e-02); ene.push_back(1.2254e-02); 
    //depth 4 
    ene.push_back(4.6040e-01); ene.push_back( 9.3186e-03); ene.push_back(9.2485e-03); 
    //depth 5 
    ene.push_back(7.3362e-01); ene.push_back( 1.2668e-02); ene.push_back(1.2574e-02); 
    //depth 6 
    ene.push_back(6.4450e-01); ene.push_back( 1.0759e-02); ene.push_back(1.0681e-02); 

*/

  int idepth = 2;

  if(idepth=2){

      //dep1
      //float x1[n]={};
      //float x2[n]={};
      //float x3[n]={};
      //float x4[n]={};

      //dep2
      float x1[n]={13.387,20.683,27.647,36.13};
      float x2[n]={13.553,20.671,27.716,35.97};
      float x3[n]={13.583,20.742,27.689,35.92};
      float x4[n]={13.480,20.657,27.634,35.99};

/*
      //dep3
      float x1[n]={13.564,20.689,27.659,36.13};
      float x2[n]={13.541,20.697,27.733,35.94};
      float x3[n]={13.593,20.736,27.675,35.94};
      float x4[n]={13.516,20.649,27.617,35.96};

      //dep4
      float x1[n]={13.553,20.686,27.667,36.2};
      float x2[n]={13.536,20.698,27.729,35.96};
      float x3[n]={13.584,20.754,27.677,35.94};
      float x4[n]={13.503,20.675,27.626,36.00};

      //dep5
      float x1[n]={13.525,20.69,27.66,36.14};
      float x2[n]={13.548,20.704,27.738,35.93};
      float x3[n]={13.624,20.729,27.685,35.94};
      float x4[n]={13.485,20.664,27.628,35.95};
*/

   //ieta==21
   int ieta=0;
   float  y1[n]  = {ene.at(90*ieta+3*idepth+1*18),  ene.at(90*ieta+3*idepth+2*18),  ene.at(90*ieta+3*idepth+3*18),   ene.at(90*ieta+3*idepth+4*18)};
   float  y1p[n] = {ene.at(90*ieta+3*idepth+1*18+1),ene.at(90*ieta+3*idepth+2*18+1),ene.at(90*ieta+3*idepth+3*18+1), ene.at(90*ieta+3*idepth+4*18+1)};
   float  y1n[n] = {ene.at(90*ieta+3*idepth+1*18+2),ene.at(90*ieta+3*idepth+2*18+2),ene.at(90*ieta+3*idepth+3*18+2), ene.at(90*ieta+3*idepth+4*18+2)};

   //ieta==22
   ieta=1;
   float  y2[n]  = {ene.at(90*ieta+3*idepth+1*18),  ene.at(90*ieta+3*idepth+2*18),  ene.at(90*ieta+3*idepth+3*18),   ene.at(90*ieta+3*idepth+4*18)};
   float  y2p[n] = {ene.at(90*ieta+3*idepth+1*18+1),ene.at(90*ieta+3*idepth+2*18+1),ene.at(90*ieta+3*idepth+3*18+1), ene.at(90*ieta+3*idepth+4*18+1)};
   float  y2n[n] = {ene.at(90*ieta+3*idepth+1*18+2),ene.at(90*ieta+3*idepth+2*18+2),ene.at(90*ieta+3*idepth+3*18+2), ene.at(90*ieta+3*idepth+4*18+2)};

   //ieta==23
   ieta=2;
   float  y3[n]  = {ene.at(90*ieta+3*idepth+1*18),  ene.at(90*ieta+3*idepth+2*18),  ene.at(90*ieta+3*idepth+3*18),   ene.at(90*ieta+3*idepth+4*18)};
   float  y3p[n] = {ene.at(90*ieta+3*idepth+1*18+1),ene.at(90*ieta+3*idepth+2*18+1),ene.at(90*ieta+3*idepth+3*18+1), ene.at(90*ieta+3*idepth+4*18+1)};
   float  y3n[n] = {ene.at(90*ieta+3*idepth+1*18+2),ene.at(90*ieta+3*idepth+2*18+2),ene.at(90*ieta+3*idepth+3*18+2), ene.at(90*ieta+3*idepth+4*18+2)};

   //ieta==24
   ieta=3;
   float  y4[n]  = {ene.at(90*ieta+3*idepth+1*18),  ene.at(90*ieta+3*idepth+2*18),  ene.at(90*ieta+3*idepth+3*18),   ene.at(90*ieta+3*idepth+4*18)};
   float  y4p[n] = {ene.at(90*ieta+3*idepth+1*18+1),ene.at(90*ieta+3*idepth+2*18+1),ene.at(90*ieta+3*idepth+3*18+1), ene.at(90*ieta+3*idepth+4*18+1)};
   float  y4n[n] = {ene.at(90*ieta+3*idepth+1*18+2),ene.at(90*ieta+3*idepth+2*18+2),ene.at(90*ieta+3*idepth+3*18+2), ene.at(90*ieta+3*idepth+4*18+2)};

   TF1 *f1 = new TF1("f1","pol1",0,40);

   TGraph *gr4 = new TGraphAsymmErrors(n,x4,y4,xn,xp,y4n,y4p);
   gr4->Fit("f1","R");
   gr4->GetFunction("f1")->SetLineColor(2);
   gr4->SetLineColor(2);
   gr4->SetLineWidth(4);
   gr4->SetMarkerColor(2);
   gr4->SetMarkerStyle(21);
   //gr->GetXaxis()->SetTitle("depth");
   //gr->GetYaxis()->SetTitle("energy [GeV]");
   //gr->Draw("P");


   TGraph *gr1 = new TGraphAsymmErrors(n,x1,y1,xn,xp,y1n,y1p);
   gr1->Fit("f1","R");
   gr1->GetFunction("f1")->SetLineColor(4);
   gr1->SetLineColor(4);
   gr1->SetLineWidth(4);
   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(21);

   TGraph *gr2 = new TGraphAsymmErrors(n,x2,y2,xn,xp,y2n,y2p);
   gr2->Fit("f1","R");
   gr2->GetFunction("f1")->SetLineColor(3);
   gr2->SetLineColor(3);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(3);
   gr2->SetMarkerStyle(21);

   TGraph *gr3 = new TGraphAsymmErrors(n,x3,y3,xn,xp,y3n,y3p);
   gr3->Fit("f1","R");
   gr3->GetFunction("f1")->SetLineColor(1);
   gr3->SetLineColor(1);
   gr3->SetLineWidth(4);
   gr3->SetMarkerColor(1);
   gr3->SetMarkerStyle(21);


   TMultiGraph *mg = new TMultiGraph();
mg->Add(gr1);
mg->Add(gr2);
mg->Add(gr3);
mg->Add(gr4);
mg->Draw("AP");
  
  mg->GetXaxis()->SetTitle("Average Nvertex");
   mg->GetYaxis()->SetTitle("Energy [GeV]");
   mg->GetXaxis()->SetLimits(0.,40.);
   if(idepth==0) mg->GetYaxis()->SetRangeUser(0.0,0.5);
   else if(idepth==1) mg->GetYaxis()->SetRangeUser(0.3,1.);
   else if(idepth==2 || idepth==3) mg->GetYaxis()->SetRangeUser(0.3,0.8);
   else mg->GetYaxis()->SetRangeUser(0.5,1.0);
   //depth2
   //mg->GetYaxis()->SetRangeUser(0.4,1.2);
   //depth1
   //mg->GetYaxis()->SetRangeUser(0.,0.8);

  TLegend *legend = new TLegend(0.15,0.65,0.55,0.90);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->AddEntry(gr1, "ieta = 21", "L");
    legend->AddEntry(gr2, "ieta = 22", "L");
    legend->AddEntry(gr3, "ieta = 23", "L");
    legend->AddEntry(gr4, "ieta = 24", "L");
    legend->Draw("same");

  system("mkdir -vp "+path);
  c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.png", path.Data(), idepth+1));
  c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.pdf", path.Data(), idepth+1));
  c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.eps", path.Data(), idepth+1));

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->Modified();
  }
}
