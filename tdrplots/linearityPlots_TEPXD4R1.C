#include "linearityPlots.C"

void linearityPlots_TEPXD4R1()
{
  setTDRStyle();
  Log = true;

  // TEPX D4R1 clusters
  //plotLuminometer("TDRplotscluster.root", "ClustersD4R1", "TEPX Disk 4 Ring 1 clusters, +z", pu_min, pu_max, pileup, 0, 2500, "Mean number of clusters / BX");


  // TEPX D4R1 coincidences
  //plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidences_disk4combinedring1", "TEPX Disk 4 Ring 1 coincidences", pu_min, pu_max, pileup, 0, 600, "Mean number of coincidences / BX");
  //plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinphiS2D4R1", "TEPX-D4R1 coincidences in #phi, +z", pu_min, pu_max, pileup, 0, 250, "Mean number of coincidences / BX");
  //plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidencesinRS2D4R1", "TEPX-D4R1 coincidences in r, +z", pu_min, pu_max, pileup, 0, 80, "Mean number of coincidences / BX");


  //updated root file with clusters at full stats
  plotLuminometer("TEPXLinearityGraphs.root", "Clusters_Dp4R1", "TEPX Disk 4 Ring 1 clusters, +z", pu_min, pu_max, pileup, 0, 2500, "Mean number of clusters / BX");
  plotLuminometer("TEPXLinearityGraphs.root", "Coincidences2x_Inphi_Dp4R1", "TEPX-D4R1 coincidences in #phi, +z", pu_min, pu_max, pileup, 0, 250, "Mean number of coincidences / BX");
  
}
