
#include <Servo.h>
Servo servoku;


int lock = 0;
int panel_naik = 1;
int panel_turun =1;
int panel_panggil = 1;
//untuk ultrasonic 1 (kapasitas)
int trig1 = 11;
int echo1 = 12;
//untuk ultrasonic 2 (jarak user)
int trig2 = 7;
int echo2 = 8;

int servo = 9;

float durasi1, jarak1;
float durasi2, jarak2;
int led_merah= 2, led_hijau=3;
int jarakuser=30, jaraksampah=15;

void setup()
{

  servoku.attach(servo);
  //pinKode ultrasonic sensor
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(led_merah,OUTPUT);
  pinMode(led_hijau,OUTPUT);

  Serial.begin(9600);
}

void loop()
{

  //hitung ultrasonic 2 jarak sampah
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  delayMicroseconds(10);
  durasi2 = pulseIn(echo2, HIGH);
  jarak2 = (durasi2 * 0.034) / 2;

  //hitung ultrssonic 1 kapasitas 
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  delayMicroseconds(10);
  durasi1 = pulseIn(echo1, HIGH);
  jarak1 = (durasi1 * 0.034) / 2;
   
  //kendali tutup
  if ((jarak1 < jaraksampah) && (panel_panggil == 1))
    {
      Serial.println("Memanggil Truk Sampah");
      Serial.println(jarak1); 
      panel_panggil = 0;
      lock = 1;
    
    }
  else if ((jarak1 >= jaraksampah)&&(panel_panggil == 0 ) )
  {
    
    //buka pintu tempat sampah
    panel_panggil = 1;
    lock = 0;
  }

   if ((jarak2 <= jarakuser) &&(panel_naik == 1)&&(lock == 0))
    {
  
      Serial.println("Tempat sampah membuka"); 
      Serial.println(jarak1); 
     servoku.write(0);
     delay (500);
        panel_naik = 0;
        panel_turun = 1;
    }
    //tutup pintu
    else if ((panel_turun == 1)&& (jarak2 > jarakuser))
    {
      delay(1000);
      Serial.println("Tempat sampah menutup");
      Serial.println(jarak2); 
      servoku.write(90);
      delay (500);
      panel_naik = 1;
      panel_turun = 0;
    }
  
  //pengendalian lampu
  if (jarak1<jaraksampah)
  {
      digitalWrite(led_merah,HIGH);
  }else
  {
      digitalWrite(led_merah,LOW);
  }
  
  if (jarak2<=jarakuser)
  {
      digitalWrite(led_hijau,HIGH);
  }else
  {
      digitalWrite(led_hijau,LOW);
  }
  
}
