import serial
import sys
import time
from dataclasses import dataclass
import struct
from keys.keys import KeyList

KEYS = KeyList()

# class Arduino:
#     serialObj = 'COM1'
#     serialPort: int = 9600
#     baudRate: int = None


#     def setSerial(self, port):
#         self.serialObj = serial.Serial(port=port, baudrate=self.baudRate)

#     def setBaudrate(self, rate):
#         # self.serialObj = serial.Serial(port=port, baudrate=self.baudRate)


py_serial = serial.Serial(
    # Window
    port='COM10',

    # 보드 레이트 (통신 속도)
    baudrate=9600,
)

# 보내는 데이터의 형식 선언
# bool, int = 1byte, 4byte 총 5byte 크기의 데이터


@dataclass
class ProtocolSendKey:
    press: bool = None
    key: int = None


# ProtoSend타입의 데이터를 바이트로 직렬화함
def serializeProtocol(_protoSend):
    # < : little endian
    # ? : boolean - 1byte
    # i : integer - 4byte
    return struct.pack('<?i', _protoSend.press, _protoSend.key | 0)


# def deserialize_protocol(data):
#     press, press_value, key = struct.unpack('!??I', data)
#     return Protocol(press=bool(press), key=key if press else None)


def inputKey(method, key, delay=None):
    if method not in ['press', 'release', 'push']:
        raise ValueError(
            "Invalid method. Method must be 'press', 'release', or 'push'.")

    if not isinstance(key, int):
        raise TypeError("Key must be an integer.")

    if method in ['push'] and not isinstance(delay, int):
        raise TypeError(
            "Delay must be an integer for 'push' method.")

    if (method == 'press'):
        py_serial.write(serializeProtocol(
            ProtocolSendKey(press=True, key=key)))
    elif (method == 'release'):
        py_serial.write(serializeProtocol(
            ProtocolSendKey(press=False, key=key)))
    elif (method == 'push'):
        py_serial.write(serializeProtocol(
            ProtocolSendKey(press=True, key=key)))
        time.sleep(delay/1000)
        py_serial.write(serializeProtocol(
            ProtocolSendKey(press=False, key=key)))


# 시리얼 통신의 최대 크기는 900byte
sendData = ProtocolSendKey(press=False, key=65)
byteData = serializeProtocol(sendData)
print(byteData)

inputKey('press', KEYS.KEY_LEFT_SHIFT)
time.sleep(0.2)
inputKey('press', KEYS.KEY_1)
time.sleep(0.1)
inputKey('release', KEYS.KEY_1)
time.sleep(0.1)
inputKey('press', KEYS.KEY_Q)
time.sleep(0.1)
inputKey('release', KEYS.KEY_Q)
time.sleep(0.1)
inputKey('release', KEYS.KEY_LEFT_SHIFT)


# for i in range(10):

#     inputKey('push', KEY_RIGHT_ALT, 50)
#     inputKey('push', 97, 50)

while True:

    # time.sleep(0.1)
    # break
    if py_serial.readable():
        response = py_serial.read(4)
        print(int.from_bytes(response, 'little'))
