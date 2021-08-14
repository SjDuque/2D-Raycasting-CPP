cmake_minimum_required(VERSION 3.15)
project(main)

# Settings C/C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Setting output directories
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# If you are using VCPKG:
# find_package(raylib CONFIG REQUIRED)

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)

	FetchContent_Declare(
		raylib
		URL https://github.com/raysan5/raylib/archive/master.tar.gz
	)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)

		set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

		# build raylib
		add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

	endif()
endif()

#-------------------------
# Include any headers and c files to add to the executable
#-------------------------
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)

file(GLOB_RECURSE main_sources
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${main_sources})

# If you are using a package manager such as brew or apt-get
target_link_libraries(${PROJECT_NAME} raylib)

# If you are using VCPKG:
# target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARIES}) 

#-------------------------
# Copy assets
#-------------------------

# Set a symbolic link so exe can find the /assets folder

set(link_src "${CMAKE_SOURCE_DIR}/assets")
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") # use "if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND APPLE)" if your configs get separated on osx
	set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/<assets") 
else() 
	set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/assets") 
endif() 

if (UNIX)
	add_custom_command( 
		TARGET ${PROJECT_NAME} 
		POST_BUILD COMMAND ${CMAKE_COMMAND} 
				-E create_symlink ${link_src} ${link_dst} 
		DEPENDS ${link_dst} 
		COMMENT "symbolic link ${link_src} => ${link_dst}" 
	)
else()
	file(COPY ${link_src} DESTINATION ${link_dst}/..)
	message(STATUS "copying files ${link_src} => ${link_dst}") 
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# That's it! You should have an example executable that you can run. Have fun!