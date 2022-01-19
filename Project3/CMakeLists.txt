cmake_minimum_required(VERSION 3.0.0)
project(Project3 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/test)

#external ibs:
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/../lib)


#OpenCV
#find_package( OpenCV REQUIRED )
#include_directories( ${OpenCV_INCLUDE_DIRS} )

# fcm executable
set(FCMODEL_FILES src/fmc/FCModel.h src/fmc/FCModelFactory.cpp src/fmc/FCModelFactory.h src/fmc/FCModelContext.h )
set(UTILS src/utils/math_utils.h)

add_executable(fcm src/fmc/fcm.cpp ${FCMODEL_FILES} ${UTILS} )