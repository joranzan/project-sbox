# '''
# ALPHA 값을 변경하며 C++로 작성된 MPU 6050 연산 후 시각화
# '''

import os

def main():
    print("시작 숫자 선택 : ", end= " ")
    start = float(input())
    # print("끝 숫자 선택 : ", end= " ")
    # end = float(input())
    print("increment 선택 ex) 0.1, 0.01, ... : ", end= " ")
    incre = float(input())
    for i in range(1,10):
        alpha = start + (i * incre)
        command = rf"C:\Users\SSAFY\source\repos\serial_test\x64\Release\serial_test.exe {alpha}"
        os.system(command)

if __name__ == "__main__":
    main()