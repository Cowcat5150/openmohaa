cmake_minimum_required(VERSION 3.12)

project(omohclient)

add_subdirectory("../cgame" "./cgame")

file(GLOB SOURCES_CLIENT "./*.c*")
file(GLOB_RECURSE SOURCES_UILIB "../uilib/*.c*")

set(SOURCES_CLIENT ${SOURCES_CLIENT}
	# Gamespy
	"${CMAKE_SOURCE_DIR}/code/gamespy/cl_gamespy.c"
)

# Made as an interface and not static, as static only links used methods
add_library(omohclient INTERFACE)
target_compile_definitions(omohclient INTERFACE APP_MODULE)
target_compile_features(omohclient INTERFACE cxx_nullptr)
target_compile_features(omohclient INTERFACE c_variadic_macros)
target_link_libraries(omohclient INTERFACE omohsdl_client)
target_link_libraries(omohclient INTERFACE gcd)

# Sound stuff
target_compile_definitions(omohclient INTERFACE USE_CODEC_MP3)

if (NOT NO_MODERN_DMA)
	# Use OpenAL
	find_package(OpenAL REQUIRED)

	if (OPENAL_FOUND)
		target_compile_definitions(omohclient INTERFACE USE_OPENAL=1 NO_MODERN_DMA=0)
		if (MSVC)
			target_include_directories(omohclient INTERFACE ${OPENAL_INCLUDE_DIR}/AL)
		else()
			target_include_directories(omohclient INTERFACE ${OPENAL_INCLUDE_DIR})
		endif()

		if(NOT USE_SYSTEM_LIBS)
			target_compile_definitions(omohclient INTERFACE USE_OPENAL_DLOPEN=1)
		else()
			# Link against system OpenAL
			target_link_libraries(omohclient INTERFACE OpenAL::OpenAL)
		endif()
	endif()

	list(FILTER SOURCES_CLIENT EXCLUDE REGEX "./snd_([a-zA-Z0-9_]+)\.c$")
	file(GLOB SOURCES_CLIENT_SND "./snd_*_new.c*" "./snd_codec*.c*")
	list(APPEND SOURCES_CLIENT ${SOURCES_CLIENT_SND})
else()
	#
	# Fallback to old DMA sound system
	#
	message(NOTICE "OpenAL was explicitly disabled - fallback to old SDL sound system")
	target_compile_definitions(omohclient INTERFACE NO_MODERN_DMA=1)
	set(NO_MODERN_DMA TRUE)

	list(FILTER SOURCES_CLIENT EXCLUDE REGEX "./snd_([a-zA-Z0-9_]+)\.cpp$")
	file(GLOB_RECURSE SOURCES_CLIENT_SND "./new/*.c*")
	list(APPEND SOURCES_CLIENT ${SOURCES_CLIENT_SND})
endif()

set(OLD_VALUE ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if(USE_INTERNAL_MAD)
	add_subdirectory("../libmad" "./libmad" EXCLUDE_FROM_ALL)
	target_link_libraries(omohclient INTERFACE mad)
else()
	include(FindPackageHandleStandardArgs)
	find_path(LIBMAD_INCLUDE_DIRS mad.h)
	find_library(LIBMAD_LIBRARIES mad)
	find_package_handle_standard_args(
		LibMad
		DEFAULT_MSG
		LIBMAD_LIBRARIES
		LIBMAD_INCLUDE_DIRS
	)
	target_include_directories(omohclient INTERFACE ${LIBMAD_INCLUDE_DIRS})
	target_link_libraries(omohclient INTERFACE ${LIBMAD_LIBRARIES})
endif()

set(BUILD_SHARED_LIBS ${OLD_VALUE} CACHE BOOL "" FORCE)

target_sources(omohclient INTERFACE ${SOURCES_CLIENT} ${SOURCES_UILIB})
