import serial
import pickle
import sys
import time
from dataclasses import dataclass, asdict
import struct

py_serial = serial.Serial(
    # Window
    port='COM8',

    # 보드 레이트 (통신 속도)
    baudrate=9600,
)


@dataclass
class Protocol:
    press: bool = None
    key: int = None


def serialize_protocol(protocol_instance):
    # press_value = 1 if protocol_instance.press else 0
    # key_value = 0 if protocol_instance.key == None else protocol_instance.key
    return struct.pack('<?i', protocol_instance.press, protocol_instance.key | 0)


# def deserialize_protocol(data):
#     press, press_value, key = struct.unpack('!??I', data)
#     return Protocol(press=bool(press), key=key if press else None)


# 시리얼 통신 최대 크기는 900byte로
# 유니코드 1글자당 2byte로 최대 450글자 전송가능으로 예상
sendData = Protocol(press=False, key=32768456)
byteData = serialize_protocol(sendData)
print(byteData)
# print(sys.getsizeof(byteData))
# # print(byteData)
# # py_serial.write(byteData)
# string = 'asd'
# print(sys.getsizeof(string))
# encString = string.encode()
# print(sys.getsizeof(encString))

# print('asd'.encode())
# py_serial.write('asd'.encode())
py_serial.write(byteData)

while True:

    # time.sleep(0.1)
    # break
    if py_serial.readable():

        # 들어온 값이 있으면 값을 한 줄 읽음 (BYTE 단위로 받은 상태)
        # BYTE 단위로 받은 response 모습 : b'\xec\x97\x86b\xec\x9d\x8c\r\n'
        response = py_serial.read(4)
        print(int.from_bytes(response, 'little'))

        # 디코딩 후, 출력 (가장 끝의 \n을 없애주기위해 슬라이싱 사용)
        # print(response[:len(response)-1].decode())
