#include <Keyboard.h>

// char receivedString[];

typedef struct _protocol
{
  bool press;
  int key;

} protocol;

void setup()
{

  // 시리얼 통신 시작 (boadrate: 9600)
  Serial.begin(9600);
}

protocol protocolData;
void loop()
{
  // 컴퓨터로부터 시리얼 통신이 전송되면, 한줄씩 읽어와서 cmd 변수에 입력
  // 5번째 버퍼
  if (Serial.available() >= 5)
  {
    char *pReceivedData = (char *)&protocolData;
    // n번째 바이트 자리에 넣음
    Serial.readBytes(pReceivedData, 5);

    // Serial.println(protocolData.press);
    Serial.write((char *)&protocolData.key, 4);
  }
  else if (Serial.available() > 0)
  {
    Serial.flush();
  }
}