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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
    ${CMAKE_CURRENT_BINARY_DIR}/src/AbstractClass
    ${CMAKE_CURRENT_BINARY_DIR}/assets/images
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

# Sources et UI
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.hpp)
file(GLOB_RECURSE UIS CONFIGURE_DEPENDS src/UI/*.ui)



if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")
endif()

# Exécutable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}  
)

#SD2 manual
find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIBRARY NAMES SDL2)

if(NOT SDL2_INCLUDE_DIR OR NOT SDL2_LIBRARY)
    message(FATAL_ERROR "SDL2 not found")
endif()

find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image)

find_package(OpenGL REQUIRED)  
find_library(GLU_LIBRARY NAMES GLU glu32)



target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AbstractClass
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/images
    ${CMAKE_CURRENT_BINARY_DIR}/Better_Dwarf_Fortress_autogen/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

# Link Qt
target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    OpenGL::GL
    ${GLU_LIBRARY}
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC_MACRO_NAMES "Q_OBJECT")