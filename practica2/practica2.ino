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

/*
   * Nota 1: Cambiar la frecuencia de la señal periódica y verificar si la conversión A/D te proporciona una correcta 
   * resolución de la señal convertida. Probar con 50Hz, 100 Hz, 500 Hz, 1000 Hz, 1500 Hz, 3000Hz y 5000 Hz. 
   * Analizar los datos y responder a las siguiente pregunta  ¿Qué ocurre en cada uno de estos casos? 
   * "Indicarlo en el fichero .ino que se entraga mediante líneas comentadas"
   * Nota 2: Utilizar el mismo número de muestras al tener en cuenta la nota 1. 
   * El número de muestras se debe proporcionar a través del monitor.
   */

int* muestras; // Vector de muestras
const int pinEntrada = A0; 
int nLecturas = 0;
   
void setup() {
  // Inicializamos el terminal
  Serial.begin(9600); 
  // Inicialiamos el pin de entrada
  pinMode(pinEntrada,INPUT);
}

void loop() {
  // Leemos el numero de lecturas
  Serial.println("Introduce el numero de lecturas: ");
  nLecturas = Serial.readString().toInt(); // La cadena obtenida la transformamos en un entero
  if(nLecturas != 0){
    // Realizamos una reserva de memoria del vector de muestras
    muestras = (int*) malloc (sizeof(int)* nLecturas);
    // Lectura del pin de entrada
    for(int i=0; i<nLecturas; i++){
      muestras[i] = analogRead(pinEntrada);
    }
    // Imprimimos los resultados obtenidos
    for(int i=0; i< nLecturas; i++){
      Serial.println(muestras[i]);
    }
    // Liberamos la memoria del vector de muestras
    free(muestras);
  }
}

// Resultados obtenidos
