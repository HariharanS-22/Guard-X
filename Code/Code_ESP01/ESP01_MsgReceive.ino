#define BLYNK_TEMPLATE_ID "TMPL3ywuMoMTw"
#define BLYNK_TEMPLATE_NAME "STM32 ESP01"
#define BLYNK_AUTH_TOKEN    "gmDjNw-gBtEsIfF44BeUT3wA5KXw96Bl"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Black_pearl";
char pass[] = "t3ra552x";

char buffer[32];
uint8_t indexBuf = 0;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud",80);
}

void loop()
{
  Blynk.run();

  while(Serial.available())
  {
    char c = Serial.read();

    // End of line received
    if(c == '\n')
    {
      buffer[indexBuf] = '\0';

      if(strncmp(buffer,"D:",2)==0)
      {
        float dist = atof(buffer+2);
        Blynk.virtualWrite(V3, dist);
      }

      indexBuf = 0;   // reset buffer
    }
    else
    {
      if(indexBuf < sizeof(buffer)-1)
        buffer[indexBuf++] = c;
    }
  }
}