cmake_minimum_required(VERSION 3.14)  # 设置 CMake 最低版本需求
project(MyProject VERSION 1.0)      # 定义项目名和版本

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 设置用于 Emscripten 的工具链
set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist)

# 包含 FetchContent 模块
include(FetchContent)

# 获取 nlohmann/json 从 GitHub
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(MyApp src/image_processor.cpp)
target_include_directories(MyApp PRIVATE ${json_SOURCE_DIR}/include)

# 设置 Emscripten 的特定编译选项
set_target_properties(MyApp PROPERTIES
  OUTPUT_NAME "index"
  SUFFIX ".html"
  COMPILE_FLAGS "-s WASM=1"
  LINK_FLAGS "-s EXPORTED_FUNCTIONS='[\"_processImage\", \"_malloc\", \"_free\"]' -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]' --shell-file ${CMAKE_SOURCE_DIR}/html_template/shell_minimal.html"
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

