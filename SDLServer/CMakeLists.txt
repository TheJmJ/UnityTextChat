#USER DEFINED VARIABLES
#set(CLIENTNAME Client) #Defina your ClientName
#set(SERVERNAME Server) #Define your ServerName
set(ProjectConf_GameClientName "Client" CACHE FILEPATH "Give your game name format GameName_Client")
set(ProjectConf_GameServertName "Server" CACHE FILEPATH "Give your server name format ServerName_Server")
set(CLIENTNAME ${ProjectConf_GameClientName}) #Defina your ClientName
set(SERVERNAME ${ProjectConf_GameServertName}) #Define your ServerName

# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required (VERSION 3.2.3)
if (COMMAND cmake_policy)
    # Libraries linked via full path no longer produce linker search paths
    cmake_policy (SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
    # Honor the visibility properties for SHARED target types only
    cmake_policy (SET CMP0063 OLD)
endif ()
# Set project name
#project (${CLIENTNAME})
# Set CMake modules search path
#set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/)
#include(${CMAKE_SOURCE_DIR}/CMake/ProjectCommon.cmake)

# Set project name
project (${SERVERNAME})
# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/)
include(${CMAKE_SOURCE_DIR}/CMake/ProjectCommon.cmake)
# Include UrhoCommon.cmake module after setting project name
#include (UrhoCommon)
# Define target name
set (TARGET_NAME ${SERVERNAME})
# Define source files
#define_source_files ()
#file (GLOB CPP_FILES src/Server/*.cpp)
#file (GLOB H_FILES src/Server*.h)
#set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
#add_executable(${SERVERNAME} ${SOURCE_FILES})
setup_server_exe()