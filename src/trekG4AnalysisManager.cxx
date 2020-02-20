#include "trekG4AnalysisManager.h"

trekG4AnalysisManager::trekG4AnalysisManager(){
  std::cout<<" --- Starting trekG4AnalysisManager...\n";
  csiMapper=new trekG4CsImapper();
  clust=new trekG4Cluster();
}
void trekG4AnalysisManager::init(){
  // order is important here
  // trekG4CsiMapper() must be initialized before trekG4Cluster()
  csiMapper->init();
  clust->init();
  fired1=false;     tof1Info=NULL;
  fired2=false;     tof2Info=NULL;
  fired3=false;
  evtInfo=NULL;     ttcInfo=NULL;
  tgtInfo=NULL;
  csiInfo=NULL;
  mwpcInfo=NULL;
}
trekG4AnalysisManager::~trekG4AnalysisManager(){
  std::cout<<" --- Exiting trekG4AnalysisManager...\n";
  delete clust;
  delete csiMapper;
}
// Method is needed for assigning various cluster particles
// will be used for cluster PID in CsI(Tl)
void trekG4AnalysisManager::setClusterPID(std::string pid1,std::string pid2,std::string pid3,std::string pid4,std::string pid5,std::string pid6){
  clustPid1=pid1;     clustPid4=pid4;
  clustPid2=pid2;     clustPid5=pid5;
  clustPid3=pid3;     clustPid6=pid6;
}
void trekG4AnalysisManager::beginRoot(std::string name,int channel){
  outFile=new TFile(name.c_str(),"RECREATE");
  switch(channel){
    case 7:
      std::cout<<" --- Checking out channel numnber 7 for kicks!!! \n";
      n1="Opening angle between #pi^{+}#pi^{0}: cos(#theta_{#pi^{+}#pi^{0}})";
      n2="Opening angle between 2#gamma: cos(#theta_{2#gamma})";
      n3="2#gamma total energy: E_{2#gamma}";
      n4="Invariant mass of #pi^{0}";
      clust->defHistos(n1,n2,n3,n4);
      setClusterPID("gamma","gamma",dummy,dummy,dummy,dummy);
      clust->setPID("#gamma1","#gamma2",dummy,dummy,dummy,dummy);
      clust->primaryPID("#pi^{+}","#pi^{0}",dummy,dummy);
      break;
    case 14:
      std::cout<<" --- Alright Channel 14 is ready for business!!! \n";
      n1="Opening angle between #mu^{+}A': cos(#theta_{#mu^{+}A'})";
      n2="Opening angle between e^{+}e^{-}: cos(#theta_{e^{+}e^{-}})";
      n3="Total energy of e^{+}e^{-}: E_{e^{+}e^{-}}";
      n4="Invariant mass of A'";
      clust->defHistos(n1,n2,n3,n4);
      setClusterPID("e+","e-",dummy,dummy,dummy,dummy);
      clust->setPID("e^{+}","e^{-}",dummy,dummy,dummy,dummy);
      clust->primaryPID("#mu^{+}","A'",dummy,dummy);
      break;
  }// end of swith statement
  // set scoring mass here:
  clust->setScoreMass(mass);
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
  double g3x, g3y, g3z;
  int labelPi0;
  // Event loop...
  std::cout<<" Entering event loop... \n";
  for(Int_t i=0; i<nentries; i++){
    pTree->GetEntry(i);
    // clear these entries at the beginning of every event
    g1E.clear();   index1.clear();
    g2E.clear();   index2.clear();
    g3E.clear();   index3.clear();
    clust->empty();
    // make sure this is a good gap event: 
    // Check experimental trigger condition. 
    double k=225.;
    const int size=12;
    greaterThan<double,size> gtof2(tof2Info->tof2_E, size, k);
    greaterThan<double,size> gttc(ttcInfo->ttc_E, size, k);
    //std::cout<<"---- checking the size here: "<<size<<" : "<<gtof2.countGreater()<<"\n";
    // Skip if not triggered
    if(tgtInfo->dummy<0 || ttcInfo->dummy<0 || tof2Info->dummy<0 || tof1Info->tof1_E<0){
      goto endLoop;
    }
    // make sure good track in the gap
    if(gtof2.countGreater()==0 || gttc.countGreater()==0 || tof1Info->tof1_E<k) goto endLoop;
    //gT.countGreater();
    /*
    for(int n=0; n<12;n++){
      for(int m=0; m<3;m++){
        if(tgtInfo->targetE[m]<90.0 && tof1Info->tof1_E<90.0){
          if(ttcInfo->ttc_E[n]<90.0 && tof2Info->tof2_E[n]<=90.0){
	    goto endLoop;
	  }
	}
      }
    }*/
    for(int j=0; j<768; j++){
      if(csiInfo->csiID[j]>=0 /* && csiInfo->ECsI[j]<245*/){
        labelPi0=csiInfo->lablePi01[j];
        //if(labelPi0!=0) goto endLoop;
	  fired1=true;
	clust->setClusterVar(j,csiInfo->addEcsi[j]/1000.);
      }
    } // end of CsI for loop
    if(fired1){
      // particle 1
      // find max element and its corresponding index
      GeV=1/1000.0;
      // detected charged particle vertex info.
      primpx=tgtInfo->tp_x[0]*GeV;
      primpy=tgtInfo->tp_y[0]*GeV;
      primpz=tgtInfo->tp_z[0]*GeV;
      // 1st secondary particle vertex info.
      sec1px=tgtInfo->tp_x[1]*GeV;
      sec1py=tgtInfo->tp_y[1]*GeV;
      sec1pz=tgtInfo->tp_z[1]*GeV;
      sec1E=std::sqrt(sec1px*sec1px+sec1py*sec1py+sec1pz*sec1pz);
      // 2nd secondary particle vertex info.
      sec2px=tgtInfo->tp_x[2]*GeV;
      sec2py=tgtInfo->tp_y[2]*GeV;
      sec2pz=tgtInfo->tp_z[2]*GeV;
      sec2E=std::sqrt(sec2px*sec2px+sec2py*sec2py+sec2pz*sec2pz);
      Eprim=.10854562540178539;
      Eprim=.10854562540178539;
      clust->primtgtEloss(primpx, primpy, primpz, Eprim, primlen);
      clust->evalClusters();
      // Lorentz Vector and invariant mass eval for tgt secondaries
      clust->set2ndryParticle(sec1px,sec1py,sec1pz,sec1E,1);
      clust->set2ndryParticle(sec2px,sec2py,sec2pz,sec2E,2);
      //clust->fillHistos();
      clust->empty();
      /*
      Eg1=*max_element(g1E.begin(), g1E.end());
      d1=std::max_element(g1E.begin(), g1E.end())-g1E.begin();
      pos1=index1[d1]; //returns CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g1px=csiInfo->csi_px[pos1]; g1py=csiInfo->csi_py[pos1]; g1pz=csiInfo->csi_pz[pos1];
      g1x=csiInfo->csi_x[pos1]; g1y=csiInfo->csi_y[pos1]; g1z=csiInfo->csi_z[pos1];
      tgt1E=tgtInfo->sE[1];
      tgt1pl=tgtInfo->targL[1];
      // particle 2
      // find max element and its corresponding index
      Eg2=*max_element(g2E.begin(), g2E.end());
      d2=std::max_element(g2E.begin(), g2E.end())-g2E.begin();
      pos2=index2[d2]; //returns unique CsI copyID which will be used get physics info.
      // Get 4-vector info. and construct LV
      g2px=csiInfo->csi_px[pos2]; g2py=csiInfo->csi_py[pos2]; g2pz=csiInfo->csi_pz[pos2];
      g2x=csiInfo->csi_x[pos2]; g2y=csiInfo->csi_y[pos2]; g2z=csiInfo->csi_z[pos2];
      tgt2E=tgtInfo->sE[2];
      tgt2pl=tgtInfo->targL[2];
      primlen=tgtInfo->targL[0];
      // Set variables in case of 3-cluster events
      if(fired3){ // For now this is a special Kpi2 case for pi0->e+e-gamma
        // particle 3
        // find max element and its corresponding index
        Eg3=*max_element(g3E.begin(), g3E.end());
        d3=std::max_element(g3E.begin(), g3E.end())-g3E.begin();
        pos3=index3[d3]; //returns unique CsI copyID which will be used get physics info.
        // Get 4-vector info. and construct LV
        g3px=csiInfo->csi_px[pos3]; g3py=csiInfo->csi_py[pos3]; g2pz=csiInfo->csi_pz[pos3];
        tgt3E=tgtInfo->sE[3];
        tgt3pl=tgtInfo->targL[3];
        g3x=csiInfo->csi_x[pos3]; g3y=csiInfo->csi_y[pos3]; g3z=csiInfo->csi_z[pos3];
	// fill target variables
        clust->target3Eloss(tgt1E,tgt1pl);
        clust->target4Eloss(tgt2E,tgt2pl);
        clust->target1Eloss(tgt3E,tgt3pl);
	// fill 3 & 4-vector variables
	clust->setParticle3(g1px, g1py, g1pz, Eg1);
	clust->setParticle4(g2px, g2py, g2pz, Eg2);
	clust->setParticle1(g3px, g3py, g3pz, Eg3);
	goto endLoop;
      }
      // fill target variables
      clust->target1Eloss(tgt1E,tgt1pl);
      clust->target2Eloss(tgt2E,tgt2pl);
      // fill 3 & 4-vector variables
      clust->setParticle1(g1px, g1py, g1pz, Eg1);
      clust->setParticle2(g2px, g2py, g2pz, Eg2);
      // Fill various histograms
      //clust->targetEloss(tgt1E,tgt1pl,tgt2E,tgt2pl);
      clust->setPi0label(labelPi0);
      if(i % 1000==0){
        std::cout<<" ievt.. "<<i<<std::endl;
	//std::cout<<" --- pi0 channel label is:      "<<evtInfo->lablePi01<<std::endl;
        std::cout<<" --- charged particle px,py,pz: "<<primpx<<"\t"<<primpy<<"\t"<<primpz<<std::endl;
        std::cout<<" --- gamma1 the max element is: "<<Eg1<<"\t"<<pos1<<"\t"<<csiInfo->csi_pz[pos1]<<"\t"<<csiInfo->particle[pos1]<<std::endl;
        std::cout<<" --- gamma2 the max element is: "<<Eg2<<"\t"<<pos2<<"\t"<<csiInfo->csi_pz[pos2]<<std::endl;
        std::cout<<"-----------------------------------------------------------\n";
      }*/
    }
    endLoop:
    if(i % 1000==0){
      std::cout<<" ievt.. "<<i<<std::endl;
      std::cout<<"-----------------------------------------------------------\n";
    }
    // need to reset fired values to false
    fired1=false; fired2=false;  fired3=false;
  } // end of event loop
  //clust->plotHistos();
}
