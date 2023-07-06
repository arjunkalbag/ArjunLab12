/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/student/Desktop/IoT/ArjunLab12/src/ArjunLab12.ino"
// libraries
#include "MQTT.h"
#include "oled-wing-adafruit.h"

void setup();
void loop();
void resetDisplay();
#line 5 "/Users/student/Desktop/IoT/ArjunLab12/src/ArjunLab12.ino"
SYSTEM_THREAD(ENABLED);

void callback(char *topic, byte *payload, unsigned int length);

OledWingAdafruit display;
MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();

  pinMode(D7, OUTPUT);

  client.subscribe("testtopic/CoolTopic1");
}
void loop()
{
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("testtopic/CoolTopic1");
    Serial.println("X");
  }
  display.loop();

  if (display.pressedA())
  {
    client.publish("testtopic/CoolTopic1", "A!");
  }
  if (display.pressedB())
  {
    client.publish("testtopic/CoolTopic1", "B!");
  }
  if (display.pressedC())
  {
    client.publish("testtopic/CoolTopic1", "C!");
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("callback");
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();

  if (String(p).equals("1"))
  {
    Serial.println("HIGH");
    digitalWrite(D7, HIGH);
  }
  else if (String(p).equals("0"))
  {
    Serial.println("LOW");
    digitalWrite(D7, LOW);
  }
  else if (String(p).equals("A!"))
  {
    resetDisplay();
    display.println("A!");
    display.display();
  }
  else if (String(p).equals("B!"))
  {
    resetDisplay();
    display.println("B!");
    display.display();
  }
  else if (String(p).equals("C!"))
  {
    resetDisplay();
    display.println("C!");
    display.display();
  }
  else
  {
    Serial.println(p);
  }
}
void resetDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
}