cmake_minimum_required(VERSION 3.2)
project(generic)
set(CMAKE_CXX_STANDARD 23)
set(SOURCES_PATH ${CMAKE_SOURCE_DIR}/source)

set(HEADERS
)
set (SOURCES
	${SOURCES_PATH}/main.cpp
)
find_package(nlohmann_json REQUIRED)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)