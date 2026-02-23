#define BLYNK_TEMPLATE_ID "TMPL3ywuMoMTw"
#define BLYNK_TEMPLATE_NAME "STM32 ESP01"
#define BLYNK_AUTH_TOKEN    "gmDjNw-gBtEsIfF44BeUT3wA5KXw96Bl"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Black_pearl";
char pass[] = "t3ra552x";

void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud", 80);
}

BLYNK_WRITE(V0)
{
  int val = param.asInt();
  Serial.print("LED:");
  Serial.println(val);
}

void loop()
{
  Blynk.run();
}
