cmake_minimum_required(VERSION 3.16)
project("Better_Dwarf_Fortress")

set(CMAKE_CXX_STANDARD 17)

# Qt6 modules requis
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

# Automatisation Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include dirs
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Sources et UI
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE UIS CONFIGURE_DEPENDS src/UI/*.ui)

# Exécutable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${UIS}  # Obligatoire pour que AUTOUIC les traite
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/Better_Dwarf_Fortress_autogen/include
)

# Link Qt
target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    opengl32
)
