#ifndef trekG4Var_h
#define trekG4Var_h 1

#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>

class trekG4Var{
public:
  trekG4Var(); //default constructor
  ~trekG4Var(); // destructor
  void printUsage(std::string name);
  bool parseArgs(int argc, char** argv);
  std::string getFile(){return fileName;};
  std::string getName(){return nameRoot;};
  inline bool getHelp(){return writeHelp;}
  int getEventMax(){return nmax;};
  int getChannel(){return channel;};
  double getMass(){return mass;};
  double getThreshold(){return threshold;};
private:
  std::string fileName;
  std::string nameRoot;
  int nmax, channel;
  double mass,threshold;
  bool writeHelp;
};
#endif
