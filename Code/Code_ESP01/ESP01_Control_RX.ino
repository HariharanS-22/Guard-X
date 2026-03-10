#define BLYNK_TEMPLATE_ID "TMPL3ywuMoMTw"
#define BLYNK_TEMPLATE_NAME "STM32 ESP01"
#define BLYNK_AUTH_TOKEN "gmDjNw-gBtEsIfF44BeUT3wA5KXw96Bl"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[]="Black_pearl";
char pass[]="t3ra552x";

int joyX=512,joyY=512;
int speed = 800;

char buffer[32];
uint8_t indexBuf = 0;

void setup(){
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass,"blynk.cloud",80);
}

BLYNK_WRITE(V0)   // Speed
{
  int newSpeed = param.asInt();
  if (newSpeed != speed) {
    speed = newSpeed;
    Serial.printf("S:%d\r\n", speed);
  }
}

BLYNK_WRITE(V1){
  joyX=param.asInt();
  Serial.printf("J:%d,%d\r\n",joyX,joyY);
}

BLYNK_WRITE(V2){
  joyY=param.asInt();
  Serial.printf("J:%d,%d\r\n",joyX,joyY);
}

void loop(){
  Blynk.run();

  while(Serial.available())
  {
    char c = Serial.read();
    // Ignore carriage return
    if(c == '\r') 
      continue;
    // End of line received
    if(c == '\n')
    {
      buffer[indexBuf] = '\0';

      if(strncmp(buffer,"D:",2)==0)
      {
        float dist = atof(buffer+2);
        Blynk.virtualWrite(V3, dist);
      }

      if(strncmp(buffer,"V:",2)==0)
      {
        float vel = atof(buffer+2);
        Blynk.virtualWrite(V4, vel);
      }

      indexBuf = 0;   // reset buffer
    }
    else
    {
      if(indexBuf < sizeof(buffer)-1)
        buffer[indexBuf++] = c;
      else
        indexBuf = 0;    // overflow protection
    }
  }
  
}