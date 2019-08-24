#ifndef trekG4Cluster_h
#define trekG4Cluster_h 1
#include <string>
#include <TH1D.h>
#include <TH2D.h>
#include <TList.h>
#include <TLorentzVector.h>
#include <TDirectory.h>

class trekG4Cluster{
public:
  trekG4Cluster();
  ~trekG4Cluster();
  void defHistos(std::string,std::string,std::string,std::string);
  void fillHistos();
  void primtgtEloss(double px,double py,double pz,double tgtE,double tgtpL);
  void target1Eloss(double tgtE,double tgtpL);
  void target2Eloss(double tgtE,double tgtpL);
  void target3Eloss(double tgtE,double tgtpL);
  void setPrimpartl(double px,double py,double pz,double energy);
  void setParticle1(double px,double py,double pz,double energy);
  void setParticle2(double px,double py,double pz,double energy);
  void setParticle3(double px,double py,double pz,double energy);
  void plotHistos();
private:
  std::string tgtn1, tgtn2, tgtn3;
  double prm1px,prm1py,prm1pz,prm1E;
  double par1px,par1py,par1pz,par1E;
  double par2px,par2py,par2pz,par2E;
  double par3px,par3py,par3pz,par3E;
  double targE1, targPl1;
  double targE2, targPl2;
  double targE3, targPl3;
  double opAng1, opAng2; // opAng1 is for pi+pi0
  TH1D* h1ang1,*h1ang2,*h1ang3,*h1Etot,*h1inv;
  TH1D* h1Eloss[4];
  TH2D* h2Eloss[4];
  TLorentzVector par1lv, par2lv, par3lv, pi0lv, piPlv;
  TVector3 par1v3, par2v3, par3v3, pi0v3, piPv3;
};
#endif
