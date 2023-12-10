# (distance, theta) --> (x,y)
# same coordinate system

import serial

ser = serial.Serial('COM6', 115200)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        _, x_val, _, y_val = line.split()
        x = float(x_val)
        y = float(y_val)
        print('x:', x, ' y:', y)
        
        