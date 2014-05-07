cmake_minimum_required( VERSION 2.6 )

# --------------------------------------------
# Project name definition
# --------------------------------------------
project( "kT Engine" )

cmake_policy( SET CMP0015 NEW )

# --------------------------------------------
# Allow the developer to select if Dynamic or Static libraries are built
# --------------------------------------------
option( BUILD_SHARED_LIBS "Build kT Engine as Shared Libraries" OFF )

if( BUILD_SHARED_LIBS )
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  set( kt_lib_type SHARED )
  add_definitions( -DKT_BUILDING_LIBRARY  -DKT_DYNAMIC )
else()
  set( kt_lib_type STATIC )
endif( BUILD_SHARED_LIBS )
# --------------------------------------------

# --------------------------------------------
# Naming the libraries accordingly to the setup
# --------------------------------------------

# --------------------------------------------
# Add -d to debug builds
# --------------------------------------------
set( CMAKE_DEBUG_POSTFIX -d )

# --------------------------------------------
# Add -s to the static libs
# --------------------------------------------
if( NOT BUILD_SHARED_LIBS )
	set( kt_lib_suffix -s )
else()
	set( kt_lib_suffix  )
endif( NOT BUILD_SHARED_LIBS )

# --------------------------------------------
# Correctly named.
# --------------------------------------------

# --------------------------------------------
# Add the compiler include / lib paths
# to the default CMake paths
# --------------------------------------------
set(CMAKE_INCLUDE_PATH $CMAKE_INCLUDE_PATH $ENV{INCLUDE})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $ENV{LIB})
set(CMAKE_LIBRARY_PATH $CMAKE_LIBRARY_PATH $LIBRARY_OUTPUT_PATH)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# --------------------------------------------
# Add the folder to the compilation includes path
# --------------------------------------------
include_directories( include )


