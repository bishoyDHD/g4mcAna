# g4mcAna
Analysis code for e36G4MC

This example is rather straightforward to run, simply do the following:
1. Create a build directroy in the g4mcAna/ dir:
   ~$ cd g4mcAna/
   ~$ mkdir buildAna

2. Change into the buildAna/ dir:
   ~$ cd buildAna

3. Create a build environment by running cmake and compile using make:
   ~$ cmake ../
   ~$ make -jN
   Here N represents the number of cores. Make sure that cmake has successfully created a build environment.
