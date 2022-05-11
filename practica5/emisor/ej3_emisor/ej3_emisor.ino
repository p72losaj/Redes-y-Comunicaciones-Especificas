/**
 * REDES Y COMUNICACIONES ESPECIFICAS
 * Autor: Jaime Lorenzo Sanchez
 */
// Variables globales
int* vector; // vector de muestras
int lecturas; // Numero de lecturas

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {;}
  Serial.println("SOY EL EMISOR");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Mostramos un menu de funciones
  menu();
  // Esperamos a que el usuario seleccione una opcion
  while(Serial.available() == 0){;}
  int opcion = Serial.parseInt();
  // Mostramos la opcion elegida
  Serial.println(opcion);
  // Hacemos una nueva captura
  if(opcion == 1){
    Serial.print("Introduce el numero de lecturas: ");
    // Esperamos a que el usuario introduzca el numero de lecturas
    while(Serial.available() == 0){;}
    // Obtenemos el numero de lecturas
    lecturas = Serial.parseInt();
    // Mostramos el numero de lecturas
    Serial.println(lecturas);
    // Reservamos la memoria del vector
    vector = (int*) malloc (sizeof(int)* lecturas);
    // El usuario introduce los datos a traves del canal Serial
    for(int i=0; i < lecturas; i++){
      Serial.print("Introduce un valor: ");
      // Esperamos a que el usuario introduzca un valor
      while(Serial.available() == 0){;}
      // Leemos el valor introducido por el usuario y lo guardamos en el vector
      vector[i] = Serial.parseInt();
    }
    // inicializamos el valor maximo,minimo y el sumatorio de las lecturas obtenidas
    int maximo = vector[0]; 
    int minimo = vector[0]; 
    float suma = 0;
    for(int i=0; i<lecturas; i++){
      // Obtenemos el valor maximo
      maximo = max(vector[i],maximo);
      // Obtenemos el valor minimo
      minimo = min(vector[i],minimo);
      // Obtenemos el sumatorio de las lecturas obtenidas
      suma = suma + vector[i];
    }
    // Obtenemos la media de las lecturas obtenidas
    float media = suma / lecturas;
    // Avisamos al receptor del comienzo de envio de los datos
    Serial1.print("z");
    // Mostramos el valor maximo
    Serial.print("Maximo: ");
    Serial.println(maximo);
    // Enviamos el valor maximo al receptor
    Serial1.print(maximo); 
    // Mostramos el valor minimo
    Serial.print("Minimo: ");
    Serial.println(minimo);
    // Enviamos el valor minimo al receptor
    Serial1.print(minimo);
    // Mostramos la media
    Serial.print("Media: ");
    Serial.println(media);
    // Enviamos la media al receptor
    Serial1.print(media);
    // El fin de la secuencia enviada al receptor sera un espacio en blanco
    Serial1.print(" ");
  }
  // Mostramos datos del vector
  else if(opcion == 2){
    // Imprimimos el vector en el receptor
    Serial1.println("Mostrando las muestras recibidas por el receptor");
    for(int i=0; i < lecturas; i++){
      Serial1.println("Lectura Muestra");
      Serial1.print(i+1);
      Serial1.println(vector[i]);
    }
    // Imprimimos el vector en el emisor
    Serial.println("Mostrando las muestras recibidas por el emisor");
    for(int i=0; i<lecturas; i++){
      Serial.println("Lectura Muestra");
      Serial.print(i+1);
      Serial.println(vector[i]);
    }
  }
}

// Funciones auxiliares

void menu(){
  Serial.println("1. Hacer una nueva captura");
  Serial.println("2. Mostrar datos del vector");
  Serial.print("Introduce una opcion: ");
}
