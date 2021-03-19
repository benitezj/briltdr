#include "linearityPlots.C"


void plotLuminometer_OTLayers(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);


void linearityPlots_OT()
{
  setTDRStyle();
  //lumi_sqrtS = "#sqrt{s} = 14 TeV";
  //extraText  = "Phase-2 Simulation Preliminary";  

  //OT Layer 6
  plotLuminometer("OT-newsamples-12march2021.root", "ghBarrelL6", "Outer Tracker Layer 6 track stubs", 0.5, 210, pileup, 0, 1200, "mean number of stubs / bx");

  //OT layers 
  plotLuminometer_OTLayers("OT-newsamples-12march2021.root","ghBarrelL","Outer Tracker track stubs per layer", 0.5, 210, pileup,  0, 2900 , "mean number of stubs / bx");
}


/////////////////////////////////
//// aux function
void plotLuminometer_OTLayers(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2){

  TString outfile=LuminometerName;
  outfile.ReplaceAll(" ","_");

  TFile Finput(filename,"read");
  
  TGraphErrors* Counts[6];
  TF1* F[6];


  Fit = new TF1(LuminometerName+"Fit","[0]+[1]*x", x_min, x_max);
  Fit->SetLineWidth(2);
  Fit->SetLineColor(2);
  
  int firstl=0;

  
  TLegend leg(0.2,0.5,0.4,0.8);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);
  

  ///Extract the graphs and apply fit
  for(long l=firstl;l<6;l++){
    TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+(l+1));
    if(!G){ cout<<"Wrong graph name: "<<graphname+(l+1)<<endl; return;}

    ///copy for linear graph
    Counts[l] = new TGraphErrors();
    for(int i=0;i<G->GetN();i++){
      float x=G->GetX()[i];
      float y=G->GetY()[i];
      float ye=G->GetEY()[i];
      Counts[l]->SetPoint(i,x,y);
      Counts[l]->SetPointError(i,0,ye);
    }

    F[l]=(TF1*)Fit->Clone(Fit->GetName()+graphname+(l+1));
    G->Fit(F[l],"Q","N",fitmin,fitmax);
  }
  

  ////////////////////////
  ////Linearity graph
  generateCanvas(LuminometerName, x_min, x_max,x_title,y_min,y_max, y_title);
  for(long l=firstl;l<6;l++){
    Counts[l]->SetMarkerColor(6-l);
    Counts[l]->SetLineColor(6-l);
    Counts[l]->Draw("pesame");
    F[l]->SetLineColor(6-l);
    F[l]->Draw("lsame");
    leg.AddEntry(Counts[l],TString("Barrel layer ")+(l+1),"pl");
  }
  leg.Draw();
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");    



  ///////////////////
  //residuals graph
  TGraphErrors Residuals[6];
  generateCanvas(LuminometerName,x_min, x_max,x_title, -50, 50, "linearity residuals (%) ");
  
  for(long l=firstl;l<6;l++){
    for(int i=0;i<Counts[l]->GetN();i++){
      float x=Counts[l]->GetX()[i];
      float y=Counts[l]->GetY()[i];
      float ye=Counts[l]->GetEY()[i];
      Residuals[l].SetPoint(i,x,100*(y-F[l]->Eval(x))/F[l]->Eval(x));
      Residuals[l].SetPointError(i,0,100*ye/F[l]->Eval(x));
    }
    Residuals[l].SetMarkerColor(6-l);
    Residuals[l].SetLineColor(6-l);
    Residuals[l].Draw("pesame");
  }
  
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1,210,1);
  line.DrawLine(0,-1,210,-1);
  text.DrawLatexNDC(0.2,0.85,LuminometerName);

  leg.SetX1NDC(0.2);
  leg.SetY1NDC(0.15);
  leg.SetX2NDC(0.4);
  leg.SetY2NDC(0.45);
  leg.Draw();
  printCanvas(outfile+"_Linearity_residuals");
 

}
