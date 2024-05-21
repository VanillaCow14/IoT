# IoT
Proyecto parte de la materia programacion para internet. 

# Introduccion.
Para comenzar con este proyecto se tuvieron que conseguir distintas cosas por ejemplo conocimiento en Arduino y distintas placas para poder trabajar con ellas como lo son la placa ESP32 y Arduino Uno.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/d281e170-d83f-421f-be60-413116b3ca2d)

El código se divide en tres partes la primera es la declaración del led el cual se usara en el pin numero 7 de nuestro Arduino, la siguiente parte es el Setup en el cual le indicamos a la placa que el modo del pin va a ser de salida y en este caso el pin usado es el ya mencionado pin 7, por ultimo tenemos el loop en el cual configuramos lo que se va a hacer le indicamos que estará prendido 3000 milisegundos con las líneas 10 y 11 y le indicamos que se apagara 1000 milisegundos con  la línea 12 y 13 esto significa que estará en una intermitencia con un intervalo de 3 segundos prendido y 1 segundo apagado.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/684273c3-3c8c-4a19-9e9b-e92de8a991b0)

Aquí vemos el circuito prendido con nuestro led emitiendo luz.


Por su similitud de la placa de ESP32 y de Arduino Uno, nos permite usar el mismo codigo para que prenda la placa del ESP32 solo cambiando el pin con el que se va a ejecutar la prueba

![image](https://github.com/VanillaCow14/IoT/assets/142856302/2c026d71-9300-4bae-b274-96f5197f4072)

Este codigo es que encontramos en el propio repositorio puesto que es con el que se ejecuto la prueba para poder prender el led y corrrobar que la placa estaba funcionando. 

![image](https://github.com/VanillaCow14/IoT/assets/142856302/b09b0f44-366a-467c-882d-aaf2a096a1ba)

Aqui vemos que en efecto el led emite luz con este codigo. 

# Procedimiento de Arduino a IoT. 
Para poder generar el cambio de un simple arduino a IoT se requiere de una interfaz en este caso se busca usar una pagina web esta pagina web se debe de cargar de cierta forma al arduino ya que ahi mismo es donde se almacena la pagina en este caso se tiene algo muy peculiar y es que se puede traspolar a algo mas grande que mas adelante mostraremos.

Para empezar con el archivo .ino
Vemos que se tiene decclaradas varias cosas la mas importande de todas estas la libreria WiFi.h y las credenciales del internet que se este usando. 

![image](https://github.com/VanillaCow14/IoT/assets/142856302/91b10c52-981a-41be-bf4b-3cad709f5aa1)

Acto seguido se continua con la configuracion de la pagina web la cual se tiene escrita completamente aqui. 

![Captura de pantalla 2024-05-20 192327](https://github.com/VanillaCow14/IoT/assets/142856302/4c39359c-f088-4c19-8ebf-0f084849e44b)
![Captura de pantalla 2024-05-20 192346](https://github.com/VanillaCow14/IoT/assets/142856302/8a657f25-fff1-4c35-9c1a-7a98fd435c2f)
![Captura de pantalla 2024-05-20 192357](https://github.com/VanillaCow14/IoT/assets/142856302/0bbe90e3-a0e3-4e79-97e6-de91d8df3586)

Despues seguiria la configuracion de de nuestros pines y lo que se busca conseguir con ellos. 

![Captura de pantalla 2024-05-20 192412](https://github.com/VanillaCow14/IoT/assets/142856302/b2a9c1b0-8272-4f72-b043-6a7e4113c169)

Por ultimo encontramos con el ciclo que seguira nuestro led mientras esta conectado. 

![Captura de pantalla 2024-05-20 192438](https://github.com/VanillaCow14/IoT/assets/142856302/9dd4b292-3fff-40c8-90ef-132fd672f8bc)


Con el archivo IoT.ino es que se controla la placa y que tenemos la web creada.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/e12775cf-11e3-4aa9-adf6-73337a255890)


Como se puede ver se tiene el boton de encendido y de apagado que en efecto prende y apaga el propio led esto gracias al servidor con la ip que monta la propia placa. 

![image](https://github.com/VanillaCow14/IoT/assets/142856302/c60027f8-8b24-4512-8f2a-61e7888199dd)

Sin embargo y como se comentaba anteriormente esta idea se puede escalar a un sistema entero esto teniendo los modulos y los equipamientos necesarios para hacer un ecosistema de hogar inteligente como se mostrara en seguida.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/2469eb7a-0232-4fa7-b4ef-4c159dac8d6c)

Como podemos ver tenemos multiples opciones que se tienen como lo son recomendaciones, los dispositivos que se tienen adquiridos y un inicio de sesion.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/cf8b0dbe-4ce3-4a8e-9200-2c2e7e78c753)

Con los dispositivos se tiene que se pueden tener esta variedad de dispositivos.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/a9dace42-59a7-4030-96ab-d9513e40fd5e)

Se pueden apreciar las distintas recomendaciones que se le da al usuario.

![image](https://github.com/VanillaCow14/IoT/assets/142856302/6c43bc59-066c-46a0-a896-6b56378bae4f)

Y si actualmente se necesitara podria controlar ya nuestro led.















