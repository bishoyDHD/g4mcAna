#ifndef trekG4Mass2_h
#define trekG4Mass2_h 1
// Template class to calculate beta2 and mass2

#include <TRandom3.h>
#include <random>

template<typename T> 
class trekG4Mass2{
public:
  trekG4Mass2();
  trekG4Mass2(double t1,double t2,double pl1,double pl2,double p){
  tof1=t1; tof2=t2; plen=(pl2-pl1)/1000.;
  P=p;
  dt=(t2-t1)*1e-9;
  };
  double beta2();
  double mass2();
protected:
  const double c=2.99792458e8;
private:
  double beta, b2, M2;
  double tof1, tof2, plen, P, dt;
};
template<typename T> 
double trekG4Mass2<T>::beta2(){
  beta=plen/(gRandom->Gaus(dt,100e-12)*c);
  b2=beta*beta;
  return b2;
}
template<typename T> 
double trekG4Mass2<T>::mass2(){
  M2=P*P*(1/beta2()-1);
  return M2;
}
#endif
