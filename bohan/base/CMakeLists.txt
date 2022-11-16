#Make 最低版本号要求
cmake_minimum_required(VERSION 3.10.2)

#项目信息
project(base)

#include路径
include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/spdlog/include
)

# 查找当前目录下的所有源文件
#并将名称保存到 LIB_SRC 变量
aux_source_directory(./ LIB_SRC)


#三方库lib和头文件
if(APPLE)
    SET(SPD_LOG_DIR ./spdlog/lib/mac)
elseif(UNIX)
    SET(SPD_LOG_DIR ./spdlog/lib/linux)
elseif(WIN32)
    SET(SPD_LOG_DIR ./spdlog/lib/win32)
endif()

LINK_DIRECTORIES(${SPD_LOG_DIR})

# 设置可执行文件生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../libs) 

#生成debug版本
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -std=c++17  -g -ggdb")


#其他系统库
ADD_LIBRARY(base SHARED ${LIB_SRC})

target_link_libraries(base  spdlog)


