echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

copy ..\..\..\..\Utilities\LibGen\ar.exe .\
rmdir /Q /S .\Output\Release\Obj
mkdir       .\Output\Release\Obj
copy ".\Output\Encoder Interrupt Method Release\Obj" .\Output\Release\Obj

ar.exe -r -c -s ..\Lib\TIMER_LIB.a   .\Output\Release\Obj\Timer.o
ar.exe -r -c -s ..\Lib\PWM_LIB.a     .\Output\Release\Obj\pwm.o
ar.exe -r -c -s ..\Lib\ENCODER_LIB.a .\Output\Release\Obj\Encoder.o

pause
