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
  * Este analisis se ha realizado mediante un estudio de las imagenes almacenadas en el directorio images.
  * Además, se ha utilizado un intervalo de tiempo entre la obtención de cada muestra en cada frecuencia utilizada de 0 ms
  * Para ver los valores reales obtenidos, ver el archivo graphics.py ( se recomienda usar un bloc de notas, como gedit)
  * 
  * 1) Señal senoidal de 5 voltios de amplitud y una fecuencia de 1000 Hz
  * 
  * -> Señal senoidal con una frecuencia de 1 hz:
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal senoidal con una frecuencia de 50 Hz:
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal senoidal con una frecuencia de 100 Hz:
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal senoidal con una frecuencia de 1000 Hz:
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal senoidal con una frecuencia de 1500 Hz
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal senoidal con una frecuencia de 3000 Hz
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal senoidal con una frecuencia de 5000 Hz
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal senoidal con una frecuencia de 10000 hz
  * Tras la obtención de 20 muestras, se genera una señal senoidal como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * 2) Realizar el mismo proceso para una señal triangular
  * 
  * -> Señal triangular con una frecuencia de 1 hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal triangular con una frecuencia de 50 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal triangular con una frecuencia de 100 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * Sin embargo, no podemos realizar un estudio de la señal con los datos obtenidos. Una posible solución es aumentar el tiempo 
  * entre la obtención de cada muestra ( se realiza mediante la función delay(x), siendo x el tiempo en ms)
  * 
  * -> Señal triangular con una frecuencia de 1000 hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal triangular con una frecuencia de 1500 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal triangular con una frecuencia de 3000 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal triangular con una frecuencia de 5000 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  * 
  * -> Señal triangular conn una frecuencia de 10000 Hz
  * Tras la obtención de 20 muestras, se genera una señal triangular como la mostrada en la imagen correspondiente.
  * En este caso, si podemos realizar un estudio de la señal obtenida. Podemos comprobar tanto la evolución de la señal como su
  * periodicidad, así como observar que la diferencia de amplitud de la señal ( diferencia entre el voltaje obtenido en el punto 
  * máximo global de la señal y el voltaje obtenido en el punto mínimo global de la señal)
  */
