cmake_minimum_required(VERSION 3.14)
project(mviz)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
if(NOT BUILD_EXAMPLES_MVIZ)
  set(BUILD_EXAMPLES_MVIZ False)
endif()

include(FetchContent)
find_package(Eigen3)
find_package(manif)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.0.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.85
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(raylib imgui)

if(NOT Eigen3_FOUND)
  FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

  set(BUILD_TESTING OFF)
  set(EIGEN_BUILD_PKGCONFIG OFF)
  FetchContent_MakeAvailable(Eigen)
  add_library(Eigen3::Eigen ALIAS eigen)

endif()
if(NOT manif_FOUND)
  FetchContent_Declare(
    manif
    GIT_REPOSITORY https://github.com/artivis/manif
    GIT_TAG 0.0.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)
  FetchContent_MakeAvailable(manif)

endif()

add_library(
  imgui STATIC
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_demo.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_draw.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_tables.cpp
  ${FETCHCONTENT_BASE_DIR}/imgui-src/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${FETCHCONTENT_BASE_DIR}/imgui-src)

add_library(mviz STATIC src/rlImGui.cpp src/camera.cc)
target_link_libraries(mviz PUBLIC raylib imgui)

if(APPLE)
  target_link_libraries(
    mviz
    PUBLIC
      "-framework Cocoa, -framework OpenGL, -framework IOKit, -framework CoreVideo"
  )
endif()

target_include_directories(
  mviz PUBLIC ./include ${FETCHCONTENT_BASE_DIR}/raylib-src/examples/shaders)

if(BUILD_EXAMPLES_MVIZ)
  add_executable(demo src/demo.cc)
  target_link_libraries(demo PUBLIC mviz)
endif()
