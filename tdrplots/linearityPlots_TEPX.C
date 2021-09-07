#include "linearityPlots.C"

void linearityPlots_perdisk(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);
void linearityPlots_perringclusters(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);
void linearityPlots_perringcoincidences(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);

void linearityPlots_TEPX()
{
  
  setTDRStyle();
  Log = true;
  
  //////////////////
  //clusters
//  plotLuminometer("TDRplotscluster.root", "cluster_TEPX", "TEPX clusters", pu_min, pu_max, pileup, 0, 60000, "Mean number of clusters / BX");
//  linearityPlots_perdisk("TDRplotscluster.root", "cluster_disk", "TEPX clusters, +z", pu_min, pu_max, pileup, 0, 9000, "Mean number of clusters / BX");
//  linearityPlots_perringclusters("TDRplotscluster.root", "Clusters", "TEPX clusters", pu_min, pu_max, pileup, 0, 2200, "Mean number of clusters / BX");

  /////////////////////////
  //coincidences
  //  plotLuminometer("TDRplots_2xcoincidences.root", "2xCoincidences_TEPX", "TEPX coincidences", pu_min, pu_max, pileup, 0, 6000, "Mean number of coincidences / BX");
  //linearityPlots_perdisk("TDRplots_2xcoincidences.root", "2xCoincidences_disk", "TEPX coincidences, +z", pu_min, pu_max, pileup, 0, 800, "Mean number of coincidences / BX");
  //linearityPlots_perringcoincidences("TDRplots_2xcoincidences.root", "2xCoincidencesinphiS2", "TEPX coincidences in #phi", pu_min, pu_max, pileup, 0, 250, "Mean number of coincidences / BX");
  //linearityPlots_perringcoincidences("TDRplots_2xcoincidences.root", "2xCoincidencesinRS2", "TEPX coincidences in r", pu_min, pu_max, pileup, 0, 70, "Mean number of coincidences / BX");


  ///updated root file with full stats for clusters
  linearityPlots_perdisk("TEPXLinearityGraphs.root", "Clusters_Dp", "TEPX clusters, +z", pu_min, pu_max, pileup, 0, 9000, "Mean number of clusters / BX");
  linearityPlots_perdisk("TEPXLinearityGraphs.root", "Coincidences2x_total_Dp", "TEPX coincidences, +z", pu_min, pu_max, pileup, 0, 800, "Mean number of coincidences / BX");
  
}


    
void linearityPlots_perdisk(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2)
{
 
  
  TString outfile=LuminometerName+"_"+y_title;
  fixOutputFileName(&outfile);

 
  TFile Finput(filename,"read"); 
  
  TGraphErrors* Counts[4];
  TF1* F[4];
  TGraphErrors Residuals[4];
  for(long l=0;l<4;l++){
    Counts[l] =NULL;
    F[l] = NULL;
  }
  
  
  ///Extract the graphs and apply fit
  for(long l=0;l<4;l++){
    
    TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+(l+1));//+"combined");
    if(!G){ cout<<"Wrong graph name: "<<graphname+(l+1)<<endl; return;}
    
    ///copy for linear graph
    Counts[l] = new TGraphErrors();
    for(int i=0;i<G->GetN();i++){
      float x=G->GetX()[i];
      float y=G->GetY()[i];
      float ye=G->GetEY()[i];
      Counts[l]->SetPoint(i,x,y);
      Counts[l]->SetPointError(i,0,ye);
    }
    
    F[l] = fitGraph(G,LuminometerName+graphname+l, x_min, x_max, fitmin, fitmax);
  }
  
  
  ////////////////////////
  ////Linearity graph
  TLegend leg(0.15,0.54,0.38,0.78);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);

  generateCanvas(LuminometerName, x_min, x_max, x_title, y_min, y_max, y_title); 

  for(long l=0;l<4;l++){//+z side only
    Counts[l]->SetMarkerColor(4-l);
    Counts[l]->SetLineColor(4-l);
    Counts[l]->Draw("pesame");
    F[l]->SetLineColor(4-l);
    F[l]->Draw("lsame");
    leg.AddEntry(Counts[l],TString("Disk +")+(l+1),"pl");
  }
  leg.Draw();
  printCanvas(outfile+"_Linearity");    
  
  
  
  ///////////////////
  //residuals graph
  generateCanvasResiduals(LuminometerName,x_min, x_max, x_title);
  
  for(long l=0;l<4;l++){
    for(int i=0;i<Counts[l]->GetN();i++){
      float x=Counts[l]->GetX()[i];
      float y=Counts[l]->GetY()[i];
      float ye=Counts[l]->GetEY()[i];
      //Residuals[l].SetPoint(i,x-l,100*(y-F[l]->Eval(x))/F[l]->Eval(x));
      Residuals[l].SetPoint(i,(1.+(l-2)*0.03)*x,100*(y-F[l]->Eval(x))/F[l]->Eval(x));
      Residuals[l].SetPointError(i,0,100*ye/F[l]->Eval(x));
    }
    Residuals[l].SetMarkerColor(4-l);
    Residuals[l].SetMarkerSize(0.5);
    Residuals[l].SetLineColor(4-l);
    Residuals[l].SetLineWidth(2);
    Residuals[l].Draw("pesame");
  }   
  leg.SetX1NDC(0.76);
  leg.SetY1NDC(0.64);
  leg.SetX2NDC(0.98);
  leg.SetY2NDC(0.90);
  leg.Draw();
  printCanvas(outfile+"_Linearity_residuals");
    
}




