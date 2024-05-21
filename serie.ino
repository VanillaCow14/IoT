#include <WiFi.h>

//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------
const char* ssid     = "";
const char* password = "";

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request

String estadoSalida = "off";

const int salida[] = {2, 4, 21, 22, 23}; // Definir las salidas

//------------------------CODIGO HTML------------------------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset='utf-8' />"
"<title>Servidor Web ESP32</title>"
"<style>"
"body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }"
"h1 { color: #333; }"
".container { max-width: 600px; margin: 0 auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0,0,0,0.1); border-radius: 10px; }"
".button { display: inline-block; padding: 15px 25px; font-size: 24px; margin: 20px; color: #fff; background-color: #007BFF; border: none; border-radius: 5px; cursor: pointer; text-decoration: none; }"
".button:hover { background-color: #0056b3; }"
".button:active { background-color: #004080; }"
"</style>"
"</head>"
"<body>"
"<div class='container'>"
"<h1>Control de Luces ESP32</h1>"
"<p><a href='/on' class='button'>Encender</a></p>"
"<p><a href='/off' class='button'>Apagar</a></p>"
"</div>"
"</body>"
"</html>";

//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");
  
  for (int i = 0; i < 5; i++) {
    pinMode(salida[i], OUTPUT); 
    digitalWrite(salida[i], LOW);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); 
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}

//----------------------------LOOP----------------------------------

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("Nuevo Cliente.");       // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
     
            if (header.indexOf("GET /on") >= 0) {
              Serial.println("Encendiendo GPIOs");
              estadoSalida = "on";
              for (int i = 0; i < 5; i++) {
                digitalWrite(salida[i], HIGH);
                delay(200);  // Retardo para simular una serie de luces
                digitalWrite(salida[i], LOW);
              }
              // Mantener las luces encendidas después de la secuencia
              for (int i = 0; i < 5; i++) {
                digitalWrite(salida[i], HIGH);
              }
            } else if (header.indexOf("GET /off") >= 0) {
              Serial.println("Apagando GPIOs");
              estadoSalida = "off";
              for (int i = 0; i < 5; i++) {
                digitalWrite(salida[i], LOW);
              }
            }
            client.println(pagina);
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
