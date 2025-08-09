cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("cubix" LANGUAGES CXX VERSION 1.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
    add_definitions(-DNOMINMAX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /Zc:preprocessor")
endif()


# Git info
set(GIT_BRANCH "main")
set(GIT_SHA "unknown")
set(GIT_COMMIT_COUNT "0")

string(TIMESTAMP NOW_UNIX "%s" UTC)
set(GIT_COMMIT_TIME ${NOW_UNIX})

find_package(Git QUIET)
if(GIT_FOUND)
    function(runGit VAR_NAME)
        execute_process(
            COMMAND "${GIT_EXECUTABLE}" ${ARGN}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE ${VAR_NAME}
            RESULT_VARIABLE COMMAND_RESULT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )

        if(COMMAND_RESULT EQUAL 0 AND NOT ${VAR_NAME} STREQUAL "")
            set(${VAR_NAME} "${${VAR_NAME}}" PARENT_SCOPE)
        endif()
    endfunction()

    runGit(GIT_BRANCH       branch --show-current)
    runGit(GIT_SHA          rev-parse --verify HEAD)
    runGit(GIT_COMMIT_COUNT rev-list --count HEAD)
    runGit(GIT_COMMIT_TIME  show -s --format=%ct)
endif()

message(STATUS "GIT_BRANCH is '${GIT_BRANCH}'")
message(STATUS "GIT_SHA is '${GIT_SHA}'")
message(STATUS "GIT_COMMIT_TIME is '${GIT_COMMIT_TIME}'")

add_compile_definitions(
    BUILD_TYPE="${CMAKE_BUILD_TYPE}"
    PREVIEW_BUILD="${PREVIEW_BUILD}"
    GIT_BRANCH="${GIT_BRANCH}"
    GIT_SHA="${GIT_SHA}"
    GIT_COMMIT_COUNT="${GIT_COMMIT_COUNT}"
    GIT_COMMIT_TIME="${GIT_COMMIT_TIME}"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_BUILD=1)
endif()

# Deps
include_directories("${CMAKE_SOURCE_DIR}/cubix/src-deps")

#RakNet
set (RAKNET_GENERATE_SAMPLES OFF CACHE BOOL "" FORCE)
set (RAKNET_ENABLE_DLL OFF CACHE BOOL "" FORCE)
if (WIN32)
    add_compile_definitions(RAKNET_SUPPORT_IPV6=1)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-deps/RakNet")
include_directories("${CMAKE_SOURCE_DIR}/cubix/src-deps/RakNet/Source")
if (WIN32)
    set_target_properties(RakNetLibStatic PROPERTIES STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:\"LIBCD.lib LIBCMTD.lib MSVCRT.lib\"" )
endif()

#RapidJSON
set (RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set (RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-deps/rapidjson")
include_directories("${CMAKE_SOURCE_DIR}/cubix/src-deps/rapidjson/include")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
#Zlib
add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-deps/zlib")

#Snappy
set(SNAPPY_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SNAPPY_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-deps/snappy")
include_directories(
    "${CMAKE_SOURCE_DIR}/cubix/src-deps/snappy"
    "${CMAKE_BINARY_DIR}/cubix/src-deps/snappy"
)

# src
add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src/common")

if (WIN32)
    add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src/win")
elseif (UNIX)
    add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src/linux")
endif()

# src-server
add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-server/common")

if (WIN32)
    add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-server/win")
elseif (UNIX)
    add_subdirectory("${CMAKE_SOURCE_DIR}/cubix/src-server/linux")
endif()