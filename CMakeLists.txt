cmake_minimum_required(VERSION 3.21)
project(master_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(master_cpp
        main.cpp
        defines.h
        master/master.cpp
        master/master.h
        network/network.cpp
        network/network.h
        packet/packet_struct.h
        crc/crc.cpp
        crc/crc.h
        packet/packet.cpp
        packet/packet.h)
