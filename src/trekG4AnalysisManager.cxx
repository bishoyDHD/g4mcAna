#include "trekG4AnalysisManager.h"

trekG4AnalysisManager::trekG4AnalysisManager(){
  fired1=false;     tof1Info=NULL;
  fired2=false;     tof2Info=NULL;
  evtInfo=NULL;     ttcInfo=NULL;
  tgtInfo=NULL;
  csiInfo=NULL;
  mwpcInfo=NULL;
  clust=new trekG4Cluster();
}

trekG4AnalysisManager::~trekG4AnalysisManager(){
  delete clust;
}

void trekG4AnalysisManager::beginRoot(std::string name,int channel){
  outFile=new TFile(name.c_str(),"RECREATE");
  switch(channel){
    case 7:
      n1="Opening angle between #pi^{+}#pi^{0}: cos(#theta_{#pi^{+}#pi^{0}})";
      n2="Opening angle between 2#gamma: cos(#theta_{2#gamma})";
      n3="2#gamma total energy: E_{2#gamma}";
      n4="Invariant mass of #pi^{0}";
      clust->defHistos(n1,n2,n3,n4);
      break;
    case 14:
      n1="Opening angle between #pi^{+}#pi^{0}: cos(#theta_{#pi^{+}#pi^{0}})";
      n2="Opening angle between e^{+}e^{-}: cos(#theta_{e^{+}e^{-}})";
      n3="Total energy of e^{+}e^{-}: E_{e^{+}e^{-}}";
      n4="Invariant mass of A^{'}";
      clust->defHistos(n1,n2,n3,n4);
      break;
  }// end of swith statement
}

void trekG4AnalysisManager::writeRoot(){
  outFile->Write();
  clust->plotHistos();
  outFile->Close();
}

void trekG4AnalysisManager::analyze(TFile* pfile){
  TTree* pTree=(TTree*)pfile->Get("K+");
  pTree->SetBranchAddress("MCevtInfo", (TObject **) &evtInfo);
  pTree->SetBranchAddress("MCtgtInfo", (TObject **) &tgtInfo);
  pTree->SetBranchAddress("MCmwpcInfo", (TObject **) &mwpcInfo);
  pTree->SetBranchAddress("MCcsiInfo", (TObject **) &csiInfo);
  pTree->SetBranchAddress("MCttcInfo", (TObject **) &ttcInfo);
  pTree->SetBranchAddress("MCtof1Info", (TObject **) &tof1Info);
  pTree->SetBranchAddress("MCtof2Info", (TObject **) &tof2Info);
  nentries=pTree->GetEntries();
  double g1x, g1y, g1z;
  double g2x, g2y, g2z;
  // Event loop...
  std::cout<<" Entering event loop... \n";
  for(Int_t i=0; i<nentries; i++){
    pTree->GetEntry(i);
    g1E.clear();   index1.clear();
    g2E.clear();   index2.clear();
    // make sure this is a good event: 
    // Check experimental trigger condition. 
    // Skip if not triggered
    for(int n=0; n<12;n++){
      for(int m=0; m<3;m++){
        if(tgtInfo->targetE[m]==-10000 || tof1Info->tof1_E==-1000){
          if(ttcInfo->ttc_E[n]==-10000 || tof2Info->tof2_E[n]==-1000){
	    goto endLoop;
	  }
	}
      }
    }
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
    } // end of CsI for loop
    if(fired1 && fired2){
      //gamma1
      // find max element and its corresponding index
      GeV=1000.0;
      Eg1=*max_element(g1E.begin(), g1E.end());
      d1=std::max_element(g1E.begin(), g1E.end())-g1E.begin();
      pos1=index1[d1]; //returns CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g1px=csiInfo->csi_px[pos1]; g1py=csiInfo->csi_py[pos1]; g1pz=csiInfo->csi_pz[pos1];
      g1lv.SetPxPyPzE(g1px,g1py,g1pz,Eg1);
      g1x=csiInfo->csi_x[pos1]; g1y=csiInfo->csi_y[pos1]; g1z=csiInfo->csi_z[pos1];
      g1v3.SetXYZ(g1px,g1py,g1pz);
      tgt1E=tgtInfo->sE[1];
      tgt1pl=tgtInfo->targL[1];
      //gamma2
      // find max element and its corresponding index
      Eg2=*max_element(g2E.begin(), g2E.end());
      d2=std::max_element(g2E.begin(), g2E.end())-g2E.begin();
      pos2=index2[d2]; //returns unique CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g2px=csiInfo->csi_px[pos2]; g2py=csiInfo->csi_py[pos2]; g2pz=csiInfo->csi_pz[pos2];
      //Eg2=Eg2/GeV;
      g2lv.SetPxPyPzE(g2px,g2py,g2pz,Eg2);
      //g2lv.SetXYZT(g2x,g2y,g2z,Eg2);
      g2x=csiInfo->csi_x[pos2]; g2y=csiInfo->csi_y[pos2]; g2z=csiInfo->csi_z[pos2];
      g2v3.SetXYZ(g2px,g2py,g2pz);
      tgt2E=tgtInfo->sE[2];
      tgt2pl=tgtInfo->targL[2];
      // Fill various histograms
      //clust->targetEloss(tgt1E,tgt1pl,tgt2E,tgt2pl);
      //clust->fillHistos(g1px,g1py,g1pz,Eg1,g2px,g2py,g2pz,Eg2);
      if(i % 1000==0){
        std::cout<<" ievt.. "<<i<<std::endl;
        std::cout<<" --- gamma1 the max element is: "<<Eg1<<"\t"<<pos1<<"\t"<<csiInfo->csi_pz[pos1]<<std::endl;
        std::cout<<" --- gamma2 the max element is: "<<Eg2<<"\t"<<pos2<<"\t"<<csiInfo->csi_pz[pos2]<<std::endl;
        std::cout<<"-----------------------------------------------------------\n";
      }

      // construct LV for pi0 from 2gamma LV
      pi0lv=g1lv+g2lv;
      // Fill ROOT histos
      //h1MassG->Fill(Eg1+Eg2);
    }
    endLoop:
    // need to reset fired values to false
    fired1=false; fired2=false;
  } // end of event loop
}
