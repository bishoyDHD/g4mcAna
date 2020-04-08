#ifndef trekG4PiZeroBoost_h
#define trekG4PiZeroBoost_h
// simple template to calculate the 
// generalized boost of pi0

#include <TFile.h>
#include <TLorentzVector.h>

using std::pow;
using std::sqrt;
template<typename T>
class trekG4PiZeroBoost{
public:
  trekG4PiZeroBoost();
  trekG4PiZeroBoost(double Px,double Py,double Pz){
    px=Px; py=Py; pz=Pz;
    p_piP=sqrt(pow(px,2)+pow(py,2)+pow(pz,2));
    EpiP=sqrt(pow(p_piP,2)+pow(m_piP,2));
  };
  double calcEpi0();
  void Boost();
  double Bx();
  double By();
  double Bz();
  inline double B2(){return b2;}
  inline double Px(){return px_cm;}
  inline double Py(){return py_cm;}
  inline double Pz(){return pz_cm;}
  inline double E(){return E_cm;}
  inline double Gamma(){return gamma;}
  inline void gammaLV(double Px,double Py,double Pz,double Energy){
    px_g=Px; py_g=Py; pz_g=Pz; E_g=Energy;
  }
  inline void gammaLV(const TLorentzVector lv){
    px_g=lv.Px(); py_g=lv.Py(); pz_g=lv.Pz(); E_g=lv.E();
  }
private:
  inline void SetPx(double Px){px_cm=Px;}
  inline void SetPy(double Py){py_cm=Py;}
  inline void SetPz(double Pz){pz_cm=Pz;}
  inline void SetE(double Energy){E_cm=Energy;}
  inline void SetGamma(double Gamma){gamma=Gamma;}
  inline void SetB2(double beta2){b2=beta2;}
  const double M_k=.493677,m_piP=.13957018;
  double gamma,b2;
  double p_piP;
  double px,py,pz;
  double px_cm,py_cm,pz_cm,E_cm;
  double px_g,py_g,pz_g,E_g;
  double bx,by,bz,Epi0,EpiP;
};
template<typename T>
double trekG4PiZeroBoost<T>::calcEpi0(){
  Epi0=M_k-EpiP;
  return Epi0;
}
template<typename T>
double trekG4PiZeroBoost<T>::Bx(){
  bx=px/calcEpi0();
  return bx;
}
template<typename T>
double trekG4PiZeroBoost<T>::By(){
  by=py/calcEpi0();
  return by;
}
template<typename T>
double trekG4PiZeroBoost<T>::Bz(){
  bz=pz/calcEpi0();
  return bz;
}
template<typename T>
void trekG4PiZeroBoost<T>::Boost(){
  //Boost this Lorentz vector
  b2 = Bx()*Bx() + By()*By() + Bz()*Bz();
  gamma = 1.0 / TMath::Sqrt(1.0 - b2);
  Double_t bp = Bx()*px_g + By()*py_g + Bz()*pz_g;
  Double_t gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;
  
  SetB2(b2);
  SetGamma(gamma);
  SetPx(px_g + gamma2*bp*Bx() + gamma*Bx()*E_g);
  SetPy(py_g + gamma2*bp*By() + gamma*By()*E_g);
  SetPz(pz_g + gamma2*bp*Bz() + gamma*Bz()*E_g);
  SetE(gamma*(E() + bp));
}
#endif
