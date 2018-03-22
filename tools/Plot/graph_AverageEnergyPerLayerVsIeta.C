//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Internal";
//TString extraText   = "Preliminary";
TString lumiText = "5.9 fb^{-1} (13 TeV)";
//TString lumiText = "35.9 fb^{-1} (13 TeV)";
//TString lumiText = "Simulation (13 TeV)";

bool AddCMS( TCanvas* C );

using namespace RooFit ;
using namespace std ;

void graph_AverageEnergyPerLayerVsIeta(){

        TString rtfilename = "/afs/cern.ch/user/j/jmao/public/HCalMipCali/Plots/test_tree10/out.root";

        TFile rtFile(rtfilename);
        TTree* outtree = (TTree*)rtFile.Get("outtree");

        long nentries = outtree->GetEntries();
        std::cout << "nentries: "<< nentries <<"\n" << std::endl;
        
        int ieta, vtxbin, idepth;
        float pos_mean, pos_errhigh, pos_errlow;
  
        outtree->SetBranchAddress("ieta", &ieta);
        outtree->SetBranchAddress("vtxbin", &vtxbin);
        outtree->SetBranchAddress("idepth", &idepth);
        outtree->SetBranchAddress("pos_mean", &pos_mean);
        outtree->SetBranchAddress("pos_errhigh", &pos_errhigh);
        outtree->SetBranchAddress("pos_errlow", &pos_errlow);


        //************************************************************************************//
        int num_ieta, Vtxbin;
        num_ieta = 9; //ieta[18,26]
        Vtxbin = 0; //all vtx

        //int Ieta[num_ieta];
        float Ieta[num_ieta];
        memset(Ieta,0.,sizeof(Ieta));

        vector<int> vec_num_idepth;
        int num_idepth, max_num_idepth;
        max_num_idepth = 7;
        
        float Depth[num_ieta][max_num_idepth];
        float Depth_n[num_ieta][max_num_idepth];
        float Depth_p[num_ieta][max_num_idepth];

        float Layer[num_ieta][max_num_idepth];

        float Pos_mean[num_ieta][max_num_idepth], Pos_errhigh[num_ieta][max_num_idepth], Pos_errlow[num_ieta][max_num_idepth];
        
        float EdepPerLayer_mean[num_ieta][max_num_idepth], EdepPerLayer_errhigh[num_ieta][max_num_idepth], EdepPerLayer_errlow[num_ieta][max_num_idepth];
        
        float AverageEdepPerLayer[num_ieta];
        float Weight[num_ieta][max_num_idepth];

        memset(Depth,0.,sizeof(Depth));
        memset(Depth_n,0.,sizeof(Depth_n));
        memset(Depth_p,0.,sizeof(Depth_p));

        memset(Layer,0.,sizeof(Layer));

        memset(Pos_mean,0.,sizeof(Pos_mean));
        memset(Pos_errhigh,0.,sizeof(Pos_errhigh));
        memset(Pos_errlow,0.,sizeof(Pos_errlow));

        memset(EdepPerLayer_mean,0.,sizeof(EdepPerLayer_mean));
        memset(EdepPerLayer_errhigh,0.,sizeof(EdepPerLayer_errhigh));
        memset(EdepPerLayer_errlow,0.,sizeof(EdepPerLayer_errlow));

        memset(AverageEdepPerLayer,0.,sizeof(AverageEdepPerLayer));
        memset(Weight,0.,sizeof(Weight));

        //Get Pos Info
        for(int iEntry=0;iEntry<nentries;iEntry++){

                outtree->GetEntry(iEntry);

                for(int i=0; i<num_ieta; i++)
                {
                
                        Ieta[i] = 18 + i;
                        if(Ieta[i]==18) num_idepth = 5;
                        else if(Ieta[i]==26) num_idepth = 7;
                        else num_idepth = 6;

                        vec_num_idepth.push_back(num_idepth);
                        //std::cout << "i = " << i << " , num_idepth = " << vec_num_idepth.at(i)  << endl;

                        //if(iEntry==0) std::cout << "i = " << i << " , num_idepth = " << vec_num_idepth.at(i)  << endl;

                        for(int j=0; j<int(vec_num_idepth.at(i)); j++)
                        {
                                Depth[i][j] = 1 + j;
                                //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j]  << endl;

                                //if(iEntry==0) std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j]  << endl;
                               
                                //if(ieta==Ieta[i] && idepth==Depth[i][j] && vtxbin==Vtxbin && Pos_mean[i][j]==0)
                                if(ieta==18+i && idepth==1+j && vtxbin==0)
                                {
                                        Pos_mean[i][j] = pos_mean;
                                        Pos_errhigh[i][j] = pos_errhigh;
                                        Pos_errlow[i][j] = pos_errlow;
                                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , mean = " << pos_mean  << endl;
                                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << Pos_mean[i][j]  << endl;
                                }//end of if

                        }//end of loop over idepth

                }//end of loop over ieta

        }// end of loop over events

        for(int i=0; i<num_ieta; i++)
        {
                //std::cout << "i = " << i << " , num_idepth = " << vec_num_idepth.at(i)  << endl;
                for(int j=0; j<int(vec_num_idepth.at(i)); j++)
                {
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j]  << endl;

                        //depth 1
                        Layer[i][0] = 1;

                        //depth 2
                        if(Ieta[i]!=26) 
                                Layer[i][1] = 3;
                        else
                                Layer[i][1] = 2;

                        //depth 3
                        if(Ieta[i]==18)
                               Layer[i][2] = 4;
                        else if(Ieta[i]==26)
                               Layer[i][2] = 2;
                        else
                               Layer[i][2] = 3;

                        //depth 4
                        if(Ieta[i]!=26) 
                                Layer[i][3] = 3;
                        else
                                Layer[i][3] = 2;

                        //depth 5
                        if(Ieta[i]==18)
                               Layer[i][4] = 4.5;
                        else if(Ieta[i]==26)
                               Layer[i][4] = 3;
                        else
                               Layer[i][4] = 4;

                        //depth 6
                        if(j==5)
                                Layer[i][5] = 4;

                        //depth 7
                        if(j==6)
                                Layer[i][6] = 4; 
                        
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , layer = " << Layer[i][j] << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << Pos_mean[i][j]  << endl;
                }
        }

        for(int i=0; i<num_ieta; i++)
        {
                 //std::cout << "i = " << i << " , num_idepth = " << vec_num_idepth.at(i)  << endl;
                for(int j=0; j<int(vec_num_idepth.at(i)); j++)
                {
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j]  << endl;

                        EdepPerLayer_mean[i][j] = Pos_mean[i][j] / Layer[i][j] ;
                        //EdepPerLayer_errhigh[i][j] = Pos_errhigh[i][j] / Layer[i][j] ;
                        //EdepPerLayer_errlow[i][j] = Pos_errlow[i][j] / Layer[i][j] ;
                        
                        if(i==7 && j==0)
                        { 
                                EdepPerLayer_errhigh[7][0] = 0.65 / Layer[i][j] ;
                                EdepPerLayer_errlow[7][0] = 0.65 / Layer[i][j] ;
                        }
                        else
                        {
                                EdepPerLayer_errhigh[i][j] = Pos_errhigh[i][j] / Layer[i][j] ;
                                EdepPerLayer_errlow[i][j] = Pos_errlow[i][j] / Layer[i][j] ;
                        }
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , layer = " << Layer[i][j] << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << Pos_mean[i][j]  << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << EdepPerLayer_mean[i][j]  << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << EdepPerLayer_mean[i][j] << " , Errhigh = " << EdepPerLayer_errhigh[i][j] << " , Errlow = " << EdepPerLayer_errlow[i][j]   << endl;
                }
        }

        float Weight_sum = 0.;
        float Temp_sum = 0.;

        for(int i=0; i<num_ieta; i++)
        {
                std::cout << "i = " << i << " , num_idepth = " << vec_num_idepth.at(i)  << endl;
                Weight_sum = 0.;
                Temp_sum = 0.;
                for(int j=0; j<int(vec_num_idepth.at(i)); j++)
                {
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j]  << endl;
/*
                        EdepPerLayer_mean[i][j] = Pos_mean[i][j] / Layer[i][j] ;

                        if(i==7 && j==0)
                        { 
                                EdepPerLayer_errhigh[7][0] = 0.65 / Layer[i][j] ;
                                EdepPerLayer_errlow[7][0] = 0.65 / Layer[i][j] ;
                        }
                        else
                        {
                                EdepPerLayer_errhigh[i][j] = Pos_errhigh[i][j] / Layer[i][j] ;
                                EdepPerLayer_errlow[i][j] = Pos_errlow[i][j] / Layer[i][j] ;
                        }
*/
                        Weight[i][j] = TMath::Power(EdepPerLayer_errhigh[i][j] + EdepPerLayer_errlow[i][j], -2);

                        Weight_sum += Weight[i][j];
                        Temp_sum += EdepPerLayer_mean[i][j] * Weight[i][j];
                        
                        
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , layer = " << Layer[i][j] << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << Pos_mean[i][j]  << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << EdepPerLayer_mean[i][j]  << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << EdepPerLayer_mean[i][j] << " , Errhigh = " << EdepPerLayer_errhigh[i][j] << " , Errlow = " << EdepPerLayer_errlow[i][j]   << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Mean = " << EdepPerLayer_mean[i][j] << " , Errhigh = " << EdepPerLayer_errhigh[i][j] << " , Errlow = " << EdepPerLayer_errlow[i][j] << " , Weight = " << Weight[i][j]  << endl;
                        //std::cout << "ieta = " << Ieta[i] << " , idepth = " << Depth[i][j] << " , Weight = " << Weight[i][j] << " , Weight_sum = " << Weight_sum << " , Temp_sum = " << Temp_sum  << endl;
                }

                AverageEdepPerLayer[i] = Temp_sum / Weight_sum;
                std::cout << "i = " << i << " , average = " << AverageEdepPerLayer[i]  << endl;
        }


        TGraph *gr = new TGraph(num_ieta,Ieta,AverageEdepPerLayer);
        gr->SetLineColor(9);
        gr->SetLineWidth(4);
        gr->SetMarkerColor(9);
        gr->SetMarkerStyle(21);

        //************************************************************************************//

        TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

        TMultiGraph *mg = new TMultiGraph();
        mg->Add(gr);
        mg->Draw("ALP");
  
        mg->GetXaxis()->SetTitle("Ieta");
        mg->GetYaxis()->SetTitle("AverageEnergy [GeV] / layer");
        mg->GetXaxis()->SetLimits(17.,27.);
        mg->GetYaxis()->SetRangeUser(0.,0.4);

        TLegend *legend = new TLegend(0.15,0.65,0.55,0.90);
        legend->SetBorderSize(0);
        legend->SetTextFont(42);
        legend->SetTextSize(0.04);
        legend->SetFillStyle(0);
        legend->SetFillColor(0);
        legend->SetLineColor(0);
        legend->AddEntry(gr, "Average", "L");
        //legend->Draw("same");

        //system("mkdir -vp "+path);
        c1->SaveAs("Average_Energy_per_layer_vs_depth.png");
        c1->SaveAs("Average_Energy_per_layer_vs_depth.pdf");
        c1->SaveAs("Average_Energy_per_layer_vs_depth.eps");
        //c1->SaveAs(Form("%s/NoIso_test_pileupCorr_depth%d.eps", path.Data(), d));

        // TCanvas::Update() draws the frame, after which one can change it
        c1->Update();
        c1->Modified();
       
}

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.905;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.185;
  float cmsy = 0.940;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.118;
  float extray = cmsy;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);
   
  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};
