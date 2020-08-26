echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib\Common\Inc
rmdir /Q /S .\Lib\Common\Lib
rmdir /Q /S .\Lib
rmdir /Q /S Build\Output
del build\*.emSession
del build\*.jlink
del build\*.a
del .\src\.clang-format

rmdir /Q /S .\src\App\FreeRTOS
rmdir /Q /S .\src\App\USBDevice
rmdir /Q /S .\src\App\UWB
rmdir /Q /S .\src\App\IPS
rmdir /Q /S .\src\App\LCD
rmdir /Q /S .\src\App\
rmdir /Q /S .\src\BSP\MCU
rmdir /Q /S .\src\BSP\Clock
rmdir /Q /S .\src\BSP\Timer
rmdir /Q /S .\src\BSP\Dma
rmdir /Q /S .\src\BSP\Spim

