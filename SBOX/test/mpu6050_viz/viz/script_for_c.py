# '''
# ALPHA 값을 변경하며 C++로 작성된 MPU 6050 연산 후 시각화
# '''

import os

def create_directory(directory_path):
    try:
        # 디렉토리 생성
        os.makedirs(directory_path, exist_ok=True)
        print(f"디렉토리 '{directory_path}'가 생성되었습니다.")
    except OSError as error:
        print(f"디렉토리 생성 중 오류 발생: {error}")

def main():
    print("시각화할 시나리오 선택 : ", end= " ")
    scenario = input()
    # 디렉토리 경로 설정
    new_directory_path = f"../data/{scenario}"
    # 디렉토리 생성
    create_directory(new_directory_path)

    print("시작 숫자 선택 : ", end= " ")
    start = float(input())
    # print("끝 숫자 선택 : ", end= " ")
    # end = float(input())
    print("increment 선택 ex) 0.1, 0.01, ... : ", end= " ")
    incre = float(input())
    
    for i in range(1, 10):
        alpha = start + (i * incre)
        command = rf"C:\Users\SSAFY\source\repos\serial_test\x64\Release\serial_test.exe {alpha} {scenario}"
        os.system(command)
if __name__ == "__main__":
    main()