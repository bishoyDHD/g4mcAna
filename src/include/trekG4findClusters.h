#ifndef trekG4findClusters_h
#define trekG4findClusters_h 1

#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <map>

class trekG4findClusters{
public:
  trekG4findClusters();
  ~trekG4findClusters();
  void findClusters(std::map<std::pair<double,double>,double> csiClust,std::vector<double> csiE,std::vector<double> csiTheta,std::vector<double> csiPhi);
private:
  typedef std::vector<double> ve;
  //extern ve indexph;
  ve indexph;
  // function that returns highest value of std::vector
  // then iterate in decending order from max->min
  std::size_t get_nthIndex(ve, std::size_t k);
  std::vector<double> *phval, *clusth, *clusphi;
  std::pair<double,double> angP1, angP2, angP3, angP4;
  std::pair<double,double> angP5, angP6, angP7, angP8;
  std::pair<double,double> angE1, angE2, angE3, angE4, angE5;
  std::pair<double,double> angE6, angE7, angE8, angE9, angE10;
  std::pair<double,double> tppair;
  double posTheta, negTheta, posPhi, negPhi; // adding or subtracting 7.5*deg
  std::vector<double> csThet,csPhi;
  std::map<std::pair<double,double>,bool> csiCheck;
  double ntheta,nphi,Eclus,thetaE,phiE,clusZ,clusR;
  int clusCrys;
  int numOfsingleClus,numOfClus;
};
#endif
