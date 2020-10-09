/*
 * program pengembangan mobile robot untuk monitoring kondisi lingkungan 
 * development by Made Agus Andi Gunawan(IDNmakerspace Algorithm Factory)s
 * last edited : 25 Sept 2020
 */

//Daftar library
#include<Servo.h>
#include <LiquidCrystal_I2C.h>

//Daftar penggunaan pin pada arduino
#define pinservo 9
#define pinled 8
#define trigpin 3
#define echopin 2
#define sensor1 A0
#define pinrelay 7

//Pemanggilan fungsi dari library
Servo servoku;
LiquidCrystal_I2C lcd(0x27, 16, 2);

//variabel global yang kana digunakan dalam fungsi
int sudut = 0; 
char t;
 
void setup() 
{
  //untuk memberikan fungsi pada pin 
  pinMode(13,OUTPUT);   //kiri motors maju
  pinMode(12,OUTPUT);   //kiri motor balik
  pinMode(11,OUTPUT);   //Kanan motor maju
  pinMode(10,OUTPUT);   //kanan motor balik
  pinMode(pinled,OUTPUT);   //led indikator
  pinMode(trigpin, OUTPUT);  //pin trigger sebagai transmitter
  pinMode(echopin, INPUT);   //pin echo sebagai receiver
  pinMode(sensor1, INPUT);   //pin untuk touch sensor
  pinMode(pinrelay, OUTPUT);  //pin relay untuk on/off  
  servoku.attach(pinservo);  //pin servo

  //baudrate
  Serial.begin(9600);

  //lcd inisialisasi
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("pengujian");
  lcd.setCursor(0, 1);
  lcd.print("ROBOT MOBILE");
  delay(1000);
  lcd.clear();
}
 
void loop() 
{
  //blok fungsi untuk menggerakan servo kekanan dan kekiri dengan sudut 0 - 100 derajat
  for (sudut = 0; sudut <= 180; sudut += 1) 
  { 
    servoku.write(sudut);              
    delay(15);                       
  }
  for (sudut = 180; sudut >= 0; sudut -= 1)
  { 
    servoku.write(sudut);              
    delay(15);
  }
  
  if(Serial.available())
  {
    t = Serial.read();
    Serial.print("hasil : ");
    Serial.println(t);
  }
   
  if(t == 'F'){            //bergerka maju
    digitalWrite(13,HIGH);
    digitalWrite(11,HIGH);
  }
   
  else if(t == 'B'){      //bergerak mundur
    digitalWrite(12,HIGH);
    digitalWrite(10,HIGH);
  }
   
  else if(t == 'L'){      //belok kanan
    digitalWrite(11,HIGH);
  }
   
  else if(t == 'R'){      //belok kiri
    digitalWrite(13,HIGH);
  }
  
  else if(t == 'W'){    //menghidupkan led on dan off
    digitalWrite(9,HIGH);
  }
  else if(t == 'w'){
    digitalWrite(9,LOW);
  }
   
  else if(t == 'S'){      //berhenti
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  }
  delay(100);
}
