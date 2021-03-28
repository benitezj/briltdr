#include "linearityPlots.C"

void linearityPlots_TEPXD4R1()
{
  setTDRStyle();
  
  // TEPX D4R1 clusters
  plotLuminometer("TDRplotscluster.root", "ClustersD4R1", "TEPX Disk 4 Ring 1", 0.5, 210, pileup, 0, 2500, "mean number of clusters / bx");

  // TEPX D4R1 coincidences
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidences_disk4combinedring1", "TEPX Disk 4 Ring 1", 0.5, 210, pileup, 0, 600, "mean number of coincidences / bx");
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinphiS2D4R1", "TEPX Disk 4 Ring 1 coincidences in#phi, +z side", 0.5, 210, pileup, 0, 250, "mean number of coincidences / bx");
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinRS2D4R1", "TEPX Disk 4 Ring 1 coincidences in r, +z side", 0.5, 210, pileup, 0, 80, "mean number of coincidences / bx");

}
