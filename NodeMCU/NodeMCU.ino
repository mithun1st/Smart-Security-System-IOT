

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

String tem,str = "";

const String pas = "alpha", ext = "close";



char auth[] = "XO5tPgy2O6-kgNplfXXy35rTgtWdWQ_a";

WidgetLED le0(V0);
WidgetLED le1(V1);
WidgetLED le2(V2);
WidgetLED le3(V3);


char ssid[] = "mi4x";
char pass[] = "654321";

void setup()
{


  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  le0.off();
  le1.off();
  le2.off();
  le3.off();
}


//terminal
BLYNK_WRITE(V7)
{
  tem=str;
  str = param.asStr();
  Serial.print(str);

  if (pas == str) {
    Blynk.virtualWrite(V7, "Command Accecpt :)");
    le0.on();
  }
  else if(tem==pas && str!=ext){
    str=pas;
  }
  else if (ext == str) {
    Blynk.virtualWrite(V7, "Log off . . .");
    le0.off();
  }
  else{
    Blynk.virtualWrite(V7, "Access Denied !!");
  }
}

//light
BLYNK_WRITE(V8)
{
  int i = param.asInt();

  if (str == pas && i == 1) {
    Serial.print("a1");
    le1.on();
    Blynk.virtualWrite(V7, "Light is ON");
  }
  if (str == pas && i == 0) {
    Serial.print("a0");
    le1.off();
    Blynk.virtualWrite(V7, "Light is OFF");
  }
  if(str!=pas){
    Blynk.virtualWrite(V7, "Access Denied !!");
  }
}

//fan
BLYNK_WRITE(V9)
{
  int i = param.asInt();

  if (str == pas && i == 1) {
    Serial.print("b1");
    le2.on();
    Blynk.virtualWrite(V7, "Fan is ON");
  }
  if (str == pas && i == 0) {
    Serial.print("b0");
    le2.off();
    Blynk.virtualWrite(V7, "Fan is OFF");
  }
  if(str!=pas){
    Blynk.virtualWrite(V7, "Access Denied !!");
  }
}

//door
BLYNK_WRITE(V10)
{
  int i = param.asInt();

  if (str == pas && i == 1) {
    Serial.print("c1");
    le3.on();
    Blynk.virtualWrite(V7, "Door OPEN");
  }
  if (str == pas && i == 0) {
    Serial.print("c0");
    le3.off();
    Blynk.virtualWrite(V7, "Door CLOSE");
  }
  if(str!=pas){
    Blynk.virtualWrite(V7, "Access Denied !!");
  }
}


void loop()
{
  Blynk.run();

}
