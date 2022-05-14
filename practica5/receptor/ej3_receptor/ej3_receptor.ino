/**
 *  REDES Y COMUNICACIONES ESPECIFICAS
 *  Autor: Jaime Lorenzo Sanchez
 *  Programa para envio y recepcion de caracteres a trvés del puerto de comunicaciones inalambrica
 *  del Xbee.
 *  En los monitores/hiperterminales se introducen los caracteres y se pulsa intro para enviarlos
 */

// Parametros globales

char byte1='0'; // Caracter del puerto de Xbee
int maximo=0; // Maximo enviado por el emisor
int minimo=0; // Minimo enviado por el emisor
float media=0; // Media enviada por el emisor
int contador=0; // Para saber que valor es enviado por el emisor y donde guardarlo
int imprimir_valores=0; // Controla la impresion por el canal serie de los datos, evitando un bucle infinito

void setup()
{
  //Se abre el puerto Serie y se configuran los datos a 9600 bps.
  Serial.begin(9600);
  //Se abre el puerto Serie1 y se configuran los datos a 9600 bps.
  Serial1.begin(9600);
  //Se espera de la conexión con la terminal
  while (!Serial) {; }
  // Se inicializa el led 13
  pinMode(LED_BUILTIN, OUTPUT);
} 
 
 
void loop()
{   
  Serial.println("<----------- BIENVENIDO. SOY EL RECEPTOR----------->")
  // Se verifica si el puerto del Xbee tiene algún caracter
  if(Serial1.available())
  {
    if(contador==0)
    {
      // Se recibe el carácter del puerto del Xbee
      byte1 = Serial1.read(); 
      // Si recibimos una 'Z' es que el emisor va a mandar los valores en un orden en concreto
      if(byte1=='z')
      {
        // Se recibe el valor maximo
        contador=1; 
        //Se inicializan las variables
        maximo=0;
        minimo=0;
      }
    }
    else if(contador>0 and contador<5)
    {
      // Recibimos la media
      if(contador==3)
      {
        float aux2 = Serial1.parseFloat();
        media=aux2;
        contador=4;
      }
      // Recibimos el minimo
      if(contador==2)
      {
        int aux = Serial1.parseInt();
        minimo=aux;
        contador=3;
      }
      // Recibimos el maximo
      if(contador==1)
      {
        int aux = Serial1.parseInt();
        maximo=aux;
        contador=2;
      }
      // Recibimos el caracter (espacio) de finalizacion de la secuencia a enviar
      if(contador==4)
      {
        contador=0;
        imprimir_valores=1;
      }     
    } 
    // Mostramos los valores recibidos
    if(imprimir_valores==1)
    {
      Serial.print("Valor maximo obtenido: ");
      Serial.println(maximo);
      Serial.print("Valor minimo obtenido: ");
      Serial.println(minimo);
      Serial.print("Valor medio obtenido: ");
      Serial.println(media);
      imprimir_valores=0;
      //Controlamos si se activa el led 13 dependiendo si la diferencia es mayor que media.
      int diferencia= maximo-minimo;
      // Activamos el led 13
      if(diferencia > media)
      {
        Serial.println("El led 13 se activa");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      // Desactivamos el led 13
      else
      {
        Serial.println("El led 13 se desactiva");
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }
} 
