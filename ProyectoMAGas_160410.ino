// Proyecto MAGas (Medidor Ambiental de Gas)
// Estudiante: María Angélica Vargas Masís; Código y prototipo: Roberto José Vargas Masís 
// Feria Científica 2016 en el Liceo Regional de Flores, Heredia, Costa Rica

// Definiciones y librerías necesarias 

const int gasPin = A2; // Salida analoga del sensor de Gas MQ2 al Arduino en el Pin A2

#include "DHT.h" // Librería del sensor de Humedad y Temperatura DHT11
  #define DHTPIN A1 // Pin en el cual se encuentra conectado el sensor de Humedad y Temperatura DHT11
  #define DHTTYPE DHT11 // Definición del modelo del sensor de Humedad y Temperatura DHT11
  DHT dht(DHTPIN, DHTTYPE); // Definición de la variable que se utiliza para comunicarse con el sensor de Humedad y Temperatura DHT11

#include <LiquidCrystal.h> // Librería de la pantalla LCD "lcd1602 key shield itead studio"
  LiquidCrystal lcd(8,9,4,5,6,7); // Definición de los pines que utiliza la pantalla LCD 1602 key shield itead studio"

// Funciones en ejecución

void setup() {
  Serial.begin(9600); // Inicio de la comunicación serial

lcd.begin(16, 2); // Establece el número de LEDs para las de columnas y filas:
  lcd.setCursor(1, 0); // Mueve el cursor a la posición 1,0 en la pantalla LCD "lcd1602 key shield itead studio"
  lcd.print("Proyecto Magas"); // Imprime el Texto "Proyecto Magas" en la pantalla LCD "lcd1602 key shield itead studio"
  lcd.setCursor(0, 1); // Mueve el cursor a la posición 0,1 en la pantalla LCD "lcd1602 key shield itead studio"
  lcd.print("Leyendo Sensores"); // Imprime el texto "Leyendo Sensores" en la pantalla LCD "lcd1602 key shield itead studio"

delay(2000); // Retraso de 2 segundos antes del inicio de lectura de los sensores

dht.begin(); // Inicio del sensor
  Serial.println("CLEARDATA"); // Limpia los datos que quedan de proyectos anteriores
  Serial.println("LABEL,Acolumn,Bcolumn,Temperatura, Humedad, Gas"); // Nombre de las columnas que aparecerán en Monitor serial y/o Excel por medio de la Hoja PLX-DAQ 
  Serial.println("RESETTIMER"); // Reinicia el tiempo a 0
}

// Funciones en bucle
void loop() {
delay(500); // Retraso de 0.5 segundos entre las mediciones
  float Temperature = dht.readTemperature(); // Lectura de la Temperatura en alrededor de 250 milisegundos a 2 segundos
  float Humidity = dht.readHumidity(); // Lectura de la Humedad en alrededor de 250 milisegundos a 2 segundos

lcd.clear(); // Limpia los datos que quedan en la pantalla de proyectos anteriores

Serial.print("DATA,TIME,TIMER,"); // Escribe el tiempo en Acolumn y el tiempo entre cada medición en Bcolumn
  Serial.print(Temperature); // Escribe el valor de Temperatura en °C (grados celsius)
  Serial.print(","); // Separador del Valor de Temperatura-Humedad
  Serial.print(Humidity); // Escribe el valor de Humedad Relativa en %
  Serial.print(","); // Separador del Valor de Humedad-Gas
  Serial.println(analogRead(gasPin)); // Escribe el valor de Gas en ppm (partes por millón; para que funcione en

char tempF[6]; // Valores de la variable Temperatura como caracteres
  char humF[6]; // Valores de la variable Humedad como caracteres
  dtostrf(Temperature, 5, 1, tempF); // Convierte un valor flotante a una matriz de caracteres para el valor de la variable Temperatura
  dtostrf(Humidity, 2, 0, humF); // Convierte un valor flotante a una matriz de caracteres para el valor de la variable Humedad
 
lcd.print("T:"); // Imprime en la pantalla LCD T:
  lcd.print(tempF); // Imprime en la pantalla LCD el valor de la variable tempF
  lcd.print((char)223); // Salida del carácter Grados
  lcd.print("C "); // Imprime en la pantalla LCD °C
  lcd.print("H: "); // Imprime en la pantalla LCD H:
  lcd.print(humF); // Imprime en la pantalla LCD el valor de la variable humF
  lcd.print("%"); // Imprime en la pantalla LCD %
  lcd.setCursor(3, 1); // Mueve el cursor a la posición 3,1
  lcd.print("Gas: "); // Imprime en la pantalla LCD Gas:
  lcd.print(analogRead(gasPin)); // Imprime en la pantalla LCD el valor de la variable gasPin
  lcd.print(" ppm"); // Imprime en la pantalla LCD ppm

delay(500); // Retraso de 0.5 segundos para volver a leer los sensores
  }
