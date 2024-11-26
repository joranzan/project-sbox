'''
C++로 연산한 값 시각화
'''

import pandas as pd
import matplotlib.pyplot as plt

def lineplot(x, ax, scenario):
    f = pd.read_csv(f"../data/{scenario}/fil_data_{scenario}_{x}.csv")
    
    scenario = scenario.upper()
    acc = f'acc{scenario}'
    # gyro = f'gyro{scenario}'
    fil = f'fil{scenario}'

    # 각 칸에 해당하는 축에 선을 그리기
    ax.plot(f[acc], label=acc, color='pink', linewidth=0.7)
    # ax.plot(f[gyro], label=gyro, color='orange', linewidth=0.7)
    ax.plot(f[fil], label=fil, color='blue', linewidth=0.7)

    ax.set_xlabel('# of Data')
    ax.set_ylabel('Sensor Data')
    ax.set_title(f'Sensor Data (ALPHA = {x})')
    ax.legend(loc='upper left', fontsize=6)

def main():
    print("시각화할 시나리오 선택 :", end=" ")
    scenario = input()
    print("시작 숫자 선택 : ", end= " ")
    start = float(input())
    # print("끝 숫자 선택 : ", end= " ")
    # end = float(input())
    print("increment 선택 ex) 0.1, 0.01, ... : ", end= " ")
    incre = float(input())

    fig, axs = plt.subplots(3, 3, figsize=(15, 5))  # 1x3 서브플롯 생성
    
    for i in range(3):  # 0.1부터 0.9까지
        for j in range(3):
            x = start + ((i * 3 + j + 1) * incre)
            lineplot(x, axs[i, j], scenario)

    plt.tight_layout()  # subplot 간의 간격 조정
    plt.show()

if __name__ == "__main__":
    main()