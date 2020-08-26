echo %~dp0
pushd %~dp0
set CurrentDir=%CD%
chdir /d %CurrentDir%

copy ..\..\..\..\Utilities\LibGen\ar.exe .\
rmdir /Q /S .\Output\Release\Obj
mkdir       .\Output\Release\Obj
copy ".\Output\LCDzzer Release\Obj" .\Output\Release\Obj

ar.exe -r -c -s ..\StdLib\Lib\IMU_LIB.a .\Output\Release\Obj\imu.o .\Output\Release\Obj\PololuV3.o
ar.exe -r -c -s ..\StdLib\Lib\TIMER_LIB.a .\Output\Release\Obj\Timer.o
ar.exe -r -c -s ..\StdLib\Lib\PWM_LIB.a .\Output\Release\Obj\pwm.o
ar.exe -r -c -s ..\StdLib\Lib\I2C_LIB.a .\Output\Release\Obj\i2c.o
ar.exe -r -c -s ..\StdLib\Lib\ENCODER_LIB.a .\Output\Release\Obj\Encoder.o
ar.exe -r -c -s ..\StdLib\Lib\PID_LIB.a .\Output\Release\Obj\PID.o
ar.exe -r -c -s ..\StdLib\Lib\SERIAL_LIB.a .\Output\Release\Obj\Serial.o .\Output\Release\Obj\Usart.o .\Output\Release\Obj\Uart.o
ar.exe -r -c -s ..\StdLib\Lib\USONIC_LIB.a .\Output\Release\Obj\UltraSound.o
ar.exe -r -c -s ..\StdLib\Lib\UWB_LIB.a .\Output\Release\Obj\deca_device.o .\Output\Release\Obj\deca_params_init.o
ar.exe -r -c -s ..\StdLib\Lib\IPS_LIB.a .\Output\Release\Obj\ips.o .\Output\Release\Obj\matrix.o
ar.exe -r -c -s ..\StdLib\Lib\GUI_LIB.a .\Output\Release\Obj\gui.o .\Output\Release\Obj\Font.o  .\Output\Release\Obj\comic.o  .\Output\Release\Obj\arimo20.o
ar.exe -r -c -s ..\StdLib\Lib\SPIM_LIB.a .\Output\Release\Obj\spim.o
pause
