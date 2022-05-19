/**

***Redes y comunicaciones específicas***
ALUMNO: Jaime Lorenzo Sanchez

*/
int capturas[250]={0}; //inicializamos el vector con un tamaño maximo de 250 y a 0
int i; //Variable que controla los bucles for
char opcion; // Variable que controla la opcion del menu
int maxVal=0; //Donde guardaremos el valor maximo
int minVal=0; //Donde guardaremos el valor minimo
int puerto_escucha; // Variable donde almacenaremos el puerto de escucha.
int numero_muestras=0; // Lo inicializamos a 0 el limitador de capturas.


void setup(){
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {; //Espera la conexión con la terminal}
  Serial.print("<------------ Bienvenido a la P5:3 ------------->\n");
  Serial.print("->SOY EL EMISOR\n");
  Serial.print("->EMISOR: Introduzca una tecla para empezar el programa.\n");
}


void loop(){
  delay(200);
  menu(0); // Imprimimos el menu
  delay(1000);
  while (Serial.available()>0){ // Esperamos que el usuario seleccione la opción del menu.
    opcion=Serial.read();
    Serial.print(opcion);
    delay (500);
    switch(opcion){
      // En esta opción se lee un número de muestras indicadas por el usuario y por el puerto que se le indique. 
      case '1': 
        Serial.write("\n--------------------------------------\n");
        Serial.print("Opcion 1 elegida\n");
        limpiarbuffer();
        //Introducir la cantidad de los conjuntos
        Serial.print("Introduzca la cantidad de numeros del conjunto: ");
        limpiarbuffer();
        while(Serial.available()==0){delay (1000);}
        numero_muestras=Serial.parseInt();
        Serial.print(numero_muestras);
        Serial.print("\n");
        //El usuario podrá introducir los valores por la terminal
        for (i=0;i<numero_muestras;i++){
          Serial.print("P[");
          Serial.print(i);
          Serial.print("]: ");
          limpiarbuffer();
          while(Serial.available()==0){delay (1000);}
          capturas[i] = Serial.parseInt();
          Serial.print(capturas[i]);
          Serial.print("\n");
        }
        //Se pasara el número de captura que se han realizado para obtener los calculos del maximo y minimo
        calculos(numero_muestras);
        //Se vuelve a imprimir el menu
        menu(0);
        break;

      case '2':
        //ESTE CASO SERA PARA IMPRIMIR EL VECTOR DE MUESTRAS RECOGIDO ANTERIORMENTE
        Serial.write("\n--------------------------------------\n");
        Serial.println ("Opcion 2 elegida");
        //Se imprimiera en el receptor
        imprimirvector_receptor(numero_muestras);
        //Se imprimira en el emisor
        imprimirvector_emisor(numero_muestras);
        
        //Se vuelve a imprimir el menu
        menu(0);
        break;
    }
  }
}

//FUNCIONES
void menu(int opcion){ // Función del menu
  Serial.write("--------------------------------------\n");
  Serial.write("1.- Hacer una nueva captura\n");
  Serial.write("2.- Mostrar datos del vector\n");
  Serial.write("Indica la opcion: ");
  limpiarbuffer();
  delay(1000);
  while(Serial.available()==0){delay (1000);}
}

void limpiarbuffer(){ // Se ha creado esta función para limpiar el buffer
  Serial.read();//Leyendo la basura del buffer lo limpiamos, ya que con el \n se nos mete basura.
}
 
// Es la función que emprime en la serial del receptor 
void imprimirvector_receptor(int tam){ // Se le pasa el tamaño del vector mostrado para la hora de imprimir que imprima solo los valores que se han capturado
    Serial1.write("--------------------------------------\n");
   for (i=0;i<numero_muestras;i++){
        Serial1.print("Vector[");
        Serial1.print(i);
        Serial1.print("]: ");
        Serial1.print(capturas[i]);
        Serial1.print("\n");
        delay(100);
       }
       Serial1.write("--------------------------------------\n");
      
    //Controla si el tamaño del vector es 0, si es 0 no se ha tomado ninguna muestra por parte del usuario.
    if (tam==0)
      Serial1.print("->No existen muestras para imprimir\n");
}

// Es la función que emprime en la serial del emisor
void imprimirvector_emisor(int tam){ // Se le pasa el tamaño del vector mostrado para la hora de imprimir que imprima solo los valores que se han capturado
   for (i=0;i<numero_muestras;i++){
        Serial.print("Vector[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.print(capturas[i]);
        Serial.print("\n");
        delay(100);
       }
       
    //Controla si el tamaño del vector es 0, si es 0 no se ha tomado ninguna muestra por parte del usuario.
    if (tam==0)
      Serial.print("->No existen muestras para imprimir\n");
}

//Función del emisor, donde calculamos el maximo, minimo y la media
void calculos(int tam){ 

   maxVal = capturas[0];//Inicializamos el maximo con el primer elemento del vector.
   minVal = capturas[0];//Inicializamos el minimo con el primer elemento del vector.
   float mediaVal = 0;//Inicializamos la media con el valor 0.
   
   for (int i = 0; i < tam; i++) {
      maxVal = max(capturas[i],maxVal); //Hacemos uso de la función max de arduino para encontrar el maximo
      minVal = min(capturas[i],minVal); //Hacemos uso de la función min de arduino para encontrar el minimo
      mediaVal = mediaVal + capturas[i]; // Hacemo la suma de todos los elementos del vector para luego dividirlo por el tamaño.
   }
   mediaVal = mediaVal/tam;
   
   //Enviamos una 'z' para avisar al receptor que se va a empezar a enviar los datos en el siguiente orden
   Serial1.print("z");
   delay(2000);
   Serial.print("Maximo: "); 
   Serial.print(maxVal);
   
   Serial1.print(maxVal); //Primero recibira el valor del maximo para que lo almacene
   Serial.print("\n");
   delay(2000);
   Serial.print("Minimo: ");
   Serial.print(minVal);
   
   Serial1.print(minVal); //En segundo lugar recibira el minimo.
   Serial.print("\n");
   delay(2000);
   Serial.print("Media: ");
   Serial.print(mediaVal);
   
   Serial1.print(mediaVal); //Y por último la media
   Serial.print("\n");
   delay(2000);
   Serial1.print(" "); // Es importante que reciba el espacio para que sepa el receptor de que ha terminado la secuencia.
}
