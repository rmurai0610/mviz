cmake_minimum_required(VERSION 3.14)
project(mviz)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 3.7.0
  GIT_PROGRESS TRUE)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.85
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(raylib imgui)

add_library(
  imgui STATIC
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_demo.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_draw.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_tables.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${FETCHCONTENT_BASE_DIR}/imgui-src)

add_library(mviz STATIC src/rlImGui.cpp)
target_link_libraries(mviz PUBLIC raylib imgui)

if(APPLE)
  target_link_libraries(
    mviz
    PUBLIC
      "-framework Cocoa, -framework OpenGL, -framework IOKit, -framework CoreVideo"
  )
endif()

target_include_directories(
  mviz PUBLIC ./include ${FETCHCONTENT_BASE_DIR}/raylib/examples/shaders)

add_executable(demo src/demo.cc)
target_link_libraries(demo PUBLIC mviz)
