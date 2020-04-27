#include "trekG4AnalysisManager.h"
#include "trekG4Mass2.h"

trekG4AnalysisManager::trekG4AnalysisManager():chNum(-1),
nentries(-1){
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
  h1M2=new TH1D("mass2", "Mass Squared",150,-15000.0,35000);
  h1P[0]=new TH1D("targetP", "Charged Particle Momentum in the Target",75,0.0,.25);
  h1P[1]=new TH1D("mwpcP", "Charged Particle Momentum at C4",75,0.0,.25);
  clust->setChannel(channel);
  chNum=channel;
  switch(channel){
    case 3:
      std::cout<<" --- Alright Channel 3 is ready for business!!! \n";
      n1="Opening angle between #mu^{+} and e^{+}e^{-}: cos(#theta_{#mu^{+}e^{+}e^{-}})";
      n2="Opening angle between e^{+}e^{-}: cos(#theta_{e^{+}e^{-}})";
      n3="Total energy of e^{+}e^{-}: E_{e^{+}e^{-}}";
      n4="Invariant mass of e^{+}e^{-}";
      clust->setNumOfSecondaries(2);
      clust->defHistos(n1,n2,n3,n4);
      setClusterPID("e^{+}","e^{-}",dummy,dummy,dummy,dummy);
      clust->setPID("e^{+}","e^{-}");
      clust->primaryPID("#pi^{+}","e^{+}e^{-}",dummy,dummy);
      break;
    case 7:
      std::cout<<" --- Checking out channel number 7 for kicks!!! \n";
      n1="Opening angle between #pi^{+}#pi^{0}: cos(#theta_{#pi^{+}#pi^{0}})";
      n2="Opening angle between 2#gamma: cos(#theta_{2#gamma})";
      n3="2#gamma total energy: E_{2#gamma}";
      n4="Invariant mass of #pi^{0}";
      clust->setNumOfSecondaries(2);
      clust->defHistos(n1,n2,n3,n4);
      setClusterPID("gamma","gamma",dummy,dummy,dummy,dummy);
      clust->setPID("#gamma1","#gamma2");
      clust->primaryPID("#pi^{+}","#pi^{0}",dummy,dummy);
      break;
    case 14:
      std::cout<<" --- Alright Channel 14 is ready for business!!! \n";
      n1="Opening angle between #mu^{+}A': cos(#theta_{#mu^{+}A'})";
      n2="Opening angle between e^{+}e^{-}: cos(#theta_{e^{+}e^{-}})";
      n3="Total energy of e^{+}e^{-}: E_{e^{+}e^{-}}";
      n4="Invariant mass of A'";
      clust->setNumOfSecondaries(2);
      clust->defHistos(n1,n2,n3,n4);
      setClusterPID("e+","e-",dummy,dummy,dummy,dummy);
      clust->setPID("e^{+}","e^{-}");
      clust->primaryPID("#mu^{+}","A'",dummy,dummy);
      break;
    case 16:
      std::cout<<" --- Alright Channel 16 is ready for business!!! \n";
      n1="Opening angle between #mu^{+}e^{+}e^{-}: cos(#theta_{#mu^{+}e^{+}e^{-}})";
      n2="Opening angle between e^{+}e^{-}: cos(#theta_{e^{+}e^{-}})";
      n3="Total energy of e^{+}e^{-}: E_{e^{+}e^{-}}";
      n4="Invariant mass of e^{+}e^{-}";
      clust->setNumOfSecondaries(2);
      clust->defHistos(n1,n2,n3,n4);
      clust->setPID("e^{+}","e^{-}");
      clust->primaryPID("#mu^{+}","e^{+}e^{-}",dummy,dummy);
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

void trekG4AnalysisManager::analyze(TFile* pfile,int evtMax=-1){
  TTree* pTree=(TTree*)pfile->Get("K+");
  pTree->SetBranchAddress("MCevtInfo", (TObject **) &evtInfo);
  pTree->SetBranchAddress("MCtgtInfo", (TObject **) &tgtInfo);
  pTree->SetBranchAddress("MCmwpcInfo", (TObject **) &mwpcInfo);
  pTree->SetBranchAddress("MCcsiInfo", (TObject **) &csiInfo);
  pTree->SetBranchAddress("MCttcInfo", (TObject **) &ttcInfo);
  pTree->SetBranchAddress("MCtof1Info", (TObject **) &tof1Info);
  pTree->SetBranchAddress("MCtof2Info", (TObject **) &tof2Info);
  // if no max number of events specified
  // default is to run all the events in the ROOT file
  if(evtMax<0)
    nentries=pTree->GetEntries();
  else
    nentries=evtMax;
  double g1x, g1y, g1z;
  double g2x, g2y, g2z;
  double g3x, g3y, g3z;
  int labelPi0;
  clust->setThreshold(threshold);
  // make sure that the gap momentum >=150 MeV
  double k=149.;
  double pc4=0.,p_tgt=0.;
  // Event loop...
  //std::cout<<" Entering event loop... \n";
  for(Int_t i=0; i<nentries; i++){
    pTree->GetEntry(i);
    // clear these entries at the beginning of every event
    g1E.clear();   index1.clear();
    g2E.clear();   index2.clear();
    g3E.clear();   index3.clear();
    clust->empty();
    // make sure this is a good gap event: 
    // ensure gap momentum is experimental (>=150MeV)
    size=tof2Info->tof2_P.size();
    greaterThan<double> gtof2(tof2Info->tof2_P, size, k);
    size=ttcInfo->ttc_p.size();
    greaterThan<double> gttc(ttcInfo->ttc_p, size, k);
    size=mwpcInfo->c2_p.size();
    greaterThan<double> gc2(mwpcInfo->c2_p, size, k);
    // check experimental trigger condition. 
    // skip if not triggered
    if(tgtInfo->dummy<0 || ttcInfo->dummy<0 || tof2Info->dummy<0 || tof1Info->tof1_E<0){
      goto endLoop;
    }
    // make sure good track in the gap
    if(gtof2.countGreater()==0 || gttc.countGreater()==0 ||
       tof1Info->tof1_E<=k || gc2.countGreater()==0){
      goto endLoop;
    }
    //std::cout<<"***** Good gap event!\n";
    // detected charged particle vertex info.
    primpx=tgtInfo->tp_x[0]*GeV;
    primpy=tgtInfo->tp_y[0]*GeV;
    primpz=tgtInfo->tp_z[0]*GeV;
    p_tgt=std::sqrt(std::pow(primpx,2)+std::pow(primpy,2)+std::pow(primpz,2));
    pc4=std::sqrt(std::pow(mwpcInfo->c4p_x,2)+std::pow(mwpcInfo->c4p_y,2)+
                  std::pow(mwpcInfo->c4p_z,2));
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
    // Lorentz Vector and invariant mass eval for tgt secondaries
    clust->set2ndryParticle(sec1px,sec1py,sec1pz,sec1E,1);
    clust->set2ndryParticle(sec2px,sec2py,sec2pz,sec2E,2);
    // obtain energy of secondary particle once they exit the target
    targetEloss[1]=(sec1E-tgtInfo->targetE[1]*GeV);
    targetEloss[2]=(sec2E-tgtInfo->targetE[2]*GeV);
    // Fill histogram for mass2 & charged particle momentum
    for(UInt_t n=0; n<tof2Info->tof2_P.size(); n++){
      if(tof2Info->tof2_P[n]>=150. && pc4>=150.){
        trekG4Mass2<double> m2(tof1Info->t1,tof2Info->t2[n],tof1Info->tof1_pL,
                               tof2Info->tof2_pL[n],pc4);
        h1M2->Fill(m2.mass2());
        h1P[0]->Fill(p_tgt);
        h1P[1]->Fill(pc4*GeV);
        // fill target momenta for good gap events.
        if(chNum==7 || chNum==14 || chNum==16){
          //std::cout<<"************* Entering Fill Momentum method\n";
          clust->fillMomentum(0,p_tgt);
          clust->fillMomentum(1,sec1E);
          clust->fillMomentum(2,sec2E);
          clust->fillMomentum(pc4*GeV);
        }
        // correct for target energy-loss event-by-event.
        if(chNum==7 || chNum==14 || chNum==16){
          //std::cout<<"************* Entering Fill Momentum method\n";
          clust->setTargetEloss(1,targetEloss[1]);
          clust->setTargetEloss(2,targetEloss[2]);
        }
      }
    }
    //std::cout<<"---- checking the size here: "<<size<<" : "<<gtof2.countGreater()<<"\n";
    // entering CsI analysis segment
    for(UInt_t j=0; j<csiInfo->csiID.size(); j++){
      if(csiInfo->csiID[j]>=0 && csiInfo->addEcsi[j]>=threshold){
        labelPi0=csiInfo->lablePi01[j];
	csiID=csiInfo->csiID[j];
	csiE=csiInfo->addEcsi[j]/1000.;
	fired1=true;
	clust->setClusterVar(csiID,csiE);
      }
    } // end of CsI for-loop
    if(fired1){
      Eprim=.10854562540178539;
      clust->evalClusters();
      //clust->fillHistos();
      clust->empty();
    } // end of fired1 if-loop
    endLoop:
    if(i % 1000==0){
      std::cout<<" ievt.. "<<i<<std::endl;
      std::cout<<"-----------------------------------------------------------\n";
    }
    // need to reset fired values to false
    fired1=false; fired2=false;  fired3=false;
  } // end of event for-loop
  //clust->plotHistos();
}
