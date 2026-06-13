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

CPMAddPackage("gh:SanderMertens/flecs#d7d0c4f")
list(APPEND LIBS flecs::flecs)

CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    GIT_TAG master 
    DOWNLOAD_ONLY YES
)
if(imgui_ADDED)
    set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
    )

    add_library(imgui STATIC ${IMGUI_SOURCES})
    
    target_include_directories(imgui PUBLIC 
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
    )

    target_link_libraries(imgui PUBLIC SDL3::SDL3)
endif()
list(APPEND LIBS imgui)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Syncing modified assets..."
)

# Ties the asset target as a dependency to your executable
add_dependencies(${PROJECT_NAME} copy_assets)