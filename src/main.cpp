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
//Clip clips[CLIP_COUNT] = {Clip(clip_text, 1000, true), Clip(clip_image, 1000, true), Clip(clip_gif, 1000, true), Clip(clip_text, 1000, false)};
Clip clips[CLIP_COUNT] = {Clip(clip_text, 1000, false), Clip(clip_image, 1000, false), Clip(clip_gif, 1000, false), Clip(clip_text, 1000, false)};
ushort current_clip = 0;

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
  Serial.print("Connected, my IP is ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED, LOW);

  server.begin();
}

// Function to process the request. Gets full request text, returns whatever needs to be returned to the webserver client
String respond(String request){
  // Strip the HTTP from the end of the string
  if(request.indexOf("HTTP/1.1") != -1)
    request.replace(" HTTP/1.1",""); // TODO: This is bad, make this respect other HTTP versions!

  // If the request is GET
  if(request.indexOf("GET ") != -1){
    // Strip the GET
    request.replace("GET ", "");

    // Debug stuff
    Serial.print("Stripped request is: ");
    Serial.println(request);

    // Activate a clip
    if(request.indexOf("/activate/") == 0){
      request.replace("/activate/", "");
      int clip_number = request.toInt();
      if(clip_number >= 0 && clip_number < CLIP_COUNT){
        Serial.printf("Activating clip %d\n", clip_number);
        clips[clip_number].is_active = true;
        return header_ok + "Clip " + String(clip_number) + " is now active!";
      } 
      Serial.printf("Invalid clip number %d\n", clip_number);
      return header_404 + "Invalid clip number.";
    }

    // Deactivate a clip
    if(request.indexOf("/deactivate/") == 0){
      request.replace("/deactivate/", "");
      int clip_number = request.toInt();
      if(clip_number >= 0 && clip_number < CLIP_COUNT){
        Serial.printf("Deactivating clip %d\n", clip_number);
        clips[clip_number].is_active = false;
        return header_ok + "Clip " + String(clip_number) + " is now not active!";
      } 
      Serial.printf("Invalid clip number %d\n", clip_number);
      return header_404 + "Invalid clip number.";
    }

    return header_404 + page_404;
  } 

  // We don't support non-GET yet, just throw an internal server error, fuck it
  return header_503 + page_503;
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

  // TODO: Add code to monitor clip time and switch active clips so this is async

  if(clips[current_clip].is_active){
    Serial.printf("Showing clip %d: \n", current_clip);
    clips[current_clip].show();
  }
  current_clip = (current_clip+1)%CLIP_COUNT;
}