cmake_minimum_required(VERSION 3.23)
project(COMP345_Warzone)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP345_Warzone
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        CardsDriver.h
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        GameEngineDriver.h
        Map.cpp
        Map.h
        MapDriver.cpp
        MapDriver.h
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        OrdersDriver.h
        Player.cpp
        Player.h
        PlayerDriver.cpp
        PlayerDriver.h)
