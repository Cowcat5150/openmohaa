cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(identity)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

option(BUILD_SERVER "Build dedicated server" ON)
option(BUILD_CLIENT "Build client" ON)
option(BUILD_RENDERER_GL1 "Build GL1 renderer" ON)
option(BUILD_RENDERER_GL2 "Build GL2 renderer" OFF)
option(BUILD_GAME_LIBRARIES "Build game module libraries" ON)
option(BUILD_GAME_QVMS "Build game module qvms" ON)
option(BUILD_STANDALONE "Build binaries for standalone games" OFF)

option(USE_ARCHLESS_FILENAMES "Don't include the architecture in binary filenames" ON)
option(USE_RENDERER_DLOPEN "Dynamically load the renderer(s)" OFF)
option(USE_OPENAL "OpenAL audio" ON)
option(USE_OPENAL_DLOPEN "Dynamically load OpenAL" ON)
option(USE_HTTP "HTTP download support" ON)
option(USE_CODEC_VORBIS "Ogg Vorbis support" ON)
option(USE_CODEC_OPUS "Ogg Opus support" ON)
option(USE_CODEC_MAD "MP3 support" ON)
option(USE_VOIP "Voice chat" OFF)
option(USE_MUMBLE "Mumble support" OFF)
option(USE_FREETYPE "Freetype font rendering" OFF)

option(USE_INTERNAL_LIBS "Use internally packaged libraries" ON)
option(USE_INTERNAL_SDL "Use internal SDL binary (if available)" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_ZLIB "Use internal copy of zlib" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_JPEG "Use internal copy of libjpeg" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_OGG "Use internal copy of ogg" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_VORBIS "Use internal copy of vorbis" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_OPUS "Use internal copy of opus" ${USE_INTERNAL_LIBS})
option(USE_INTERNAL_MAD "Use internal copy of libmad" ${USE_INTERNAL_LIBS})

# Release build by default, set externally if you want something else
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/code)

# Enable unit testing
include(CTest)

include(compilers/all)
include(platforms/all)
include(libraries/all)
include(deploy/all)

include(version)

include(server)
include(renderer_gl1)
include(renderer_gl2)
include(client)
include(basegame)
#include(missionpack)
include(launcher)

<<<<<<< HEAD
add_executable(omohaaded "code/null/null_client.c" "code/null/null_input.c" "code/null/null_snddma.c")
target_compile_definitions(omohaaded PRIVATE APP_MODULE DEDICATED)
target_compile_features(omohaaded PUBLIC cxx_nullptr)
target_compile_features(omohaaded PUBLIC c_variadic_macros)
target_link_libraries(omohaaded PRIVATE omohserver)
target_link_libraries(omohaaded PRIVATE syslib)
target_link_libraries(omohaaded PRIVATE qcommon qcommon_standalone)

# Add the gamespy dependency
target_include_directories(omohaaded PUBLIC "code/qcommon" "code/script" "code/gamespy" "code/server")
set_target_properties(omohaaded PROPERTIES OUTPUT_NAME "omohaaded${TARGET_BIN_SUFFIX}")
set_target_properties(omohaaded PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

INSTALL(TARGETS omohaaded DESTINATION ${CMAKE_INSTALL_BINDIR}/${BIN_INSTALL_SUBDIR})

if (MSVC)
	target_link_options(omohaaded PRIVATE "/MANIFEST:NO")
	INSTALL(FILES $<TARGET_PDB_FILE:omohaaded> DESTINATION ${CMAKE_INSTALL_BINDIR}/${BIN_INSTALL_SUBDIR} OPTIONAL)
endif()

if (NOT BUILD_NO_CLIENT)
	##
	## Client app
	##
	option(NO_MODERN_DMA "Use older sound-system" FALSE)

	add_subdirectory("code/client")
	add_subdirectory("code/renderercommon")
	add_subdirectory("code/sdl")

	add_executable(openmohaa "misc/dummy.c")
	target_link_libraries(openmohaa PRIVATE syslib)
	target_link_libraries(openmohaa PRIVATE omohserver)
	target_link_libraries(openmohaa PRIVATE omohclient)
	target_link_libraries(openmohaa PRIVATE omohrenderer)
	target_link_libraries(openmohaa PRIVATE qcommon qcommon_standalone)

	# Add the gamespy dependency
	target_include_directories(openmohaa PUBLIC "code/qcommon" "code/script" "code/gamespy" "code/server" "code/client" "code/uilib")
	set_target_properties(openmohaa PROPERTIES OUTPUT_NAME "openmohaa${TARGET_BIN_SUFFIX}")
	set_target_properties(openmohaa PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

	INSTALL(TARGETS openmohaa DESTINATION ${CMAKE_INSTALL_BINDIR}/${BIN_INSTALL_SUBDIR})

	if (MSVC)
		target_link_options(openmohaa PRIVATE "/MANIFEST:NO")
		INSTALL(FILES $<TARGET_PDB_FILE:openmohaa> DESTINATION ${CMAKE_INSTALL_BINDIR}/${BIN_INSTALL_SUBDIR} OPTIONAL)
	endif()

	if(UNIX AND NOT APPLE)
		# Configure the .desktop entries with the arch suffix
		configure_file(
			misc/linux/org.openmoh.openmohaa.desktop.in
			${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaa.desktop
			@ONLY
		)
		configure_file(
			misc/linux/org.openmoh.openmohaab.desktop.in
			${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaab.desktop
			@ONLY
		)
		configure_file(
			misc/linux/org.openmoh.openmohaas.desktop.in
			${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaas.desktop
			@ONLY
		)

		# Install .desktop entries
		install(FILES ${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaa.desktop  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
		install(FILES ${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaab.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
		install(FILES ${CMAKE_BINARY_DIR}/misc/linux/org.openmoh.openmohaas.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

		install(FILES misc/linux/org.openmoh.openmohaa.metainfo.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)

		install(FILES misc/openmohaa.svg DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/symbolic/apps/ RENAME org.openmoh.openmohaa.svg)
	endif()
endif()

#
# Launcher
#
if (NOT MORPHOS)
add_subdirectory(code/Launcher)
endif()

#
# uninstall target
#
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
=======
include(tests/all)
>>>>>>> main
