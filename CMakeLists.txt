cmake_minimum_required(VERSION 3.5)
#Top level CmakeLists.txt

project(g4mcAna)

#add_subdirectory(trkDictdir)
FIND_PACKAGE(OpenMP)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core Thread dl Minuit MathCore RIO Hist Tree Net)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include
                    ${ROOT_INCLUDE_DIR})

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.h)

##### FOR THE ROOT COMPILER #########################
EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
### Need to set CMAKE_FLAGS for root otherwise program will not compile
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

##### FOR THE ROOT LINKER #########################
EXECUTE_PROCESS(COMMAND root-config --glibs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
set(ROOT_LIBRARIES ${ROOT_LIBRARIES})
#####################################################

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

ROOT_GENERATE_DICTIONARY(dictDir ${CMAKE_CURRENT_SOURCE_DIR}/src/include/TrekMCtree.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/src/include/trekG4LinkDef.hh)


#add binary called "e32g4mcAna" built from main.cxx
add_executable(e36g4mcAna e36G4Ana.cxx dictDir ${sources} ${headers})

#link executable to the e36g4mcAna
if(OpenMP_CXX_FOUND)
	target_link_libraries(e36g4mcAna PUBLIC OpenMP::OpenMP_CXX "-L${ROOT_LIBRARY_DIR}" ${ROOT_LIBRARIES})
endif()
# copy *.dat files into build dir
set(datFiles
  csiMap.dat
  )
foreach(_script ${datFiles})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

