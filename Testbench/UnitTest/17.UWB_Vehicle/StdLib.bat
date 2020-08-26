echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib
mkdir .\Lib\
mkdir .\Lib\Common
mkdir .\src\App

mklink /H .\src\.clang-format ..\..\..\StdLib\Common\Inc\.clang-format

mklink /j .\Lib\Common\Inc ..\..\..\StdLib\Common\Inc

mklink /j .\Lib\Common\Lib ..\..\..\StdLib\Common\Lib

rmdir /Q /S .\src\BSP\MCU
mklink /j .\src\BSP\MCU ..\..\..\StdLib\stm32F7\BSP\MCU

rmdir /Q /S .\src\BSP\Clock
mklink /j .\src\BSP\Clock ..\..\..\StdLib\stm32F7\BSP\Clock

rmdir /Q /S .\src\BSP\Timer
mklink /j .\src\BSP\Timer ..\..\..\StdLib\stm32F7\BSP\Timer

rmdir /Q /S .\src\BSP\Spim
mklink /j .\src\BSP\Spim ..\..\..\StdLib\stm32F7\BSP\Spim

rmdir /Q /S .\src\BSP\Dma
mklink /j .\src\BSP\Dma ..\..\..\StdLib\stm32F7\BSP\Dma

rmdir /Q /S .\src\App\LCD
mklink /j .\src\App\LCD ..\..\..\StdLib\Module\LCD

rmdir /Q /S .\src\App\UWB
mklink /j .\src\App\UWB ..\..\..\StdLib\Module\UWB

rmdir /Q /S .\src\App\IPS
mklink /j .\src\App\IPS ..\..\..\StdLib\Module\IPS

rmdir /Q /S .\src\App\Cube3D
mklink /j .\src\App\Cube3D ..\..\..\StdLib\Module\Cube3D

copy ..\..\..\StdLib\Common\Lib\GUI\DPGUI_GCC_M7_R10.a build\


pause