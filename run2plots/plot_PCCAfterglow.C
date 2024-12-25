#include "common.C"

void plot_PCCAfterglow(){
  getHists();

  TH1F*RawC=(TH1F*)Raw->Clone("RawC");
  RawC->SetMarkerSize(0.8);
  TH1F*CorrC=(TH1F*)Corr->Clone("CorrC");
  CorrC->SetMarkerSize(0.8);
  
  TLegend leg(0.45,0.2,0.95,0.4);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.AddEntry(RawC,"Before afterglow subtraction","p");
  leg.AddEntry(CorrC,"After afterglow subtraction","p");

  
  ///Simple plot
  generateCanvas("",0,3525,"BCID", -20, 800, "PCC");
  Raw->Draw("histpsame");
  Corr->Draw("histpsame");
  leg.Draw();
  printCanvas("PCCAfterglow-v1");


  //plot with zoomed part at bottom
  TLegend* leg2=(TLegend*)leg.Clone("leg2");
  leg2->SetX1NDC(0.5); leg2->SetY1NDC(0.1);leg2->SetX2NDC(0.95);leg2->SetY2NDC(0.3);
  generateCanvasSplit("",0,3525,"BCID", -20, 800, "PCC",-10,45);
  canv->cd(1);
  Raw->Draw("histpsame");
  Corr->Draw("histpsame");
  leg2->Draw();
  canv->cd(2);
  Raw->Draw("histpsame");
  Corr->Draw("histpsame");
  printCanvas("PCCAfterglow-v1p2");
  
  
  
}


