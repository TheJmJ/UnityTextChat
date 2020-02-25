# COPYRIGHT: JONI MUSTAKANGAS

cmake_minimum_required(VERSION 3.7)
# Set CMake modules search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# Set CMake SDL PATHS

set(PROJECTNAME MyGame)

project(${PROJECTNAME})
# Set CMake modules search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# Set CMake SDL PATHS
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2/)
set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_image/)
set(SDL2_mixer_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_mixer/)
set(SDL2_net_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_net/)
set(SDL2_TTF_PATH ${CMAKE_SOURCE_DIR}/SDL2/SDL2_ttf/)
message(${SDL2_DIR})
message(${SDL2_image_DIR})
message(${SDL2_mixer_DIR})
message(${SDL2_net_DIR})
message(${SDL2_TTF_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
include_directories(
${SDL2_INCLUDE_DIRS} 
${SDL2_IMAGE_INCLUDE_DIRS} 
${SDL2_MIXER_INCLUDE_DIRS} 
${SDL2_NET_INCLUDE_DIR} 
${SDL2_TTF_INCLUDE_DIR}  )

add_executable(${PROJECTNAME} src/Main.cpp)
LINK_DIRECTORIES(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARY} ${SDL2_NET_LIBRARY} ${SDL2_TTF_LIBRARY})
find_library(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARY} ${SDL2_NET_LIBRARY} ${SDL2_TTF_LIBRARY})

target_link_libraries(${PROJECTNAME} 
${SDL2_LIBRARIES} 
${SDL2_IMAGE_LIBRARIES} 
${SDL2_MIXER_LIBRARY} 
${SDL2_NET_LIBRARY}	
${SDL2_TTF_LIBRARY}	
)
link_directories(${PROJECTNAME} ${SDL2_MIXER_LIBRARY})
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
file (GLOB SDL2_image_DLL_FILES ${SDL2_image_DIR}/lib/x86/*.dll)
file (GLOB SDL2_mixer_DLL_FILES ${SDL2_mixer_DIR}/lib/x86/*.dll)
file (GLOB SDL2_net_DLL_FILES ${SDL2_net_DIR}/lib/x86/*.dll)
file (GLOB SDL2_ttf_DLL_FILES ${SDL2_TTF_PATH}/lib/x86/*.dll)
file (GLOB IMAGES_C ${CMAKE_SOURCE_DIR}/img/*.bmp *.png *tga *jpg *tif)


add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_image_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_mixer_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_net_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SDL2_ttf_DLL_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
#add_custom_target(build-time-make-directory ALL
#    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/img/)
add_custom_command(
	TARGET ${PROJECTNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/img/)
add_custom_command(
        TARGET ${PROJECTNAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${IMAGES_C}
                ${CMAKE_CURRENT_BINARY_DIR}/img/)
  