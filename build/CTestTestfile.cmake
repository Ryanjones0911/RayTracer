# CMake generated Testfile for 
# Source directory: /Users/ryan/RayTracer
# Build directory: /Users/ryan/RayTracer/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[all_tests]=] "/Users/ryan/RayTracer/build/all_tests")
set_tests_properties([=[all_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/ryan/RayTracer/CMakeLists.txt;32;add_test;/Users/ryan/RayTracer/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
