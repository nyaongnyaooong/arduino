#include "Keyboard.h"  // Keyboard library
#include "Mouse.h"     // Mouse library


String reqData = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:


  while (Serial.available()) {
    char data = Serial.read();
    reqData.concat(data);
    // reqData = Serial.read();
  }

  if (reqData == "a") {
    digitalWrite(LED_BUILTIN, HIGH);
    Keyboard.println(reqData);
    //reqData = "";
  } else if (reqData == "Click_Left"){
    digitalWrite(LED_BUILTIN, HIGH);
    Mouse.click();
    digitalWrite(LED_BUILTIN, LOW);

  } else if (reqData == "Click_Right"){
    digitalWrite(LED_BUILTIN, HIGH);
    Mouse.click(MOUSE_RIGHT);
    digitalWrite(LED_BUILTIN, LOW);

  }

  reqData = "";

/*
  if (reqData > 0 && reqData < 128) {
    //resKey(reqData);
    digitalWrite(LED_BUILTIN, HIGH);
    Keyboard.write(reqData);
    reqData = 0;
    digitalWrite(LED_BUILTIN, LOW);

  } else if (reqData == 129) {
    Keyboard.press(reqData);
    reqData = 0;

  }
  */

    // if (reqData) {
    // //resKey(reqData);
    // digitalWrite(LED_BUILTIN, HIGH);
    // Keyboard.press(reqData);
    // delay(1000);                      // wait for a second
    // Keyboard.releaseAll();
    // reqData = 0;
    // digitalWrite(LED_BUILTIN, LOW);

  
    delay(1000);                      // wait for a second
}


void resKey(int reqData) {
  digitalWrite(LED_BUILTIN, HIGH);
  Keyboard.write("STEEMIT!");
  digitalWrite(LED_BUILTIN, LOW);
  reqData = 0;
  return;
}
