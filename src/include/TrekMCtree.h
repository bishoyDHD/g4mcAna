#ifndef TrekMCtree_HH
#define TrekMCtree_HH 1

#include <array>
#include <TObject.h>
#include <TString.h>
#include <map>

class TrekMCtree : public TObject {
public:
  TrekMCtree();
  ~TrekMCtree();
  ClassDef(TrekMCtree,1);
};

class TrekEventInfo: public TrekMCtree{
public:
  Int_t run;
  Int_t event;
  Int_t n, lable, lablePi01, lablePi02;
  Int_t trid[7];

  // state vector variables before the B-field:
  //  Needed for msc study --> G4 & Ext. Kalman Filter
  Double_t svx, svy, svz, svL;
  Double_t svnx, svny, svnz;
  Double_t psv; //momentum of state vector before B-field
  TrekEventInfo();
  ~TrekEventInfo();
  ClassDef(TrekEventInfo,2);
};

class TrekTargetInfo: public TrekMCtree{
public:
  Int_t n;
  //Double_t tg_x, tg_y, tg_z;
  //Double_t tp_x, tp_y, tp_z, t_p;
  std::array<Double_t,7> trid;
  std::array<Double_t,7> tg_x, tg_y, tg_z;
  std::array<Double_t,7> tp_x, tp_y, tp_z, t_p;
  Double_t tgt_dirx, tgt_diry, tgt_dirz;
  std::array<Double_t,7> targetE;
  std::array<Double_t,7> genEne;
  std::vector<Double_t> tgt_x, tgt_y, tgt_z;
  std::vector<Double_t> tgtPx, tgtPy, tgtPz;
  std::vector<Double_t> targetdE; 
  std::vector<Double_t> targetdt;
  std::array<Double_t,7> targL;
  // target surface variables
  Double_t sx, sy, sz, sE[7];
  std::map<Int_t,TString> particleDef;
  Double_t snx, sny, snz, totP;
  int dummy;
  
  TrekTargetInfo();
  ~TrekTargetInfo();
  ClassDef(TrekTargetInfo,2);
};

class TrekSftInfo: public TrekMCtree{
public:
  Int_t SFTid[2];
  Double_t SFTwposx[2];
  Double_t SFTwposy[2];
  Double_t SFTwposz[2];
  Double_t SFTpx[2];
  Double_t SFTpy[2];
  Double_t SFTpz[2];
  Double_t SFTnx[2];
  Double_t SFTny[2];
  Double_t SFTnz[2];
  int dummy;

  TrekSftInfo();
  ~TrekSftInfo();
  ClassDef(TrekSftInfo,2);
};

class TrekTof1Info: public TrekMCtree{
public:
  Double_t tof1_E, tof1_P, tof1_pL;
  Double_t tof1_x, tof1_y, tof1_z;
  Double_t tof1_nx, tof1_ny, tof1_nz;
  Double_t tof1_px, tof1_py, tof1_pz;
  Double_t tof1wpos; //[3];
  Double_t t1;

  TrekTof1Info();
  ~TrekTof1Info();
  ClassDef(TrekTof1Info,2);
};

class TrekAcInfo: public TrekMCtree{
public:
  Int_t dRays, photoEl;
  Double_t ac_E, acEkin, acMom, ac_pathL;
  Double_t ac_x, ac_y, ac_z;
  Double_t acp_x, acp_y, acp_z;
  Double_t acn_x, acn_y, acn_z;
  TrekAcInfo();
  ~TrekAcInfo();
  ClassDef(TrekAcInfo,2);
};

class TrekMwpcInfo: public TrekMCtree{
public:
  std::vector<Int_t> gapNo;
  std::vector<Double_t> c2_x, c2_y, c2_z;
  Double_t c3_x, c3_y, c3_z;
  Double_t c4_x, c4_y, c4_z;

  std::vector<Double_t> c2p_x, c2p_y, c2p_z;
  Double_t c3p_x, c3p_y, c3p_z;
  Double_t c4p_x, c4p_y, c4p_z;

  std::vector<Double_t> c2dir_x; 
  std::vector<Double_t> c2dir_y; 
  std::vector<Double_t> c2dir_z; 
  std::vector<Double_t> c2wpos_x;
  std::vector<Double_t> c2wpos_y;
  std::vector<Double_t> c2wpos_z;
  std::vector<Double_t> c2_p;
  int dummy;

  Double_t c3dir_x;  
  Double_t c3dir_y;  
  Double_t c3dir_z;  
  Double_t c3wpos_x; 
  Double_t c3wpos_y; 
  Double_t c3wpos_z; 
  Double_t c3edep; 

  Double_t c4dir_x;
  Double_t c4dir_y;
  Double_t c4dir_z;
  Double_t c4wpos_x;
  Double_t c4wpos_y;
  Double_t c4wpos_z;
  Double_t c4edep; 
  Double_t plen;
  TrekMwpcInfo();
  ~TrekMwpcInfo();
  ClassDef(TrekMwpcInfo,2);
};

class TrekGvInfo: public TrekMCtree{
public:
  std::array<Double_t,12> eneGapVeto;

  TrekGvInfo();
  ~TrekGvInfo();
  ClassDef(TrekGvInfo,2);
};

class TrekTof2Info: public TrekMCtree{
public:
  std::vector<Int_t> gapNo;
  std::vector<Double_t> tof2_E, tof2_P, tof2_pL;
  std::vector<Double_t> tof2_x, tof2_y, tof2_z;
  std::vector<Double_t> tof2_nx, tof2_ny, tof2_nz;
  std::vector<Double_t> tof2_px, tof2_py, tof2_pz;
  std::vector<Double_t> t2;

  std::vector<Double_t> px;
  std::vector<Double_t> py;
  std::vector<Double_t> pz;
  int dummy;

  TrekTof2Info();
  ~TrekTof2Info();
  ClassDef(TrekTof2Info,2);
};

class TrekPgcInfo: public TrekMCtree{
public:
  Double_t pgc_E;
  Double_t time;
  TString particle;

  TrekPgcInfo();
  ~TrekPgcInfo();
  ClassDef(TrekPgcInfo,2);
};

class TrekTtcInfo: public TrekMCtree{
public:
  std::vector<Int_t> gapNo;
  std::vector<Double_t> ttc_E; //required for triggering

  // surface outside the TTC for msc testing
  std::vector<Double_t> ttcS_E, ttcS_P, ttc_pL;
  std::vector<Double_t> ttc_x,  ttc_y,  ttc_z;
  std::vector<Double_t> ttc_nx, ttc_ny, ttc_nz;
  std::vector<Double_t> ttc_px, ttc_py, ttc_pz;
  std::vector<Double_t> ttc_p;
  int dummy;
  TrekTtcInfo();
  ~TrekTtcInfo();
  ClassDef(TrekTtcInfo,2);
};

class TrekCsiInfo: public TrekMCtree{
public:
  std::vector<TString> particle;
  std::vector<Int_t> lable, lablePi01, lablePi02;
  std::vector<Int_t> csiID, trackID;
  std::vector<Double_t> ECsI, addEcsi;
  std::vector<Double_t> csi_x, csi_y, csi_z;
  std::vector<Double_t> csi_px, csi_py, csi_pz;
  std::vector<Double_t> csi_plen, csi_phi, csi_theta;
  std::vector<Double_t> t_CsI;
  int dummy;

  TrekCsiInfo();
  ~TrekCsiInfo();
  ClassDef(TrekCsiInfo,2);
};
#endif
