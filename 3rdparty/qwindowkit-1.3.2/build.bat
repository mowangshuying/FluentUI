call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
ninja --version
mkdir build
cd build
cmake -DCMAKE_MESSAGE_LOG_LEVEL=STATUS -DCMAKE_PREFIX_PATH=C:\Qt\6.5.1\msvc2019_64 -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_INSTALL_PREFIX=D:\qwindowkit\build\installed -G"Ninja Multi-Config" ..
cmake --build . --target install --config Debug
cmake --build . --target install --config Release
pause

