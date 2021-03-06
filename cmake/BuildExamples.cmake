option(BUILD_EXAMPLES "Build examples." ON)
if (BUILD_EXAMPLES)
  message(STATUS "Build examples ENABLED")
  add_subdirectory (${PROJECT_SOURCE_DIR}/examples)
else()
  message(STATUS "Build examples DISABLED (you can activate unit tests with '-DBUILD_EXAMPLES=ON' cmake option)")
endif()
message(STATUS "-------------------------------------------------------------------------------")
