cmake_minimum_required(VERSION 2.8.4)
project(vocgen)

find_package( OpenCV REQUIRED )


include_directories(${PROJECT_SOURCE_DIR}/include)
# dynamic linking
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(SOURCE_FILES main.cpp file_io.cpp)
add_executable(vocgen ${SOURCE_FILES})
target_link_libraries(vocgen ${OpenCV_LIBS} )
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(vocgen ${PROJECT_SOURCE_DIR}/lib/libDBoW2.so)