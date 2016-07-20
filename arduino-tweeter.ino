#include <Twitter.h>
#include <Ethernet.h>
#include <dht.h>
#include "config.h"

#define dht_apin A0

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1, 175);
// char apiKey[] = "123456789-abcdefghijklmnopxyz";
Twitter twitter(apiKey);
dht DHT;

void setup() {
  Serial.begin(9600);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  Serial.println("connecting ...");
    
  DHT.read11(dht_apin); 
  String message = "Temperature is " + String(DHT.temperature,0) + "° " + "Humidity is " + String(DHT.humidity,0) + "%";
  
  char msg[50];
  message.toCharArray(msg,50);
     
    if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop() {
}
