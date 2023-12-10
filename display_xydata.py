import serial
import pygame
from collections import deque

def transform_coordinate(x, y):
    x = ((x + 4600) / 15)  # x 좌표변환
    y = ((y + 4600) / 15)  # y 좌표변환
    return int(x), int(y)

ser = serial.Serial('COM6', 115200)

# deque를 사용하여 최대 10000개의 데이터만 저장하도록 합니다.
x_data = deque(maxlen=1200)
y_data = deque(maxlen=1200)

pygame.init()
win_size = 700
win = pygame.display.set_mode((win_size, win_size))  # Pygame 윈도우를 생성합니다.

while len(x_data) < 10000:  # x_data의 길이가 10000보다 작은 동안 계속 실행합니다.
    if ser.in_waiting > 0:
        line = ser.readline().decode('latin1').rstrip()
        data = line.split()  # 데이터를 분리합니다.
        if len(data) == 3:  # 데이터가 4개의 요소를 가지는지 확인합니다.
            _, x_val, y_val = data
            try:
                x = float(x_val)
                y = float(y_val)
            except ValueError:
                continue  # 현재의 데이터를 건너뛰고 다음 데이터를 처리합니다.

            x, y = transform_coordinate(x, y)  # 좌표를 변환합니다.

            x_data.append(x)
            y_data.append(y)

            win.fill((0, 0, 0))  # 윈도우를 검은색으로 채웁니다.
            for i in range(len(x_data)):
                pygame.draw.rect(win, (255, 255, 255), pygame.Rect(x_data[i], y_data[i], 2.5, 2.5))  # 점을 찍습니다.
            pygame.display.update()  # 화면을 갱신합니다.

