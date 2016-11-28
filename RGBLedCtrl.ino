#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "080927wifi";
const char *password = "";
ESP8266WebServer server(80);

char led_status[50];
String webSite;

#define LEDR 5
#define LEDG 4
#define LEDB 14

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}
void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title> NodeMCU 網頁測試 </title>";
  webSite += "<style>";
  webSite += "body{background-image:url('https://lh6.googleusercontent.com/Q3hlEtYrpncx4RO0dCGMVJBYRvn--C-LhT3Wot3JSdf5ObpOJWOeYnZKL6OoFlhusH4XbEGbCJ6E1po=w1047-h681-rw'); font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}";
  webSite += "div{width:500px; text-align: center; margin: 50 auto;}";
  webSite += "</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>RGB LED Control form</h1>";
  webSite += "<p id=\"ledStatus\">You can select a RGB LED color ...</p>";
  webSite += "<form action=\"form1\">";
  webSite += "<input type=\"radio\" id=\"red\" name=\"led\" value=\"red\"><label for=\"red\">Color 青</label>";
  webSite += "<input type=\"radio\" id=\"green\" name=\"led\" value=\"green\"><label for=\"green\">Color 紫</label>";
  webSite += "<input type=\"radio\" id=\"blue\" name=\"led\" value=\"blue\"><label for=\"blue\">Color 黃</label><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</div>";
   webSite += "<div>110419008王柏尊</div>";
      webSite += "<div>110419009徐尉秦</div>";
        webSite += "<div>110419027房駿慈</div>";
  webSite += "</body></html>";
}
void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
  if(server.arg("led") == "red"){
     snprintf(led_status,50,"Now, RGB LED color is 青...");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,LOW);
  }
  else if(server.arg("led") == "green"){
     snprintf(led_status,50,"Now, RGB LED color is 紫...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,LOW);
  }
  else if(server.arg("led") == "blue"){
     snprintf(led_status,50,"Now, RGB LED color is 黃...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,HIGH);
  }
server.send (200,"text/html",led_status );
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
  buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

