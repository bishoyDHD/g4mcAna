#ifndef trekG4Cluster_h
#define trekG4Cluster_h 1
#include <string>
#include <map>
#include <TH1D.h>
#include <TH2D.h>
#include <TList.h>
#include <TLorentzVector.h>
#include <TDirectory.h>
#include "trekG4findClusters.h"
#include "trekG4CsImapper.h"
#include "clusterScore.h"

class trekG4Cluster{
public:
  trekG4Cluster();
  ~trekG4Cluster();
  clusterScore* getClusterScore() const;
  void init();
  // cluster evaluation function
  void evalClusters();
  void empty();
  void defHistos(std::string,std::string,std::string,std::string);
  void fillHistos();
  void setPi0label(int lpi0);
  inline void setChannel(int ch){channel=ch;}
  void setPID(std::string pid1,std::string pid2);
  void setPID(std::string pid1,std::string pid2,std::string pid3);
  void setPID(std::string pid1,std::string pid2,std::string pid3,std::string pid4);
  void setPID(std::string pid1,std::string pid2,std::string pid3,std::string pid4,std::string pid5,std::string pid6);
  void primaryPID(std::string p1,std::string p2,std::string p3,std::string p4);
  void primtgtEloss(double px,double py,double pz,double tgtE,double tgtpL);
  void setcsiMap(const std::map<int,std::pair<double,double>> &csiMap);
  void setcsiMap();
  inline std::map<int,std::pair<double,double>> getcsiMap(){return csiMap;};
  void setPrimVect3(double x,double y,double z);
  void target1Eloss(double tgtE,double tgtpL);
  void target2Eloss(double tgtE,double tgtpL);
  void target3Eloss(double tgtE,double tgtpL);
  void target4Eloss(double tgtE,double tgtpL);
  void setPrimpartl(double px,double py,double pz,double energy);
  void setParticle1(double px,double py,double pz,double energy);
  void setParticle2(double px,double py,double pz,double energy);
  void setParticle3(double px,double py,double pz,double energy);
  void setParticle4(double px,double py,double pz,double energy);
  void set2ndryParticle(double px,double py,double pz,double energy,int n);
  void calcMolierRad(double px,double py,double pz,double energy);
  void setScoreMass(double sMass); // set mass for scoring
  void plotHistos();
  void plotHistos(TH1D*);
  void setClusterVar(int j,double Enecsi);
  inline void setThreshold(double a){threshold=a;}
private:
  int multiCrys, singleCrys;
  double threshold,channel;
  double mass;
  trekG4findClusters* fclusters;
  std::string tgtn1, tgtn2, tgtn3, tgtcorr;
  std::string primPid1, primPid2, primPid3, primPid4;
  std::string clustPid1, clustPid2, clustPid3, clustPid4, clustPid5, clustPid6;
  int labelPi0,csiMultip;
  double primx,primy,primz;
  double E2clust;
  double primtgt1px,primtgt1py,primtgt1pz;
  double prm1px,prm1py,prm1pz,prm1E;
  double prm2px,prm2py,prm2pz,prm2E;
  double prm3px,prm3py,prm3pz,prm3E;
  double pr2px,pr2py,pr2pz,pr2E;
  double par1px,par1py,par1pz,par1E,par1theta,par1phi;
  double par2px,par2py,par2pz,par2E,par2theta,par2phi;
  double par3px,par3py,par3pz,par3E,par3theta,par3phi;
  double par4px,par4py,par4pz,par4E,par4theta,par4phi;
  // secondaries in the target
  double tgtid1px,tgtid1py,tgtid1pz,tgtid1E,tgtid1theta,tgtid1phi;
  double tgtid2px,tgtid2py,tgtid2pz,tgtid2E,tgtid2theta,tgtid2phi;
  double tgtid3px,tgtid3py,tgtid3pz,tgtid3E,tgtid3theta,tgtid3phi;
  double primtgtE1, primtgtPl1;
  double targE1, targPl1;
  double targE2, targPl2;
  double targE3, targPl3;
  double targE4, targPl4;
  // cluster map
  std::map<int,std::pair<double,double>> csiMap;
  std::map<std::pair<double,double>,double> csiClust;
  std::map<std::pair<double,double>,bool> csiCheck;
  int csiID;
  std::vector<double> Ecsi,theta,phi;
  std::vector<double> clusEne,clusThetaE,clusPhiE;
  std::vector<double> singleEne,singTheta,singPhi;
  double opAng1, opAng2; // opAng1 is for pi+pi0
  TH1D* h1ang1,*h1ang2,*h1ang3,*h1Etot,*h1inv;
  TH1D* h1inv2,*h1ggAng,*h1beta,*h1gamma;
  TH1D* h1bx,*h1by,*h1bz;
  TH1D* h1Mcut,*h1Ecut,*h1Gcut,*h1Pcut;
  TH1D* h1angCorr[4],*h1Ecorr,*h1invCorr;
  TH1D* h1Eloss[4];
  TH1D* h1Multip;
  TH2D* h2Eloss[4];
  // LorentzVector definitions
  TLorentzVector par1lv,par2lv,par3lv,par4lv,pi0lv,piPlv,prim2lv;
  TLorentzVector par1lvCorr, par2lvCorr, par3lvCorr;
  TLorentzVector par4lvCorr, pi0lvCorr, piPlvCorr;
  TLorentzVector gamma1lv, gamma2lv;
  // TVector3 definitions
  TVector3 par1v3, par2v3, par3v3, par4v3, pi0v3, piPv3;
  TVector3 par1v3Corr, par2v3Corr, par3v3Corr;
  TVector3 par4v3Corr, pi0v3Corr, piPv3Corr;
  TVector3 gamma1v3,gamma2v3;
  bool moreChan;
  // pointer to CsI mapper
  trekG4CsImapper* fcsimap;
  clusterScore* fscore;
};
#endif
