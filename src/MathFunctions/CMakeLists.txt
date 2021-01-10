aux_source_directory(. MathFunctions_source)
# add the library that runs
add_library(MathFunctions ${MathFunctions_source})

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(MathFunctions
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                           )

target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

if(USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
endif()

if(BUILD_SHARED_LIBS)
  # define the symbol stating we are using the declspec(dllexport) when
  # building on windows
  target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")
endif()

# setup the version numbering
set_property(TARGET MathFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET MathFunctions PROPERTY SOVERSION "1")

# install rules
set(installable_libs MathFunctions tutorial_compiler_flags)
install(TARGETS MathFunctions DESTINATION lib)
install(FILES src/MathFunctions.h DESTINATION include)
