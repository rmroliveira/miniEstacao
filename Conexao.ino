#include <ESP8266WiFi.h> 

const char* ssid = "cbOliveira"; 
const char* password = "0l1v31r@";
 
WiFiServer server(80); 

void setup() {
  Serial.begin(74880); 
  delay(10);
   
  Serial.println("");
  Serial.println("");
  Serial.print("Conectando a "); 
  Serial.print(ssid);
   
  WiFi.begin(ssid, password); 
   
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print("."); 
  }
  Serial.println(""); 
  Serial.print("Conectado a rede sem fio ");
  Serial.println(ssid); 
  server.begin(); 
  Serial.println("Servidor iniciado"); 
   
  Serial.print("IP para se conectar ao NodeMCU: "); 
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  pinMode(A0, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  
  if (!client) {
    return;
  }
  
  Serial.println("Novo cliente se conectou!");
  
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); 
   
  client.println("HTTP/1.1 200 OK"); 
  
  if (request.indexOf("C") != -1){
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1><center>Ola cliente!</center></h1>");
    
  
    if(analogRead(A0)>500) { //sem chuva
      client.println("<h1><center>Atualmente sem chuva.</center></h1>");
    }
  
    if(analogRead(A0)<=500 && analogRead(A0)>=300){
      client.println("<h1><center>Chuva moderada.</center></h1>");
    }
    
    if(analogRead(A0)<300){//chuva intensa
      client.println("<h1><center>Chuva intensa.</center></h1>");
    }
    client.println("</html>"); 
  }
  delay(1);
  Serial.println("Cliente desconectado"); 
  Serial.println("");
}
