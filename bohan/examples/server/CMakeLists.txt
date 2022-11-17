#Make 最低版本号要求
cmake_minimum_required(VERSION 3.10.2)

#项目信息
project(tcp_server)

#include路径
include_directories(
${PROJECT_SOURCE_DIR}
#base
${PROJECT_SOURCE_DIR}/../../base
#net
${PROJECT_SOURCE_DIR}/../../net
)

# 查找当前目录下的所有源文件
#并将名称保存到 LIB_SRC 变量
aux_source_directory(./ LIB_SRC)

#三方库lib和头文件
#LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/../libs)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../build/libs)

#三方库lib和头文件
if(APPLE)
    SET(SPD_LOG_DIR ${PROJECT_SOURCE_DIR}/../../base/spdlog/lib/mac)
elseif(UNIX)
    SET(SPD_LOG_DIR ${PROJECT_SOURCE_DIR}/../../base/spdlog/lib/linux)
elseif(WIN32)
    SET(SPD_LOG_DIR ${PROJECT_SOURCE_DIR}/../../base/spdlog/lib/win32)
endif()

LINK_DIRECTORIES(${SPD_LOG_DIR})

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../output) 

#生成debug版本
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -std=c++17  -g -ggdb")

ADD_EXECUTABLE(tcp_server ${LIB_SRC})

TARGET_LINK_LIBRARIES(tcp_server 
   base
   net
   pthread
)


