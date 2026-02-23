#define BLYNK_TEMPLATE_ID "TMPL3ywuMoMTw"
#define BLYNK_TEMPLATE_NAME "STM32 ESP01"
#define BLYNK_AUTH_TOKEN "gmDjNw-gBtEsIfF44BeUT3wA5KXw96Bl"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Black_pearl";
char pass[] = "t3ra552x";

int joyX = 512;
int joyY = 512;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
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