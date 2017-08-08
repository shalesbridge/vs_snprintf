cmake_minimum_required(VERSION 2.6)

option(test "Run tests." OFF)

set(PROJECT_NAME snprintf_compat)
 
add_library (snprintf_compat snprintf_compat.c snprintf_compat.h)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()


if (test)
	# Taken from documentation at https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project

	# Download and unpack googletest at configure time
	configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	  RESULT_VARIABLE result
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	if(result)
	  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
	  RESULT_VARIABLE result
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	if(result)
	  message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
			 ${CMAKE_BINARY_DIR}/googletest-build)

	# The gtest/gtest_main targets carry header search path
	# dependencies automatically when using CMake 2.8.11 or
	# later. Otherwise we have to add them here ourselves.
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
	  include_directories("${gtest_SOURCE_DIR}/include")
	endif()

	# Now simply link against gtest or gtest_main as needed. Eg
	add_executable(runTests tests.cpp)
	target_link_libraries(runTests gtest_main snprintf_compat)
	# add_test(NAME example_test COMMAND example)
endif()

# if (test)
# # Locate GTest
# add_subdirectory(googletest)
# set (GTEST_ROOT ${CMAKE_SOURCE_DIR}/googletest)
# # find_package(GTest REQUIRED)
# find_package(Threads REQUIRED)
# include_directories(${CMAKE_SOURCE_DIR}/googletest/googletest/include)
# # include_directories(
# # ${GMOCK_INCLUDE_DIRS}
# # ${GTEST_INCLUDE_DIRS}
# # )
# 
# # Link runTests with what we want to test and the GTest and pthread library
# add_executable(runTests tests.cpp)
# target_link_libraries(runTests gtest)
# endif()
