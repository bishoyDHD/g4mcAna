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
  // -----> initialize all variables to zero: safety technique
  prm1px=0.;      prm1py=0.;        prm1pz=0.;       prm1E=0.;
  par1px=0.;      par1py=0.;        par1pz=0.;       par1E=0.;
  par2px=0.;      par2py=0.;        par2pz=0.;       par2E=0.;
  par3px=0.;      par3py=0.;        par3pz=0.;       par3E=0.;
  primtgtE1=0.;   primtgtPl1=0.;
  targE1=0.;      targPl1=0.;
  targE2=0.;      targPl2=0.;
  targE3=0.;      targPl3=0.;
  // -----> initialize to false: Case for clusters > 2
  moreChan=false;
  tgtn2="Target E_{loss}";
  tgtcorr="Target E_{loss} correction";
  tgtn3="Target E_{loss} vs. target Path length";
  labelPi0=-999; // initial dummy var for pi0 channels
}
trekG4Cluster::~trekG4Cluster(){
}
// define given primary particles for given channel
void trekG4Cluster::primaryPID(std::string p1,std::string p2,std::string p3,std::string p4){
  primPid1=p1;         primPid3=p3;
  primPid2=p2;         primPid4=p4;
}
// define secondary particles according to channel
// ignore 2-body decays
void trekG4Cluster::setPID(std::string pid1,std::string pid2,std::string pid3,std::string pid4,std::string pid5,std::string pid6){
  clustPid1=pid1;     clustPid4=pid4;
  clustPid2=pid2;     clustPid5=pid5;
  clustPid3=pid3;     clustPid6=pid6;
}
// Define histograms to be filled
void trekG4Cluster::defHistos(std::string n1,std::string n2,std::string n3,std::string n4){
  gStyle->SetOptStat(0);
  h1ang1=new TH1D("h1ang1",n1.c_str(),55,-1.1,1.1);
  h1ang2=new TH1D("h1ang2",n2.c_str(),55,-1.1,1.1);
  h1Etot=new TH1D("h1Etot",n3.c_str(),75,0.0,0.30);
  h1inv=new TH1D("h1inv",n4.c_str(),75,0.0,0.30);
  h1Ecorr=new TH1D("ecorr",tgtcorr.c_str(),75,-.01,0.30);
  h1invCorr=new TH1D("invCorr","Invariant mass of A' (E_{loss} applied)",75,0.0,0.30);
  // Target energy-loss correction histograms
  std::ostringstream ecorr;
  std::ostringstream h1E,h2E;
  h1E<<"h1Eloss_";
  h2E<<"h2Eloss_";
  //h1ang3=new TH1D("h1ang3",tgtn1.c_str(),25,-1.05,1.05);
  for(int i=0; i<4; i++){
    h1E<<i;
    h2E<<i;
    h1Eloss[i]=new TH1D(h1E.str().c_str(),tgtn2.c_str(),25,-.01,0.15);
    h2Eloss[i]=new TH2D(h2E.str().c_str(),tgtn3.c_str(),50,0.0,100.,25,0.0,0.05);
  }
}
// Set values for different partilces and 
// construct corresponding Lorentz vectors
// --------------->  SET TARGET VARIABLES <----------------
void trekG4Cluster::primtgtEloss(double px,double py,double pz,double tgtE, double tgtpL){
  // primary particle 1
  primtgtE1=tgtE/1000.;   primtgtPl1=tgtpL;
  primtgt1px=px, primtgt1py=py, primtgt1pz=pz;
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
void trekG4Cluster::target4Eloss(double tgtE, double tgtpL){
  // particle 4
  targE4=tgtE/1000.;   targPl4=tgtpL;
  h1Eloss[3]->Fill(targE4);
  h2Eloss[3]->Fill(targPl4,targE4);
}
// --------------->  SET LABEL OF pi0 <----------------
void trekG4Cluster::setPi0label(int lpi0){
  labelPi0=lpi0;
}
// --------------->  SET CsI(Tl) VARIABLES <----------------
void trekG4Cluster::setPrimpartl(double px,double py,double pz,double energy){
  // primary particle 1 -- depends on channel
  prm1px=px/1000.;  prm1py=py/1000.;  prm1pz=pz/1000.; prm1E=energy/1000.;
} 
void trekG4Cluster::setPrimVect3(double x,double y,double z){
  primx=x; primy=y; primz=z;
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
void trekG4Cluster::setParticle4(double px,double py,double pz,double energy){
  // particle 4 -- depends on channel
  par4px=px/1000.;  par4py=py/1000.;  par4pz=pz/1000.; par4E=energy/1000.;
} 
// --------------->  FILL HISTOGRAMS <----------------
void trekG4Cluster::fillHistos(){
  // Set Loretz vector variables
  par1lv.SetPxPyPzE(par1px,par1py,par1pz,par1E);
  par2lv.SetPxPyPzE(par2px,par2py,par2pz,par2E);
  piPlv.SetPxPyPzE(primtgt1px,primtgt1py,primtgt1pz,prm1E);
  //std::cout<<" --- checking the pi0 channel: "<<labelPi0<<std::endl;
  pi0lv=par1lv+par2lv;
  // ------ Energy loss correction application -------///
  par1lvCorr.SetPxPyPzE(par1px,par1py,par1pz,par1E+targE1);
  par2lvCorr.SetPxPyPzE(par2px,par2py,par2pz,par2E+targE2);
  pi0lvCorr=par1lvCorr+par2lvCorr;
  h1invCorr->Fill(pi0lvCorr.M());
  h1Ecorr->Fill(pi0lvCorr.E());
  //pi0lv=par1lv+par3lv+par4lv;
  //par3lv.SetPxPyPzE(par3px,par3py,par3pz,par3E);
  //par4lv.SetPxPyPzE(par4px,par4py,par4pz,par4E);
  //par3v3.SetXYZ(par3px,par3py,par3pz);
  //par4v3.SetXYZ(par4px,par4py,par4pz);
  // TVector3 for opening angle determination
  par1v3.SetXYZ(par1px,par1py,par1pz);
  par2v3.SetXYZ(par2px,par2py,par2pz);
  piPv3.SetXYZ(primtgt1px,primtgt1py,primtgt1pz);
  //piPv3.SetXYZ(primx,primy,primz);
  pi0v3.SetXYZ(pi0lv.Px(),pi0lv.Py(),pi0lv.Pz());
  // fill histograms accordingly
  h1inv->Fill(pi0lv.M());
  h1Etot->Fill(pi0lv.E());
  opAng1=std::cos(piPv3.Angle(pi0v3));
  opAng2=std::cos(par1v3.Angle(par2v3));
  h1ang2->Fill(opAng2);
  h1ang1->Fill(opAng1);
}
// --------------->  PLOT HISTOGRAMS <----------------
void trekG4Cluster::plotHistos(){
  TCanvas* c1=new TCanvas("c1","Inv. Mass and total E",800,900);
  TCanvas* c2=new TCanvas("c2","Energy Loss 2 gammas",800,900);
  TCanvas* c3=new TCanvas("c3","2D Eloss vs path length",900,700);
  TCanvas* c4=new TCanvas("c4","2D Eloss vs path length",900,600);
  TCanvas* c5=new TCanvas("c5","Inv. Mass and total E corr",800,900);

  std::ostringstream E1, Eclustpid1, Eclustpid2, cosTheta1, cosTheta2, M;
  E1<<"E_{"<<clustPid1<<clustPid2<<"} [GeV]";
  M<<"M_{"<<clustPid1<<clustPid2<<"} [GeV/c^{2}]";
  cosTheta1<<"cos(#theta_{"<<clustPid1<<clustPid2<<"})";
  cosTheta2<<"cos(#theta_{"<<primPid1<<primPid2<<"})";
  Eclustpid1<<"E_{"<<clustPid1<<"} [GeV]";
  Eclustpid2<<"E_{"<<clustPid2<<"} [GeV]";
  c1->Divide(2,2);
  c1->cd(1);
  h1Etot->GetXaxis()->SetTitle(E1.str().c_str());
  h1Etot->GetYaxis()->SetTitle("counts/bin");
  h1Etot->Draw("hist");
  c1->cd(2);
  h1inv->GetXaxis()->SetTitle(M.str().c_str());
  h1inv->GetYaxis()->SetTitle("counts/bin");
  h1inv->Draw("hist");
  c1->cd(3);
  h1ang2->GetXaxis()->SetTitle(cosTheta1.str().c_str());
  h1ang2->GetYaxis()->SetTitle("counts/bin");
  h1ang2->Draw("hist");
  c1->cd(4);
  h1ang1->GetXaxis()->SetTitle(cosTheta2.str().c_str());
  h1ang1->GetYaxis()->SetTitle("counts/bin");
  h1ang1->Draw("hist");
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
  leg1->AddEntry(h1Eloss[0],clustPid1.c_str(),"l");
  leg1->AddEntry(h1Eloss[1],clustPid2.c_str(),"l");
  leg1->Draw();
  c2->Write();

  c3->cd();
  h2Eloss[0]->GetXaxis()->SetTitle("path length [mm]");
  h2Eloss[0]->GetYaxis()->SetTitle(Eclustpid1.str().c_str());
  h2Eloss[0]->Draw("colz0");
  c3->Write();

  c4->cd();
  h2Eloss[1]->GetXaxis()->SetTitle("path length [mm]");
  h2Eloss[1]->GetYaxis()->SetTitle(Eclustpid2.str().c_str());
  h2Eloss[1]->Draw("colz0");
  c4->Write();
  // ------ Energy-loss correction plots ---------- //
  c5->Divide(2,1);
  c5->cd(1);
  h1Ecorr->GetXaxis()->SetTitle(E1.str().c_str());
  h1Ecorr->GetYaxis()->SetTitle("counts/bin");
  h1Ecorr->Draw("hist");
  c5->cd(2);
  h1invCorr->GetXaxis()->SetTitle(M.str().c_str());
  h1invCorr->GetYaxis()->SetTitle("counts/bin");
  h1invCorr->Draw("hist");
  c5->Write();
}