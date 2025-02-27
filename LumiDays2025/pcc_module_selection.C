#include "common.C"

//TString inputfile="/afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/PerModuleStability_veto_Block5_Sty1_Sty2.root";
//KEY: TH1F	h_modcount_vs_LS708_p;1	Module 306204692 Weight=198E-5 Stability=28E-4
//KEY: TH1F	h_modcount_vs_LS832_p;1	Module 306270212 Weight=162E-5 Stability=300E-4

//TString inputfile="/afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/PerModuleStability_veto_Block1_Sty1.root";
//KEY: TH1F     h_modcount_vs_LS644_p;1 Module 305303572 Weight=77E-5 Stability=49E-4
//KEY: TH1F	h_modcount_vs_LS271_p;1	Module 304177184 Weight=109E-5 Stability=240E-4
//TString mod1name="h_modcount_vs_LS644_p";
//TString mod2name="h_modcount_vs_LS271_p";
//float mod1Q=49E-4; float mod1W=77E-5;
//float mod2Q=240E-4; float mod2W=109E-5;

//TString inputfile="/afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/PerModuleStability_veto_Block1_selection1.root";
TString inputfile="./briltdr/LumiDays2025/PerModuleStability_veto_Block1_selection1.root";
//KEY: TH1F	h_modcount_vs_LS716_p;1	Module 306208788 Weight=35E-5 Stability=69E-4
//KEY: TH1F     h_modcount_vs_LS103_p;1Module 304091168 Weight=82E-5 Stability=974E-4
TString mod1name="h_modcount_vs_LS716_p";
TString mod2name="h_modcount_vs_LS103_p";
float mod1Q=69E-4; float mod1W=35E-5;
float mod2Q=974E-4; float mod2W=82E-5;

int LSRange=22000;
float WRange=150e-5;
float QRange=0.05;

TGraph* getGraph(TFile*F,TString name,int color=1, int rebin=0, float scale=1){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TH1F*P=(TH1F*)F->Get(name);
  if(!P){cout<<name<<" not found"<<endl; return 0;}
  if(rebin>1) P->Rebin(rebin);

  TGraph*G=new TGraph();
  for(int i=1;i<P->GetNbinsX();i++){
    if(P->GetBinContent(i)>0)
      G->SetPoint(G->GetN(),P->GetBinCenter(i),scale*P->GetBinContent(i));
  }
  
  G->SetMarkerColor(color);
  G->SetMarkerStyle(8);
  G->SetMarkerSize(0.6);
  
  return G;
}


void pcc_module_selection(){
  setTDRStyle();
 
  TFile F(inputfile.Data());
  if(F.IsZombie()) return;


  ///Plot 1: 
  TGraph* module1=getGraph(&F,mod1name,1,0,mod1W);
  if(!module1){cout<<"No module1"<<endl; return;}

  TGraph* module2=getGraph(&F,mod2name,4,0,mod2W);
  if(!module2){cout<<"No module2"<<endl; return;}

  TLegend leg(0.45,0.78,0.92,0.90);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  char txt[100];
  sprintf(txt,"Module 1:  W=%.2fE-3,  Q=%.1fE-3",mod1W*1000,mod1Q*1000);
  leg.AddEntry(module1,txt,"p");
  sprintf(txt,"Module 2:  W=%.2fE-3,  Q=%.1fE-3",mod2W*1000,mod2Q*1000);
  leg.AddEntry(module2,txt,"p");

  
  //Plot 1
  generateCanvas("",0,LSRange,"Lumisection", 0.0, WRange, "Fraction of Total PCC");
  module1->Draw("psame");
  module2->Draw("psame");
  leg.Draw();
  TLine line;
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.SetLineColor(1);
  line.DrawLine(0,mod1W,LSRange,mod1W);
  line.SetLineColor(4);
  line.DrawLine(0,mod2W,LSRange,mod2W);
  printCanvas("pcc_module_selection_examplemodule");

  ///Plot 2
  TH1F*Q=(TH1F*)F.Get("StabilityDeviation");
  LogY=1;
  generateCanvas("",0.,QRange,"Module Stability Quality (Q) ", 0.5, 200, "# of modules");
  Q->Draw("histsame");
  line.SetLineColor(2);
  line.DrawLine(0.015,0.5,0.015,50);
  TLatex text;
  text.SetTextSize(0.03);
  text.DrawTextNDC(0.7,0.85,TString("Entries: ")+Q->GetEntries());
  sprintf(txt,"Mean: %.4f",Q->GetMean());
  text.DrawTextNDC(0.7,0.82,txt);
  sprintf(txt,"RMS: %.4f",Q->GetRMS());
  text.DrawTextNDC(0.7,0.79,txt);
  int overflow=0;
  for(int b=1;b<=Q->GetNbinsX();b++)
    if(Q->GetBinCenter(b)>QRange) overflow += Q->GetBinContent(b); 
  sprintf(txt,"Overflow: %d",overflow);
  text.DrawTextNDC(0.7,0.76,txt);
  printCanvas("pcc_module_selection_distribution");
}



