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
  //TFile *file=new TFile("../chan14And16NoSec100MeVU1.root");
  //TFile *file=new TFile("../chan14NoSec100MeVU1.root");
  //TFile *file=new TFile("../chan14NoSec50MeVU1.root");
  //TFile *file=new TFile("../chan14Geantino.root");
  //TFile *file=new TFile("../chan16Geantino.root");
  //TFile *file=new TFile("../chan14And16Geantino.root");
  //TFile *file=new TFile("../chan14NoSecNoCD100MeVU1.root");
  //TFile *file=new TFile("../chan7NoSec.root");
  TFile *file=new TFile("../chan16NoSec.root");
  string name="e36g4MC.root";
  trekG4AnalysisManager* trekMC=new trekG4AnalysisManager();
  trekMC->beginRoot(name);
  trekMC->analyze(file);
  trekMC->writeRoot();

  return 0;
}
