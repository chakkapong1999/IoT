#include <WiFi.h>
#include <HTTPClient.h>

/////////////////////////////////////////EDIT HERE//////////////////////////////////////////////////
const char* ssid = "MAX";                                                              //  
const char* password = "55555555";                                                      //
                                                                                                  //
const char* jsonString = "{\"Test heroku\":\"CPE - 496\"}";//YOUR_JSON_DATA                                 //
const String topic = "\"topic\"";

String serverName = "https://iot496.herokuapp.com/data/write";//YOUR_SERVER  //        
////////////////////////////////////////////////////////////////////////////////////////////////////

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  HttpPost(jsonString);
}

void loop(){
  
}

void HttpPost(String jsondata){
  HTTPClient http;
  const String packedData = "{\"topic\": " + topic + ", \"data\": " + jsondata + "}";
  Serial.println(packedData);
  http.begin(serverName.c_str());
  
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.POST(packedData.c_str());

  Serial.print("HHTP Response code: ");
  Serial.println(httpResponseCode);
  
  if(httpResponseCode == 200){
    Serial.println("Sucessful");
    http.GET();
    String payload = http.getString();
    Serial.println(payload);
  }
  else{
    Serial.println("Error");
  }
  

  http.end();
}
