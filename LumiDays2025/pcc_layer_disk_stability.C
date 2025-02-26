#include "common.C"

TGraph* getGraph(TFile*F,TString name,int color=1, int rebin=0){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TProfile*P=(TProfile*)F->Get(name);
  if(!P){cout<<name<<" not found"<<endl; return 0;}
  if(rebin>0)P->Rebin(rebin);
  
  TGraph*G=new TGraph();
  for(int i=1;i<P->GetNbinsX();i++){
    if(P->GetBinContent(i)>0)
      G->SetPoint(G->GetN(),P->GetBinCenter(i),P->GetBinContent(i));
  }
  
  G->SetMarkerColor(color);
  G->SetMarkerStyle(8);
  G->SetMarkerSize(0.6);
  
  return G;
}


TGraph* getGraphFPIX(TFile*F,int side,int color=1, int rebin=0){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TProfile*P=(TProfile*)F->Get(TString("Histo_Disk1S")+side+"_pfx");
  if(!P){cout<<"Disk 1 side "<<side<<" not found"<<endl; return 0;}
  if(rebin>0)P->Rebin(rebin);

  TProfile*P2=(TProfile*)F->Get(TString("Histo_Disk2S")+side+"_pfx");
  if(!P2){cout<<"Disk 2 side "<<side<<" not found"<<endl; return 0;}
  if(rebin>0)P2->Rebin(rebin);

  TProfile*P3=(TProfile*)F->Get(TString("Histo_Disk3S")+side+"_pfx");
  if(!P3){cout<<"Disk 3 side "<<side<<" not found"<<endl; return 0;}
  if(rebin>0)P3->Rebin(rebin);

  TGraph*G=new TGraph();
  for(int i=1;i<P->GetNbinsX();i++){
    float y=0;
    if(P->GetBinContent(i)>0) y+=P->GetBinContent(i);
    if(P2->GetBinContent(i)>0) y+=P2->GetBinContent(i);
    if(P3->GetBinContent(i)>0) y+=P3->GetBinContent(i);
    if(y>0)
      G->SetPoint(G->GetN(),P->GetBinCenter(i),y);
  }
  
  G->SetMarkerColor(color);
  G->SetMarkerStyle(8);
  G->SetMarkerSize(0.6);
  
  return G;
}



void pcc_layer_disk_stability(){
  setTDRStyle();
 
  TFile F("/afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/Histogras_stability_and_Lienarity.root","read");
  if(F.IsZombie()) return;
  
  TGraph* Histo_Layer4_pfx=getGraph(&F,"Histo_Layer4_pfx",1,2);
  if(!Histo_Layer4_pfx){cout<<"No Histo_Layer4_pfx"<<endl; return;}

  TGraph* Histo_Layer3_pfx=getGraph(&F,"Histo_Layer3_pfx",2,2);
  if(!Histo_Layer3_pfx){cout<<"No Histo_Layer3_pfx"<<endl; return;}

  TGraph* Histo_Layer2_pfx=getGraph(&F,"Histo_Layer2_pfx",3,2);
  if(!Histo_Layer2_pfx){cout<<"No Histo_Layer2_pfx"<<endl; return;}
  
  TGraph* Histo_S1_pfx=getGraphFPIX(&F,1,4,2);
  if(!Histo_S1_pfx){cout<<"No FPIX Side 1"<<endl; return;}

  TGraph* Histo_S2_pfx=getGraphFPIX(&F,2,6,2);
  if(!Histo_S2_pfx){cout<<"No FPIX Side 2"<<endl; return;}

  
  TLegend leg(0.5,0.70,0.7,0.90);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.AddEntry(Histo_Layer4_pfx,"BPIX Layer 4","p");
  leg.AddEntry(Histo_Layer3_pfx,"BPIX Layer 3","p");
  leg.AddEntry(Histo_Layer2_pfx,"BPIX Layer 2","p");

  TLegend leg2(0.72,0.77,0.85,0.90);
  leg2.SetFillColor(0);
  leg2.SetLineColor(0);
  leg2.SetFillStyle(0);
  leg2.SetBorderSize(0);
  leg2.AddEntry(Histo_S1_pfx,"FPIX-","p");//Side 1 is - z coordinate
  leg2.AddEntry(Histo_S2_pfx,"FPIX+","p");//Side 2 is + z coordinate
 
  generateCanvas("",0,300e3,"Lumisection", 0.0, 0.8, "Fraction of Total PCC");
  Histo_Layer4_pfx->SetStats(0);
  Histo_Layer4_pfx->Draw("psame");
  Histo_Layer3_pfx->Draw("psame");
  Histo_Layer2_pfx->Draw("psame");
  Histo_S1_pfx->Draw("psame");
  Histo_S2_pfx->Draw("psame");
  leg.Draw();
  leg2.Draw();
  printCanvas("pcc_layer_disk_stability");
 
}


