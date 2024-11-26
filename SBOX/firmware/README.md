# README

### STM32CubeIDE 설치

1. [STM32CubeIDE 1.9.0 exe](https://www.st.com/en/development-tools/stm32cubeide.html#get-software) 프로그램 다운로드
2. STM32CubeIDE 1.9.0 exe 실행하여 설치

### STM32 프로젝트 생성

1. STM32CubeIDE Workspace Launch
2. File > New > STM32 Project
3. Board Selector > ‘NUCLEO-F103RB’ 검색 > ‘NUCLEO-F103RB’ 보드 선택
4. Project Name 입력 > Finish 
5. ‘Initialize all peripherals with their default Mode?’ > ‘Yes’ 클릭

### ioc 파일 설정

** 개발하면서 상황에 맞게 커스텀할 것**

> **Middleware FREERTOS 설정**
> 
1. Middleware > FREERTOS 
2. Interface를 ‘CMSIS_V2’ 로 설정
3. Configuration > Advanced settings > ‘USE_NEWLIB_REENTRANT’ 를 ‘Enabled’로 설정
4. Categories의 ‘System Core’ > SYS > ‘Timebase Source’ 를 ‘TIM4’로 설정

> **Project Manager 설정**
> 

Code Generator > Generated files > ‘Generate peripheral initialization as a pair of ‘.c/.h’ files per peripheral’ 를 TRUE로 설정

* 모든 설정 완료 후 Ctrl+S (Generate Code)

### FREERTOS 활용 방법

** task == thread**

1. task 추가 및 설정: ioc파일에서 FREERTOS > Configuration > Tasks and Queues > Add
2. freertos 파일 접근: Core > Src > freertos.c
3. task 함수를 커스텀하여 활용