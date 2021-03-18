#include "linearityPlots.C"

void linearityPlots_TEPX()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  extraText  = "       Phase-2 Simulation Preliminary";    
  writeExtraText = true;

  //TEPX clusters
  plotLuminometer("TDRplotscluster.root", "cluster_TEPX", "TEPX clusters", 0.5, 210, pileup, 0, 60000, "mean number of clusters / bx");

  //TEPX coincidences
  plotLuminometer("TDRplots2xtotal_phi_R.root", "2xCoincidences_TEPX", "TEPX coincidences", 0.5, 210, pileup, 0, 6000, "mean number of coincidences / bx");

  //TEPX clusters per disk

  //TEPX coincidences per disk

  //TEPX clusters per ring

  //TEPX coincidences per ring
  
  
  //TEPX D4R1 clusters
  plotLuminometer("TDRplotscluster.root", "cluster_D4R1", "TEPX Disk 4 Ring 1 clusters", 0.5, 210, pileup, 0, 5000, "mean number of clusters / bx");

  //TEPX D4R1 coincidences
  plotLuminometer("TDRplots2xtotal_phi_R.root", "2xCoincidences_D4R1", "TEPX Disk 4 Ring 1 coincidences", 0.5, 210, pileup, 0, 600, "mean number of coincidences / bx");
  
}



