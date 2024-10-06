#include <Keypad.h>  // Librería para el teclado matricial

const byte ROWS = 4;  // Cuatro filas
const byte COLS = 4;  // Cuatro columnas

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Conexión del teclado: pines del teclado conectados a los pines del Arduino
byte rowPins[ROWS] = {11, 10, 9, 8};  // Pines conectados a las filas
byte colPins[COLS] = {7, 6, 5, 4};  // Pines conectados a las columnas

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String password = "12345";  // Contraseña predefinida
String inputPassword;

const int ledVerde = 2;  // Pin del LED verde
const int ledRojo = 3;   // Pin del LED rojo
unsigned long timer = 0;  // Temporizador para los LEDs

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  Serial.begin(9600);  // Para monitoreo
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
    inputPassword += key;
    
    // Si se presiona '#', verificamos la contraseña
    if (key == '#') {
      if (inputPassword.length() == 6) {  // La longitud incluye el caracter '#'
        verificarPassword();
      } else {
        Serial.println("Longitud incorrecta de la contraseña");
        encenderLed(ledRojo);
      }
      inputPassword = "";  // Limpiamos el buffer de la contraseña ingresada
      timer = millis();  // Reiniciamos el temporizador al presionar '#'
    }
  }

  // Si la contraseña es correcta o incorrecta, mantenemos el LED encendido por 1 minuto
  if (millis() - timer >= 60000) {  // 60000 ms = 1 minuto
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
  }
}

void verificarPassword() {
  if (inputPassword.substring(0, inputPassword.length() - 1) == password) {  // Excluimos el caracter '#'
    encenderLed(ledVerde);
    Serial.println("Contraseña correcta");
  } else {
    encenderLed(ledRojo);
    Serial.println("Contraseña incorrecta");
  }
}

void encenderLed(int led) {
  digitalWrite(ledVerde, LOW);  // Asegura que ambos LEDs estén apagados antes de encender uno
  digitalWrite(ledRojo, LOW);
  digitalWrite(led, HIGH);
}
