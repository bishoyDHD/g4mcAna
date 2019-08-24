#include "trekG4Cluster.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

trekG4Cluster::trekG4Cluster(){
  h1ang1=NULL;    h1ang2=NULL;    h1ang3=NULL;
  h1Etot=NULL;    h1inv=NULL;     //h1Eloss=NULL;
  //h2Eloss=NULL;
  tgtn2="Target E_{loss}";
  tgtn3="Target E_{loss} vs. target P_{len}";
}
trekG4Cluster::~trekG4Cluster(){
}

void trekG4Cluster::defHistos(std::string n1,std::string n2,std::string n3,std::string n4){
  gStyle->SetOptStat(0);
  h1ang1=new TH1D("h1ang1",n1.c_str(),25,-1.05,1.05);
  h1ang2=new TH1D("h1ang2",n2.c_str(),25,-1.05,1.05);
  h1Etot=new TH1D("h1Etot",n3.c_str(),75,0.0,0.30);
  h1inv=new TH1D("h1inv",n4.c_str(),75,0.0,0.30);
  //h1ang3=new TH1D("h1ang3",tgtn1.c_str(),25,-1.05,1.05);
  for(int i=0; i<2; i++){
    std::ostringstream h1E;
    h1E<<"h1Eloss_"<<i;
    std::ostringstream h2E;
    h2E<<"h2Eloss_"<<i;
    h1Eloss[i]=new TH1D(h1E.str().c_str(),tgtn2.c_str(),25,0.0,0.15);
    h2Eloss[i]=new TH2D(h2E.str().c_str(),tgtn3.c_str(),50,0.0,100.,25,0.0,0.05);
  }
}

// Set values for different partilces and 
// construct corresponding Lorentz vectors
// --------------->  SET TARGET VARIABLES <----------------
void trekG4Cluster::primtgtEloss(double px,double py,double pz,double tgtE, double tgtpL){
  // particle 1
  targE1=tgtE/1000.;   targPl1=tgtpL;
  h1Eloss[0]->Fill(targE1);
  h2Eloss[0]->Fill(targPl1,targE1);
}
void trekG4Cluster::target1Eloss(double tgtE, double tgtpL){
  // particle 1
  targE1=tgtE/1000.;   targPl1=tgtpL;
  h1Eloss[0]->Fill(targE1);
  h2Eloss[0]->Fill(targPl1,targE1);
}
void trekG4Cluster::target2Eloss(double tgtE, double tgtpL){
  // particle 2
  targE2=tgtE/1000.;   targPl2=tgtpL;
  h1Eloss[1]->Fill(targE2);
  h2Eloss[1]->Fill(targPl2,targE2);
}
void trekG4Cluster::target3Eloss(double tgtE, double tgtpL){
  // particle 3
  targE3=tgtE/1000.;   targPl3=tgtpL;
  h1Eloss[2]->Fill(targE3);
  h2Eloss[2]->Fill(targPl3,targE3);
}
// --------------->  SET CsI(Tl) VARIABLES <----------------
void trekG4Cluster::setPrimpartl(double px,double py,double pz,double energy){
  // primary particle 1 -- depends on channel
  prm1px=px/1000.;  prm1py=py/1000.;  prm1pz=pz/1000.; prm1E=energy/1000.;
} 
void trekG4Cluster::setParticle1(double px,double py,double pz,double energy){
  // particle 1 -- depends on channel
  par1px=px/1000.;  par1py=py/1000.;  par1pz=pz/1000.; par1E=energy/1000.;
} 
void trekG4Cluster::setParticle2(double px,double py,double pz,double energy){
  // particle 2 -- depends on channel
  par2px=px/1000.;  par2py=py/1000.;  par2pz=pz/1000.; par2E=energy/1000.;
} 
void trekG4Cluster::setParticle3(double px,double py,double pz,double energy){
  // particle 3 -- depends on channel
  par3px=px/1000.;  par3py=py/1000.;  par3pz=pz/1000.; par3E=energy/1000.;
} 
// --------------->  FILL HISTOGRAMS <----------------
void trekG4Cluster::fillHistos(){
  par1lv.SetPxPyPzE(par1px,par1py,par1pz,par1E);
  par2lv.SetPxPyPzE(par2px,par2py,par2pz,par2E);
  par3lv.SetPxPyPzE(par3px,par3py,par3pz,par3E);
  pi0lv=par1lv+par2lv+par3lv;
  // TVector3 for opening angle determination
  par1v3.SetXYZ(par1px,par1py,par1pz);
  par2v3.SetXYZ(par2px,par2py,par2pz);
  par3v3.SetXYZ(par3px,par3py,par3pz);
  opAng2=std::cos(par1v3.Angle(par2v3));
  h1inv->Fill(pi0lv.M());
  h1Etot->Fill(par1E+par2E);
  h1ang2->Fill(opAng2);
}
// --------------->  PLOT HISTOGRAMS <----------------
void trekG4Cluster::plotHistos(){
  TCanvas* c1=new TCanvas("c1","Inv. Mass and total E",800,900);
  TCanvas* c2=new TCanvas("c2","Energy Loss 2 gammas",800,900);
  TCanvas* c3=new TCanvas("c3","2D Eloss vs path length",900,700);
  TCanvas* c4=new TCanvas("c4","2D Eloss vs path length",900,600);

  c1->Divide(2,1);
  c1->cd(1);
  h1Etot->GetXaxis()->SetTitle("E_{2#gamma}");
  h1Etot->GetYaxis()->SetTitle("counts/bin");
  h1Etot->Draw("hist");
  c1->cd(2);
  h1inv->GetXaxis()->SetTitle("M_{2#gamma}");
  h1inv->GetYaxis()->SetTitle("counts/bin");
  h1inv->Draw("hist");
  c1->Write();

  c2->cd();
  h1Eloss[0]->GetXaxis()->SetTitle("Energy [GeV]");
  h1Eloss[0]->GetYaxis()->SetTitle("counts/bin");
  h1Eloss[0]->SetLineWidth(2);
  h1Eloss[0]->Draw("hist");
  h1Eloss[1]->SetLineColor(kRed);
  h1Eloss[1]->SetLineWidth(2);
  h1Eloss[1]->Draw("hist same");
  auto leg1=new TLegend(0.1,0.7,0.48,0.9);
  leg1->SetHeader("Legend","C");
  leg1->AddEntry(h1Eloss[0],"#gamma1","l");
  leg1->AddEntry(h1Eloss[1],"#gamma2","l");
  leg1->Draw();
  c2->Write();

  c3->cd();
  h2Eloss[0]->GetXaxis()->SetTitle("path length [mm]");
  h2Eloss[0]->GetYaxis()->SetTitle("E_{#gamma1} [GeV]");
  h2Eloss[0]->Draw("colz0");
  c3->Write();

  c4->cd();
  h2Eloss[1]->GetXaxis()->SetTitle("path length [mm]");
  h2Eloss[1]->GetYaxis()->SetTitle("E_{#gamma2} [GeV]");
  h2Eloss[1]->Draw("colz0");
  c4->Write();
}
