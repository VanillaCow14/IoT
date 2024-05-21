#include <WiFi.h>

//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------

const char* ssid     = "INFINITUM559C";
const char* password = "Enterasys2024";

//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request

String estadoSalida = "off";

const int salida = 14;

//------------------------CODIGO HTML------------------------------
String pagina = R"====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hogar inteligente </title>
    <style>
        /* Estilos CSS */
        .navbar {
            width: 100%;
            height: 80px;
            background-color: #003366;
            display: flex;
            justify-content: flex-end;
            align-items: center;
            color: #003366;
        }

        .navbar h1 {
            margin: auto;
            color: rgb(234, 209, 16);
        }

        .botones {
            text-align: center;
            margin-top: 20px; /* Añadido margen superior para separar de la barra de navegación */
        }

        .button-on, .button-off {
            height: 50px;
            width: 100px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            margin: 10px;
        }

        .button-on {
            background-color: green;
            color: white;
        }

        .button-off {
            background-color: red;
            color: white;
        }
    </style>
</head>
<body>
    <div class="navbar">
        <h1>Encendido de LEDS</h1>
    </div>

    <div class="botones">
        <h1>Selecciona una opción para los LEDS</h1>
        <a href='/on'><input class="button-on" id="button-on" onclick="botonEncender()" value="Encendido"/></a>
        <a href='/off'><input class="button-off" id="button-off" onclick="botonApagar()" value="Apagado"/></a>
    </div>

    <script>
        function botonEncender(){
            console.log("Encender LED");
            consultarGET("encender");
        }
        function botonApagar(){
            console.log("Apagar LED");
            consultarGET("apagar");
        }

        function consultarGET(consulta){
            const Http = new XMLHttpRequest();
            console.log('Consulta ${consulta}');
            Http.open("Get",consulta);
            Http.send();

            Http.onreadystatechange = (e) => {
                console.log(Http.status);
                console.log(Http.response);
            }
        }
        const elementoApagar = document.getElementById("botonApagar")
        elementoApagar.addEventListener("click", botonApagar)
    </script>
</body>
</html>
)====";



//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");
  
  pinMode(salida, OUTPUT); 
  digitalWrite(salida, LOW);

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
    Serial.println("New Client.");          // 
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
              Serial.println("GPIO on");
              estadoSalida = "on";
              digitalWrite(salida, HIGH);
            } else if (header.indexOf("GET /off") >= 0) {
              Serial.println("GPIO off");
              estadoSalida = "off";
              digitalWrite(salida, LOW);
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
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}