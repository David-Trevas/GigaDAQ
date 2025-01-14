#include "GigaDAQ.h"
#include <Servo.h>

GigaDAQ daq(PORTRAIT_USBDOWN);
Servo motor;

uint32_t currTime, prevTime;

const int PHOTOCELL = A0;
const int SERVO_POS = 9;

void setup() {
  Serial.begin(115200);
  motor.attach(SERVO_POS);
  daq.begin();
  analogReadResolution(16);

  daq.slider[0] = Slider("Servo Position", 5, 85, 70, 12, BLUE, WHITE);
  daq.slider[0].setXlimits(0.0, 180.0);
  daq.slider[0].setPosition(90.0, 1.0);
  daq.slider[0].setMode(HORIZONTAL);
  daq.slider[0].setSlideAction(choosePosition);
  motor.write(90);

  daq.textbox[0] = Textbox("Slider val", 77, 85, 20, 12, WHITE, BLUE);
  daq.textbox[0].setDisplayText(String(daq.slider[0].posX));

  daq.button[0] = Button("Take data", 20, 70, 60, 13, BLACK, CYAN);
  daq.button[0].setDisplayText("Reading");
  daq.button[0].setButtonUp(dataButton);

  daq.textbox[1] = Textbox("Photovalue", 5, 10, 60, 10, BLACK, YELLOW);
  daq.textbox[1].setDisplayText("Photocell value");

  daq.drawAll();
  prevTime = millis();
}

void loop() {
  currTime = millis();

  if(currTime - prevTime >= 200){
    daq.handleInputs();
    prevTime = currTime;
  }

  daq.updateDisplays();
}

void dataButton(){
  int i, val;
  String buttonText = "";
  float currentPos;
  unsigned int sum = 0;

  currentPos = daq.slider[0].posX;

  for(i = 0; i < 10; i++){
    val = analogRead(PHOTOCELL);
    sum += val;
    //sum += (int)(1000.0*sin(currentPos/57.0));
    buttonText = "R #";
    buttonText += String(i+1);
    buttonText += " ";
    buttonText += String(val);
    Serial.println(buttonText);
    daq.textbox[1].setDisplayText(buttonText);
    daq.updateDisplays();
    buttonText = "";
    delay(100);
  }

  daq.textbox[1].setDisplayText(String(sum/10));
  Serial.println(String(sum/10));
}

void choosePosition(){
  int motorPos;
  motorPos = (int)(daq.slider[0].posX);
  motor.write(motorPos);
  daq.textbox[0].setDisplayText(String(motorPos));
  Serial.println(String(motorPos));
  daq.updateDisplays();
}
