/*************************************************************

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT DebugSerial

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); 

#include <BlynkSimpleStream.h>

char auth[] = "4WDRdLKzQokS4MYS5GSzvELm9v6Oecwj";

const int pump=5;
const int buzzer=6;
const int x=A0;
const int fire=4;
const int noise=3;

void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  pinMode(pump,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(x,INPUT);
  pinMode(fire, INPUT);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop()
{
  Blynk.run();
  tilted();
  is_fire();
  is_noise();
}

void tilted(){
  int val=analogRead(x);
  Blynk.virtualWrite(V13,val);
  if(val<255){
    Blynk.virtualWrite(V12,"Tilted");
  }else{
    Blynk.virtualWrite(V12,".....");
  }
}

void is_fire(){
  int val=digitalRead(fire);
  if(val){
    Blynk.virtualWrite(V14,"Fire");
  }else{
    Blynk.virtualWrite(V14,".....");
  }
}

void is_noise(){
  int val=digitalRead(noise);
  if(val){
    Blynk.virtualWrite(V15,"Noise");
  }else{
    Blynk.virtualWrite(V15,".....");
  }
}

BLYNK_WRITE(V8){
  int val=param.asInt();
  if(val){
    digitalWrite(pump,HIGH);
    Blynk.virtualWrite(V10,"ON");
  }else{
    digitalWrite(pump,LOW);
    Blynk.virtualWrite(V10,".....");
  }
}



BLYNK_WRITE(V7){
  int val=param.asInt();
  if(val){
    digitalWrite(pump,HIGH);
    Blynk.virtualWrite(V11,"ON");
  }else{
    digitalWrite(pump,LOW);
    Blynk.virtualWrite(V11,".....");
  }
}
