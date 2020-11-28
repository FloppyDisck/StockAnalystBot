project(web-tools)

add_library(${PROJECT_NAME} src/redditscraper.cpp)
add_library(mod::web ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} httplib nlohmann_json::nlohmann_json)