#include <trekG4Var.h>

trekG4Var::trekG4Var():nameRoot("e36g4MC.root"),channel(7){

}
trekG4Var::~trekG4Var(){

}
void trekG4Var::printUsage(std::string name){
  std::cout<<" Usage:       "<<name<<" source"<<std::endl;
  std::cout<<" Must specify simulation file to be analyzed!!!"<<std::endl;
  std::cout<<" -c #channel: Enter corresponding signal channel number \n";
  std::cout<<"              to be used for cluster analysis \n";
  std::cout<<" -f:          Name of the simulation file\n";
  std::cout<<" -n #number:  maximum number of events to be processed, currently moot.\n";
  std::cout<<" -o out.root: string out.root is the name of the output ROOT file. By default, it is e36g4MC.root\n";
  std::cout<<" Example:     ./e36g4mcAna -[opt1] -[opt2] /path/to/G4Sim.root\n";
  std::cout<<" -h:          Print this help menu\n";
}

bool trekG4Var::parseArgs(int argc, char** argv){
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
	  i++;
	  break;
	case 'c':
	  channel=std::stoi(argv[i+1]);
	  i++;
	  break;
	case 'f':
	  fileName=argv[i+1];
	  i++;
	  break;
	case 'o':
	  nameRoot=argv[i+1];
	  i++;
	  break;
      }// end of switch statement
    }// end of top if loop
    else{ // default options
      fileName=argv[i];
      //channel=7;
    }
  }
  if(writeHelp){
    if(nmax>0){
      std::cout<<" Max number of evens: "<<nmax<<std::endl;
    }
  }
  return true;
}
