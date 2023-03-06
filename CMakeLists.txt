cmake_minimum_required(VERSION 3.25.2)

project(hserialize)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/include")

add_library(${PROJECT_NAME}_lib SHARED 
    lib_src/array.cpp
    lib_src/core.cpp
    lib_src/object.cpp
    lib_src/primitive.cpp)

add_library(${PROJECT_NAME}_lib::serialize ALIAS ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/lib_src)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib::serialize)