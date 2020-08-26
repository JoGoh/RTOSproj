#!/bin/bash -f

rm -r -f ./Lib/Common/Inc
rm -r -f ./Lib/Common/Lib
rm -r -f ./Lib
rm -r -f ./build/Output
rm       ./build/*.emSession
rm       ./build/*.jlink

rm -r -f ./Src/App/USBDevice
rm -r -f ./Src/App/UWB
rm -r -f ./Src/App/USB
rm -r -f ./Src/App/LCD
rm       ./Src/BSP/MCU
rm       ./Src/BSP/Clock
rm       ./Src/BSP/CAN
rm       ./Src/BSP/UART
rm       ./Src/BSP/SPIM

