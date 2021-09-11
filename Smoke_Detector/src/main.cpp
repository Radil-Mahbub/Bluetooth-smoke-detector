#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial (2,3); // RX || TX

//MQ-2 setting
#define gasPin A0
int Sval = 0;
const int Slimit = 800;

//outputs
#define buzzer 12
#define Rled 7
#define Gled 6

void setup()
{
  BTserial.begin (9600);
  Serial.begin (9600);

  pinMode (Rled, OUTPUT);
  pinMode (Gled, OUTPUT);
  pinMode (buzzer, OUTPUT);
}

void loop()
{

   Sval = analogRead(gasPin);

   //If smoke is detected
   if (Sval > Slimit)
   {
    digitalWrite (Gled, LOW);
    digitalWrite (Rled, HIGH);
    
    tone (buzzer, 10000);
    noTone (buzzer);
    delay (100);
    tone (buzzer, 10000);
    delay (100);
    
    BTserial.print ("!!FIRE!!");
    BTserial.print (",");
   }

   else
   {
    digitalWrite (Rled, LOW);
    digitalWrite (Gled, HIGH);
    noTone (buzzer);
    
    BTserial.print ("All good");
    BTserial.print (",");
   }
   
   BTserial.print (Sval);
   BTserial.print(";");
   
   Serial.println (Sval);

}
