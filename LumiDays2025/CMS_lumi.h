#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

//
// Global variables
//

TString cmsText     = "CMS";
float cmsTextFont   = 61;  // default is helvetic-bold

bool writeExtraText = false;
//TString extraText   = "Phase-2 Simulation Preliminary";
TString extraText   = "Phase-2 Simulation";
float extraTextFont = 52;  // default is helvetica-italics
float extraTextOffset   = 0.1;//corresponds to the length of the cmsText

// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.5;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version

float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;

// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;


TString lumi_sqrtS = "14 TeV";

bool drawLogo      = false;
int iPos=0;//postion of CMS Preliminary

void CMS_lumi( TPad* pad , TString plotTitle);

