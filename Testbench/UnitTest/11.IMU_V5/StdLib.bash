#!/bin/bash -f

rm -r -f ./Lib
mkdir ./Lib/
mkdir ./Lib/Common


cd ./Lib/Common
ln -s ../../../../../StdLib/Common/Inc Inc 
ln -s ../../../../../StdLib/Common/Lib Lib
cd ../..

rm -r -f ./src/App
mkdir    ./src/App

cd       ./src/BSP/

rm -r -f MCU
ln -s ../../../../../StdLib/stm32F7/BSP/MCU MCU

rm -r -f Clock
ln -s ../../../../../StdLib/stm32F7/BSP/Clock Clock


rm -r -f Timer
cd ../..
cp    ../../../StdLib/Release/TIMER_LIB.a ./Lib
cd       ./src/BSP/
ln -s ../../../../../StdLib/stm32F7/BSP/Timer   Timer
ln -s ../../../../../StdLib/stm32F7/BSP/Spim    Spim
ln -s ../../../../../StdLib/stm32F7/BSP/Dma     Dma
ln -s ../../../../../StdLib/stm32F7/BSP/I2c     I2c

cd ../App/
ln -s ../../../../../StdLib/Module/LCD          LCD
ln -s ../../../../../StdLib/Module/ImuPololuV5  ImuPololuV5
ln -s ../../../../../StdLib/Module/ImuAlgo      ImuAlgo
cd ../..
