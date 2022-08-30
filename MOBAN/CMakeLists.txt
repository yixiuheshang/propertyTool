project(propertyExcelTool)
cmake_minimum_required(VERSION 3.24)

add_definitions(
    "-std=c++14"
    "-frtti"
    "-fexceptions"
    #"-g"
    "-O3"
    "-O2"
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/
)

file(GLOB SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/lib)
# 指定可执行文件存放目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件
# add_executable(propertyExcelTool ${SRC_LIST})
# 构建可执行程序
add_executable(propertyExcelTool ${SRC_LIST})
target_link_libraries(propertyExcelTool libjsoncpp.a)