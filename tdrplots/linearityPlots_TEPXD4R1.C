#include "linearityPlots.C"

void linearityPlots_TEPXD4R1()
{
  setTDRStyle();
  
  // TEPX D4R1 clusters
  plotLuminometer("TDRplotscluster.root", "ClustersD4R1", "TEPX Disk 4 Ring 1 clusters", 0.5, 210, pileup, 0, 2500, "Mean number of clusters / BX");

  // TEPX D4R1 coincidences
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidences_disk4combinedring1", "TEPX Disk 4 Ring 1 coincidences", 0.5, 210, pileup, 0, 600, "Mean number of coincidences / BX");
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinphiS2D4R1", "TEPX-D4R1 coincidences in#phi, +z", 0.5, 210, pileup, 0, 250, "Mean number of coincidences / BX");
  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinRS2D4R1", "TEPX-D4R1 coincidences in r, +z", 0.5, 210, pileup, 0, 80, "Mean number of coincidences / BX");

}
