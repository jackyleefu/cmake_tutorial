aux_source_directory(. MathFunctions_source)
# 添加一个库目标
add_library(MathFunctions ${MathFunctions_source})

# 只要链接到该库, 自动加入头文件路径.
target_include_directories(MathFunctions
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                           )

# 附加编译器选项.
target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

# 由用户决定是否使用该库.
option(USE_MYMATH "Use tutorial provided math implementation" ON)

if(USE_MYMATH)
  # 如果使用该库则添加编译器宏定义
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
endif()

if(BUILD_SHARED_LIBS)
  # 如果编译为动态库则添加编译器宏定义, windows的动态库的必须要有导出符号.
  target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")
endif()

# 设置库目标的属性.
set_property(TARGET MathFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET MathFunctions PROPERTY SOVERSION "1")

# 添加安装规则
set(installable_libs MathFunctions tutorial_compiler_flags)
install(TARGETS MathFunctions DESTINATION lib)
install(FILES src/MathFunctions.h DESTINATION include)
