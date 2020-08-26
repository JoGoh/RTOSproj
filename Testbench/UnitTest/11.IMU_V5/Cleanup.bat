echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

rmdir /Q /S .\Lib\Common\Inc
rmdir /Q /S .\Lib\Common\Lib
rmdir /Q /S .\Lib
rmdir /Q /S Build\Output
del Build\*.emSession
del Build\*.jlink
del .\Src\.clang-format

rmdir /Q /S .\Src\App\FreeRTOS
rmdir /Q /S .\Src\App\USBDevice
rmdir /Q /S .\Src\App\UWB
rmdir /Q /S .\Src\App\Encoders
rmdir /Q /S .\Src\App\PID
rmdir /Q /S .\Src\App\ImuPololuV5
rmdir /Q /S .\Src\App\ImuAlgo
rmdir /Q /S .\Src\App\LCD
rmdir /Q /S .\Src\App\ImuPololuV5

rmdir /Q /S .\Src\BSP\I2c
rmdir /Q /S .\Src\BSP\SPIM
rmdir /Q /S .\Src\BSP\UART
rmdir /Q /S .\Src\BSP\MCU
rmdir /Q /S .\Src\BSP\USB
rmdir /Q /S .\Src\BSP\Clock
rmdir /Q /S .\Src\BSP\Timer
rmdir /Q /S .\Src\BSP\Pwm
rmdir /Q /S .\Src\BSP\Ccm
rmdir /Q /S .\Src\BSP\Motors
rmdir /Q /S .\Src\BSP\Dma