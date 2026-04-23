cmake_minimum_required(VERSION 3.16)
project(online_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(online_library
    src/Author.cpp
    src/Book.cpp
    src/Catalog.cpp
    src/Library.cpp
    src/Loan.cpp
    src/LoanFactory.cpp
    src/ReservationQueue.cpp
    src/Review.cpp
    src/SearchCriteria.cpp
    src/Subscription.cpp
    src/User.cpp
    src/main.cpp
)
