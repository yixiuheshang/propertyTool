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
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(. SRC_LIST) 
# add_executable(propertyExcelTool ${SRC_LIST})
add_executable(propertyExcelTool ${SRC_LIST})
target_link_libraries(propertyExcelTool libjsoncpp.a)