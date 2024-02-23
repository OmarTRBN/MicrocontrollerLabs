import serial
import time

arduino = serial.Serial('COM8', 9600)
time.sleep(2)

while True:
    data = input("Enter a string to display on the LCD: ")
    arduino.write(data.encode())  
    time.sleep(1)  # Delay to prevent flooding the serial port
