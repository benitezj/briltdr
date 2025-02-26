#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"

bool LogX=false;
bool LogY=false;
TLatex text;
TLine line;
TCanvas* canv = NULL;
TH1F* hist = NULL;//frame

extraText  = "Preliminary";
lumi_sqrtS ="2024 (13.6 TeV)";


void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title,
		    float y_min, float y_max, TString y_title){

  int W = 800;
  int H = 600;


  // references for T, B, L, R
  float T = 0.08*H;
  float B = 0.12*H; 
  float L = 0.13*W;
  float R = 0.075*W;


  canv = new TCanvas(LuminometerName+"_"+x_title+"_"+y_title,"",50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  //canv->SetTickx(0);
  //canv->SetTicky(0);
  canv->SetLogx(LogX);
  canv->SetLogy(LogY);
  
  hist = new TH1F(LuminometerName+x_title+"_"+y_title,"",1,x_min,x_max);
  hist->GetXaxis()->SetNdivisions(5,5,0);
  hist->GetXaxis()->SetTitle(x_title);
  hist->GetXaxis()->SetRangeUser(x_min,x_max);
  //hist->GetXaxis()->SetNoExponent(1);
  hist->GetYaxis()->SetMaxDigits(5);
  hist->GetYaxis()->SetNdivisions(5,5,0);
  hist->GetYaxis()->SetTitleOffset(1.15);
  hist->GetYaxis()->SetTitle(y_title);
  hist->GetYaxis()->SetMaxDigits(4);
  hist->GetYaxis()->SetRangeUser(y_min,y_max);
  hist->Draw();

  CMS_lumi( canv, LuminometerName);
}

void printCanvas(TString fileName){
  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  canv->Print(fileName+".png",".png");
  canv->Print(fileName+".pdf",".pdf");
  delete canv;
  delete hist;
}
