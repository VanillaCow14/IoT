#define foco1 19
#define foco2 21
#define entrada1 0

#include <WiFi.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "esp_system.h"


#include <Adafruit_NeoPixel.h>
#include <OneWire.h>

#define pinLEDWS1812B 21
Adafruit_NeoPixel pixels(1, pinLEDWS1812B, NEO_GRB + NEO_KHZ800);

WiFiServer servidor(80);


uint8_t newMACAddress[] = {0x31, 0xAE, 0xA5, 0x07, 0x0D, 0x66};


#Internetpersonal
char ssid[100]     = "Starchild";
char password[100] = "2FacedLovers";




bool finMensaje = false;
long int tiempoConexionInicio = 0;
String currentLine = "";
long int tiempoComparacion = 0;
int contadorMensaje = 0;
long int t0 = 0, t1 = 0;
bool botonActivado = false;
int contadorBoton = true;
void conectaWiFi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
  WiFi.begin(ssid, password);




  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    Serial.print(".");



  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  //http://sensorMaestro.local
  if (!MDNS.begin("sensorMaestro")) {

  }
  else {
    servidor.begin();
    MDNS.addService("http", "tcp", 80);
  }
}

void funcionInterrupcionBoton(){
  botonActivado = true;
  t0 = millis();
}

void setup() {
  pinMode(foco1, OUTPUT);
  pinMode(foco2, OUTPUT);
  digitalWrite(foco1, LOW);
  digitalWrite(foco2, LOW);

  Serial.begin(115200);
  
 pixels.begin(); 
  conectaWiFi();
  Serial.println("ok");
  pinMode(entrada1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(entrada1), funcionInterrupcionBoton, FALLING);


}

void loop() {
  t1 = millis();
  if(botonActivado && (t1 > (t0+250))){
    botonActivado = false;
    Serial.print("{\"boton\":\"activado\",\"cuenta\":");
    Serial.print(contadorBoton);
    Serial.println("}");
    contadorBoton++;
  }
  WiFiClient clienteServidor = servidor.available();
  finMensaje = false;
  if (clienteServidor) {
    tiempoConexionInicio = xTaskGetTickCount();
    while (clienteServidor.connected()) {
      if (clienteServidor.available() > 0) {
        char c = clienteServidor.read();
        //Espera a que el mensaje JSON finalice
        if (c == '}') {
          finMensaje = true;
        }
        if (c == '\n') {
          if (currentLine.length() == 0) {
            //Inicia la respuesta

          } else {   //Limpiar linea si llega una nueva
            currentLine = "";
          }
        } else if (c != '\r') {  //Si no llega un caracter \r guarda el byte en la linea actual
          currentLine += c;      
        }

        //Se termino de recibir el mensaje
        uint8_t pin = 0;
        uint8_t estado = 0;
        if (finMensaje) {
          String mensajeJSON = currentLine;
          StaticJsonDocument<200> doc;
          DeserializationError error = deserializeJson(doc, mensajeJSON);
          
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            Serial.println(mensajeJSON);
           
          }
          else {
            uint8_t comando = doc["comando"];
            //const char* clave = doc["clave"];
            if(comando > 0){
              Serial.print("Comando: ");
              Serial.print(comando);
            }
            

            if(comando == 1){
              uint8_t pin = doc["pin"];
              uint8_t estado = doc["estado"];
              pinMode(pin, OUTPUT);
              digitalWrite(pin, estado);
              Serial.print(" pin:");
              Serial.print(pin);
              Serial.print(" estado: ");
              Serial.println(estado);
            }
            else if(comando == 2){
              uint8_t pin = doc["pin"];
              uint8_t azul = doc["azul"];
              uint8_t verde = doc["verde"];
              uint8_t rojo = doc["rojo"];  
              Serial.print(" pin:");
              Serial.print(pin);
              Serial.print(" azul: ");
              Serial.print(azul);
              Serial.print(" verde: ");
              Serial.print(azul);
              Serial.print(" rojo: ");
              Serial.println(rojo);
              pixels.clear(); 
              pixels.setPixelColor(0, pixels.Color(rojo, verde, azul));
              pixels.show();            
            }
            else if(comando == 3){
              uint8_t pin = doc["pin"];
              uint8_t pwm = doc["pwm"];    
              pinMode(pin, OUTPUT);
              analogWrite(pin, pwm);  
              Serial.print(" pin:");
              Serial.print(pin);
              Serial.print(" pwm: ");
              Serial.println(pwm);
                       
            }
           
            clienteServidor.println("HTTP/1.1 200 OK");
            clienteServidor.println("Content-type:text/html");
            clienteServidor.println();
            clienteServidor.print("{\"respuesta\":\"ok\",\"numeroMensaje\":\"");
            clienteServidor.print(contadorMensaje);
            clienteServidor.println("\"}");
            clienteServidor.println();
            contadorMensaje++;
            break;
           

         

          }
          
          break;

        }

        //Si el mensaje o conexion toma mas de 3000ms termina el ciclo while
        tiempoComparacion =  xTaskGetTickCount();
        if (tiempoComparacion > (tiempoConexionInicio + 500)) {
          Serial.println("Error timeout");
          break;

        }

      }

    }
    clienteServidor.stop(); //Detener al cliente


  }

}