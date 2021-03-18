#include "linearityPlots.C"

void linearityPlots_test()
{
  setTDRStyle();

//// the following is already default, but can be modified here
//  lumi_sqrtS = "#sqrt{s} = 14 TeV";
//  extraText  = "Phase-2 Simulation Preliminary";


  plotLuminometer("TDRplotscluster.root", "cluster_TEPX", "TEPX clusters",  // input file , TGraphErrors name, luminometer title
		  0.5, 210, pileup,                                        // x-axis
		  0, 60000, "mean number of clusters / bx");               // y-axis
                                                                           // two additional arguments are there if need to change fit range
}



