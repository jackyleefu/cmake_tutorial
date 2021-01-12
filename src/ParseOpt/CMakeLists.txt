# 配置子目录, 子项目下有自己的CMakeLists.txt, cmake会立即去配置子目录, 等待完成后才继续执行.
if(MSVC)
  message(STATUS "### generate GetOpt for MSVC")
  add_subdirectory(./GetOpt)
endif()

# 将指定目录下的所有源文件存入到变量, 但不会递归目录.
aux_source_directory(. ParseOpt_source)

set(LibName ParseOpt)
# 添加一个库目标, 是静态库还是动态库由BUILD_SHARED_LIBS变量决定.
add_library(${LibName} ${ParseOpt_source})

# 只要某个目标链接到该库,那个目标就自动加入指定的查找路径; 而编译自己时则不需要. 
target_include_directories(${LibName} 
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    "${CMAKE_BINARY_DIR}"
)

# 链接库, tutorial_compiler_flags 目标库用于附加编译器选项.
target_link_libraries(${LibName} PUBLIC tutorial_compiler_flags)

if(MSVC)
  message(STATUS "### link GetOpt for MSVC")
  target_link_libraries(${LibName} PRIVATE GetOpt)
endif()

# 设置库目标的属性.
set_property(TARGET ${LibName} PROPERTY VERSION "1.0.0")
set_property(TARGET ${LibName} PROPERTY SOVERSION "1")

# 添加安装规则
set(installable_libs ${LibName} tutorial_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES parseOpt.h DESTINATION include)
