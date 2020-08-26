echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib
mkdir .\Lib\
mkdir .\Lib\Common
mkdir .\Src\App

mklink /H .\Src\.clang-format ..\..\..\StdLib\Common\Inc\.clang-format

mklink /j .\Lib\Common\Inc ..\..\..\StdLib\Common\Inc

mklink /j .\Lib\Common\Lib ..\..\..\StdLib\Common\Lib

rmdir /Q /S .\Src\BSP\MCU
mklink /j .\Src\BSP\MCU ..\..\..\StdLib\stm32F7\BSP\MCU

rmdir /Q /S .\Src\BSP\Clock
mklink /j .\Src\BSP\Clock ..\..\..\StdLib\stm32F7\BSP\Clock

rmdir /Q /S .\Src\BSP\Timer
mklink /j .\Src\BSP\Timer ..\..\..\StdLib\stm32F7\BSP\Timer

rmdir /Q /S .\Src\BSP\Spim
mklink /j .\Src\BSP\Spim ..\..\..\StdLib\stm32F7\BSP\Spim

rmdir /Q /S .\Src\BSP\Dma
mklink /j .\Src\BSP\Dma ..\..\..\StdLib\stm32F7\BSP\Dma

rmdir /Q /S .\Src\App\LCD
mklink /j .\Src\App\LCD ..\..\..\StdLib\Module\LCD

rmdir /Q /S .\Src\App\USound
mklink /j .\Src\App\USound ..\..\..\StdLib\Module\USound

pause