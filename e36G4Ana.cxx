#include "trekG4AnalysisManager.h"
#include "trekG4Var.h"
#include <TFile.h>
#include <math.h>
#include <iostream>
using namespace std;

int main(int argc,char** argv){
  trekG4Var* pargs=new trekG4Var();
  if(!pargs->parseArgs(argc,argv)){
    pargs->printUsage("e36g4mcAna");
    return 0; //executes the exit procedure
  }
  // need activate parseArgs function
  pargs->parseArgs(argc,argv);
  std::string fileName=pargs->getFile();
  TFile *file=new TFile(fileName.c_str());
  string name=pargs->getName();
  trekG4AnalysisManager* trekMC=new trekG4AnalysisManager();
  trekMC->beginRoot(name);
  trekMC->analyze(file);
  trekMC->writeRoot();

  return 0;
}
