#include "linearityPlots.C"

void plot_OTrates(){

  TFile FileInput("OT_TDR-23march2021.root");

  TH2F * HOcc = (TH2F*)FileInput.Get("h2dOccupancyRodModBarrelL6");
  if(!HOcc) return;

  int firstmod = 13;//corresponds to first module on +Z side 
  int lastmod  = 25;
  int firstladder = 2;//there is an offset in the binning, total number of ladders is 76
  int lastladder = 77;

  float count=0.;
  
  TH1F HRateVsLadder("HRateVsLadder","",76,0.5,76.5);
     

  for(Int_t j=1;j<=HOcc->GetNbinsY();j++){
    float count_per_ladder = 0.;
    for(Int_t i=1;i<=HOcc->GetNbinsX();i++){
      count += HOcc->GetBinContent(i,j);

      if(i<firstmod || i>lastmod || j<firstladder || j>lastladder) continue;
      count_per_ladder += HOcc->GetBinContent(i,j);
    }
    
    if(j<firstladder || j>lastladder) continue;
    HRateVsLadder.Fill(j,count_per_ladder);
    cout<<"ladder"<<j-1<<"   "<<count_per_ladder<<endl;
  }

  cout<<" total "<<count<<endl;


  ///CMS Style plot of the rates
  setTDRStyle();
  TString plottitle("Outer Tracker Layer 6, +z side");
  HRateVsLadder.SetMarkerStyle(8);
  HRateVsLadder.SetMarkerColor(1);
  generateCanvas(plottitle,0, 77, "TB2S ladder id", 0, 10, "mean number of stubs / bx");
  HRateVsLadder.Draw("histpsame");
  printCanvas("OTRates_perladder",plottitle);
  
  
}
