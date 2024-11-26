'''
1. 사용자로부터 ALPHA 값 입력 받음
2. STM32 헤더 파일의 ALPHA 값 변경
3. STM32 프로젝트 빌드 및 보드에 업로드
4. 실시간 시각화
'''
# from real_tim.param_change import change_alpha_value
from param_change import change_alpha_value
import subprocess
import time

DEFAULT_FILE_PATH = r"C:\Users\SSAFY\Desktop\mpu6050_lib_test\Core\Inc\MPU6050.h"
FW_UPDATE_PATH = r"C:\Users\SSAFY\Desktop\S10P31A304\test\mpu6050_viz\batch\fw_update.bat"
VIZ_SCRIPT_PATH = r"C:\Users\SSAFY\Desktop\S10P31A304\test\mpu6050_viz\real_time_viz\mpu_real_time.py"  # mpu_viz.py 파일의 경로를 설정해주세요

def main():
    new_alpha_value = float(input("새로운 ALPHA 값을 입력하세요: "))  # 사용자 입력 받음
    change_alpha_value(DEFAULT_FILE_PATH, new_alpha_value)
    
    subprocess.run([FW_UPDATE_PATH], shell=True)
    time.sleep(5)  # 5초 기다림
    subprocess.run(["python", VIZ_SCRIPT_PATH, str(new_alpha_value)], shell=True)  # mpu_viz.py 실행
    input("아무 키나 누르세요...")

if __name__ == "__main__":
    main()