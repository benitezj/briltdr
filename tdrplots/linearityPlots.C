#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"


TString pileup="pile-up";//x-axis title for simulation
TLatex text;
TLine line;
TF1 * Fit = NULL;
TCanvas* canv = NULL;
TH1F* hist = NULL;
float residual_range = 5;//%

void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title){
  int iPeriod=0;// uses the lumi_sqrtS string
  int iPos=0;//postion of CMS Preliminary
  
  int W = 800;
  int H = 600;
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;


  canv = new TCanvas(LuminometerName+"_"+x_title+"_"+y_title,"",50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  //canv->SetLogx(1);
  
  hist = new TH1F(LuminometerName+x_title+"_"+y_title,"",1,x_min,x_max);
  hist->GetXaxis()->SetNdivisions(6,5,0);
  hist->GetXaxis()->SetTitle(x_title);
  hist->GetXaxis()->SetRangeUser(x_min,x_max);
  hist->GetYaxis()->SetNdivisions(6,5,0);
  hist->GetYaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetTitle(y_title);
  hist->GetYaxis()->SetMaxDigits(3);
  hist->GetYaxis()->SetRangeUser(y_min,y_max);
  hist->Draw();

  
  CMS_lumi( canv, iPeriod, iPos );
}


void printCanvas(TString canvName){

  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  //canv->Print(canvName+".pdf",".pdf");
  canv->Print(canvName+".png",".png");
  delete canv;
  delete hist;
}



void plotLuminometer(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2){

  TString outfile=LuminometerName;
  outfile.ReplaceAll(" ","_");
  outfile.ReplaceAll("+","p");
  outfile.ReplaceAll("-","p");
  outfile.ReplaceAll(",","_");

  
  TFile F(filename,"read");
  if(F.IsZombie()){ cout<<"Bad input file: "<<filename<<endl; return;}
  TGraphErrors* G=(TGraphErrors*)F.Get(graphname);
  if(!G){ cout<<"Wrong graph name: "<<graphname<<endl; return;}

  //fit original graph otherwise fits stas appear on plot
  Fit = new TF1(LuminometerName+"Fit","[0]+[1]*x", x_min, x_max);
  Fit->SetLineWidth(2);
  Fit->SetLineColor(2);
  G->Fit(Fit,"Q","N",fitmin,fitmax);

  ///linear graph
  TGraphErrors Counts;
  for(int i=0;i<G->GetN();i++){
    float x=G->GetX()[i];
    float y=G->GetY()[i];
    float ye=G->GetEY()[i];
    Counts.SetPoint(i,x,y);
    Counts.SetPointError(i,0,ye);
  }
    
  generateCanvas(LuminometerName,x_min, x_max, x_title, y_min, y_max, y_title);
  Counts.Draw("pesame");
  Fit->Draw("lsame");
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");
  
  //residuals
  TGraphErrors Residuals;
  for(int i=0;i<Counts.GetN();i++){
    float x=Counts.GetX()[i];
    float y=Counts.GetY()[i];
    float ye=Counts.GetEY()[i];
    Residuals.SetPoint(i,x,100*(y-Fit->Eval(x))/Fit->Eval(x));
    Residuals.SetPointError(i,0,100*ye/Fit->Eval(x));
  }

  generateCanvas(LuminometerName,x_min, x_max, x_title, -residual_range, residual_range, "linearity residuals (%) ");
  Residuals.Draw("pesame");
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1,210,1);
  line.DrawLine(0,-1,210,-1);
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity_residuals");


  delete Fit;
}