void linearityPlots_perringclusters(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2)
{
  
  TString outfile=LuminometerName+"_"+y_title;
  fixOutputFileName(&outfile);

  TFile Finput(filename,"read");
  if(Finput.IsZombie()) return;
  
  TGraphErrors* Counts[4][5];
  TF1* F[4][5];
  TGraphErrors Residuals[4][5];
  for(long l=0;l<4;l++){
    for(long m=0;m<5;m++){
      Counts[l][m] = NULL;
      F[l][m] = NULL;
    }
  }
    
  ///Extract the graphs and apply fit
  for(long l=0;l<4;l++){
    for(long m=0;m<5;m++){
      TString objectname=graphname+"D"+(l+1)+"R"+(m+1);
      TGraphErrors* G=(TGraphErrors*)Finput.Get(objectname);
      if(!G){ cout<<"Wrong graph name: "<<objectname<<endl; return;}
      
      ///copy for linear graph
      Counts[l][m] = new TGraphErrors();
      for(int i=0;i<G->GetN();i++){
	float x=G->GetX()[i];
	float y=G->GetY()[i];
	float ye=G->GetEY()[i];
	Counts[l][m]->SetPoint(i,x,y);
	Counts[l][m]->SetPointError(i,0,ye);
	
      }
      F[l][m] = fitGraph(G, LuminometerName+graphname+"D"+(l+1)+"R"+(m+1), x_min, x_max, fitmin, fitmax);
    }
  } 


  
  ////////////////////////
  ////Linearity graph (only +z side)
  for(long l=0;l<4;l++){
    generateCanvas(LuminometerName+", Disk +"+(l+1),x_min, x_max, x_title, y_min, y_max, y_title);
    TLegend leg(0.15,0.58,0.38,0.78);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);	
    for(long m=0;m<5;m++){      
      Counts[l][m]->SetMarkerColor(5-m);
      Counts[l][m]->SetLineColor(5-m);
      Counts[l][m]->Draw("pesame");
      F[l][m]->SetLineColor(5-m);
      F[l][m]->Draw("lsame");
      leg.AddEntry(Counts[l][m],TString("Ring ")+(m+1),"pl");
    }
    leg.Draw(); 
    printCanvas(outfile+"Disk"+(l+1)+"_Linearity");
  }
  
  
  
  ///////////////////
  //residuals graph
  for(long l=0;l<4;l++){
    generateCanvasResiduals(LuminometerName+", Disk +"+(l+1),x_min, x_max, x_title);
    TLegend leg(0.76,0.68,0.98,0.90);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);
    
    for(long m=0;m<5;m++){
      for(int i=0;i<Counts[l][m]->GetN();i++){	
	float x=Counts[l][m]->GetX()[i];
	float y=Counts[l][m]->GetY()[i];
	float ye=Counts[l][m]->GetEY()[i];
	Residuals[l][m].SetPoint(i,(1.+(m-2)*0.03)*x,100*(y-F[l][m]->Eval(x))/F[l][m]->Eval(x));
	Residuals[l][m].SetPointError(i,0,100*ye/F[l][m]->Eval(x));
      }

      leg.AddEntry(Counts[l][m],TString("Ring ")+(m+1),"pl");
      Residuals[l][m].SetMarkerColor(5-m);
      Residuals[l][m].SetMarkerSize(0.5);
      Residuals[l][m].SetLineColor(5-m);
      Residuals[l][m].SetLineWidth(2);
      Residuals[l][m].Draw("pesame");      
    }

    leg.Draw();
    printCanvas(outfile+"Disk"+(l+1)+"_Linearity_residuals");
  }
  
}




