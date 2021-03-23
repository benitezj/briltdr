#include "linearityPlots.C"

void linearityPlots_HF()
{
  setTDRStyle();

//// the following is already default, but can be modified here
//  lumi_sqrtS = "#sqrt{s} = 14 TeV";
//  extraText  = "Phase-2 Simulation Preliminary";
//  Log = false;

  //linear graphs
  plotLuminometer("HFoc.root", "MuVsPU", "HF Trigger Tower Occupancy", 0 , 210, pileup, 0. , 1.5, "mean number of towers / bx");
  plotLuminometer("HFet.root", "ETvsPU", "HF Transverse Energy", 0 , 210, pileup, 0. , 3000, "mean E_{T} sum (GeV) / bx ");


}



