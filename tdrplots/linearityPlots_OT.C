#include "linearityPlots.C"


void plotLuminometer_OTLayers(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);


void linearityPlots_OT()
{
  setTDRStyle();

  //Layer 6
  plotLuminometer("OT-newsamples-12march2021.root", "ghBarrelL6", "Outer Tracker Barrel Layer 6", 0.5, 210, pileup, 0, 1200, "mean number of stubs / bx");

  //All layers 
  plotLuminometer_OTLayers("OT-newsamples-12march2021.root","ghBarrelL","Outer Tracker Barrel", 0.5, 210, pileup,  0, 2900 , "mean number of stubs / bx");
}


/////////////////////////////////
//// aux function
void plotLuminometer_OTLayers(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2){

  TString outfile=LuminometerName+"_"+y_title;
  fixOutputFileName(&outfile);
 
  TFile Finput(filename,"read");
  
  TGraphErrors* Counts[6];
  TF1* F[6];

  int firstl=0;

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

    F[l] = fitGraph(G,LuminometerName+graphname+l, x_min, x_max, fitmin, fitmax);
  }
  

  ////////////////////////
  ////Linearity graph
  TLegend leg(0.2,0.5,0.4,0.8);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);
  generateCanvas(LuminometerName, x_min, x_max,x_title,y_min,y_max, y_title);
  for(long l=firstl;l<6;l++){
    Counts[l]->SetMarkerColor(6-l);
    Counts[l]->SetLineColor(6-l);
    Counts[l]->Draw("pesame");
    F[l]->SetLineColor(6-l);
    F[l]->Draw("lsame");
    leg.AddEntry(Counts[l],TString("Layer ")+(l+1),"pl");
  }
  leg.Draw();
  printCanvas(outfile+"_Linearity");    



  ///////////////////
  //residuals graph
  TGraphErrors Residuals[6];
  float temp=residual_range;
  residual_range = 50;
  generateCanvasResiduals(LuminometerName, x_min, x_max, x_title);
  residual_range = temp;
  
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
  
  leg.SetX1NDC(0.2);
  leg.SetY1NDC(0.15);
  leg.SetX2NDC(0.4);
  leg.SetY2NDC(0.45);
  leg.Draw();
  printCanvas(outfile+"_Linearity_residuals");


}
