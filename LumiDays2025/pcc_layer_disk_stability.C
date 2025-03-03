#include "common.C"

//TString inputfile="/afs/cern.ch/user/l/lcuevasp/public/veto_2024_histograms/Histograms_stability_and_Lienarity_veto_allPeriods.root";
TString inputfile="./briltdr/LumiDays2025/Histograms_stability_and_Lienarity_veto_allPeriods.root";


TGraph* getGraph(TFile*F,TString name,int color=1, int rebin=0, TString namenorm=""){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TProfile*P=(TProfile*)F->Get(name);
  if(!P){cout<<name<<" not found"<<endl; return 0;}

  if(namenorm.CompareTo("")!=0){
    TH2D*H = (TH2D*)F->Get(namenorm);
    if(!H){cout<<namenorm<<" not found "<<endl; return 0;}
    cout<<namenorm<<" mean "<<H->GetMean(2)<<endl;
    P->Scale(1./(float)H->GetMean(2));
  }
  
  //if(rebin>1) P->Rebin(rebin);

  TGraph*G=new TGraph();

  for(int i=1;i<P->GetNbinsX();i++){
    if(P->GetBinContent(i)>0)
      G->SetPoint(G->GetN(),P->GetBinCenter(i),P->GetBinContent(i));
  }

  
  if(rebin%2!=0){cout<<" rebin parameter must be even"<<endl; return 0;}


  TGraph*GR=new TGraph();
  int i=1;
  while(i<G->GetN()){
    if(rebin==6){
      GR->SetPoint(GR->GetN(),
		  (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3)+G->GetPointX(i+4)+G->GetPointX(i+5))/6,
		  (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3)+G->GetPointY(i+4)+G->GetPointY(i+5))/6);
      i+=6;
    }else if(rebin==4){
      GR->SetPoint(GR->GetN(),
		  (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3))/4,
		  (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3))/4);
      i+=4;
    }else if(rebin==2){
      GR->SetPoint(GR->GetN(),
		  (G->GetPointX(i)+G->GetPointX(i+1))/2,
		  (G->GetPointY(i)+G->GetPointY(i+1))/2);
      i+=2;
    }else{
      GR->SetPoint(GR->GetN(),G->GetPointX(i),G->GetPointY(i));
      i++;
    }
  }
  
  
  GR->SetMarkerColor(color);
  GR->SetMarkerStyle(8);
  GR->SetMarkerSize(0.6);
  
  return GR;
}


TGraph* getGraphFPIX(TFile*F,int side,int color=1, int rebin=0, bool norm=0){
  if(!F){cout<<"invalid File"<<endl; return 0;}
  
  TProfile*P=(TProfile*)F->Get(TString("Histo_Disk1S")+side+"_pfx");
  if(!P){cout<<"Disk 1 side "<<side<<" not found"<<endl; return 0;}

  TProfile*P2=(TProfile*)F->Get(TString("Histo_Disk2S")+side+"_pfx");
  if(!P2){cout<<"Disk 2 side "<<side<<" not found"<<endl; return 0;}
 
  TProfile*P3=(TProfile*)F->Get(TString("Histo_Disk3S")+side+"_pfx");
  if(!P3){cout<<"Disk 3 side "<<side<<" not found"<<endl; return 0;}

//  if(rebin>1)P->Rebin(rebin);
//  if(rebin>1)P2->Rebin(rebin);
//  if(rebin>1)P3->Rebin(rebin);

  float ynorm=0.;
  if(norm){
    TH2D*H = (TH2D*)F->Get(TString("Histo_Disk1S")+side);
    if(!H){cout<<" Disk1 norm not found "<<endl; return 0;}
    ynorm+=H->GetMean(2);

    TH2D*H2 = (TH2D*)F->Get(TString("Histo_Disk2S")+side);
    if(!H2){cout<<" Disk2 norm not found "<<endl; return 0;}
    ynorm+=H2->GetMean(2);
    
    TH2D*H3 = (TH2D*)F->Get(TString("Histo_Disk3S")+side);
    if(!H3){cout<<" Disk3 norm not found "<<endl; return 0;}
    ynorm+=H3->GetMean(2);
  }


  TGraph*G=new TGraph();
  for(int i=1;i<P->GetNbinsX();i++){
    float y=0;
    if(P->GetBinContent(i)>0) y+=P->GetBinContent(i);
    if(P2->GetBinContent(i)>0) y+=P2->GetBinContent(i);
    if(P3->GetBinContent(i)>0) y+=P3->GetBinContent(i);

    if(ynorm>0) y/=ynorm;
    
    if(y>0){
      G->SetPoint(G->GetN(),P->GetBinCenter(i),y);
    }
  }


  if(rebin%2!=0){cout<<" rebin parameter must be even"<<endl; return 0;}
  
  TGraph*GR=new TGraph();
  int i=1;
  while(i<G->GetN()){
    if(rebin==6){
      GR->SetPoint(GR->GetN(),
		   (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3)+G->GetPointX(i+4)+G->GetPointX(i+5))/6,
		   (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3)+G->GetPointY(i+4)+G->GetPointY(i+5))/6);
      i+=6;
    }else if(rebin==4){
      GR->SetPoint(GR->GetN(),
		  (G->GetPointX(i)+G->GetPointX(i+1)+G->GetPointX(i+2)+G->GetPointX(i+3))/4,
		  (G->GetPointY(i)+G->GetPointY(i+1)+G->GetPointY(i+2)+G->GetPointY(i+3))/4);
      i+=4;
    }else if(rebin==2){
      GR->SetPoint(GR->GetN(),
		  (G->GetPointX(i)+G->GetPointX(i+1))/2,
		  (G->GetPointY(i)+G->GetPointY(i+1))/2);
      i+=2;
    }else{
      GR->SetPoint(GR->GetN(),G->GetPointX(i),G->GetPointY(i));
      i++;
    }
  }
  
  
  GR->SetMarkerColor(color);
  GR->SetMarkerStyle(8);
  GR->SetMarkerSize(0.6);
  
  return GR;
}



