#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"


TString pileup="Pileup";//x-axis title for simulation
TString residuals_xtitle="Deviation from linearity (%)";
float residual_range = 5;//%
bool Log=false;// this will set log scale for x-axis in residuals plot only
TLatex text;
TLine line;
TF1 * Fit = NULL;
TCanvas* canv = NULL;
TH1F* hist = NULL;


void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title){
  
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
  canv->SetLogx(false);
  canv->SetLogy(false);
  
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

  //text.DrawLatexNDC(0.2,0.85,LuminometerName);
  text.DrawLatexNDC(canv->GetLeftMargin() + 0.10, 1 - 0.8*canv->GetTopMargin(), LuminometerName);

  int iPeriod=0;// uses the lumi_sqrtS string
  int iPos=0;//postion of CMS Preliminary
  CMS_lumi( canv, iPeriod, iPos );
}


void generateCanvasResiduals(TString LuminometerName, float x_min, float x_max, TString x_title){
  generateCanvas(LuminometerName,x_min, x_max, x_title, -residual_range, residual_range,residuals_xtitle);
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(x_min,1,x_max,1);
  line.DrawLine(x_min,-1,x_max,-1);
  canv->SetLogx(Log);
  return ;
}

void printCanvas(TString fileName){
  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  if(Log)canv->Print(fileName+"_Log.png",".png");
  else canv->Print(fileName+".png",".png");
  delete canv;
  delete hist;
}

void fixOutputFileName(TString * outfile){
  outfile->ReplaceAll(" ","_");
  outfile->ReplaceAll("+","p");
  outfile->ReplaceAll("-","m");
  outfile->ReplaceAll(",","_");
  outfile->ReplaceAll("#","_");
  outfile->ReplaceAll("(","_");
  outfile->ReplaceAll(")","_");
  outfile->ReplaceAll("{","_");
  outfile->ReplaceAll("}","_");
  outfile->ReplaceAll("/","_");
  outfile->ReplaceAll("\\","_");
}


TF1* fitGraph(TGraphErrors * G, TString LuminometerName, float x_min, float x_max, float fitmin, float fitmax){
  TF1 * F= new TF1(LuminometerName+"Fit","[0]+[1]*x", x_min, x_max);
  F->SetLineWidth(2);
  F->SetLineColor(2);
  G->Fit(F,"Q","N",fitmin,fitmax);
  return F;
}



void plotLuminometer(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2){
  
  TString outfile=LuminometerName+"_"+y_title;
  fixOutputFileName(&outfile);
  
  
  TFile File(filename,"read");
  if(File.IsZombie()){ cout<<"Bad input file: "<<filename<<endl; return;}
  TGraphErrors* G=(TGraphErrors*)File.Get(graphname);
  if(!G){ cout<<"Wrong graph name: "<<graphname<<endl; return;}
  
  //fit original graph otherwise fits stas appear on plot
  Fit = fitGraph(G, LuminometerName, x_min, x_max, fitmin, fitmax);
		  
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
  printCanvas(outfile+"_Linearity");
  
  //residuals
  TGraphErrors Residuals;
  for(int i=0;i<Counts.GetN();i++){
    float x=Counts.GetX()[i];
    float y=Counts.GetY()[i];
    float ye=Counts.GetEY()[i];
    //Residuals.SetPoint(i,x,100*(y-Fit->Eval(x))/Fit->Eval(x));
    //Residuals.SetPointError(i,0,100*ye/(Fit->Eval(x)));
    Residuals.SetPoint(i,x,100*(y-Fit->Eval(x))/(Fit->Eval(x) - Fit->Eval(0)));//correct for large noise level, imporant for HFET
    Residuals.SetPointError(i,0,100*ye/(Fit->Eval(x) - Fit->Eval(0)));
  }

  generateCanvasResiduals(LuminometerName, x_min, x_max, x_title);
  Residuals.Draw("pesame");
  //printCanvasResiduals(outfile+"_Linearity_residuals", LuminometerName, x_min, x_max);
  printCanvas(outfile+"_Linearity_residuals");

  delete Fit;
}


