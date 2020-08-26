#!/bin/bash -f

rm -r -f ./Lib
mkdir ./Lib/
mkdir ./Lib/Common


cd ./Lib/Common
ln -s ../../../../../StdLib/Common/Inc Inc 
ln -s ../../../../../StdLib/Common/Lib Lib
cd ../..

ln -s ../../../StdLib/Common/Inc/.clang-format ./src/.clang-format

#mkdir    ./src/App

cd       ./src/BSP/

rm -r -f MCU
ln -s ../../../../../StdLib/stm32F1/BSP/MCU MCU

rm -r -f Clock
ln -s ../../../../../StdLib/stm32F1/BSP/Clock Clock


rm -r -f Timer
cd ../..
cp    ../../../StdLib/Release/TIMER_LIB.a ./Lib
cd       ./src/BSP/
ln -s ../../../../../StdLib/stm32F1/BSP/SPIM    SPIM
ln -s ../../../../../StdLib/stm32F1/BSP/UART    UART

cd ../App/
ln -s ../../../../../StdLib/Module/LCD         LCD
ln -s ../../../../../StdLib/Module/UWB         UWB
ln -s ../../../../../StdLib/Module/Shell       Shell
ln -s ../../../../../StdLib/Module/IPS         IPS
cd ../..


