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
  int getMaxN(){return nmax;};
private:
  std::string fileName;
  std::string nameRoot;
  int nmax;
};
#endif
