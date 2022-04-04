/**
 * Redes y Comunicaciones Especificas
 * Practica 2. Conversion A/D mediante Arduino
 * Realizado por Jaime Lorenzo Sanchez
 */

// Vector de muestras
int* muestras; 
// Pin analogico
int pin_analogico = 0;
   
void setup() {
  // Inicializamos el terminal
  Serial.begin(9600); 
  while(!Serial){;}
}


void loop(){
  // Numero de muestras a proporcionar a través del monitor serie
  int lecturas = 0;
  // El número de muestras se debe proporcionar a tráves del monitor serie.
  Serial.print("Introduce el numero de lecturas: ");
  // Esperamos a que el usuario introduzca el numero de muestras
  while(Serial.available() == 0){;}
  lecturas = Serial.readString().toInt(); // La cadena obtenida la transformamos en un entero
  // El numero de lecturas debe ser distinto a 0
  Serial.println(lecturas);
  if(lecturas != 0){
    // Reservamos memoria para el vector de muestras
    muestras = (int*) malloc (sizeof(int)* lecturas);
    // El canal de entrada (puerto analógico) se debe proporcionar a través del monitor serie
    Serial.print("Introduce el canal de entrada (pin analogico): ");
    // Esperamos a que el usuario introduzca el puerto de entrada
    while(Serial.available() == 0){;}
    pin_analogico = Serial.readString().toInt();
    Serial.println(pin_analogico);
    // Leemos el numero de muestras del pin
    for(int i=0; i<lecturas; i++){
      muestras[i] = analogRead(pin_analogico);
    }
    // Imprimimos los resultados obtenidos
    Serial.println("Mostrando los resultados obtenidos");
    for(int i=0; i<lecturas; i++){
      // La senal analogica sera proporcionada por el generador de funciones
      float voltaje = muestras[i] * (5.0 / 1023.0);
      Serial.print(muestras[i]);
      Serial.print(" || ");
      Serial.println(voltaje);
      
    }
    // Liberamos la memoria del vector
    free(muestras);
  }
}

// Resultados obtenidos

/*
 * 
 * Nota 1: Cambiar la frecuencia de la señal periódica y verificar si la conversión A/D te proporciona una correcta 
 * resolución de la señal convertida. Probar con 50Hz, 100 Hz, 500 Hz, 1000 Hz, 1500 Hz, 3000Hz y 5000 Hz. 
 * Analizar los datos y responder a las siguiente pregunta  ¿Qué ocurre en cada uno de estos casos? 
 * Nota 2: Utilizar el mismo número de muestras al tener en cuenta la nota 1. 
 * El número de muestras se debe proporcionar a través del monitor.
 */

 /*
  * Analisis de los datos por Jaime Lorenzo Sanchez
  * 1) Señal senoidal de 5 voltios de amplitud y una fecuencia de 1000 Hz -> Ver las graficas del directorio senoidal
  * 1 hz -> Imagen2
  * 50 Hz -> Imagen4
  * 100 Hz -> Imagen5
  * 1khz -> Imagen1
  * 1500 Hz -> Imagen6
  * 3000 Hz -> Imagen7
  * 5000 Hz -> Imagen8
  * 10 Khz -> Imagen3
  * 2) Realizar el mismo proceso para una señal triangular
  * 1 hz -> Imagen9
  * * 50 Hz -> Imagen10
  * 100 Hz -> Imagen11
  * 1khz -> Imagen12
  * 1500 Hz -> Imagen13
  * 3000 Hz -> Imagen14
  * 5000 Hz -> Imagen15
  * 10 Khz -> Imagen16
  */
