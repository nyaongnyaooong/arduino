#include <Keyboard.h>

struct Protocol_ {
  bool press;
  int key;
};

void setup() {
  // 시리얼 통신 시작 (boadrate: 9600)
  Serial.begin(9600);

  // Key 입력 시작
  Keyboard.begin();
}

// 들어오는 데이터 해석
// void interpretProtocol(Serial_ serial, char *pProtocolVariable, size_t byteLength) {
void interpretProtocol(Serial_ serial, Protocol_ protocolVariable, size_t byteLength) {
  // 미리 선언한 protocol 타입의 변수 데이터가 시작하는 첫번째 byte의 포인터 주소
  char *pProtocolVariable = (char *)&protocolVariable;

  // 전달받은 데이터 5byte를 미리 선언한 protocol 타입의 변수에 차례대로 넣음
  serial.readBytes((char *)&protocolVariable, byteLength);
}

void processKeyboard(Keyboard_ keyboard, bool press, int keyNumber) {

  // ASCII 코드 범위 내 숫자는 그대로 출력
  if (keyNumber) {
    if (press)
      keyboard.press(keyNumber);
    else
      keyboard.release(keyNumber);
  }
}

Protocol_ protocolData;

void loop() {
  // 5byte의 데이터를 받기로 프로토콜로 약속됨
  if (Serial.available() >= 5) {
    // 5byte씩 데이터 해석하여 protocolData에 넣음
    Serial.readBytes((char *)&protocolData, 5);

    processKeyboard(Keyboard, protocolData.press, protocolData.key);

    // Serial.write((char *)&protocolData.key, 4);
  } else if (Serial.available() > 0) {
    // 5byte 미만의 데이터는 삭제해버림
    Serial.flush();
  }
}

// if (Serial.available() >= 5) {
//   char *pReceivedData = (char *)&protocolData;
//   // n번째 바이트 자리에 넣음
//   Serial.readBytes(pReceivedData, 5);

//   // Serial.println(protocolData.press);
//   Serial.write((char *)&protocolData.key, 4);
// } else if (Serial.available() > 0) {
//   Serial.flush();
// }