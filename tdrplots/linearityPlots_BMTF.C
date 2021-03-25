#include "linearityPlots.C"

void linearityPlots_BMTF()
{
  setTDRStyle();

//// the following is already default, but can be modified here
  lumi_sqrtS = "Run 324980 (2018)";
  extraText  = "Preliminary";


  plotLuminometer("BMTF_324980.root", "RateVsLumi_RateInkHz_LumiInE34",  
		  "Barrel Muon Track Finder (BMTF)",                      
		  0, 2, "HFOC Inst. Luminosity (x10^{34} cm^{-2}s^{-1})",  
		  0, 300, "rate of L1 tracks (kHz)",        
		  0.3,2.0);                                         //fit range
                                                                          

  
}
