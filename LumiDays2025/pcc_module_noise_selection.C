#include "common.C"


///afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/PerModuleStability_vetoB0_NoiseVsModule.root
TString inputfile="./briltdr/LumiDays2025/PerModuleStability_vetoB0_NoiseVsModule.root";

float QRangeLow=-5;
float QRange=1;


void pcc_module_noise_selection(){
  setTDRStyle();
 
  TFile F(inputfile.Data());
  if(F.IsZombie()) return;

  TGraph*Q=(TGraph*)F.Get(";1");

  //Plot 1
  lumi_sqrtS ="Fill 9639 (2024, 13.6 TeV)";
  LogY=1;
  generateCanvas("",0,1900,"Module index", 1e-5,10, "#mu_{PCC} for Super Separation periods");
  Q->Draw("psame");
  line.SetLineColor(2);
  line.DrawLine(0,1e-3,1900,1e-3);
  printCanvas("pcc_module_noise_selection");


  
//  TH1F H("H","",100,QRangeLow,QRange);
//  for(int i=1;i<Q->GetN();i++)
//    if(Q->GetPointY(i)>0)
//      H.Fill(log(Q->GetPointY(i)));
//
//  
//  ////PLOT 2
//  LogY=0;
//  generateCanvas("",QRangeLow,QRange,"log(#mu_{PCC})", 0,10, "# of modules");
//  H.Draw("histsame");
//  
//
//  TLatex text;
//  text.SetTextSize(0.03);
//  text.DrawTextNDC(0.7,0.85,TString("Entries: ")+H.GetEntries());
//  char txt[100];
////  sprintf(txt,"Mean: %.4f",Q->GetMean());
////  text.DrawTextNDC(0.7,0.82,txt);
////  sprintf(txt,"RMS: %.4f",Q->GetRMS());
////  text.DrawTextNDC(0.7,0.79,txt);
//  int overflow=0;
//  for(int b=1;b<=H.GetNbinsX();b++)
//    if(H.GetBinCenter(b)>QRange) overflow += H.GetBinContent(b); 
//  sprintf(txt,"Overflow: %d",overflow);
//  text.DrawTextNDC(0.7,0.76,txt);
//  int underflow=0;
//  for(int b=1;b<=H.GetNbinsX();b++)
//    if(H.GetBinCenter(b)<QRangeLow) underflow += H.GetBinContent(b); 
//  sprintf(txt,"Underflow: %d",underflow);
//  text.DrawTextNDC(0.7,0.73,txt);
//  printCanvas("pcc_module_noise_selection_distribution");

}



