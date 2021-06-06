#include "linearityPlots.C"

void simple_plot(TString filename, TString countsname, TString residualsname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title);


void linearityPlots_HF()
{
  setTDRStyle();
  
  //// the following is already default, but can be modified here
  //  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  //  extraText  = "Phase-2 Simulation Preliminary";
  //  Log = false;
  
  
  Log = true;
  plotLuminometer("HFoc.root", "MuVsPU", "HF Tower Occupancy", 0.1 , 220, pileup, 0 , 2.0, "Mean number of towers / BX",0,200);
  plotLuminometer("HFet.root", "ETvsPU", "HF Transverse Energy", 0.1 , 220, pileup, 0 , 5000, "Mean E_{T} sum [GeV] / BX",0,200);
  

  //plots without fit, just pull the graphs from the root file
  //   Log = false;
  //   simple_plot("HFoc.root","MuVsPU", "RatioVsPU", "HF Tower Occupancy", 0 , 220, pileup, 0. , 2.0, "mean number of towers / bx");
  //   simple_plot("HFet.root","ETvsPU", "RatioVsPU", "HF Transverse Energy", 0 , 220, pileup, 0. , 5000, "mean E_{T} sum (GeV) / bx ");
  //   Log = true;
  //   simple_plot("HFoc.root","MuVsPU", "RatioVsPU", "HF Tower Occupancy", 0.1, 220, pileup, 0. , 2.0, "mean number of towers / bx");
  //   simple_plot("HFet.root","ETvsPU", "RatioVsPU", "HF Transverse Energy", 0.1 , 220, pileup, 0. , 5000, "mean E_{T} sum (GeV) / bx ");
  
}



void simple_plot(TString filename, TString countsname, TString residualsname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title){

  TString outfile=LuminometerName;
  fixOutputFileName(&outfile);  
  
  TFile File(filename,"read");
  if(File.IsZombie()){ cout<<"Bad input file: "<<filename<<endl; return;}
  TGraphErrors* G=(TGraphErrors*)File.Get(countsname);
  if(!G){ cout<<"Wrong graph name: "<<countsname<<endl; return;}
  
  Fit = (TF1*)G->FindObject("f131");
  if(!Fit){cout<<"Wrong function name"<<endl;return;}
  
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
  TGraphErrors* R=(TGraphErrors*)File.Get(residualsname);
  if(!R){ cout<<"Wrong graph name: "<<residualsname<<endl; return;}
  TGraphErrors Residuals;
  for(int i=0;i<R->GetN();i++){
    float x=R->GetX()[i];
    float y=R->GetY()[i];
    float ye=R->GetEY()[i];
    Residuals.SetPoint(i,x,y);
    Residuals.SetPointError(i,0,ye);
  }

  generateCanvasResiduals(LuminometerName, x_min, x_max, x_title);
  Residuals.Draw("pesame");
  printCanvas(outfile+"_Linearity_residuals");

}



