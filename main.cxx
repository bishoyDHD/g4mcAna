#include "trekG4AnalysisManager.h"
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <math.h>
#include <iostream>
using namespace std;

int main(){
  //TFile *file=new TFile("../testing.root");
  //TFile *file=new TFile("../testingTarget.root");
  //TFile *file=new TFile("../chan16NoSec.root");
  TFile *file=new TFile("../chan7NoSec.root");
  string name="e36g4MC.root";
  trekG4AnalysisManager* trekMC=new trekG4AnalysisManager();
  trekMC->beginRoot(name);
  trekMC->analyze(file);
  trekMC->writeRoot();
  //delete file;
  //delete trekMC;

  /*
  TTree *tree=(TTree*)file->Get("K+");

  Int_t nentries=tree->GetEntries();

  TrekEventInfo *eventInfo=NULL;
  TrekTargetInfo *targetInfo=NULL;
  TrekCsiInfo *csiInfo=NULL;

  tree->SetBranchAddress("MCevtInfo",(TObject **) &eventInfo);
  tree->SetBranchAddress("MCtgtInfo",(TObject **) &targetInfo);
  tree->SetBranchAddress("MCcsiInfo",(TObject **) &csiInfo);

  // 4/3-vector definitions:
  TLorentzVector g1lv, g2lv, pi0lv, piPlv;
  TVector3 g1v3, g2v3, pi0v3, piPv3;
  std::vector<double> g1E,g2E,piE;
  std::vector<int> i1, i2;
  double g1px, g1py, p1pz, Eg1;
  double g2px, g2py, p2pz, Eg2;
  double pi0px, pi0py, pi0pz, Epi0;
  double piPpx, piPpy, piPpz, EpiP;
  int d1,d2,pos1, pos2;
  bool fired1=false;
  bool fired2=false;

  std::cout<<" Total number of events is: "<<nentries<<std::endl;
  for(Int_t i=0;i<nentries;i++){
    tree->GetEntry(i);

    std::cout<<" ievt. "<<eventInfo->event<<" \n";
    g1E.clear();   i1.clear();
    g2E.clear();   i2.clear();
    for(int j=0;j<768;j++){
      if(csiInfo->csi_x[j]!=-10000){
        if(csiInfo->trackID[j]==2){
	  fired1=true;
	  g1E.push_back(csiInfo->ECsI[j]);
	  i1.push_back(j);
	  cout<<j<<"  "<<csiInfo->trackID[j]<<"  "<<csiInfo->csi_px[j]<<"  "<<csiInfo->csi_py[j]<<"  "<<csiInfo->csi_pz[j]<<"  "<<csiInfo->ECsI[j]<<endl;
	}
	if(csiInfo->trackID[j]==3){
	  fired2=true;
	  g2E.push_back(csiInfo->ECsI[j]);
	  i2.push_back(j);
	  cout<<j<<"  "<<csiInfo->trackID[j]<<"  "<<csiInfo->csi_px[j]<<"  "<<csiInfo->csi_py[j]<<"  "<<csiInfo->csi_pz[j]<<"  "<<csiInfo->ECsI[j]<<endl;
	}
      }
    }
    // We want to ensure that there are at least e+ and e- hits
    if((fired1)&&(fired2)){
      //gamma1
      Eg1=*max_element(g1E.begin(),g1E.end());
      d1=std::max_element(g1E.begin(),g1E.end())-g1E.begin();
      pos1=i1[d1];
      //std::cout<<" --- the max element is: "<<Eg1<<"  "<<csiInfo->csi_px[pos1]<<std::endl;
      //gamma2
      Eg2=*max_element(g2E.begin(),g2E.end());
      d2=std::max_element(g2E.begin(),g2E.end())-g2E.begin();
      pos2=i1[d2];
      //std::cout<<" --- the max element is: "<<Eg2<<"  "<<csiInfo->csi_px[pos2]<<std::endl;
    }
    fired1=false; fired2=false;
    std::cout<<"-----------------------------------------------------------\n";
  }
  */

  return 0;
}
