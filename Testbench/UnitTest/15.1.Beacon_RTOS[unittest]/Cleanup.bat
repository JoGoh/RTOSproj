echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib\Common\Inc
rmdir /Q /S .\Lib\Common\Lib
rmdir /Q /S .\Lib\
rmdir /Q /S Build\Output
del Build\*.emSession
del Build\*.jlink

rmdir /Q /S .\Src\App\USBDevice
rmdir /Q /S .\Src\App\UWB
rmdir /Q /S .\Src\App\Shell
rmdir /Q /S .\Src\BSP\SPIM
rmdir /Q /S .\Src\BSP\UART
rmdir /Q /S .\Src\BSP\MCU
rmdir /Q /S .\Src\BSP\USB
rmdir /Q /S .\Src\BSP\CAN
rmdir /Q /S .\Src\BSP\Clock

