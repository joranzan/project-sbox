'''
실시간 MPU 6050 시각화 프로그램
'''

import queue
import threading
import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import csv
import atexit
import sys

sensorDataQueue = queue.Queue()

# # CSV 파일 이름 설정
# if len(sys.argv) > 1:
#     csv_filename = f"ALPHA_{sys.argv[1]}.csv"
# else:
#     csv_filename = "unknown_alpha.csv"

# # csv 파일 생성
# csv_file = open(f"../data/{csv_filename}", mode='w', newline='')  # CSV 파일 열기
# csv_writer = csv.writer(csv_file)

# # CSV 파일을 닫는 함수를 등록
# def close_csv_file():
#     csv_file.close()

# # 프로그램 종료될 때 csv 파일 닫기
# atexit.register(close_csv_file)

# 센서 값 읽기 쓰래드 함수
# 그래프를 업데이트 하는 속도보다 시리얼 데이터 전송 속도가 더 빠르기 때문에
# 쓰레드를 통해 이를 해결한다.

def serialSensorRead():
    while True:
        try:
            serialData = ser.readline().decode().strip().split(',')
            # 예외 처리
            if len(serialData) != 9:
                continue
            
            accelX = float(serialData[0])
            accelY = float(serialData[1])
            accelZ = float(serialData[2])

            gyroX = float(serialData[3])
            gyroY = float(serialData[4])
            gyroZ = float(serialData[5])

            filX = float(serialData[6])
            filY = float(serialData[7])
            filZ = float(serialData[8])

            sensorDataQueue.put((float(accelX), float(accelY), float(accelZ), float(gyroX), float(gyroY), float(gyroZ), float(filX), float(filY), float(filZ)))
            # csv_writer.writerow((accelX, accelY, accelZ, gyroX, gyroY, gyroZ, filX, filY, filZ))  # 데이터를 파일에 쓰기
        except:
            print("기다려")
            

ser = serial.Serial("COM9", 115200)
# 그래프에서 보여줄 최대 정점
max_points = 100

# 그래프 설정
fig = plt.figure()
plt.subplots_adjust(left=0.125, bottom=0.1, right=0.9, top=0.9, wspace=0.2, hspace=0.5)

# Subplot을 행으로 표시
# accelAxes = fig.add_subplot(3, 1, 1, xlim=(0, max_points), ylim=(-200.0, 200.0))
# gyroAxes = fig.add_subplot(3, 1, 2, xlim=(0, max_points), ylim=(-300.0, 300.0))
# filAxes = fig.add_subplot(3, 1, 3, xlim=(0, max_points), ylim=(-200.0, 200.0))

# Subplot을 열로 표시
accelAxes = fig.add_subplot(1, 3, 1, xlim=(0, max_points), ylim=(-180.0, 180.0))
gyroAxes = fig.add_subplot(1, 3, 2, xlim=(0, max_points), ylim=(-180.0, 180.0))
filAxes = fig.add_subplot(1, 3, 3, xlim=(0, max_points), ylim=(-180.0, 180.0))


# accelAxes 그래프 상세 설정
# 그래프 제목 설정
accelAxes.set_title('Accelation')
# x축 설정
accelLineX, = accelAxes.plot([], [], lw=2)
accelLineX, = accelAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='red', label='x')
# y축 설정
accelLineY, = accelAxes.plot([], [], lw=2)
accelLineY, = accelAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='green', label='y')
# z축 설정
accelLineZ, = accelAxes.plot([], [], lw=2)
accelLineZ, = accelAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='blue', label='z')
# 그래프 옆에 x, y, z축 안내 정보 표기
accelAxes.legend(loc='upper left', bbox_to_anchor=(1.0, 1.0))

gyroAxes.set_title('Gyroscope')
gyroLineX, = gyroAxes.plot([], [], lw=2)
gyroLineX, = gyroAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='red', label='x')
gyroLineY, = gyroAxes.plot([], [], lw=2)
gyroLineY, = gyroAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='green', label='y')
gyroLineZ, = gyroAxes.plot([], [], lw=2)
gyroLineZ, = gyroAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='blue', label='z')
gyroAxes.legend(loc='upper left', bbox_to_anchor=(1.0, 1.0))

filAxes.set_title('Filtered')
filLineX, = filAxes.plot([], [], lw=2)
filLineX, = filAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='red', label='x')
filLineY, = filAxes.plot([], [], lw=2)
filLineY, = filAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='green', label='y')
filLineZ, = filAxes.plot([], [], lw=2)
filLineZ, = filAxes.plot(np.arange(max_points), np.ones(max_points, dtype=np.float64)*np.nan, lw=0.6, color='blue', label='z')
filAxes.legend(loc='upper left', bbox_to_anchor=(1.0, 1.0))

