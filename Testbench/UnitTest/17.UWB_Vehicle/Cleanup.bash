#!/bin/bash -f

rm -r -f ./Lib/Common/Inc
rm -r -f ./Lib/Common/Lib
rm -r -f ./Lib
rm -r -f ./build/Output
rm       ./build/*.emSession
rm       ./build/*.jlink
rm       ./build/*.a

rm -r -f ./src/App/FreeRTOS
rm -r -f ./src/App/USBDevice
rm -r -f ./src/App/UWB
rm -r -f ./src/App/IPS
rm -r -f ./src/App/LCD
rm -r -f ./src/App/
rm       ./src/BSP/MCU
rm       ./src/BSP/Clock
rm       ./src/BSP/Timer
rm       ./src/BSP/Dma
rm       ./src/BSP/Spim
