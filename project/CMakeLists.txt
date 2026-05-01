cmake_minimum_required(VERSION 3.16)
project(online_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(online_library
    src/Catalog.cpp
    src/Library.cpp
    src/LoanFactory.cpp
    src/User.cpp
    src/main.cpp
)
