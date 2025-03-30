cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME VulkanEngine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

project(${PROJECT_NAME} VERSION 0.0.1)

if (MSVC)
  unset(CMAKE_INCLUDE_SYSTEM_FLAG_CXX)
  unset(_CMAKE_INCLUDE_SYSTEM_FLAG_CXX_WARNING)
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)
file(GLOB_RECURSE SHADERS src/*.frag src/*.vert)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${SHADERS})

find_package(glm REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(stb REQUIRED)
find_package(tinyobjloader REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SHADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  glm::glm
  glfw
  Vulkan::Vulkan
  stb::stb
  tinyobjloader::tinyobjloader
)

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE
  GLFW_INCLUDE_VULKAN
  GLM_FORCE_RADIANS
  GLM_FORCE_DEPTH_ZERO_TO_ONE
  STB_IMAGE_IMPLEMENTATION
  TINYOBJLOADER_IMPLEMENTATION
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

message("Output binary directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("SOURCES: ${SOURCES}")
message("HEADERS: ${HEADERS}")