void linearityPlots_perringcoincidences(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2)
{
  
  TString outfile=LuminometerName+"_"+y_title;
  fixOutputFileName(&outfile);
 
  
  TFile Finput(filename,"read");
  
  TGraphErrors* Counts[4][5];
  TF1* F[4][5];
  TGraphErrors Residuals[4][5];
  for(long l=0;l<4;l++){
    for(long m=0;m<5;m++){
      Counts[l][m] = NULL;
      F[l][m] = NULL;
    }
  }
    
  //Extract the graphs and apply fit  
  for(long l=0;l<4;l++){//+z side only
    for(long m=0;m<5;m++){
      TString objectname=graphname+"D"+(l+1)+"R"+(m+1);
      TGraphErrors* G=(TGraphErrors*)Finput.Get(objectname);
      if(!G){
	cout<<"no graph: "<<objectname<<endl;
	continue;
      }

      ///copy for linear graph
      Counts[l][m] = new TGraphErrors();
      for(int i=0;i<G->GetN();i++){
	float x=G->GetX()[i];
	float y=G->GetY()[i];
	float ye=G->GetEY()[i];
	Counts[l][m]->SetPoint(i,x,y);
	Counts[l][m]->SetPointError(i,0,ye);	
      }
      
      F[l][m] = fitGraph(G, LuminometerName+graphname+"D"+l+"R"+m, x_min, x_max, fitmin, fitmax);     
    }
  } 

  
  ////////////////////////
  ////Linearity graph (+z side only)
  for(long l=0;l<4;l++){   
    generateCanvas(LuminometerName+", Disk +"+(l+1),x_min,x_max,x_title,y_min, y_max,y_title);
    TLegend leg(0.15,0.58,0.38,0.78);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);

    for(long m=0;m<5;m++){
      if(!Counts[l][m])continue;
      Counts[l][m]->SetMarkerColor(5-m);
      Counts[l][m]->SetLineColor(5-m);
      Counts[l][m]->Draw("pesame");
      F[l][m]->SetLineColor(5-m);
      F[l][m]->Draw("lsame");	
      leg.AddEntry(Counts[l][m],TString("Ring ")+(m+1),"pl");
    }
    
    leg.Draw();
    printCanvas(outfile+"Disk"+(l+1)+"_Linearity");
    
  }

  
  ///////////////////
  //residuals graph
  for(long l=0;l<4;l++){
    generateCanvasResiduals(LuminometerName+", Disk +"+(l+1),x_min,x_max,x_title);

    TLegend leg(0.76,0.68,0.98,0.90);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);
    
    for(long m=0;m<5;m++){
      if(!Counts[l][m])continue;
      for(int i=0;i<Counts[l][m]->GetN();i++){	
	float x=Counts[l][m]->GetX()[i];
	float y=Counts[l][m]->GetY()[i];
	float ye=Counts[l][m]->GetEY()[i];
	Residuals[l][m].SetPoint(i,(1.+(m-2)*0.03)*x,100*(y-F[l][m]->Eval(x))/F[l][m]->Eval(x));
	Residuals[l][m].SetPointError(i,0,100*ye/F[l][m]->Eval(x));	
      }
      
      leg.AddEntry(Counts[l][m],TString("Ring ")+(m+1),"pl");
      Residuals[l][m].SetMarkerColor(5-m);
      Residuals[l][m].SetMarkerSize(0.5);
      Residuals[l][m].SetLineColor(5-m);
      Residuals[l][m].SetLineWidth(2);
      Residuals[l][m].Draw("pesame");
    }

    leg.Draw();
    //printCanvasResiduals(outfile+"Disk"+(l+1)+"_Linearity_residuals", LuminometerName, x_min, x_max);
    printCanvas(outfile+"Disk"+(l+1)+"_Linearity_residuals");
  }
  
}
