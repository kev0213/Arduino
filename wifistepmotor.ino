#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const char *ssid = "080927wifi";
const char *password = "";
ESP8266WebServer server(80);

String webSite;
/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  
 

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 5, 4,14, 12);
char led_status[50];
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
  webSite += "<p id=\"ledStatus\"></p>";
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
/*-----( Declare Variables )-----*/
int  Steps2Take;
void handleRoot(){
  server.send(200,"text/html",webSite);
}
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  
buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.begin();


}/*--(end setup )---*/

void handleLEDStatus(){ if(server.arg("led") == "red"){
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
  small_stepper.setSpeed(500);   
  small_stepper.step(Steps2Take);
  delay(300);
  }
  else if(server.arg("led") == "green"){   
  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CCW 1 turn  
  small_stepper.setSpeed(500);  // 700 a good max speed??
  small_stepper.step(Steps2Take);
  delay(500);
  }}
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{server.handleClient();
 }
