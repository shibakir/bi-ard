import serial
import sys
from time import sleep


class Uart:
    def __init__(self):
        self._ser = serial.Serial()
        self._ser.port = 'COM15'  # TODO set the correct com port!
        self._ser.baudrate = 9600
        self._ser.timeout = 1
        try:
            self._ser.open()
        except serial.SerialException:
            print("Error while opening")
            sys.exit()

    def readData(self): # returns received data as string
        return self._ser.readline().decode("utf-8")

    def writeData(self, data): # sends string data
        to_send = bytes(data,'ASCII')
        self._ser.write(to_send)

    def close(self):
        self._ser.close()


def main():

    ser = Uart()
    while True:

        nb = input( "Choose color: " )

        ser.writeData ( nb )
        

        print( " readed data: " , ser.readData() )

        #pass # todo replace pass by actual code

if __name__ == "__main__":
    main()
