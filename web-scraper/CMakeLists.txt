project(web-scraper)

add_library(${PROJECT_NAME} src/webscraper.cpp)
add_library(mod::scraper ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} httplib nlohmann_json::nlohmann_json)