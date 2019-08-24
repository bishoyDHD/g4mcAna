#ifndef trekG4AnalysisManager_H
#define trekG4AnalysisManager_H 1
#include "trekG4Cluster.h"
#include <iostream>
#include <string>
#include <vector>
#include <TrekMCtree.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TFile.h>
#include <TH1D.h>

class trekG4AnalysisManager{
public:
  trekG4AnalysisManager();
  ~trekG4AnalysisManager();
  // Analysis routine for given rootFile
  void analyze(TFile* pfile);
  void beginRoot(std::string name,int channel);
  void writeRoot();
  TFile* outFile;
private:
  trekG4Cluster* clust;
  Int_t nentries;
  int d1, d2, pos1, pos2;
  double GeV;
  double g1px, g1py, g1pz, Eg1;
  double g2px, g2py, g2pz, Eg2;
  double pi0px, pi0py, pi0pz, Epi0;
  double piPpx, piPpy, piPpz, EpiP;
  double tgt1E, tgt1pl, tgt2E, tgt2pl;
  std::vector<double> g1E, g2E, piE;
  std::vector<int> index1, index2;
  std::string n1, n2, n3, n4; // hist names for diff. channels
  bool fired1, fired2;
  TrekEventInfo* evtInfo;
  TrekTargetInfo* tgtInfo;
  TrekTof1Info* tof1Info;
  TrekCsiInfo* csiInfo;
  TrekMwpcInfo* mwpcInfo;
  TrekTtcInfo* ttcInfo;
  TrekTof2Info* tof2Info;
  TLorentzVector g1lv, g2lv, pi0lv, piPlv;
  TVector3 g1v3, g2v3, pi0v3, piPv3;
  TH1D* h1angPi, *h1angG, *h1MassG, *h1invPi0;
};
#endif
