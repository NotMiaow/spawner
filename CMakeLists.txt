cmake_minimum_required(VERSION 3.7)
project(spawner)

include_directories(
    ${PROJECT_SOURCE_DIR}/_lib
    ${PROJECT_SOURCE_DIR}/_lib/basic_lib
    ${PROJECT_SOURCE_DIR}/headers
)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(source)

SET(CMAKE_CXX_FLAGS -pthread)
add_executable(${PROJECT_NAME} source/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spawner_lib)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})