#include <trekVar.h>

trekVar::trekVar():nameRoot("e36g4MC.root"){

}
trekVar::~trekVar(){

}
void trekVar::printUsage(std::string name){
  std::cout<<" Usage:       "<<name<<" source"<<std::endl;
  std::cout<<" Must specify simulation file to be analyzed!!!"<<std::endl;
  std::cout<<" -f:          Name of the simulation file\n";
  std::cout<<" -n #number:  maximum number of events to be processed, currently moot.\n";
  std::cout<<" -o out.root: string out.root is the name of the output ROOT file. By default, it is e36g4MC.root\n";
  std::cout<<" Example:     ./e36g4mcAna -[opt1] -[opt2] /path/to/G4Sim.root\n";
  std::cout<<" -h:          Print this help menu\n";
}

bool trekVar::parseArgs(int argc, char** argv){
  if(argc==1) return false;
  bool writeHelp=false;
  for(int i=1; i<argc; i++){
    if(argv[i][0]=='-'){
      switch(argv[i][1]){
        case 'h':
	  writeHelp=true;
	  break;
	case 'n':
	  nmax=std::stoul(argv[i+1]);
	  break;
	case 'f':
	  fileName=argv[i+1];
	  break;
	case 'o':
	  nameRoot=argv[i+1];
	  break;
      }// end of switch statement
    }// end of top if loop
    else{
      fileName=argv[i];
    }
  }
  if(writeHelp){
    if(nmax>0){
      std::cout<<" Max number of evens: "<<nmax<<std::endl;
    }
  }
  return true;
}