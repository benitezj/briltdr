#include "linearityPlots.C"

void linearityPlots_DT()
{
  setTDRStyle();

//// the following is already default, but can be modified here
  lumi_sqrtS = "Run 324980 (2018)";
  extraText  = "Preliminary";


  plotLuminometer("input.root", "graph",  // input file , TGraphErrors name
		  "DT Trigger Primitives (MB1-MB3)",                       //title
		  0, 20000, "Inst. Luminosity (x10^{30} cm^{-2}s^{-1})",   // x-axis
		  0, 4000000, "Total trigger primitive rate (Hz)",           // y-axis
		  5000,19000);                                         //fit range
                                                                          

  
}
