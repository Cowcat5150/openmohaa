cmake_minimum_required(VERSION 3.12)

project(omohserver)

add_subdirectory("../fgame" "./fgame")

file(GLOB_RECURSE SOURCES_SERVER "./*.c*")

set(SOURCES_SERVER ${SOURCES_SERVER}
	# Gamespy
	"${CMAKE_SOURCE_DIR}/code/gamespy/sv_gamespy.c"
	"${CMAKE_SOURCE_DIR}/code/gamespy/sv_gqueryreporting.c"
)

add_library(omohserver INTERFACE)
target_sources(omohserver INTERFACE ${SOURCES_SERVER})
target_compile_features(omohserver INTERFACE cxx_nullptr)
target_compile_features(omohserver INTERFACE c_variadic_macros)
target_link_libraries(omohserver INTERFACE qcommon qcommon_standalone)
target_link_libraries(omohserver INTERFACE gcd)
