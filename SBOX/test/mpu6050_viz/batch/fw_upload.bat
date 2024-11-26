REM STM32CubeProgrammer 실행해서 FW Upload

@ECHO OFF
SET "OLD_PATH=%PATH%"
SET "PATH=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin;%PATH%"
SET PROG_CLI=STM32_Programmer_CLI.exe
SET PROG_ARGS=-c port=SWD freq=4000
SET START_ADDR=0x80000000
SET VERIFY=-v
SET PROJECT="C:\Users\SSAFY\Desktop\mpu6050_lib_test\Debug\mpu6050_lib_test.elf"

%PROG_CLI% %PROG_ARGS% -w %PROJECT% %START_ADDR% %VERIFY%

SET "PATH=%OLD_PATH%"
ECHO ON