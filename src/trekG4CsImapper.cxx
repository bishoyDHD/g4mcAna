#include "trekG4CsImapper.h"

trekG4CsImapper::trekG4CsImapper(){
}
trekG4CsImapper::~trekG4CsImapper(){
}
void trekG4CsImapper::init(){
 // Make sure readMap() function is called whenever program executes
 readMap(); 
}
void trekG4CsImapper::readMap(){
  fname="csiMap.dat";
  int icrys,itype,iphi,ifb;
  mapFile.open(fname);
  if(mapFile){
    for(int i=0; i<768; i++){
      mapFile>>icrys>>itype>>iphi>>ifb;
      if(itype<9){
	thetaPhi=std::make_pair(mTheta[ifb][itype],wphi[iphi]);
	csiMap[i]=thetaPhi; // create csi map
        //std::cout<<" csiID["<<i<<"]=("<<mTheta[ifb][itype]<<", "<<wphi[iphi]<<")\n";
      }
      if(itype==9){
	thetaPhi=std::make_pair(mTheta[ifb][itype],phiCh16[iphi]);
	csiMap[i]=thetaPhi; // create csi map
        //std::cout<<" csiID["<<i<<"]=("<<mTheta[ifb][itype]<<", "<<phiCh16[iphi]<<")\n";
      }
    }
  }else{
    std::cerr<<" ****** Error opening file ''"<<fname<<".'' Please make sure you have the file \n";
    std::abort();
  }
}