# 그래프 필요 값 초기화 함수
def init():
    return accelLineX, accelLineY, accelLineZ, gyroLineX, gyroLineY, gyroLineZ, filLineX, filLineY, filLineZ

# 큐에 쌓인 데이터 통합하여 반환. 그래프에 한번에 적용하여 속도 증대.
def getAllSensorDataOnQueue():
    accelXBunch = []
    accelYBunch = []
    accelZBunch = []
    gyroXBunch = []
    gyroYBunch = []
    gyroZBunch = []
    filXBunch = []
    filYBunch = []
    filZBunch = []
    while not sensorDataQueue.empty():
        accelX, accelY, accelZ, gyroX, gyroY, gyroZ, filX, filY, filZ = sensorDataQueue.get_nowait()
        accelXBunch.append(accelX)
        accelYBunch.append(accelY)
        accelZBunch.append(accelZ)
        gyroXBunch.append(gyroX)
        gyroYBunch.append(gyroY)
        gyroZBunch.append(gyroZ)
        filXBunch.append(filX)
        filYBunch.append(filY)
        filZBunch.append(filZ)
    return tuple(accelXBunch), tuple(accelYBunch), tuple(accelZBunch), tuple(gyroXBunch), tuple(gyroYBunch), tuple(gyroZBunch), tuple(filXBunch), tuple(filYBunch), tuple(filZBunch)

# 그래프 업데이트 함수
def animate(i):
    accelX, accelY, accelZ, gyroX, gyroY, gyroZ, filX, filY, filZ = getAllSensorDataOnQueue()
    # 예외 처리
    if (accelX.count == 0 or
        accelY.count == 0 or 
        accelZ.count == 0 or
        gyroX.count == 0 or
        gyroY.count == 0 or
        gyroZ.count == 0 or
        filX.count == 0 or
        filY.count == 0 or
        filZ.count == 0):
        return

    # accel
    oldAccelX = accelLineX.get_ydata()
    # print('=============',oldAccelX)
    newAccelX = np.r_[oldAccelX[len(accelX):], accelX]
    accelLineX.set_ydata(newAccelX)

    oldAccelY = accelLineY.get_ydata()
    newAccelY = np.r_[oldAccelY[len(accelY):], accelY]
    accelLineY.set_ydata(newAccelY)

    oldAccelZ = accelLineZ.get_ydata()
    newAccelZ = np.r_[oldAccelZ[len(accelZ):], accelZ]
    accelLineZ.set_ydata(newAccelZ)

    # gyro
    oldGyroX = gyroLineX.get_ydata()
    newGyroX = np.r_[oldGyroX[len(gyroX):], gyroX]
    gyroLineX.set_ydata(newGyroX)

    oldGyroY = gyroLineY.get_ydata()
    newGyroY = np.r_[oldGyroY[len(gyroY):], gyroY]
    gyroLineY.set_ydata(newGyroY)

    oldGyroZ = gyroLineZ.get_ydata()
    newGyroZ = np.r_[oldGyroZ[len(gyroZ):], gyroZ]
    gyroLineZ.set_ydata(newGyroZ)

    # fil
    oldFilX = filLineX.get_ydata()
    newFilX = np.r_[oldFilX[len(filX):], filX]
    filLineX.set_ydata(newFilX)

    oldFilY = filLineY.get_ydata()
    newFilY = np.r_[oldFilY[len(filY):], filY]
    filLineY.set_ydata(newFilY)

    oldFilZ = filLineZ.get_ydata()
    newFilZ = np.r_[oldFilZ[len(filZ):], filZ]
    filLineZ.set_ydata(newFilZ)

    return accelLineX, accelLineY, accelLineZ, gyroLineX, gyroLineY, gyroLineZ, filLineX, filLineY, filLineZ

# 시리얼 통신 센서값 읽기 함수 쓰래드 등록 및 시작
# 이를 통해 백그라운드에서 데이터를 읽어오도록 하고, 그래프 업데이트를 한다.
# 파이썬에서 쓰레드는 백그라운드에서 Sub 작업을 처리하는 용도
serialSensorReadThread = threading.Thread(target=serialSensorRead, daemon=True)
serialSensorReadThread.start()

# 그래프 업데이트 등록 및 시작
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=200, interval=20, blit=False)
plt.show()