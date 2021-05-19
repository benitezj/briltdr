#include "CMS_lumi.h"
#include <iostream>

void 
CMS_lumi( TPad* pad , TString plotTitle)
{

  writeExtraText = ( extraText.CompareTo("") > 0 );
  
  int alignY_=1;
  int alignX_=1;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();

  
  pad->cd();
   
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  
  ///Lumi text on top right corner
  TString lumiText;
  lumiText += lumi_sqrtS;
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  
  ///CMS 
  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(11); 
  latex.SetTextSize(cmsTextSize*t);    
  float posX_ = l  + 0.04 ;
  float posY_ = 1 - 1.7*t ;
  latex.DrawLatex(posX_,posY_,cmsText);

  //plot Title
  //latex.SetTextFont(cmsTextFont);
  latex.SetTextFont(62);
  latex.SetTextAlign(11);
  latex.SetTextSize(extraOverCmsTextSize * cmsTextSize*t);      
  latex.DrawLatex(posX_,posY_ - cmsTextSize*t,plotTitle);

  
  /// Preliminary ...
  if( writeExtraText ){
      pad->cd();
      latex.SetTextFont(52);
      latex.SetTextSize(extraOverCmsTextSize * cmsTextSize * t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_+ extraTextOffset, posY_, extraText);
  }



  
  return;
}
