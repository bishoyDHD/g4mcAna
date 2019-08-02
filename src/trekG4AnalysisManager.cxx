#include "trekG4AnalysisManager.h"

trekG4AnalysisManager::trekG4AnalysisManager(){
  fired1=false;
  fired2=false;
  csiInfo=NULL;
}

trekG4AnalysisManager::~trekG4AnalysisManager(){
  delete h1angPi;
  delete h1angG;
  delete h1MassG;
  delete h1invPi0;
}

void trekG4AnalysisManager::beginRoot(std::string name){
  outFile=new TFile(name.c_str(),"RECREATE");
  h1angPi=new TH1D("h1angPi"," Opening angle of #pi^{+}#pi^{0}", 25, -1.05,1.05);
  h1angG=new TH1D("h1angG"," Opening angle of 2#gamma", 25, -1.05,1.05);
  h1MassG=new TH1D("h1MassG"," Energy of 2#gamma", 75, 0.0,0.30);
  h1invPi0=new TH1D("h1invPi0"," Invariant mass of #pi^{0}", 50, 0.0,0.20);
}

void trekG4AnalysisManager::writeRoot(){
  outFile->Write();
  outFile->Close();
}

void trekG4AnalysisManager::analyze(TFile* pfile){
  TTree* pTree=(TTree*)pfile->Get("K+");
  pTree->SetBranchAddress("MCcsiInfo", (TObject **) &csiInfo);
  nentries=pTree->GetEntries();
  // Event loop...
  for(Int_t i=0; i<nentries; i++){
    pTree->GetEntry(i);
    std::cout<<" ievt.. "<<i<<std::endl;
    g1E.clear();   index1.clear();
    g2E.clear();   index2.clear();
    for(int j=0; j<768; j++){
      if(csiInfo->csi_x[j]!=-10000){
        if(csiInfo->trackID[j]==2){
	  fired1=true;
	  g1E.push_back(csiInfo->ECsI[j]);
	  index1.push_back(j);
	}
        if(csiInfo->trackID[j]==3){
	  fired2=true;
	  g2E.push_back(csiInfo->ECsI[j]);
	  index2.push_back(j);
	}
      }
    }
    if(fired1 && fired2){
      //gamma1
      // find max element and its corresponding index
      GeV=1000.0;
      Eg1=*max_element(g1E.begin(), g1E.end());
      d1=std::max_element(g1E.begin(), g1E.end())-g1E.begin();
      pos1=index1[d1]; //returns CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g1px=csiInfo->csi_px[pos1]/GeV; g1py=csiInfo->csi_py[pos1]/GeV; g1pz=csiInfo->csi_pz[pos1]/GeV;
      Eg1=Eg1/GeV;
      g1lv.SetPxPyPzE(g1px,g1py,g1pz,Eg1);
      g1v3.SetXYZ(g1px,g1py,g1pz);
      std::cout<<" --- gamma1 the max element is: "<<Eg1<<"\t"<<pos1<<"\t"<<csiInfo->csi_px[pos1]<<std::endl;
      //gamma2
      // find max element and its corresponding index
      Eg2=*max_element(g2E.begin(), g2E.end());
      d2=std::max_element(g2E.begin(), g2E.end())-g2E.begin();
      pos2=index2[d2]; //returns unique CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g2px=csiInfo->csi_px[pos2]/GeV; g2py=csiInfo->csi_py[pos2]/GeV; g2pz=csiInfo->csi_pz[pos2]/GeV;
      Eg2=Eg2/GeV;
      g2lv.SetPxPyPzE(g2px,g2py,g2pz,Eg2);
      g2v3.SetXYZ(g2px,g2py,g2pz);
      std::cout<<" --- gamma2 the max element is: "<<Eg2<<"\t"<<pos2<<"\t"<<csiInfo->csi_px[pos2]<<std::endl;

      // construct LV for pi0 from 2gamma LV
      pi0lv=g1lv+g2lv;
      // Fill ROOT histos
      h1MassG->Fill(Eg1+Eg2);
      h1invPi0->Fill(pi0lv.M());
      h1angG->Fill(std::cos(g1v3.Angle(g2v3)));
    }
    // need to reset fired values to false
    fired1=false; fired2=false;
    std::cout<<"-----------------------------------------------------------\n";
  }
}
