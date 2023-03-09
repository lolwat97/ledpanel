#include <Arduino.h>
#include <WiFi.h>

#include <Clip.h>
#include <HTTP_text.h>
#include <WiFi_settings.h>

// LED indicator pin
#define LED 4

// No. of clips in memory
// Clip is one screen with info/gif/image etc. with specified length, can be enabled or disabled
#define CLIP_COUNT 4
Clip* clips[CLIP_COUNT];

// Define these in WiFi_settings.h
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Webserver on HTTP port
WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  Serial.println("Booted, connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
  };
  Serial.println("Connected!");
  digitalWrite(LED, LOW);

  server.begin();
}

// Function to process the request. Gets full request text, returns whatever needs to be returned to the webserver client
String respond(String request){
  if(request.indexOf("GET /fuck ") >= 0)
    return header_ok + "fuck!";
  else if(request.indexOf("GET / ") >= 0)
    return header_ok + page_ok;
  else
    return header_404 + page_404;
  
  // TODO: Add code to switch active status of the clips
  // TODO: Change clip type
  // TODO: Change clip length
}

void loop() {
  // Do we have a client on the webserver?
  WiFiClient client = server.available();
  if(client){
    // Don't know what this is, but seems important
    while(!client.available())
      delay(1);
    Serial.println("New client!");
    
    // Get full request and pass it on to processing function
    String request = client.readStringUntil('\r');
    Serial.print("Request is: ");
    Serial.println(request);
    String response = respond(request);

    // Return the response to client
    client.print(response);
    Serial.println("Sent response to client");
    Serial.println("");
  }
  // TODO: Add code to monitor clip time and switch active clips
}