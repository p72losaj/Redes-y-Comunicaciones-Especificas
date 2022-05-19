/**

***REDES Y COMUNICACIONES ESPECIFICAS***
ALUMNO: Jaime Lorenzo Sanchez
*/

// Variables globales

int* muestras; // Vector de capturas
float voltage; //Variable que utilizaremos para el calculo del voltaje
char opcion; //Variable control de opciones
int numero_muestras=0; // Lo inicializamos a 0 el limitador de capturas.

void setup(){
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {;}
}

void loop(){
  //Mensaje de bienvenida
  Serial.println("BIENVENIDO. SOY EL EMISOR");
  // Imprimimos el menu
  menu(); 
  // Esperamos a que el usuario seleccione la opcion del menu
  while(Serial.available() == 0){;}
  // Leemos la opcion seleccionada por el usuario
  opcion = Serial.read();
  // Mostramos la opcion elegida por el usuario
  Serial.println(opcion);
  switch(opcion){
      // En esta opción se lee un número de muestras indicadas por el usuario
      case '1': 
        //Introducir la cantidad de capturas
        Serial.print("Introduzca la cantidad capturas: ");
        // Esperamos a que el usuario introduzca el numero de capturas
        while(Serial.available()==0){;}
        // Obtenemos el numero de muestras
        numero_muestras=Serial.parseInt();
        // Mostramos el numero de muestras
        Serial.println(numero_muestras);        
        // Reservamos la memoria del vector
        muestras = (int*) malloc (sizeof(int)* numero_muestras);
        // Se recoge el número de muestras seleccionadas y el cual se introduce en el vector de capturas.
        for (int i = 0; i < numero_muestras; i++){
          Serial.print("Vector[");
          Serial.print(i);
          Serial.print("]: ");
          // Esperamos que el usuario introduzca una muestra por el canal Serial
          while(Serial.available()==0){;}
          // Almacenamos la muestra en el vector
          muestras[i] = Serial.parseInt();
          // Mostramos la muestra
          Serial.println(muestras[i]);
        }
        // se imprime el resultado obtenido 
        imprimirvector_receptor();
        // Mostramos de nuevo el menu
        menu();
        break;

        case '2':
        //ESTE CASO SERA PARA IMPRIMIR EL VECTOR DE MUESTRAS RECOGIDO ANTERIORMENTE
        imprimirvector_receptor();
        imprimirvector_emisor();
        // Mostramos el menu
        menu();
        break;
  }
}

//FUNCIONES

void menu(){ // Función del menu
  Serial.write("--------------------------------------\n");
  Serial.write("1.- Hacer una nueva captura\n");
  Serial.write("2.- Mostrar datos del vector\n");
  Serial.write("Indica la opcion: ");
  while(Serial.available()==0){;}
}

//Esta función se encarga de imprimir el vector por el usuario.  

void imprimirvector_receptor(){
   for (int i=0;i<numero_muestras;i++){
        // Enviamos el valor de la señal por el canal Serial1
        Serial1.println(muestras[i]);
       }
}

//Esta función se encarga de imprimir el vector en el emisor

void imprimirvector_emisor(){
   for (int i=0;i<numero_muestras;i++){
        Serial.print("Vector[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(muestras[i]);
       }
}
