/**
 * REDES Y COMUNICACIONES ESPECIFICAS
 * Autor: Jaime Lorenzo Sanchez
 */

// FUNCIONAMIENTO

/**
Primero en el receptor, tiene que darle la opción 1, para tomar esperar al emisor que mande los datos.
Posteriormente el emisor, tiene que entrar en el menú y darle al 1, para empezar enviar los valores
*/

/**
  Se nos plantean la siguiente cuestión:
 "Comprobar si hay pérdida de datos o no. Justificar la respuesta de si hay o no pérdida de datos."

Es más fiable la opción de enviar la información almacenada en un vector, ya que el delay de conexión es minima y es mucho más fiable
que si no utilizamos el vector. Ya que la muestra que se toma y a la vez se envia, existe un delay, y podemos encontrarnos que el receptor
no alcanza a obtener todos los valores enviados, por esta misma cuestión, a veces pasa que los últimos valores que imprime el receptor son 0
pero no es porque el emisor le haya enviado un 0, es que el emisor ya ha mandado los 40 valores, y el receptor habido valores que no lo ha cogido
y lo rellena con un 0.

Por lo tanto podemos concluir que a la hora de trabajar con medidas, debemos de ser precisos y primero almacenarlos en un array, para poder manipularlos o incluso
para trasportar dicha información. Aún así, se puede representar un margen de error, pero respecto a la otra opción dicho margen es casi nulo.

**/

// Variables globales

int* vector = (int*) malloc (sizeof(int)* 40);
int apartado = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {;}
  Serial.println("SOY EL EMISOR");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Introducir el puerto de escucha, que se le pedirá al usuario por pantalla  
  Serial.print("Introduzca el puerto de escucha : ");
  // Esperamos a que el usuario introduzca el puerto de escucha
  while(Serial.available()==0){;}
  // Obtenemos el puerto de escucha
  int puerto=Serial.parseInt();
  //Imprimimos el puerto de escucha que ha introducido el usuario
  Serial.println(puerto);
  // Apartado1: Almacenamos las lecturas en un vector
  if(apartado == 1){
    // Almacenamos las capturas en el vector de muestras
    for(int i=0; i < 40; i++){
      vector[i] = analogRead(puerto);
      // Enviamos la informacion almacenada en el vector al receptor
      Serial1.println(vector[i]);
    }
    // Modificamos el apartado
    apartado = 2;
  }
  // Apartado2: Mandamos las capturas sin almacenar
  else if(apartado == 2){
    // Enviamos las capturas al receptor
    for(int i=0; i<40; i++){
      Serial1.println(analogRead(puerto));
    }
    // Reiniciamos el ejercicio
    apartado = 1;
  }

}

// Funciones auxiliares
