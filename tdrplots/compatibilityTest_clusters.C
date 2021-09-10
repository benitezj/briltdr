
void compatibilityTest_clusters(){

  
  TFile FNew("TEPXLinearityGraphs.root","read");
  TFile FOld("TEPXLinearityGraphs_lowstats.root","read");

  TGraphErrors* GNew=(TGraphErrors*)FNew.Get("Clusters_Dp4R1");
  TGraphErrors* GOld=(TGraphErrors*)FOld.Get("Clusters_Dp4R1");


  TCanvas C;

  C.SetLogx(0);
  C.Clear();
  GNew->Draw("ape");
  GOld->Draw("pesame");
  C.Print("compatibilityTest_clusters_Clusters_Dp4R1.png");
  
  TGraphErrors Ratio;
  for(int i=0;i<GNew->GetN();i++){
    /* float x=GNew->GetX()[i]; */
    /* float y=GNew->GetY()[i]; */
    float yeNew=GNew->GetEY()[i];
    float yeOld=GOld->GetEY()[i]; 
    Ratio.SetPoint(i,GNew->GetX()[i],GOld->GetY()[i] / GNew->GetY()[i]);
    Ratio.SetPointError(i,0,sqrt(yeOld*yeOld) / GNew->GetY()[i] );
  }

  C.SetLogx(1);
  C.Clear();
  Ratio.GetXaxis()->SetTitle("pileup");
  Ratio.GetYaxis()->SetTitle("N_cluster low stats / N_cluster high stats");
  Ratio.GetYaxis()->SetRangeUser(0.95,1.05);
  Ratio.Draw("ape");
  TLine line;
  line.DrawLine(0.4,1,200,1);
  C.Print("compatibilityTest_clusters_Clusters_Dp4R1_ratio.png");
  
  
}
