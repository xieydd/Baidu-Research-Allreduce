cmake_minimum_required(VERSION 3.12)

project(allreduce)

#if(CMAKE_COMPILER_IS_GNUCXX)
#    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
#        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
#        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
#    endif()
#endif()
#
#if(APPLE)
#    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
#    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
#    set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
#    set(CMAKE_MACOSX_RPATH 1)
#endif()
#
#if(WIN32)
#    add_definitions(-DUNICODE -D_UNICODE)
#    set(TARGET_ARCHITECTURE "x86")
#endif()
#
include_directories(SYSTEM ${MPI_INCLUDE_PATH})


SET(CMAKE_C_COMPILER g++)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")
add_compile_options( -lstdc++ -std=c++11)

find_package( MPI REQUIRED )
#include_directories( /Users/xieyuandong/opt/openmpi/openmpi-4.0.0/include )
include_directories( SYSTEM ${MPI_INCLUDE_PATH} )
#link_directories( ${LD_LIBRARY_PATH} )

add_executable(allreduce main.cpp)
#target_link_libraries(allreduce /Users/xieyuandong/opt/openmpi/openmpi-4.0.0/lib/ )
target_link_libraries(allreduce ${LD_LIBRARY_PATH} )
