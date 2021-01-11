cmake_minimum_required(VERSION 3.15)

# 项目名称及版本号.
project(Tutorial VERSION 1.0.0)

# 如果是msvc编译器, 这添加编译器选项. 选项/source-charset:utf-8告诉编译器使用utf8读取源文件.
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# 添加一个INTERFACE库(一个伪库目标), 专门用于设置编译器选项. 好处是只有连接到该库的编译器选项才生效.而不是全局的编译器选项.
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# 添加编译器的选项
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# 设置静态库,动态库的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# 由用户决定是否静态链接库还是动态链接库.
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# CMake通过config.h.in文件将一些设置以宏的方式导入到源码中(config.h).
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 添加CMake的子项目, 子项目有自己的CMakeLists.txt, 该命令会使cmake立即去处理子目录, 完成后才继续执行.
add_subdirectory(./src/MathFunctions)

# 将指定目录下的所有源文件并存入到变量, 但不会递归目录.
aux_source_directory(./src root_source)

# 添加一个可执行目标
add_executable(${PROJECT_NAME} ${root_source})

# 链接库目标. 类似于GCC的-l选项
target_link_libraries(${PROJECT_NAME} PUBLIC MathFunctions)

# 设置编译器头文件的查找路径,类似于GCC的-I选项. 由于 config.h 文件会被写入到输出目录中, 因此需要添加输出目录, 以及可选库的头文件.
target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
)

# 添加安装目标, 相对路径则以CMAKE_INSTALL_PREFIX为前缀路径.
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
)

# 提示性文本
message(STATUS "### generate project [" ${PROJECT_NAME} "] command: cmake -B " ${PROJECT_BINARY_DIR})
message(STATUS "### build project [" ${PROJECT_NAME} "] command: cmake --build " ${PROJECT_BINARY_DIR})
message(STATUS "### install project [" ${PROJECT_NAME} "] command: cmake --install " ${PROJECT_BINARY_DIR})
message(STATUS "### program will be install to: " ${CMAKE_INSTALL_PREFIX})