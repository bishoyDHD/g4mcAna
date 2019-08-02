#ifndef trekG4AnalysisManager_H
#define trekG4AnalysisManager_H 1

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
  void beginRoot(std::string name);
  void writeRoot();
  TFile* outFile;
private:
  Int_t nentries;
  int d1, d2, pos1, pos2;
  double GeV;
  double g1px, g1py, g1pz, Eg1;
  double g2px, g2py, g2pz, Eg2;
  double pi0px, pi0py, pi0pz, Epi0;
  double piPpx, piPpy, piPpz, EpiP;
  std::vector<double> g1E, g2E, piE;
  std::vector<int> index1, index2;
  bool fired1, fired2;
  TrekCsiInfo* csiInfo;
  TLorentzVector g1lv, g2lv, pi0lv, piPlv;
  TVector3 g1v3, g2v3, pi0v3, piPv3;
  TH1D* h1angPi, *h1angG, *h1MassG, *h1invPi0;
};
#endif
