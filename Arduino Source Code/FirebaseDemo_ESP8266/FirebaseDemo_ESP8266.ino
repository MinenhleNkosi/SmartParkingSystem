//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smartparkingsystemm.firebaseio.com"
#define FIREBASE_AUTH "vCg0LrVdr0k0yM7tQUtoBeDJgvNtv4LVE0XFx3l4"
#define WIFI_SSID "B683-B1C1"
#define WIFI_PASSWORD "4ECF85A6"

void setup() {
  pinMode(D1, OUTPUT);
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("Parking_Lot_Status",0);
}

int n = 0;

void loop() {
  
  // set value
  n = Firebase.getInt("Parking_Lot_Status");
  // handle error
  if (n == 1) {
      Serial.println("Occuppied");
      Serial.println(Firebase.error());  
      return;
      
  }
  else{
    Serial.println("Vacant");
    digitalWrite(D1, LOW);
  }
 
  

}
