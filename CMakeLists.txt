cmake_minimum_required(VERSION 3.15)
project(StockAnalyst)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

# The library MUST BE PRE-COMPILED
# Read over their cmake for more information
find_package(httplib REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)


set(SPECIAL_OS_LIBS "pthread")

add_subdirectory(web-scraper)
add_subdirectory(tests)