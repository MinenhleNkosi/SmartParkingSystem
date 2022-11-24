#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "smartparkingsystem-6187e.firebaseio.com"  //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "CgaD6CuLKTMA9NNVDqdHVaDMWYy7RLn7yfpwczjl"   //Your Firebase Database Secret goes here

#define WIFI_SSID "B683-B1C1"                  //your WiFi SSID(Hotspot Name) for which your NodeMCU connects 
#define WIFI_PASSWORD "4ECF85A6"           //Password of your wifi network 

#define trigPin1 16   //D0 (We Used GPIO Pin Number)
#define echoPin1 5    //D1
#define trigPin2 4    //D2
#define echoPin2 0    //D3
#define trigPin3 2    //D4
#define echoPin3 14   //D5
 
void setup() 
{
  Serial.begin(9600);            // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() 
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }
  
  //Ultrasonic Sensor 1

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  long inch1 = duration1 / 74 / 2;         // In Inch
  
  if(inch1 < 5)
  {
    Firebase.setInt("P1 = occuppied",1);
    Serial.println("P1 is occuppied");
  }
  else
  {
     Firebase.setInt("P1 = vacant",0);
     Serial.println("P1 = vacant");
  }
  
  //Ultrasonic Sensor 2

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  long inch2 = duration2 / 74 / 2;         // In Inch

  if(inch2 < 5)
  {
    Firebase.setInt("P2 = occuppied",1);
    Serial.println("P2 = occuppied");
  }
  else
  {
     Firebase.setInt("P1 = vacant",0);
     Serial.println("P1 = vacant");
  }
  
  //Ultrasonic Sensor 3

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  long duration3 = pulseIn(echoPin3, HIGH);
  long inch3 = duration3 / 74 / 2;         // In Inch

  if(inch3 < 5)
  {
    Firebase.setInt("P3 = occuppied",1);
    Serial.println("P3 = occuppied");
  }
  else
  {
     Firebase.setInt("P1 = vacant",0);
     Serial.println("P1 = vacant");
  }
  delay(5000);
}
