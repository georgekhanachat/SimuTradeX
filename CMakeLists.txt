cmake_minimum_required(VERSION 3.26)

project(SimuTradeX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(SimuTradeXLib ${SOURCES})
add_executable(SimuTradeX main.cpp)

target_link_libraries(SimuTradeX SimuTradeXLib)
install(TARGETS SimuTradeXLib SimuTradeX
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
