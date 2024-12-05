CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(imgui_opengl_starter)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(lib/include)

# ImGui: https://github.com/ocornut/imgui
INCLUDE_DIRECTORIES(external/imgui)
INCLUDE_DIRECTORIES(external/imgui/backends)

# GLFW: https://github.com/glfw/glfw
OPTION(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
OPTION(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
OPTION(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
OPTION(GLFW_INSTALL "Generate installation target" OFF)
OPTION(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
ADD_SUBDIRECTORY(external/glfw EXCLUDE_FROM_ALL)
INCLUDE_DIRECTORIES(external/glfw/include)
INCLUDE_DIRECTORIES(external/glfw/deps)

# OpenGL: https://www.opengl.org/
FIND_PACKAGE(OpenGL REQUIRED)

FILE(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "lib/source/*.cpp")
SET(IMGUI_SOURCES external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_demo.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp external/imgui/misc/cpp/imgui_stdlib.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC glfw ${OPENGL_LIBRARIES})
