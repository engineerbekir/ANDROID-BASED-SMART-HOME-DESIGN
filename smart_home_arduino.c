#include <DHT.h>                                              
# include <SoftwareSerial.h>                             
#include <Servo.h>                                                       
char data;
Servo servo;

int led=2;
int led2=8;
int dc_in1=4;
int dc_in2=5;
int servo6=6;
int nem_isi=7;
int buzzer=9;
int pir=11;
int rx=12;
int tx=13;
int analog;
DHT dht(humidity_heat,DHT11); 
SoftwareSerial bluetooth(tx,rx); 

bool ldrdrm=false;  
   bool humiditydrm=false;
   bool mtrdrm=false;
   bool motoropen=false;
   bool motorclose=false;
   bool pirdrm=false;

void setup()                    
{    int status;  int loop=1; 
 Serial.begin(9600);              
  bluetooth.begin(9600);
  servo.attach(servo6);  
  dht.begin();
pinMode(dc_in1,OUTPUT);
pinMode(dc_in2,OUTPUT);
pinMode(nem_isi,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(pir,INPUT);
}
void loop()
{   int data;
   analog=analogRead(A0); 
   ///bluetooth  
 if(bluetooth.available())
  {   data=bluetooth.read();
 } 
  if(data=='a')
  { ldrdrm=true;
  }
   else if(data=='b')
  { ldrdrm=false;
  }
else if(data=='c')
  { humiditydrm=true;
  }
   else if(data=='d')
  {  Serial.println("humidity status false");
     humuditydrm=false;
  }
 else if(data=='i')
  { pirdrm=true;
  }
  else  if(data=='k')
  { pirdrm=false;
  }
  /////////////////////////////
  else if(data=='e')
  {  mtrdrm=true;
  }
   else if(data=='f')
  {mtrdrm=false;
  } 
else if(data=='g')
  {   motoropen=true;
      data=' ';
  }
  else  if(data=='h')
  { motorclose=true;
      data=' '; 
  }
   else  if(data=='1')
  { servo.write(0);
      data=' ';
  } else  if(data=='2')
  { servo.write(30);
      data=' ';
  } else  if(data=='3')
  {   servo.write(45);
      data=' ';
  } else  if(data=='4')
  {servo.write(60);
      data=' ';
  } else  if(data=='5')
  {servo.write(90);
      data=' ';
  }
  ///LDR  led commands
if(ldrdrm==true)
{
 if(analog<400)
  { Serial.println("high");
    digitalWrite(led2,HIGH);
delay(500);
  }
 if(analog>400)
  {Serial.println("loww");
    digitalWrite(led2,LOW);
delay(500);
  }
}
else if(ldrdrm==false)
{ digitalWrite(led2,LOW);
}
 
  // humudity sensor
if(humuditydrm==true)
{  float temperature=dht.readTemperature(); 
 int counter=0;
 Serial.print("temperature");
 Serial.println(temperature);
  if(temperature>22)
  { 
        while(1)
        {
    if(counter==1)
    {
       counter=0;
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    Serial.println("temperature above 22");
    delay(500);
    }
    if(counter==0)
    {  counter=1;
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);    
    Serial.println("temperature below 23");
    delay(500);
    }
        }//while
  }//iftemperature>22
}//if_humuditydrm
if(humiditydrm==false)
{
  digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);   
}
 //dc motor
 if(mtrdrm==true)
 {  Serial.println("motor open");
  if(motorac==true)
  { Serial.println("curtain open");
    digitalWrite(dc_in1,HIGH);
    digitalWrite(dc_in2,LOW);
      delay(500);//rotation time
    digitalWrite(dc_in1,LOW);
    digitalWrite(dc_in2,LOW);
    delay(200);  
  motoropen=false;
  } 
 if(motorkpt==true)
  {  Serial.println("curtain closed");
    digitalWrite(dc_in2,HIGH);
    digitalWrite(dc_in1,LOW);
     delay(500);//rotation time
    digitalWrite(dc_in1,LOW);
    digitalWrite(dc_in2,LOW);
   delay(200);
  motorclose=false;
  }
 }
 //mtrdrm
if(mtrdrm==false)
{motoropen=false;
motorclose=false;
    digitalWrite(dc_in1,LOW);
    digitalWrite(dc_in2,LOW);
}
//PIR code
if(pirdrm==true)
{  int movement=digitalRead(pir);   
   if(movement==1)
  {  digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    Serial.println("there is movement");    
  }
   if(movement==0)
  {  digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
  }
}
  if(pirdrm==false)
  { digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
  }  
delay(1000);
  }