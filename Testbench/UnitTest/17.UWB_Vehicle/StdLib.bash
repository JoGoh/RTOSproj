#!/bin/bash -f

rm -r -f ./Lib
mkdir ./Lib/
mkdir ./Lib/Common


cd ./Lib/Common
ln -s ../../../../../StdLib/Common/Inc Inc 
ln -s ../../../../../StdLib/Common/Lib Lib
cd ../..

ln -s ../../../StdLib/Common/Inc/.clang-format ./src/.clang-format

mkdir    ./src/App

cd       ./src/BSP/

rm -r -f MCU
ln -s ../../../../../StdLib/stm32F7/BSP/MCU MCU

rm -r -f Clock
ln -s ../../../../../StdLib/stm32F7/BSP/Clock Clock


rm -r -f Timer
cd ../..

cd       ./src/BSP/
ln -s ../../../../../StdLib/stm32F7/BSP/Timer   Timer
ln -s ../../../../../StdLib/stm32F7/BSP/Spim    Spim
ln -s ../../../../../StdLib/stm32F7/BSP/Dma     Dma

cd ../App/
ln -s ../../../../../StdLib/Module/LCD         LCD
ln -s ../../../../../StdLib/Module/UWB         UWB
ln -s ../../../../../StdLib/Module/IPS         IPS
ln -s ../../../../../StdLib/Module/Cube3D      Cube3D


cd ../..

cd ./build
cp ../../../../StdLib/Common/Lib/GUI/DPGUI_GCC_M7_R10.a     ./
cd ..
pwd
