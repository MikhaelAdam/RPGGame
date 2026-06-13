add_subdirectory(components)
add_subdirectory(state)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texturemanager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texturemanager.cpp
)