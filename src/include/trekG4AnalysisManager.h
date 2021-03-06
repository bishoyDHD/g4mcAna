#ifndef trekG4AnalysisManager_H
#define trekG4AnalysisManager_H 1
#include "trekG4Cluster.h"
#include "trekG4CsImapper.h"
#include "greaterThan.h"
#include <iostream>
#include <string>
#include <vector>
#include <TrekMCtree.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TRandom3.h>
#include <TFile.h>
#include <TH1D.h>

class trekG4AnalysisManager{
public:
  trekG4AnalysisManager();
  ~trekG4AnalysisManager();
  // Analysis routine for given rootFile
  void analyze(TFile* pfile,int evtMax);
  void beginRoot(std::string name,int channel);
  void writeRoot();
  void init();
  inline void setInvMass(double invMass){mass=invMass;};
  inline void setThreshold(double thr=20.){threshold=thr;};
  TFile* outFile;
private:
  TRandom3 random;
  Double_t dt,csiE;
  std::string clustPid1, clustPid2, clustPid3, clustPid4, clustPid5, clustPid6;
  std::string dummy="dummy";
  trekG4Cluster* clust;
  trekG4CsImapper* csiMapper;
  Int_t nentries,size,csiID;
  int d1, d2, d3, pos1, pos2, pos3;
  int chNum,trackID;
  const double MeV=1.0;
  const double GeV=1e-3*MeV;
  double mass; // mass for the particle of interest (scoring)
  double threshold;
  double g1px, g1py, g1pz, Eg1;
  double g2px, g2py, g2pz, Eg2;
  double g3px, g3py, g3pz, Eg3;
  double targetEloss;
  double primpx, primpy, primpz, Eprim,primlen;
  double sec1px,sec1py,sec1pz,sec1E;
  double sec2px,sec2py,sec2pz,sec2E;
  double sec3px,sec3py,sec3pz,sec3E;
  double tgt1E, tgt1pl, tgt2E, tgt2pl, tgt3E, tgt3pl;
  const double tgtE=.018; //average E-loss
  std::vector<double> g1E, g2E, g3E, piE;
  std::vector<int> index1, index2, index3;
  std::string n1, n2, n3, n4; // hist names for diff. channels
  bool fired1, fired2, fired3;
  void setClusterPID(std::string pid1,std::string pid2,std::string pid3,std::string pid4,std::string pid5,std::string pid6);
  TrekEventInfo* evtInfo;
  TrekTargetInfo* tgtInfo;
  TrekTof1Info* tof1Info;
  TrekCsiInfo* csiInfo;
  TrekMwpcInfo* mwpcInfo;
  TrekTtcInfo* ttcInfo;
  TrekTof2Info* tof2Info;
  TH1D* h1M2,*h1P[2];
};
#endif
