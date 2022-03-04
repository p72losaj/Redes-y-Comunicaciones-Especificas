/***********
* Redes y Comunicaciones Especificas
* Practica 0
*   1- Cargar en una variable tipo byte, el valor capturado por las entradas digitales 0 al 7, 
*      siendo el puerto de entrada digital 0 el menos significativo y el puerto de entrada 7 el más significativo.
*   2- Pausar entre una carga y otra de la variable tipo byte q se captura.
* Realizado por Jaime Lorenzo Sanchez
********************************************************/

// Pin de entrada -> Leemos la informacion
const int entrada[] = {2,3,4,5,6,7,8,9};
// Pin de salida -> Sacamos la informacion
const int salida[] = {10,11,12,13,A0,A1,A2,A3};
byte valores = 0;
byte contador = 0;

void setup() {
  // Inicializamos el terminal
  Serial.begin(9600);
  // Necesario para el uso de Serial 
  while(!Serial){; } 
  // Inicializamos los pin de entrada y salida
  for(int i=0; i < 8; i++){
    pinMode(entrada[i], INPUT_PULLUP);
    pinMode(salida[i],OUTPUT);
  }
}

void loop () {
  // Aumentamos el contador
  contador++;
  // Escribimos el valor del contador en los pin de salida
  for(int i=0; i<8; i++){
    digitalWrite(salida[i], bitRead(contador,i));
  }
}
// Escribimos los valores de entrada en la variable de entrada
for(int i=0; i<8; i++){
  bitWrite(entrada,i,digitalRead(entrada[i]));
}
// Imprimimos los valores por terminal
for(int i=0; i < 8; i++){
  Serial.println(bitRead(entrada,7-i), BIN);
}
// Realizamos una espera de 1 segundo
delay(1000);
