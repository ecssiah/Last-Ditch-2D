cmake_minimum_required(VERSION 3.0)

project(LastDitch)

set(
  HEADERS
  ./LastDitch.h
  ./src/SDL_Interface.h
  ./src/Utils.h
  ./src/systems/ConfigurationSystem.h
  ./src/systems/TimeSystem.h
  ./src/systems/InputSystem.h
  ./src/systems/EntitySystem.h
  ./src/systems/InventorySystem.h
  ./src/systems/PhysicsSystem.h
  ./src/systems/MapSystem.h
  ./src/systems/CameraSystem.h
  ./src/systems/UISystem.h
  ./src/systems/InventoryUISystem.h
  ./src/systems/ProductionUISystem.h
  ./src/systems/ManagementUISystem.h
  ./src/systems/StatusUISystem.h
  ./src/systems/RenderSystem.h)

set(
  SOURCES
  ./LastDitch.cc
  ./src/SDL_Interface.cc
  ./src/Utils.cc
  ./src/systems/ConfigurationSystem.cc
  ./src/systems/TimeSystem.cc
  ./src/systems/InputSystem.cc
  ./src/systems/EntitySystem.cc
  ./src/systems/InventorySystem.cc
  ./src/systems/PhysicsSystem.cc
  ./src/systems/MapSystem.cc
  ./src/systems/CameraSystem.cc
  ./src/systems/UISystem.cc
  ./src/systems/InventoryUISystem.cc
  ./src/systems/ProductionUISystem.cc
  ./src/systems/ManagementUISystem.cc
  ./src/systems/StatusUISystem.cc
  ./src/systems/RenderSystem.cc)

add_executable(LastDitch ${HEADERS} ${SOURCES})

target_compile_features(LastDitch PRIVATE cxx_range_for)

set(
  CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/dist/cmake/Modules")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

find_package(Eigen3 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Box2D REQUIRED)
find_package(YamlCpp REQUIRED)

include_directories(
  ${EIGEN_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${BOX2D_INCLUDE_DIR}
  ${YAMLCPP_INCLUDE_DIR})

set(SDL2_COMPILE_FLAGS "-I/usr/include/SDL2")
set(SDL2_LINK_FLAGS "-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf")

target_link_libraries(
  LastDitch
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARY}
  ${SDL2_TTF_LIBRARY}
  ${BOX2D_LIBRARY}
  ${YAMLCPP_LIBRARY})

set(COMPILE_FLAGS "-g")

set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS} ${SDL2_COMPILE_FLAGS}")
set(
  CMAKE_EXE_LINKER_FLAGS
  "${CMAKE_EXE_LINKER_FLAGS} ${SDL2_LINK_FLAGS}")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/scripts)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
  DESTINATION .)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/dist/scripts
  DESTINATION .)