# --------------------------------------------
# Add the entry point to the build
# --------------------------------------------
file(
	GLOB
	main_source_files
	src/kT/Main/*.cpp
	src/kT/Main/Win/*.cpp
)

set( ktMainLibName ktMain${kt_lib_debug_suffix})

add_library(
	${ktMainLibName}
	STATIC
	${main_source_files}
)

# --------------------------------------------
# Add the core module to the build
# --------------------------------------------
file(
	GLOB
	core_source_files
	src/kT/Core/*.cpp
	src/kT/Core/Unix/*.cpp
	src/kT/Core/Win/*.cpp
)

file(
	GLOB
	core_header_files
	include/kT/Core/*.hpp
	include/kT/Core/Unix/*.hpp
	include/kT/Core/Win/*.hpp
)

set( ktCoreLibName ktCore${kt_lib_suffix})

add_library(
	${ktCoreLibName}
	${kt_lib_type}
	${core_source_files}
	${core_header_files}
)

if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
	target_link_libraries( ${ktCoreLibName} pthread )
	target_link_libraries( ${ktCoreLibName} dl )
endif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )

# --------------------------------------------
# Add the math module to the build
# --------------------------------------------
file(
	GLOB
	math_source_files
	src/kT/Math/*.cpp
)

file(
	GLOB
	math_header_files
	include/kT/Math/*.hpp
	include/kT/Math/*.inl
)

set( ktMathLibName ktMath${kt_lib_suffix})

if( math_source_files )

	add_library(
		${ktMathLibName}
		${kt_lib_type}
		${math_source_files}
		${math_header_files}
	)
	
	target_link_libraries( ${ktMathLibName} ${ktCoreLibName} )

	add_dependencies( ${ktMathLibName} ${ktCoreLibName} )
	
endif( math_source_files )

# --------------------------------------------
# Add the window module to the build
# --------------------------------------------
file(
	GLOB
	window_source_files
	src/kT/Window/*.cpp
	src/kT/Window/Base/*.cpp
	src/kT/Window/Win/*.cpp
	src/kT/Window/X11/*.cpp
)

file(
	GLOB
	window_header_files
	include/kT/Window/*.hpp
	include/kT/Window/Base/*.hpp
	include/kT/Window/Win/*.hpp
	include/kT/Window/X11/*.hpp
)

set( ktWindowLibName ktWindow${kt_lib_suffix})

add_library(
	${ktWindowLibName}
	${kt_lib_type}
	${window_source_files}
	${window_header_files}
)

target_link_libraries( ${ktWindowLibName} ${ktCoreLibName} )

if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
	target_link_libraries( ${ktWindowLibName} X11 )
	target_link_libraries( ${ktWindowLibName} Xrandr )
endif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )

add_dependencies( ${ktWindowLibName} ${ktCoreLibName} )

# --------------------------------------------
# Add the graphics module to the build
# --------------------------------------------
include_directories( ${PNG_INCLUDE_DIR} )
add_definitions( ${PNG_DEFINITIONS} )

file(
	GLOB
	graphics_source_files
	src/kT/Graphics/*.cpp
	src/kT/graphics/GraphicsDevice/*.cpp
)

file(
	GLOB
	graphics_header_files
	include/kT/Graphics/*.hpp
	src/kT/Graphics/*.hpp
	include/kT/Graphics/GraphicsDevice/*.hpp
)

set( ktGraphicsLibName ktGraphics${kt_lib_suffix})

add_library(
	${ktGraphicsLibName}
	${kt_lib_type}
	${graphics_source_files}
	${graphics_header_files}
)

target_link_libraries( ${ktGraphicsLibName} ${ktCoreLibName} )
target_link_libraries( ${ktGraphicsLibName} ${ktWindowLibName} )

if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
	target_link_libraries( ${ktGraphicsLibName} X11 )
endif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )

add_dependencies( ${ktGraphicsLibName} ${ktCoreLibName} )
add_dependencies( ${ktGraphicsLibName} ${ktMathLibName} )

# --------------------------------------------
# Add the OGL3Device module to the build
# --------------------------------------------

find_package( OpenGL )
if( OPENGL_FOUND )

	include_directories( ${OPENGL_INCLUDE_DIR} )

	file(
		GLOB_RECURSE
		ogl3device_source_files
		src/kT/Graphics/OGL3Device/*.cpp
		src/kT/Graphics/OGL3Device/*.c
	)

	file(
		GLOB_RECURSE
		ogl3device_header_files
		include/kT/Graphics/OGL3Device/*.hpp
	)

	set( ktOGL3DeviceLibName ktOGL3Device${kt_lib_suffix})

	add_library(
		${ktOGL3DeviceLibName}
		${kt_lib_type}
		${ogl3device_source_files}
		${ogl3device_header_files}
	)

	target_link_libraries( ${ktOGL3DeviceLibName} ${ktCoreLibName} )
	target_link_libraries( ${ktOGL3DeviceLibName} ${ktWindowLibName} )
	target_link_libraries( ${ktOGL3DeviceLibName} ${ktGraphicsLibName} )
	target_link_libraries( ${ktOGL3DeviceLibName} ${OPENGL_gl_LIBRARY} )

	find_package(GLEW  REQUIRED)
	include_directories(${GLEW_INCLUDE_PATH})
	target_link_libraries( ${ktOGL3DeviceLibName} ${GLEW_LIBRARY} )
	
	add_dependencies( ${ktOGL3DeviceLibName} ${ktCoreLibName} )
	add_dependencies( ${ktOGL3DeviceLibName} ${ktWindowLibName} )
	add_dependencies( ${ktOGL3DeviceLibName} ${ktGraphicsLibName} )

endif( OPENGL_FOUND )

# --------------------------------------------
# Add the D3D11Device module to the build
# --------------------------------------------

if( CMAKE_SYSTEM_NAME STREQUAL "Windows" )
	file(
		GLOB_RECURSE
		d3d11device_source_files
		src/kT/Graphics/D3D11Device/*.cpp
		src/kT/Graphics/D3D11Device/*.hlsl
	)

	file(
		GLOB_RECURSE
		d3d11device_header_files
		include/kT/Graphics/D3D11Device/*.hpp
	)

	set( ktD3D11DeviceLibName ktD3D11Device${kt_lib_suffix})

	add_library(
		${ktD3D11DeviceLibName}
		${kt_lib_type}
		${d3d11device_source_files}
		${d3d11device_header_files}
	)

	target_link_libraries( ${ktD3D11DeviceLibName} ${ktCoreLibName} )
	target_link_libraries( ${ktD3D11DeviceLibName} ${ktWindowLibName} )
	target_link_libraries( ${ktD3D11DeviceLibName} ${ktGraphicsLibName} )
	
	add_dependencies( ${ktD3D11DeviceLibName} ${ktCoreLibName} )
	add_dependencies( ${ktD3D11DeviceLibName} ${ktWindowLibName} )
	add_dependencies( ${ktD3D11DeviceLibName} ${ktGraphicsLibName} )
	target_link_libraries( ${ktD3D11DeviceLibName} dxgi )
	target_link_libraries( ${ktD3D11DeviceLibName} debug dxguid )
	target_link_libraries( ${ktD3D11DeviceLibName} d3d11 )
	target_link_libraries( ${ktD3D11DeviceLibName} d3dcompiler )


endif( CMAKE_SYSTEM_NAME STREQUAL "Windows" )

# --------------------------------------------
# Add the game module to the build
# --------------------------------------------
file(
	GLOB
	game_source_files
	src/kT/Game/*.cpp
)

file(
	GLOB
	game_header_files
	include/kT/Game/*.hpp
)

set( ktGameLibName ktGame${kt_lib_suffix})

add_library(
	${ktGameLibName}
	${kt_lib_type}
	${game_source_files}
	${game_header_files}
)

target_link_libraries( ${ktGameLibName} ${ktCoreLibName} )

add_dependencies( ${ktGameLibName} ${ktCoreLibName} )
