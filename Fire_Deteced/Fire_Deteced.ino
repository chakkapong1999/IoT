
#include <TridentTD_LineNotify.h>
#define buzzer 33 // Use buzzer for alert 
#define FlamePin 34// This is for input pin D0
#define Green_LED 27
#define Red_LED 26
#define SSID        "MAX"
#define PASSWORD    "55555555"
#define LINE_TOKEN  "nbURs0Y5Z8Rpc7eeagrHVVYmmmlKtNKEdPOQQi02SPF"
#define LINE_TOKEN1  "y4enCjxqxVNu76jfDJG3pFKkFRhAlf75hrfpLMppC6g"
int Flame;
int count = 0;
boolean state = false;

void setup() {
  // put your setup code here, to run once:
     pinMode(buzzer, OUTPUT);
     pinMode(FlamePin, INPUT);
     pinMode(Green_LED, OUTPUT);
     pinMode(Red_LED, OUTPUT);
     Serial.begin(115200);
     WiFi.begin(SSID, PASSWORD);
    Serial.printf("WiFi connecting to %s\n",  SSID);
    while(WiFi.status() != WL_CONNECTED) 
      { 
        Serial.println("Connected"); 
        delay(400); 
      }
    Serial.printf("\nWiFi connected\nIP : ");
    Serial.println(WiFi.localIP());
    LINE.setToken(LINE_TOKEN);
    LINE.notify("System Start Ready/ขอขอบคุณที่ใช้บริการเรา");
    LINE.setToken(LINE_TOKEN1);
    LINE.notify("System Start Ready/ขอขอบคุณที่ใช้บริการเรา");   

}

void loop() {
  // put your main code here, to run repeatedly:
    Flame = digitalRead(FlamePin);
 if (Flame== LOW)
  { 
    Serial.println("Fire In the House!");
    digitalWrite(Green_LED, LOW);
   
    for(int i = 10;i>0;--i){
      delay(500);
      digitalWrite(buzzer, HIGH);
      digitalWrite(Red_LED, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      digitalWrite(Red_LED, LOW);
    }
    LINE.setToken(LINE_TOKEN);
    LINE.notify("ไฟไหม้จุด 1 ");
    LINE.notify("state : อพยพไปยังทางหนีไฟที่ใกล้ที่สุด ");   
    LINE.notifySticker(4,274);
    
    
    LINE.setToken(LINE_TOKEN1);
    LINE.notify("ไฟไหม้จุด 1 ");
    LINE.notify("state : อพยพไปยังทางหนีไฟที่ใกล้ที่สุด ");   
    LINE.notifySticker(4,274);
  }
 else
 {
    Serial.println("No flame");
    digitalWrite(buzzer, LOW);
    digitalWrite(Green_LED, HIGH);
    digitalWrite(Red_LED, LOW);    
  }
}
