// Mapper class for the CsI from e36g4MC
#ifndef trekG4CsImapper_H
#define trekG4CsImapper_H 1

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "trekG4Cluster.h"

class trekG4CsImapper{
public:
  trekG4CsImapper();
  ~trekG4CsImapper();
  void setCsImap(int csiID,int crysType,int iphi,int fb);
  std::map<int,std::pair<int,int>> getcsiMap();
  void readMap(); // actually read csiMap.dat file
private:
  // theta angles
  double mTheta[2][10]={86.25,78.75,71.25,63.75,56.25,48.75,41.25,33.75,26.25,18.75,
                       93.75,101.25,108.75,116.25,123.75,131.25,138.75,146.25,153.75,
                       161.25};
  // phi angles
  double wphi[48]={3.75,11.25,18.75,26.25,  //g3 -0
                   33.75,41.25,48.75,56.25, //g2 30
                   63.75,71.25,78.75,86.25, //g1 60
                   93.75,101.25,108.75,116.25, // g12 90
                   123.75,131.25,138.75,146.25, // g11 120
                   153.75,161.25,168.75,176.25, // g10 150
                   183.75,191.25,198.75,206.25, // g9 180
                   213.75,221.25,228.75,236.25, // g8 210
                   243.75,251.25,258.75,266.25, //g7 240
                   273.75,281.25,288.75,296.25, //g6 270
                   303.75,311.25,318.75,326.25, //g5 300
                   333.75,341.25,348.75,356.25}; //g4 330
  // channel 16 phi mapping
  // --> same angular distribution as in real data
  double phiCh16[24]={3.75,18.75,33.75,48.75,63.75,78.75,93.75,108.75,123.75,
	              138.75,153.75,168.75,183.75,198.75,213.75,228.75,243.75,
		      258.75,273.75,288.75,303.75,318.75,333.75,348.75};
  double theta, phi, z, csiID;
  std::pair<double,double> thetaPhi;
  std::map<int,std::pair<double,double>> csiMap;
  std::map<std::pair<double,double>,double> csiClust;
  std::string fname;
  std::ifstream mapFile;
  trekG4Cluster* fcluster;
};
#endif
