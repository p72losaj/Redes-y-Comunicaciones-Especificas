/*******************************************************
* Redes y Comunicaciones Especificas
* Practica 0
* Realizado por Jaime Lorenzo Sanchez
********************************************************/

void setup() {
  Serial.begin(9600); // Inicializamos el serial con un ratio de 9600 bps
  while(!Serial){; } // Necesario para el uso de Serial
}

void loop () {
  // Mostramos los puertos y su valor
  Serial.println("Mostrando los puertos y su valor, del menos significativo al mas significativo");
  for(int i=0; i < 8; i++){
    // Mostramos el numero de puerto
    Serial.print("Puerto: ");
    Serial.print(i);
    byte valor = digitalRead(i); // Cargamos en una variable tipo byte el valor obtenido por la entrada digital
    // Mostramos el valor cargado del puerto en un formato binario
    Serial.print(" -> Valor del puerto: ");
    Serial.println(valor);
    delay(900); // Espera de 900 ms
  }
}
