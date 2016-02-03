# e.g.) $ cmake -DLN_EXCEPTION_BACKTRACE=OFF ..

cmake_minimum_required (VERSION 2.8.7)
project (LuminoQuartz)

set(LN_STATIC_LIB_OUTPUT_NAME "LuminoQuartz")
set(LN_LINK_LIBS "")
set(LN_UNIT_TEST_LINK_LIBS "")
set(LN_LIB_POSTFIX "")

#------------------------------------------------------------------------------
# Options
#------------------------------------------------------------------------------

# Unicode char set.
option(LN_USE_UNICODE_CHAR_SET "Use unicode char set." ON)

# MSVC Runtime library.
option(LN_MSVC_LINK_MULTI_THREAD_STATIC_RUNTIME "static runtime (/MT, /MTd) or DLL runtime (/MD, /MDd) or to link either." OFF)

# Exceprion Backtrace.
option(LN_EXCEPTION_BACKTRACE "In some unix environment there is a possibility that can not be compiled." ON)

#------------------------------------------------------------------------------
# Files
#------------------------------------------------------------------------------
#------------------------------
# Source files.

set(LN_SOURCES_View
	include/Quartz/Application.h
	include/Quartz/Common.h
	include/Quartz/Element.h
	include/Quartz/MainWindow.h
	src/Application.cpp
	src/Element.cpp
	src/Internal.h
	src/MainWindow.cpp
)

#--------------------------------------
# Platform source files.
if (WIN32)
	
	set(LN_SOURCES_Platform_Mfc
		src/Mfc/Internal.h
		src/Mfc/MfcApplication.cpp
		src/Mfc/MfcApplication.h
		src/Mfc/targetver.h
	)
	
	#set(LN_COMPILE_FLAGS "/D_AFXDLL /Yu\"stdafx.h\"")
	#set(CMAKE_MFC_FLAG 2)
	add_definitions(/D_AFXDLL)
	
elseif (APPLE)

elseif (UNIX)
	add_definitions(-std=c++11)
endif()

#--------------------------------------
# Grouping.
source_group("View"			FILES ${LN_SOURCES_View})
source_group("Platform_Mfc"	FILES ${LN_SOURCES_Platform_Mfc})

set(LN_SOURCES
	${LN_SOURCES_View}
	${LN_SOURCES_Platform_Mfc}
)

#------------------------------------------------------------------------------
# Apply options
#------------------------------------------------------------------------------
# Unicode char set.
if (LN_USE_UNICODE_CHAR_SET)
	#add_definitions(-DUNICODE)
	#add_definitions(-D_UNICODE)
endif()

#find_package(OpenGL REQUIRED)

if (WIN32)
	if (LN_MSVC_LINK_MULTI_THREAD_STATIC_RUNTIME)
		foreach (flag CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
			if (${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if (${flag} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
		
	set(CMAKE_DEBUG_POSTFIX "d")
	
	# link librarys.
	#list(APPEND LN_LINK_LIBS
	#	"imagehlp.lib"
	#	"msacm32.lib"
	#	"Opengl32.lib")

elseif (APPLE)
	set(LN_UNIT_TEST_LINK_LIBS "pthread")
	
elseif (UNIX)
	set(LN_UNIT_TEST_LINK_LIBS "pthread")
	
	# link librarys.
	list(APPEND LN_LINK_LIBS "dl")
	list(APPEND LN_LINK_LIBS "bfd")
    find_package(X11 REQUIRED)

    #list(APPEND glfw_INCLUDE_DIRS ${X11_X11_INCLUDE_PATH})
    list(APPEND LN_LINK_LIBS ${X11_X11_LIB})

	#list(APPEND glfw_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
    list(APPEND LN_LINK_LIBS ${OPENGL_gl_LIBRARY})
	
else()
	# Not support.
    message(FATAL_ERROR "No supported platform was detected.")
endif()

set(LN_INCLUDE_DIRECTORIES
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/external
	${PROJECT_SOURCE_DIR}/external/Lumino.Core/include
)
include_directories(${LN_INCLUDE_DIRECTORIES} ${LN_PLATFORM_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# Output
#------------------------------------------------------------------------------

#set(CMAKE_CXX_FLAGS "")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -pg -O3")
#set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
#set(CMAKE_CXX_FLAGS_MINSIZEREL "")

if (LN_EXCEPTION_BACKTRACE)
	add_definitions(-DLN_EXCEPTION_BACKTRACE)
endif()

#------------------------------
# external deps.
add_subdirectory(external/Lumino.Core)
#add_subdirectory(external/Lumino.Math)

# Make postfix.
ln_make_postfix(LN_LIB_POSTFIX)

link_libraries(LuminoCore_Static)
#link_libraries(LuminoMath_Static)

#------------------------------
# library. (Unicode)

if (LN_USE_UNICODE_CHAR_SET)
	add_definitions(-DUNICODE)
	add_definitions(-D_UNICODE)
endif()

add_definitions("/EHsc")	# VS2015, cmake Ç≈ê∂ê¨Ç∑ÇÈÇ∆âΩåÃÇ©è¡Ç¶ÇƒÇµÇ‹Ç§ÇÃÇ≈ñæé¶ìIÇ…éwíËÇ∑ÇÈ

add_library(${PROJECT_NAME}_Static STATIC ${LN_SOURCES})
set_target_properties(${PROJECT_NAME}_Static PROPERTIES OUTPUT_NAME "${LN_STATIC_LIB_OUTPUT_NAME}${LN_LIB_POSTFIX}")
#set_target_properties(${PROJECT_NAME}_Static PROPERTIES INCLUDE_DIRECTORIES "${LN_INCLUDE_DIRECTORIES}")
target_link_libraries(${PROJECT_NAME}_Static ${LN_LINK_LIBS})
add_custom_command(
	TARGET ${PROJECT_NAME}_Static
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}_Static> "${CMAKE_SOURCE_DIR}/lib")

#------------------------------
# Unit test.
add_subdirectory(test)
