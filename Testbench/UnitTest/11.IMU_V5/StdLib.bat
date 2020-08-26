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


rmdir /Q /S .\Src\App\LCD
mklink /j .\Src\App\LCD ..\..\..\StdLib\Module\LCD

rmdir /Q /S .\Src\App\ImuPololuV5
mklink /j .\Src\App\ImuPololuV5 ..\..\..\StdLib\Module\ImuPololuV5

rmdir /Q /S .\Src\App\ImuAlgo
mklink /j .\Src\App\ImuAlgo ..\..\..\StdLib\Module\ImuAlgo

pause