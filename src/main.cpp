#include <Arduino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#define BUTTON_PIN 4
int count = -1;
int SensorValueArray[50];
int ValueSum;
int one_hundred_ms = 100;

ArduinoLEDMatrix matrix; // Create an instance of the ArduinoLEDMatrix class
#define ARDUINO_GRAPHICS_DEFAULT_COLOR 0xFFFFFF // Default for Graphics Library to Write as On

void setup()
{
  matrix.begin();
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
void loop()
{
  byte buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW) {
      
    if (count < 49) {
      count += 1;
      int MoistureValue = analogRead(A0);
      Serial.println(MoistureValue);
      SensorValueArray[count] = MoistureValue;
      ValueSum = ValueSum + SensorValueArray[count];
    }
    else if (count >= 49) {
      Serial.println("Done!");
      String MatrixDone = " Done!! ";
      matrix.beginDraw();
      matrix.stroke(ARDUINO_GRAPHICS_DEFAULT_COLOR);
      matrix.textScrollSpeed(one_hundred_ms);
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, ARDUINO_GRAPHICS_DEFAULT_COLOR);
      matrix.println(MatrixDone);
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();
    }
  }
  else if (buttonState == HIGH) {
    int Average = ValueSum / (count+1);
  
    if (Average > 0) {
    Serial.print("The average is ");
    Serial.println(Average);
    char message[] = " The average is: ";
    String spacesBuffer = " ";
    String MatrixMessage = spacesBuffer + "Avg: " + Average + spacesBuffer;
    matrix.beginDraw();
    matrix.stroke(ARDUINO_GRAPHICS_DEFAULT_COLOR);
    matrix.textScrollSpeed(one_hundred_ms);
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, ARDUINO_GRAPHICS_DEFAULT_COLOR);
    matrix.println(MatrixMessage);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    }
    count = -1;
    ValueSum = 0;
  }
  delay(100);
}