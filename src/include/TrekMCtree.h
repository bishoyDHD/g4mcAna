#ifndef TrekMCtree_HH
#define TrekMCtree_HH 1

#include "TObject.h"

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
  Double_t trid[7];
  Double_t tg_x[7], tg_y[7], tg_z[7];
  Double_t tp_x[7], tp_y[7], tp_z[7], t_p[7];
  Double_t tgt_x[256], tgt_y[256], tgt_z[256];
  Double_t tgt_dirx, tgt_diry, tgt_dirz;
  Double_t targetE[7];
  Double_t genEne[10];
  Double_t tgtP[256];
  Double_t tgtPx[256], tgtPy[256], tgtPz[256];
  Double_t targetdE[256]; 
  Double_t targetdt[256];
  Double_t targL[7];
  // target surface variables
  Double_t sx, sy, sz, sE[7];
  Double_t snx, sny, snz, totP;
  
  TrekTargetInfo();
  ~TrekTargetInfo();
  ClassDef(TrekTargetInfo,2);
};

class TrekSftInfo: public TrekMCtree{
public:
  Double_t SFTwposx[2];
  Double_t SFTwposy[2];
  Double_t SFTwposz[2];
  Double_t SFTpx[2];
  Double_t SFTpy[2];
  Double_t SFTpz[2];
  Double_t SFTnx[2];
  Double_t SFTny[2];
  Double_t SFTnz[2];

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
  Int_t gapNo[12];
  Double_t c2_x[12], c2_y[12], c2_z[12];
  Double_t c3_x, c3_y, c3_z;
  Double_t c4_x, c4_y, c4_z;

  Double_t c2p_x[12], c2p_y[12], c2p_z[12];
  Double_t c3p_x, c3p_y, c3p_z;
  Double_t c4p_x, c4p_y, c4p_z;

  Double_t c2dir_x[12]; 
  Double_t c2dir_y[12]; 
  Double_t c2dir_z[12]; 
  Double_t c2wpos_x[12];
  Double_t c2wpos_y[12];
  Double_t c2wpos_z[12];

  Double_t c3dir_x;  
  Double_t c3dir_y;  
  Double_t c3dir_z;  
  Double_t c3wpos_x; 
  Double_t c3wpos_y; 
  Double_t c3wpos_z; 

  Double_t c4dir_x;
  Double_t c4dir_y;
  Double_t c4dir_z;
  Double_t c4wpos_x;
  Double_t c4wpos_y;
  Double_t c4wpos_z;
  Double_t plen;
  TrekMwpcInfo();
  ~TrekMwpcInfo();
  ClassDef(TrekMwpcInfo,2);
};

class TrekGvInfo: public TrekMCtree{
public:
  Double_t eneGapVeto[12];

  TrekGvInfo();
  ~TrekGvInfo();
  ClassDef(TrekGvInfo,2);
};

class TrekTof2Info: public TrekMCtree{
public:
  Int_t gapNo[12];
  Double_t tof2_E[12], tof2_P[12], tof2_pL[12];
  Double_t tof2_x[12], tof2_y[12], tof2_z[12];
  Double_t tof2_nx[12], tof2_ny[12], tof2_nz[12];
  Double_t tof2_px[12], tof2_py[12], tof2_pz[12];
  Double_t t2[12];

  Double_t px[12];
  Double_t py[12];
  Double_t pz[12];

  TrekTof2Info();
  ~TrekTof2Info();
  ClassDef(TrekTof2Info,2);
};

class TrekPgcInfo: public TrekMCtree{
public:
  Double_t pgc_E, gamma_Ch;
  Double_t enePGC[12];

  TrekPgcInfo();
  ~TrekPgcInfo();
  ClassDef(TrekPgcInfo,2);
};

class TrekTtcInfo: public TrekMCtree{
public:
  Int_t gapNo[12];
  Double_t ttc_E[12]; //required for triggering

  // surface outside the TTC for msc testing
  Double_t ttcS_E[12], ttcS_P[12], ttc_pL[12];
  Double_t ttc_x[12],  ttc_y[12],  ttc_z[12];
  Double_t ttc_nx[12], ttc_ny[12], ttc_nz[12];
  Double_t ttc_px[12], ttc_py[12], ttc_pz[12];
  TrekTtcInfo();
  ~TrekTtcInfo();
  ClassDef(TrekTtcInfo,2);
};

class TrekCsiInfo: public TrekMCtree{
public:
  Int_t csiID[768], trackID[768];
  Double_t ECsI[768], addEcsi[768];
  Double_t csi_x[768], csi_y[768], csi_z[768];
  Double_t csi_px[768], csi_py[768], csi_pz[768];
  Double_t csi_plen[768], csi_phi[768], csi_theta[768];
  Double_t t_CsI[768];

  TrekCsiInfo();
  ~TrekCsiInfo();
  ClassDef(TrekCsiInfo,2);
};
#endif
