/**
 * Redes y Comunicaciones Especificas
 * Practica 2. Conversion A/D mediante Arduino
 * Realizado por Jaime Lorenzo Sanchez
 */
 
 /*
  * Crear un unico programa que permita realizar las siguientes tareas  
  * 1. El canal de entrada (puerto analógico) y el número de muestras se debe proporcionar a tráves del monitor serie.
  * 2. Conversion A/D de senal analogica: la señal analógica será proporcionada por el generador de funciones 
  * (señal senoidal de 5 voltios de amplitud y una fecuencia de 1000 Hz)
  * 3. Guardar los datos convertidos en un vector de un tamaño que puede ser variable valores/muestras 
  * (el número de muestras se debe pedir).
  * 4. Realizar el mismo proceso para una señal triangular, y comentar los resultados en el fichero -ino que 
  * se debe engregar mediante líneas de comentario.
  */

int opcion; // Opcion del menu
int puerto;
   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Inicializamos el serial con un ratio de 9600 bps
  while(!Serial){;} // Necesario para el uso de Serial
  
}

void loop() {
  // put your main code here, to run repeatedly:
  menu();
  while(opcion<49 || opcion > 51){
    if(Serial.available()){
      opcion = Serial.read();
    }  
  }
  switch(opcion){
    case '1':
      Serial.print("Selecciona puerto: ");
      while(puerto<48 || puerto>57){
          if(Serial.available() > 0){puerto = Serial.read();}  
  }
    break;
  }
}

void menu(){
  Serial.print("\n");
  Serial.println("(1) Obtener el canal de entrada");
  Serial.print("Introduce una opcion: ");
}

  /*
   * Nota 1: Cambiar la frecuencia de la señal periódica y verificar si la conversión A/D te proporciona una correcta 
   * resolución de la señal convertida. Probar con 50Hz, 100 Hz, 500 Hz, 1000 Hz, 1500 Hz, 3000Hz y 5000 Hz. 
   * Analizar los datos y responder a las siguiente pregunta  ¿Qué ocurre en cada uno de estos casos? 
   * "Indicarlo en el fichero .ino que se entraga mediante líneas comentadas"
   * Nota 2: Utilizar el mismo número de muestras al tener en cuenta la nota 1. 
   * El número de muestras se debe proporcionar a través del monitor.
   */
