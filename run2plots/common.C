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

TString inpath="2017-2018-Afterglow/Run2018D_27May2023/";
long Run=325170; long LSID=1; long LS1=51; long LS2=100;

lumi_sqrtS = TString("Run:")+Run+",  LS:"+LS1+"-"+LS2+"   (13 TeV)";

TH1F* Raw;
TH1F* Corr;


void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title,
		    float y_min, float y_max, TString y_title){

  int W = 800;
  int H = 600;


  // references for T, B, L, R
  float T = 0.08*H;
  float B = 0.12*H; 
  float L = 0.13*W;
  float R = 0.04*W;


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
  hist->GetXaxis()->SetNdivisions(6,5,0);
  hist->GetXaxis()->SetTitle(x_title);
  hist->GetXaxis()->SetRangeUser(x_min,x_max);
  hist->GetXaxis()->SetNoExponent(1);
  hist->GetYaxis()->SetNdivisions(6,5,0);
  hist->GetYaxis()->SetTitleOffset(1.15);
  hist->GetYaxis()->SetTitle(y_title);
  hist->GetYaxis()->SetMaxDigits(4);
  hist->GetYaxis()->SetRangeUser(y_min,y_max);
  hist->Draw();

  CMS_lumi( canv, LuminometerName);
}


void generateCanvasResiduals(TString LuminometerName, float x_min, float x_max, TString x_title,
			     float y_min, float y_max, TString y_title){
  generateCanvas(LuminometerName,x_min, x_max, x_title, y_min, y_max , y_title);
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(x_min,1,x_max,1);
  line.DrawLine(x_min,-1,x_max,-1);
  canv->SetLogx(LogX);
  return ;
}

void printCanvas(TString fileName){
  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  canv->Print(fileName+".png",".png");
  //canv->Print(fileName+".root",".root");
  delete canv;
  delete hist;
}


void getHists(){

  setTDRStyle();

  TString histid=TString("_")+Run+"_"+LSID+"_"+LS1+"_"+LS2;
  TString outfile="PCC_Afterglow";

  TString filename=inpath+"/"+Run+".root";
  TFile* File=new TFile(filename,"read");
  if(File->IsZombie()){ cout<<"Bad input file: "<<filename<<endl; return;}

  TString rawhistoname="RawLumiAvg"+histid;
  Raw=(TH1F*)File->Get(rawhistoname);
  if(!Raw){ cout<<"Wrong graph name: "<<rawhistoname<<endl; return;}
  Raw->SetStats(0);
  Raw->SetMarkerStyle(8);
  Raw->SetMarkerSize(0.4);
  Raw->SetMarkerColor(4);

  TString corrhistoname="CorrectedLumiAvg"+histid;
  Corr=(TH1F*)File->Get(corrhistoname);
  if(!Corr){ cout<<"Wrong graph name: "<<corrhistoname<<endl; return;}
  Corr->SetStats(0);
  Corr->SetMarkerStyle(2);
  Corr->SetMarkerSize(0.4);
  Corr->SetMarkerColor(2);
  
}



void generateCanvasSplit(TString LuminometerName, float x_min, float x_max, TString x_title,
			 float y_min, float y_max, TString y_title,
			 float y_min2, float y_max2){

  int W = 800;
  int H = 600;
  float T = 0.08;
  float B = 0.12; 
  float L = 0.13;
  float R = 0.04;


  canv = new TCanvas(LuminometerName+"_"+x_title+"_"+y_title,"",50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L);
  canv->SetRightMargin( R );
  canv->SetTopMargin( T );
  canv->SetBottomMargin( B );
  canv->SetLogx(LogX);
  canv->SetLogy(LogY);


  canv->Divide(1,2);
  float titlesize=0.07;
  
  ///Setup the top pad
  TPad*pad1=(TPad*)canv->cd(1);
  pad1->SetTopMargin( 1.7*T );
  pad1->SetBottomMargin(0.*B);
  pad1->SetLeftMargin(0.8*L );
  hist = new TH1F(LuminometerName+x_title+"_"+y_title,"",1,x_min,x_max);
  hist->GetXaxis()->SetNdivisions(6,5,0);
  hist->GetXaxis()->SetRangeUser(x_min,x_max);
  hist->GetXaxis()->SetNoExponent(1);
  hist->GetXaxis()->SetTitleSize(titlesize);
  hist->GetYaxis()->SetNdivisions(6,5,0);
  hist->GetYaxis()->SetTitleOffset(0.6);
  hist->GetYaxis()->SetTitle(y_title);
  hist->GetYaxis()->SetTitleSize(titlesize);
  hist->GetYaxis()->SetMaxDigits(4);
  hist->GetYaxis()->SetRangeUser(y_min,y_max);
  hist->Draw();
  CMS_lumi( canv, LuminometerName);

  //set up the bottom pad
  TPad*pad2=(TPad*)canv->cd(2);
  pad2->SetTopMargin(0.*T);
  pad2->SetLeftMargin(0.8*L);
  hist = new TH1F(LuminometerName+x_title+"_"+y_title+" pad2","",1,x_min,x_max);
  hist->GetXaxis()->SetNdivisions(6,5,0);
  hist->GetXaxis()->SetTitle(x_title);
  hist->GetXaxis()->SetTitleSize(titlesize);
  hist->GetXaxis()->SetRangeUser(x_min,x_max);
  hist->GetXaxis()->SetNoExponent(1);
  hist->GetYaxis()->SetNdivisions(6,5,0);
  hist->GetYaxis()->SetTitleOffset(0.6);
  hist->GetYaxis()->SetTitle(y_title);
  hist->GetYaxis()->SetTitleSize(titlesize);
  hist->GetYaxis()->SetMaxDigits(4);
  hist->GetYaxis()->SetRangeUser(y_min2,y_max2);
  hist->Draw();

  
}
