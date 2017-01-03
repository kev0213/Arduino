
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include<Wire.h>
#include<SPI.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#define OLED_CS    4 //CS~d1
#define OLED_DC    0 //DC~d2
#define OLED_RESET 2 //RES~d3
#define OLED_MOSI   14 //D1~d4
#define OLED_CLK   12 //D0~d5 
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define LEDR 13
#define LEDF 15
#define LEDL 5
const char *ssid = "jswan300";
const char *password = "0920630403";
char meal_status[50];
String webSite;
long randNumber;
WiFiClient client;
ESP8266WebServer server(80);

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDF, LOW);
  digitalWrite(LEDL, LOW);
}
void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title>hellow food</title>";
  webSite += "<style>";
  webSite += "body{background-image:url(http://i.imgur.com/o8FKbmE.jpg); backgroud-size:100%;background-position:center; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;  font-size:5vw;}";
  webSite += "div{width:100vw; text-align: center; margin: 50 auto;}h1{ font-size:10vw; text-shadow:3px 3px #777777;}.btn{width:5vw;height:5vw;} ";
  webSite += "input{text-align:left  padding-left:20vw;}.sub{width:80vw;height:10vw;font-size:5vw;}</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>今天要吃什麼嘞</h1>";
  webSite += "<p id=\"ledStatus\">交給老天爺決定ㄅ </p>";
  webSite += "<form action=\"form1\">";
  webSite += "<input type=\"radio\" id=\"red\" class=\"btn\" name=\"led\" value=\"all\"><label for=\"all\">有什麼吃甚麼</label><br>";
  webSite += "<input type=\"radio\" id=\"red\" class=\"btn\" name=\"led\" value=\"red\"><label for=\"red\">吃麵食</label><br>";
  webSite += "<input type=\"radio\" id=\"green\" class=\"btn\" name=\"led\" value=\"green\"><label for=\"green\">今天吃飯</label><br>";
  webSite += "<input type=\"radio\" id=\"blue\" class=\"btn\" name=\"led\" value=\"blue\"><label for=\"blue\">不吃麵也不吃飯~</label><br><br>";
  webSite += "<input type=\"submit\" class=\"sub\" value=\"submit\"></form>";
  webSite += "</div>";
webSite += "<div>";
webSite += "<p > 麵: <br>饌中華 發現 阿姨的店 刀口力 </p>";
webSite += "<p > 飯: <br>金葉 笑嘻嘻 豚太郎</p>";
webSite += "<p > 其他:<br>八方雲集 紫牛 光和果汁 好食</p>";
webSite += "</div>";
  webSite += "</body></html>";
}
void handleRoot(){
  server.send(200,"text/html",webSite);
}
void meal(int randNumber){
     display.clearDisplay();
     display.setTextColor(WHITE);  
     display.setTextSize(1);
     display.setCursor(10,0);  
     display.print(" ~");
     switch(randNumber){
case 1:display.print("zhuan zhong hua");break;
case 2:display.print("Discover");break;
case 3:display.print("auntie's shop");break;
case 4:display.print("jin ye");break;
case 5:display.print("xiao xi xi");break;
case 6:display.print("Tontaro");break;
case 7:display.print("xian wei feng");break;
case 8:display.print("zi niu");break;
case 9:display.print("Sunshine Juice");;break;
default:break;}
     display.print("~ ");
     display.setCursor(40,10);
     switch(randNumber){
case 1:display.print("noodle");break;
case 2:display.print("Spaghetti");break;
case 3:display.print("EVERYTHING");break;
case 4:display.print("siu mei");break;
case 5:display.print("fried rice");break;
case 6:display.print("Donburi");break;
case 7:display.print("Biscuits");break;
case 8:display.print("Steak");break;
case 9:display.print("breakfast");break;
default:break;}
     display.setCursor(30,20);
     switch(randNumber) {
case 1:display.print("Chinese");break;
case 2:display.print("Italian");break;             
case 3:display.print("Diversity");break;
case 4:display.print("hongkong");break;
case 5:display.print("hongkong");break;
case 6:display.print("Japanese");break;
case 7:display.print("Chinese"); break;
case 8:display.print("Western");break;
case 9:display.print("Western");;break;
default:break;}
display.display();
}
void light(int randNumber){
     Serial.print("  Num  ");
     Serial.print(randNumber);
     switch(randNumber%3) {
case 0: Serial.print(" right  ");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDF,LOW);
    digitalWrite(LEDL,LOW);
    break;
case 1:Serial.print(" front  ");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDF,HIGH);
    digitalWrite(LEDL,LOW);
    break;
case 2:Serial.print(" left  ");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDF,LOW);
    digitalWrite(LEDL,HIGH);
    break;
}
  }
void handleLEDStatus(){
  Serial.print("handleLEDStatus");
      if(server.arg("led") == "red"){
          snprintf(meal_status,50,"HERE COMES YOUR ORDER!");
          randNumber = random(1, 4); 
      }
      else if(server.arg("led") == "green"){
           snprintf(meal_status,50,"HERE COMES YOUR ORDER!");
           randNumber = random(4, 7); 
      }
      else if(server.arg("led") == "blue"){
           snprintf(meal_status,50,"HERE COMES YOUR ORDER!");
           randNumber = random(7, 10);
      }
      else{
         snprintf(meal_status,50,"HERE COMES YOUR ORDER!");
           randNumber = random(1, 10);
        }
  Serial.print("  Num  ");
  Serial.print(randNumber);
  meal(randNumber); 
  light(randNumber);
  server.send (200,"text/html",meal_status );
}
void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}
void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDF, OUTPUT);
  pinMode(LEDL, OUTPUT);
  turnoff();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Serial.begin(115200);
  buildWeb();
  WiFi.begin(ssid, password); 
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println(WiFi.localIP());
  display.clearDisplay();
  display.setTextColor(WHITE);  
  display.setTextSize(1);
  display.setCursor(40,10);
  display.print("connect~");
  display.setCursor(40,20);
  display.print(WiFi.localIP());
  display.display();
}
void loop() {
  randomSeed(analogRead(1)); 
  server.handleClient();  
}
