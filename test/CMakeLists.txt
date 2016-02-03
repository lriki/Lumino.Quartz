
set(LN_TEST_SOURCES
	Application.cpp
	Application.h
)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/external/Lumino.Core/include"
	"${PROJECT_SOURCE_DIR}/external/Lumino.Math/include"
)
	
link_libraries(LuminoQuartz_Static)

add_executable(LuminoQuartz_Test WIN32 ${LN_TEST_SOURCES})
