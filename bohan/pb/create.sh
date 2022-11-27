#!/bin/sh
###
 # @Author: bohan.lj
 # @Date: 2022-11-27 18:19:12
 # @FilePath: /Bohan/bohan/pb/create.sh
 # @LastEditors: bohan.lj
 # @LastEditTime: 2022-11-27 18:53:58
 # @Description: srouce_code
### 
SRC_DIR=./
DST_DIR=./gen

#C++
mkdir -p $DST_DIR/cpp
protoc -I=$SRC_DIR --cpp_out=$DST_DIR/cpp/ $SRC_DIR/*.proto

#JAVA
mkdir -p $DST_DIR/java
protoc -I=$SRC_DIR --java_out=$DST_DIR/java/ $SRC_DIR/*.proto

#PYTHON
mkdir -p $DST_DIR/python
protoc -I=$SRC_DIR --python_out=$DST_DIR/python/ $SRC_DIR/*.proto
