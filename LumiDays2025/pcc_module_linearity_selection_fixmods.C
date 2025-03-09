#include "common.C"


float scalePCC=1;//261;//its the number of modules in the sample to recover the total PCC for all modules
float PCCRangeLow=1.5*scalePCC;
float PCCRange=5*scalePCC;
float WRangeLow=0.98;//4e-3;
float WRange=1.03;//7e-3;
float QRange=0.01;


TString inputfile="./briltdr/LumiDays2025/PerModuleStability_veto_all_Blocks_Lty_fixExampleModules.root";
TString mod1name="Filter_306196508";
TString mod2name="Filter_305188868";
float mod1W=290E-5;
float mod2W=443E-5;




TGraphErrors* getGraph(TFile*F,TString name,int color=1, int rebin=0, float scale=1){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TGraphErrors*G=(TGraphErrors*)F->Get(name);
  if(!G){cout<<name<<" not found"<<endl; return 0;}

  TGraphErrors*GR=new TGraphErrors();
  for(int i=1;i<=G->GetN();i++){
    GR->SetPoint(i,G->GetPointX(i),scale*G->GetPointY(i));
    GR->SetPointError(i,0,scale*G->GetErrorY(i));
  }


//  if(rebin%2!=0){cout<<" rebin parameter must be even"<<endl; return 0;}
//  
//  TGraph*GR=new TGraph();
//  int i=1;
//  while(i<G->GetN()){
//    if(rebin==6){
//      GR->SetPoint(GR->GetN(),
//		   (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3)+G->GetPointX(i+4)+G->GetPointX(i+5))/6,
//		   (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3)+G->GetPointY(i+4)+G->GetPointY(i+5))/6);
//      i+=6;
//    }else if(rebin==4){
//      GR->SetPoint(GR->GetN(),
//		  (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3))/4,
//		  (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3))/4);
//      i+=4;
//    }else if(rebin==2){
//      GR->SetPoint(GR->GetN(),
//		  (G->GetPointX(i)+G->GetPointX(i+1))/2,
//		  (G->GetPointY(i)+G->GetPointY(i+1))/2);
//      i+=2;
//    }else{
//      GR->SetPoint(GR->GetN(),G->GetPointX(i),G->GetPointY(i));
//      i++;
//    }
//  }
  
  
  GR->SetMarkerColor(color);
  GR->SetLineColor(color);
  GR->SetMarkerStyle(8);
  GR->SetMarkerSize(0.6);
  
  return GR;
}


void pcc_module_linearity_selection_fixmods(){
  setTDRStyle();
 
  TFile F(inputfile.Data());
  if(F.IsZombie()) return;


  ///Plot 1: 
  TGraph* module1=getGraph(&F,mod1name,1,0,1);
  if(!module1){cout<<"No module1"<<endl; return;}
  
  TGraph* module2=getGraph(&F,mod2name,4,0,1);
  if(!module2){cout<<"No module2"<<endl; return;}

  TF1* Fit=new TF1("Fit","[0]+[1]*x",PCCRangeLow,PCCRange);
  TGraph*module1C=(TGraph*)module1->Clone("module1C");
  module1C->Fit(Fit);

  
  TF1 F1("F1","[0]+[1]*x",PCCRangeLow,PCCRange);
  F1.SetParameters(Fit->GetParameter(0),Fit->GetParameter(1));
  F1.SetLineColor(1);
  F1.SetLineWidth(2);
  
  TGraph*module2C=(TGraph*)module2->Clone("module2C");
  module2C->Fit(Fit);
  TF1 F2("F2","[0]+[1]*x",PCCRangeLow,PCCRange);
  F2.SetParameters(Fit->GetParameter(0),Fit->GetParameter(1));
  F2.SetLineColor(4);
  F2.SetLineWidth(2);
  delete Fit;
  delete module1C;
  delete module2C;
  

  char txt[100];
    
  
  TLegend leg(0.4,0.78,0.9,0.90);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  sprintf(txt,"Module 1:  W = %.1fE-3, Q_{L} = %.1fE-3",mod1W*1000,F1.GetParameter(1)*1000);
  leg.AddEntry(module1,txt,"pl");
  sprintf(txt,"Module 2:  W = %.1fE-3, Q_{L} = %.1fE-3",mod2W*1000,F2.GetParameter(1)*1000);
  leg.AddEntry(module2,txt,"pl");

  

  //Plot 1
  lumi_sqrtS ="Fill 10084 (2024, 13.6 TeV)";
  generateCanvas("",PCCRangeLow,PCCRange,"<#mu_{PCC}> per module ", WRangeLow, WRange, "Normalized Fraction of Total PCC");
  module1->Draw("psame");
  module2->Draw("psame");
  F1.DrawClone("lsame");
  F2.DrawClone("lsame");
  
  leg.Draw();
  
  TLine line;
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.SetLineColor(1);
  line.DrawLine(PCCRangeLow,mod1W,PCCRange,mod1W);
  line.SetLineColor(4);
  line.DrawLine(PCCRangeLow,mod2W,PCCRange,mod2W);
  printCanvas("pcc_module_linearity_selection_examplemodule");

  
  ///Plot 2
  TH1F*Q=(TH1F*)F.Get("LinearityDeviation_slope");
  LogY=1;
  //lumi_sqrtS ="2024 (13.6 TeV)";
  lumi_sqrtS ="Fill 10084 (2024, 13.6 TeV)";
  generateCanvas("",-QRange,QRange,"Module Linearity Quality (Q_{L}) ", 0.5, 50, "Number of modules");
  Q->Draw("histsame");
  line.SetLineColor(2);
  //line.DrawLine(0.002,0.5,0.002,20);line.DrawLine(-0.003,0.5,-0.003,20);
  line.DrawLine(0.002,0.5,0.002,20);line.DrawLine(-0.002,0.5,-0.002,20);

  
  TLatex text;
  text.SetTextSize(0.03);
  text.SetTextColor(kBlack);    
  text.SetTextFont(42);
  text.DrawTextNDC(0.75,0.85,TString("Entries: ")+Q->GetEntries());
  sprintf(txt,"Mean: %.4f",Q->GetMean());
  text.DrawTextNDC(0.75,0.81,txt);
  sprintf(txt,"RMS: %.4f",Q->GetRMS());
  text.DrawTextNDC(0.75,0.77,txt);


  printCanvas("pcc_module_linearity_selection_distribution");
}



