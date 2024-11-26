REM 프로젝트 헤드리스 빌드 + STM32 보드에 업로드

@ECHO OFF
REM STM32CubeIDE 경로
set CUBEIDE_PATH=C:\ST\STM32CubeIDE_1.15.1\STM32CubeIDE
REM WorkSpace 경로
set WORKSPACE=C:\Users\SSAFY\STM32CubeIDE\workspace_1.15.1
REM 빌드하고자하는 프로젝트 이름
set PROJECT=mpu6050_lib_test

echo Building project %PROJECT%...

cd %CUBEIDE_PATH%
CALL headless-build.bat -data %WORKSPACE% -cleanBuild %PROJECT%

ECHO ON
echo Build completed.

REM STM32CubeProgrammer 실행해서 FW Upload // CubeProgrammer 다운로드 필요

@ECHO OFF
SET "OLD_PATH=%PATH%"
SET "PATH=C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin;%PATH%"
SET PROG_CLI=STM32_Programmer_CLI.exe
SET PROG_ARGS=-c port=SWD freq=4000
SET START_ADDR=0x80000000
SET VERIFY=-v
REM 빌드 후 생성된 실행 파일 경로
SET PROJECT="C:\Users\SSAFY\Desktop\mpu6050_lib_test\Debug\mpu6050_lib_test.elf"

REM FW 업로드 명령어
%PROG_CLI% %PROG_ARGS% -w %PROJECT% %START_ADDR% %VERIFY% --RST

SET "PATH=%OLD_PATH%"
ECHO ON

@echo off

REM mobaXterm 실행 파일 경로 설정
set MOBAXTERM_PATH="C:\MobaXterm_Portable_v23.6\MobaXterm_Personal_23.6.exe"

REM mobaXterm을 COM7 포트로 실행
%MOBAXTERM_PATH% -serial COM7:115200