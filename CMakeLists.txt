cmake_minimum_required(VERSION 3.0.0)
project(Project2 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/test)

#AudioFile.h and Boost 1.78
include_directories(${CMAKE_SOURCE_DIR}/lib)

#OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Project2 src/main.cpp src/AudioEncoder.cpp src/AudioEncoder.h src/AudioPredictor.cpp src/AudioPredictor.h src/ImagePredictor.h src/ImagePredictor.cpp src/ImageEncoder.h src/ImageEncoder.cpp)
target_link_libraries( Project2 ${OpenCV_LIBS} )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)