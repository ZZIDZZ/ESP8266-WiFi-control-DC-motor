#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

WiFiServer server(80);

String header;
 
//pins
const int dcmotor1 = 5;
const int dcmotor2 = 4;

int startHour = 4, stopHour = 9;

void setup() {
  Serial.begin(115200);
  pinMode(dcmotor1, OUTPUT);
  pinMode(dcmotor2, OUTPUT);
  digitalWrite(dcmotor1, HIGH);digitalWrite(dcmotor2, HIGH);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("Waiting for new client");

  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int dcmotor1_state = HIGH;
  int dcmotor2_state = HIGH;
  if(request.indexOf("/MOTOR=CW") != -1){
    digitalWrite(dcmotor1, LOW); digitalWrite(dcmotor2, HIGH);// clockwise motor
    dcmotor1_state = LOW;
    dcmotor2_state = HIGH;
  }
  if(request.indexOf("/MOTOR=CCW") != -1){
    digitalWrite(dcmotor1, HIGH); digitalWrite(dcmotor2, LOW); // counterclockwise motor
    dcmotor1_state = HIGH;
    dcmotor2_state = LOW;
  }
  if(request.indexOf("/MOTOR=STOP") != -1){
    digitalWrite(dcmotor1, HIGH); digitalWrite(dcmotor2, HIGH); // stop/idle
    dcmotor1_state = HIGH;
    dcmotor2_state = HIGH;
  }
    
  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width\">");
  client.println("<style>");
  client.println("body{background: white;}");
  client.println(".block {display: block;width: 50%;height: 20%;border: none;background-color: #04AA6D;color: white;padding: 14px 28px;font-size: 16px;cursor:pointer;text-align: center;}");
  client.println(".block:hover {background-color: #ddd;color: black;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.print("<h2> CONTROL MOTOR: ");
  
  if(dcmotor1_state == LOW){
    client.print("CW");
  }
  else if(dcmotor2_state == LOW){
    client.print("CCW");
  }
  else client.print("STOP");
  client.print("</h2>");
  
  client.println("<br><br>");
  
  client.println("<a href=\"/MOTOR=CW\"\"><button class=\"block\">CW</button></a>");
  client.println("<a href=\"/MOTOR=CCW\"\"><button class=\"block\">CCW</button></a>");
  client.println("<a href=\"/MOTOR=STOP\"\"><button class=\"block\">STOP</button></a><br />");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
