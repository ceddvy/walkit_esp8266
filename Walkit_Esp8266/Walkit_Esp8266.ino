
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"

#define BLYNK_TEMPLATE_ID "TMPLE_cfRtY3"
#define BLYNK_DEVICE_NAME "WALKIT"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI
#define trig D2
#define echo D1

#include "BlynkEdgent.h"

BlynkTimer timer;
WidgetLCD lcd(V3);

long duration;
int distance;
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  delay(100);
  BlynkEdgent.begin();

  timer.setInterval(1000L, sendSensor);
}

int userSet;
BLYNK_WRITE(V2){
  int setValue = param.asInt();
  userSet =  setValue;
}
void loop() {
  BlynkEdgent.run();
  timer.run();
}

void sendSensor(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance <= userSet){
    Blynk.logEvent("walkit", String("Walker detected an obstacle. Now Turning."));
  }
  lcd.print(0, 0, "Distance: ");
  lcd.print(0, 1, String(distance)+ "cm");
  delay(1000);

}

