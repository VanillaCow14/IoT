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
Para poder generar el cambio de un simple arduino a IoT se requiere de una interfaz en este caso se busca usar una pagina web esta pagina web se debe de cargar de cierta forma al arduino ya que ahi mismo es donde se almacena la web.

# Interfaz. 





