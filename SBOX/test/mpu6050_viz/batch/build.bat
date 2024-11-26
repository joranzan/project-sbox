REM STM32 프로젝트 빌드

set CUBEIDE_PATH=C:\ST\STM32CubeIDE_1.15.1\STM32CubeIDE
set WORKSPACE=C:\Users\SSAFY\STM32CubeIDE\workspace_1.15.1
set PROJECT=mpu6050_lib_test

echo Building project %PROJECT%...

cd %CUBEIDE_PATH%
CALL headless-build.bat -data %WORKSPACE% -cleanBuild %PROJECT%

echo Build completed.