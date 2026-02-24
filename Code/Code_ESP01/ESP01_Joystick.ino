#define BLYNK_TEMPLATE_ID "TMPL3ywuMoMTw"
#define BLYNK_TEMPLATE_NAME "STM32 ESP01"
#define BLYNK_AUTH_TOKEN "gmDjNw-gBtEsIfF44BeUT3wA5KXw96Bl"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Black_pearl";
char pass[] = "t3ra552x";

int joyX = 512, joyY = 512;
int speed = 800;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}
BLYNK_WRITE(V0)   // Speed
{
  int newSpeed = param.asInt();
  if (newSpeed != speed) {
    speed = newSpeed;
    Serial.printf("S:%d\r\n", speed);
  }
}

BLYNK_WRITE(V1)   // X axis
{
  joyX = param.asInt();
  Serial.printf("J:%d,%d\r\n", joyX, joyY);
}

BLYNK_WRITE(V2)   // Y axis
{
  joyY = param.asInt();
  Serial.printf("J:%d,%d\r\n", joyX, joyY);
}

void loop()
{
  Blynk.run();
}