:: ---
:: https://stackoverflow.com/questions/15639781/how-to-find-the-qt5-cmake-module-on-windows
:: ---
@ECHO OFF
if exist cmake\ (
  rd /s /q cmake
)

mkdir cmake&&cd cmake
cmake .. -G"Visual Studio 15 2017"
cd ..
