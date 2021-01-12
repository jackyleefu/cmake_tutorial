cmake_minimum_required(VERSION 3.15)

# 项目名称及版本号. 可通过 <PROJECT-NAME>_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MINOR, <PROJECT-NAME>_VERSION_PATCH, and <PROJECT-NAME>_VERSION_TWEAK变量查询版本
# 也可以通过 PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_TWEAK四个变量查询版本，它们是最近一个project()命令指定的版本
project(Tutorial VERSION 1.0.0)

# 使用生成器表达式添加编译器选项. 如果是msvc编译器, 则添加编译器选项:/source-charset:utf-8, 该选项告诉MSVC编译器用utf8编码读源文件.
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

# GCC没有多架构配置, 默认的输出目录直接在项目的二进制目录下.
# MSVC使用了多配置架构, MSVC默认的输出目录是在子目录下的--config选项指定的配置目录下
# 下面命令设置MSVC下静态库和动态库的输出目录为${PROJECT_BINARY_DIR}路径下的--config选项指定的配置目录下,GCC与默认相同.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# 是否静态库还是动态库的用户选项. 它是一个布尔类型的缓存变量, 可通过 cmake-gui、ccmake、cmake -D USE_MYMATH=ON 修改或者手动修改生成目录下的 CMakeCache.txt文件后重新生成
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
if(BUILD_SHARED_LIBS)
  # 如果编译为动态库则添加编译器宏定义, windows的动态库的必须要有导出符号.
  add_compile_definitions("EXPORTING_DLL")
endif()

# CMake通过输入文件将一些设置输出到头文件中.
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 配置子目录, 子项目下有自己的CMakeLists.txt, cmake会立即去配置子目录, 等待完成后才继续执行.
if(MSVC)
  message(STATUS "### generate GetOpt for MSVC")
  add_subdirectory(./src/GetOpt)
endif()
# 配置子目录, 子项目下有自己的CMakeLists.txt, cmake会立即去配置子目录, 等待完成后才继续执行.
add_subdirectory(./src/ParseOpt)
# 配置子目录, 子项目下有自己的CMakeLists.txt, cmake会立即去配置子目录, 等待完成后才继续执行.
add_subdirectory(./src/UnicodeHelper)
# 配置子目录, 子项目下有自己的CMakeLists.txt, cmake会立即去配置子目录, 等待完成后才继续执行.
add_subdirectory(./src/MathFunctions)

# 将指定目录下的所有源文件存入到变量, 但不会递归目录.
aux_source_directory(./src root_source)

# 添加一个可执行目标
add_executable(${PROJECT_NAME} ${root_source})

# 为可执行目标添加链接库, 自动附加库的查找目录. GCC的-l和-L选项
target_link_libraries(${PROJECT_NAME} PUBLIC 
  MathFunctions 
  ParseOpt
  UnicodeHelper
)

# 设置编译器头文件的查找路径,类似于GCC的-I和-L选项. 由于 config.h 文件会被写入到二进制目录中, 因此需要添加输出目录.
target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
)

#************************************ 安装阶段 *******************************************#

# 如果用户没有设置CMAKE_INSTALL_PREFIX值, 则修改默认安装前缀到用户家目录下. 防止遇到目录权限问题.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND CMAKE_HOST_WIN32)
  set(CMAKE_INSTALL_PREFIX "$ENV{USERPROFILE}/${PROJECT_NAME}" CACHE PATH "install prefix" FORCE)
endif()

# 定义安装规则. 以后就可以使用: cmake --install <二进制目录> 命令行执行安装
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
)

# 提示性文本
message(STATUS "### generate project [" ${PROJECT_NAME} "] command: cmake -B " ${PROJECT_BINARY_DIR})
message(STATUS "### build project [" ${PROJECT_NAME} "] command: cmake --build " ${PROJECT_BINARY_DIR} " --config Release")
message(STATUS "### install project [" ${PROJECT_NAME} "] command: cmake --install " ${PROJECT_BINARY_DIR})
message(STATUS "### program will be install to: " ${CMAKE_INSTALL_PREFIX})