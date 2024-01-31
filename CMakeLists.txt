cmake_minimum_required(VERSION 3.26)
project(SimuTradeX)

set(CMAKE_CXX_STANDARD 17)


add_executable(SimuTradeX OrderBook.cpp
        main.cpp)
