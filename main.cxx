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

  return 0;
}
