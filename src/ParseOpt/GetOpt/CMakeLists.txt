# 将指定目录下的所有源文件存入到变量, 但不会递归目录.
aux_source_directory(. GetOpt_source)

set(LibName GetOpt)
# 添加一个库目标, 是静态库还是动态库由BUILD_SHARED_LIBS变量决定.
add_library(${LibName} ${GetOpt_source})

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

# 设置库目标的属性.
set_property(TARGET ${LibName} PROPERTY VERSION "1.0.0")
set_property(TARGET ${LibName} PROPERTY SOVERSION "1")

# 添加安装规则
set(installable_libs ${LibName} tutorial_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES getopt.h DESTINATION include)
