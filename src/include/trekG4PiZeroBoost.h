#ifndef trekG4PiZeroBoost_h
#define trekG4PiZeroBoost_h
// simple template to calculate the 
// generalized boost of pi0

using std::pow;
using std::sqrt;
template<typename T>
class trekG4PiZeroBoost{
public:
  trekG4PiZeroBoost();
  trekG4PiZeroBoost(double Px,double Py,double Pz){
    px=Px; py=Py; pz=Pz;
    p_piP=sqrt(pow(px,2)+pow(py,2)+pow(pz,2));
  };
  double calcEpi0();
  double getBx();
  double getBy();
  double getBz();
private:
  const double M_k=.493677,m_piP=.13957018;
  double p_piP;
  double px,py,pz,E;
  double bx,by,bz,Epi0,EpiP;
};
template<typename T>
double trekG4PiZeroBoost<T>::calcEpi0(){
  EpiP=sqrt(pow(p_piP,2)+pow(m_piP,2));
  Epi0=M_k-EpiP;
  return Epi0;
}
template<typename T>
double trekG4PiZeroBoost<T>::getBx(){
  bx=px/calcEpi0();
  return bx;
}
template<typename T>
double trekG4PiZeroBoost<T>::getBy(){
  bx=px/calcEpi0();
  return by;
}
template<typename T>
double trekG4PiZeroBoost<T>::getBz(){
  bx=px/calcEpi0();
  return bz;
}
#endif
