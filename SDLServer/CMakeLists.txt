# COPYRIGHT: JONI MUSTAKANGAS

cmake_minimum_required(VERSION 3.7)
# Set CMake modules search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# Set CMake SDL PATHS

set(PROJECTNAME ChatServer)

project(${PROJECTNAME})
# Set CMake modules search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# Set CMake SDL PATHS
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2/)
set(SDL2_net_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_net/)
message(${SDL2_DIR})
message(${SDL2_net_DIR})
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
include_directories(
${SDL2_INCLUDE_DIRS} 
${SDL2_NET_INCLUDE_DIR} )

add_executable(${PROJECTNAME} src/Main.cpp)
LINK_DIRECTORIES(${SDL2_LIBRARIES} ${SDL2_NET_LIBRARY})
find_library(${SDL2_LIBRARIES} ${SDL2_NET_LIBRARY})

target_link_libraries(${PROJECTNAME} 
${SDL2_LIBRARIES} 
${SDL2_NET_LIBRARY}	
)
file (GLOB CPP_FILES src/*.cpp)
file (GLOB H_FILES src/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

#Post Build SCRIPT
#define build path
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
#    ${PROJECT_SOURCE_DIR}/lib CACHE
#    PATH "Directory where all the .lib files are dumped." FORCE)
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#    ${PROJECT_SOURCE_DIR}/bin CACHE
#    PATH "Directory where .exe and .dll files are dumped." FORCE)
file (GLOB SDL2_DLL_FILES ${SDL2_DIR}/lib/x86/*.dll)
file (GLOB SDL2_net_DLL_FILES ${SDL2_net_DIR}/lib/x86/*.dll)

add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_net_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
  