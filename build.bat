@ECHO OFF
if exist cmake\ (
  rd /s /q cmake
)

mkdir cmake&&cd cmake
cmake ..
cd ..
