import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# def calculate_snr(signal, noise):
#     signal_power = np.sum(np.abs(signal)**2)
#     noise_power = np.sum(np.abs(noise)**2)
#     snr = 10 * np.log10(signal_power / noise_power)
#     return snr

def plot_fft(x, ax, scenario):
    f = pd.read_csv(f"../data/fil_data_{x}.csv")
    
    scenario = scenario.upper()

    acc = f'acc{scenario}'
    # gyro = f'gyro{scenario}'
    fil = f'fil{scenario}'

    fft_acc = np.fft.fft(f[acc])
    # fft_gyro = np.fft.fft(f[gyro])
    fft_fil = np.fft.fft(f[fil])

    freqs = np.fft.fftfreq(len(f))
    freqs_hz = np.fft.fftshift(freqs) * 115200  # 주파수를 Hz로 변환 (보드 속도: 115200)

    magnitude_acc = np.abs(np.fft.fftshift(fft_acc))
    # magnitude_gyro = np.abs(np.fft.fftshift(fft_gyro))
    magnitude_fil = np.abs(np.fft.fftshift(fft_fil))

    # ax.set_facecolor('black')  # 배경색을 검은색으로 설정

    ax.plot(freqs_hz, magnitude_acc, label='accX', color='pink', linewidth=0.7)
    # ax.plot(freqs_hz, magnitude_gyro, label='gyroX', color='orange', linewidth=0.7)
    ax.plot(freqs_hz, magnitude_fil, label='filX', color='blue', linewidth=0.7)
    ax.set_xlim(-115200 / 2, 115200 / 2)  # Nyquist 주파수까지만 표시
    ax.set_xlabel('Frequency (Hz)')
    ax.set_ylabel('Magnitude')
    ax.set_title(f'FFT (ALPHA = {x})')
    # ax.set_xlabel('Frequency (Hz)', color='white')
    # ax.set_ylabel('Magnitude', color = 'white')
    # ax.set_title(f'FFT (ALPHA = {x})', color='white')
    ax.legend(loc='upper left')

    # SNR 계산 및 표시
    # snr = calculate_snr(fft_acc, fft_fil)
    # ax.text(0.95, 0.95, f'SNR: {snr:.2f} dB', verticalalignment='top', horizontalalignment='right', transform=ax.transAxes, fontsize=10, bbox=dict(facecolor='white', alpha=0.5))


def main():
    print("시각화할 시나리오 선택 :", end=" ")
    scenario = input()
    print("시작 숫자 선택 : ", end= " ")
    start = float(input())
    # print("끝 숫자 선택 : ", end= " ")
    # end = float(input())
    print("increment 선택 ex) 0.1, 0.01, ... : ", end= " ")
    incre = float(input())

    # fig, ax = plt.subplots(1, 1, figsize=(15, 5))  # 1x3 서브플롯 생성
    fig, axs = plt.subplots(3, 3, figsize=(15, 5))  # 1x3 서브플롯 생성
    # fig, axs = plt.subplots(3, 3, figsize=(15, 5), facecolor='black')  # 1x3 서브플롯 생성
    
    for i in range(3):  # 0.1부터 0.9까지
        for j in range(3):
            alpha = start + ((i * 3 + j + 1) * incre)
            plot_fft(alpha, axs[i, j], scenario)

    for ax in axs.flat:
        ax.set_xlabel('Frequency (Hz)')
        ax.set_ylabel('Magnitude')
        ax.grid(True)

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()