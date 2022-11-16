#Make 最低版本号要求
cmake_minimum_required(VERSION 3.10.2)

#项目信息
project(bohan)

#include路径
include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/base
)

# 查找当前目录下的所有源文件
#并将名称保存到 LIB_SRC 变量
#aux_source_directory(./ LIB_SRC)

add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(examples)

# 设置可执行文件生成路径
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib) 

#生成debug版本
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -std=c++17 -fPIC  -Wno-write-strings -g -ggdb")

set(LIBRARY_OUTPUT_PATH ./libs)
set(OUTPUT_PATH     ./out) 

#其他系统库
#ADD_LIBRARY(base SHARED ${LIB_SRC})


