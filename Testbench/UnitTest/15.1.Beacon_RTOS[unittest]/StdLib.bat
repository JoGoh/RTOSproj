echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%


mkdir .\Lib\Common

mklink /H .\Src\.clang-format ..\..\..\StdLib\Common\Inc\.clang-format

mkdir .\Src\App

mklink /j .\Lib\Common\Inc ..\..\..\StdLib\Common\Inc

mklink /j .\Lib\Common\Lib ..\..\..\StdLib\Common\Lib

rmdir /Q /S .\Src\App\UWB
mklink /j .\Src\App\UWB ..\..\..\StdLib\Module\UWB

rmdir /Q /S .\Src\App\Shell
mklink /j .\Src\App\Shell ..\..\..\StdLib\Module\Shell

rmdir /Q /S .\Src\BSP\SPIM
mklink /j .\Src\BSP\SPIM ..\..\..\StdLib\stm32F1\BSP\SPIM

rmdir /Q /S .\Src\BSP\UART
mklink /j .\Src\BSP\UART ..\..\..\StdLib\stm32F1\BSP\UART

rmdir /Q /S .\Src\BSP\MCU
mklink /j .\Src\BSP\MCU ..\..\..\StdLib\stm32F1\BSP\MCU

rmdir /Q /S .\Src\BSP\Clock
mklink /j .\Src\BSP\Clock ..\..\..\StdLib\stm32F1\BSP\Clock

copy ..\..\..\StdLib\Release\STM32F1\*.a .\Lib

pause