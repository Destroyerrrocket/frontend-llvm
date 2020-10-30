cmake_minimum_required(VERSION 3.5.1)
project(llvm-frontend)

if (POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()

set(W4LS_LINKER "" CACHE FILEPATH "You can define a custom linker")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(W4LS_LINKER)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message(STATUS "using linker: ${W4LS_LINKER}")
		add_link_options(-fuse-ld=${W4LS_LINKER})
	else()
		message(STATUS "could not use linker (${W4LS_LINKER}): Unsupported compiler")
	endif()
endif()

# We need SSE3
add_compile_options(-mmmx -msse -msse2 -msse3 -msse4.1 -msse4.2 -mavx -mavx2)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories()
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader)

add_executable(frontend
		src/lexer/tokens/token.hpp
		src/lexer/tokens/tokenkind.hpp
		src/lexer/tokens/tokenliteral.hpp
		src/lexer/tokens/tokenidentifier.hpp
		src/lexer/lexer.hpp
		src/lexer/lexerstate.hpp
		src/lexer/attempter.hpp
		src/lexer/lexer.cpp
		src/lexer/struct.hpp
		src/lexer/lexerstate.cpp
		src/main.cpp
		src/Parser/parser.hpp
		src/Parser/parser.cpp
		src/compile.hpp
		src/compile.cpp
		src/report/report.hpp
		src/report/report.cpp
	)

target_include_directories(frontend
	PRIVATE
	${LLVM_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_link_libraries(frontend
	PRIVATE
	${llvm_libs}
	)

# Platforms
if (WIN32)
	target_compile_definitions(frontend PUBLIC -DW4LS_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
	target_compile_definitions(frontend PUBLIC -DW4LS_PLATFORM_LINUX)
endif()
