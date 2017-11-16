cmake_minimum_required(VERSION 3.8)
project(CppLab)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp learn/primer.cpp learn/primer.h lab4.cpp lab5.cpp lab6.cpp lab1.cpp lab2.cpp)
#add_executable(CppLab ${SOURCE_FILES})


set(BUILD_1 lab1)
set(SOURCE_FILES_1 lab1.cpp)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

#set(BUILD_2 lab2)
#set(SOURCE_FILES_2 lab2.cpp)
#add_executable(${BUILD_2} ${SOURCE_FILES_2})

#set(BUILD_1 lab3)
#set(SOURCE_FILES_1 lab3.cpp)
#add_executable(${BUILD_1} ${SOURCE_FILES_1})

#set(BUILD_2 lab4)
#set(SOURCE_FILES_2 lab4.cpp)
#add_executable(${BUILD_2} ${SOURCE_FILES_2})

#set(BUILD_1 lab5)
#set(SOURCE_FILES_1 lab5.cpp)
#add_executable(${BUILD_1} ${SOURCE_FILES_1})

#set(BUILD_2 lab6)
#set(SOURCE_FILES_2 lab6.cpp)
#add_executable(${BUILD_2} ${SOURCE_FILES_2})

#set(BUILD_2 A)
#set(SOURCE_FILES_2 A)
#add_executable(${BUILD_2} ${SOURCE_FILES_2})