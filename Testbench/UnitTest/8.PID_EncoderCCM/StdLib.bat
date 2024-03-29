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

rmdir /Q /S .\Src\App\Encoders
mklink /j .\Src\App\Encoders ..\..\..\StdLib\Module\Encoders

rmdir /Q /S .\Src\App\PID
mklink /j .\Src\App\PID ..\..\..\StdLib\Module\PID

rmdir /Q /S .\Src\BSP\MCU
mklink /j .\Src\BSP\MCU ..\..\..\StdLib\stm32F7\BSP\MCU

rmdir /Q /S .\Src\BSP\Clock
mklink /j .\Src\BSP\Clock ..\..\..\StdLib\stm32F7\BSP\Clock

rmdir /Q /S .\Src\BSP\Timer
mklink /j .\Src\BSP\Timer ..\..\..\StdLib\stm32F7\BSP\Timer

rmdir /Q /S .\Src\BSP\Pwm
mklink /j .\Src\BSP\Pwm ..\..\..\StdLib\stm32F7\BSP\Pwm

rmdir /Q /S .\Src\BSP\Motors
mklink /j .\Src\BSP\Motors ..\..\..\StdLib\stm32F7\BSP\Motors

rmdir /Q /S .\Src\BSP\Ccm
mklink /j .\Src\BSP\Ccm ..\..\..\StdLib\stm32F7\BSP\Ccm

pause