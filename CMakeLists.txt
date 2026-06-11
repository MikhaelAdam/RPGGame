cmake_minimum_required(VERSION 3.30)
project(RPGGame)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
if(POLICY CMP194)
    cmake_policy(SET CMP194 NEW)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPM_DOWNLOAD_VERSION 0.42.3) 


file(DOWNLOAD
    "https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.3/CPM.cmake"
    "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
    EXPECTED_HASH SHA256=a609e875fd532b067174250f6abbc3dac22fe2d64869783fb1e80bda1625c844
)

include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
set(LIBS)

CPMAddPackage("gh:libsdl-org/SDL#8e37db5")
list(APPEND LIBS SDL3::SDL3)

set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
CPMAddPackage("gh:libsdl-org/SDL_image#bec9134")
list(APPEND LIBS SDL3_image::SDL3_image)

add_subdirectory(src)