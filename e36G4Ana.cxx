#include "trekG4AnalysisManager.h"
#include "trekG4Var.h"
#include "trekG4CsImapper.h"
#include <TFile.h>
#include <math.h>
#include <iostream>
using namespace std;

int main(int argc,char** argv){
  trekG4Var* pargs=new trekG4Var();
  //trekG4CsImapper map;
  //map.readMap();
  if(!pargs->parseArgs(argc,argv)){
    pargs->printUsage("e36g4mcAna");
    return 0; //executes the exit procedure
  }
  // need activate parseArgs function
  pargs->parseArgs(argc,argv);
  std::string fileName=pargs->getFile();
  TFile *file=new TFile(fileName.c_str());
  string name=pargs->getName();
  int channel=pargs->getChannel();
  double mass=pargs->getMass();
  double threshold=pargs->getThreshold();
  std::cout<<" ...current channel number is: "<<channel<<std::endl;
  trekG4AnalysisManager* trekMC=new trekG4AnalysisManager();
  // initialize
  trekMC->init();
  trekMC->setInvMass(mass);
  trekMC->setThreshold(threshold);
  trekMC->beginRoot(name, channel);
  trekMC->analyze(file);
  trekMC->writeRoot();
  // delete respective pointers
  delete trekMC;
  delete file;

  return 0;
}
