@echo off
mkdir build
pushd .\build
cmake ..\src -G "Visual Studio 14 2015 Win64"
popd