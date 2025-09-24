#include <Arduino.h>
#define BUTTON_PIN 4
int count = -1;
int SensorValueArray[20];
int ValueSum;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
void loop()
{
  byte buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW) {
      
    if (count < 19) {
      count += 1;
      int MoistureValue = analogRead(A0);
      Serial.println(MoistureValue);
      SensorValueArray[count] = MoistureValue;
      ValueSum = ValueSum + SensorValueArray[count];
    }
    else if (count >= 19) {
      Serial.println("Done!");
    }
  }
  else if (buttonState == HIGH) {
    int Average = ValueSum / (count+1);
    if (Average > 0) {
    Serial.print("The average is ");
    Serial.println(Average);
    }
    count = -1;
    ValueSum = 0;
  }
  delay(100);
}