void pcc_layer_disk_stability(){
  setTDRStyle();
 
  TFile F(inputfile);
  if(F.IsZombie()) return;

  int rebin=6;
  
  ///Plot 1
  TGraph* Histo_Layer4_pfx=getGraph(&F,"Histo_Layer4_pfx",1,rebin);
  if(!Histo_Layer4_pfx){cout<<"No Histo_Layer4_pfx"<<endl; return;}

  TGraph* Histo_Layer3_pfx=getGraph(&F,"Histo_Layer3_pfx",2,rebin);
  if(!Histo_Layer3_pfx){cout<<"No Histo_Layer3_pfx"<<endl; return;}

  TGraph* Histo_S1_pfx=getGraphFPIX(&F,1,3,rebin);
  if(!Histo_S1_pfx){cout<<"No FPIX Side 1"<<endl; return;}

  TGraph* Histo_S2_pfx=getGraphFPIX(&F,2,4,rebin);
  if(!Histo_S2_pfx){cout<<"No FPIX Side 2"<<endl; return;}
  
  
  TLegend leg(0.5,0.78,0.7,0.90);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.AddEntry(Histo_Layer4_pfx,"BPIX Layer 4","p");
  leg.AddEntry(Histo_Layer3_pfx,"BPIX Layer 3","p");

  TLegend leg2(0.72,0.78,0.85,0.90);
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
  Histo_S1_pfx->Draw("psame");
  Histo_S2_pfx->Draw("psame");
  leg.Draw();
  leg2.Draw();
  printCanvas("pcc_layer_disk_stability");

  //-----------------------------------------------------------------------------
  //Plot 2
  TGraph* Layer4=getGraph(&F,"Histo_Layer4_pfx",1,rebin,"Histo_Layer4");
  if(!Layer4){cout<<"No Layer4"<<endl; return;}

  TGraph* Layer3=getGraph(&F,"Histo_Layer3_pfx",2,rebin,"Histo_Layer3");
  if(!Layer3){cout<<"No Layer3"<<endl; return;}

  TGraph* S1=getGraphFPIX(&F,1,3,rebin,1);
  if(!S1){cout<<"No FPIX Side 1 norm"<<endl; return;}

  TGraph* S2=getGraphFPIX(&F,2,4,rebin,1);
  if(!S2){cout<<"No FPIX Side 2 norm"<<endl; return;}

  generateCanvas("",0,300e3,"Lumisection", 0.97, 1.06, "Normalized Fraction of Total PCC");
  Layer4->SetStats(0);
  Layer4->Draw("psame");
  Layer3->Draw("psame");
  S1->Draw("psame");
  S2->Draw("psame");
  leg.Draw();
  leg2.Draw();
  TLine line;
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1.01,300e3,1.01);
  line.DrawLine(0,0.99,300e3,0.99);
  printCanvas("pcc_layer_disk_stability_norm");

  
}


