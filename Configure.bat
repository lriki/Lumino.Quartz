
mkdir build
mkdir build\Lumino.Core
cd build\Lumino.Core

cmake ..\..\external/Lumino.Core -G"Visual Studio 12" -DHLD_MSVC_LINK_MULTI_THREAD_STATIC_RUNTIME=OFF

pause
