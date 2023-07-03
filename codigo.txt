#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define   BUZZER   7
#define   ENTRADA_A  13
#define   ENTRADA_B  12
#define   ENTRADA_C  11
#define   ENTRADA_D  10
#define   SALIDA_A   2
#define   SALIDA_B   3
#define   SALIDA_C   4
#define   SALIDA_D   5


int melodia[ ] = {262, 196, 196, 220, 196, 0, 247, 262};
int duracionNotas[] = {4, 8, 8, 4, 4, 4, 4, 4};
int nivelActual = 1;
int velocidad = 500;
const int NIVEL_MAX = 100;
int secuencia[NIVEL_MAX];
int secuenciaUsuario[NIVEL_MAX];
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup(){
  initialize();
  welcomeMessage();
}

void loop(){
  lcd.setCursor( 0, 1 );
  lcd.print("NIVEL:    ");
  lcd.setCursor( 7, 1 );
  lcd.print(nivelActual);
  lcd.setCursor( 9, 1 );
  lcd.print("      ");

   if(nivelActual == 1){
      generaSecuencia();
      muestraSecuencia();
      leeSecuencia();
   }
   if(nivelActual != 1){
      muestraSecuencia();
      leeSecuencia();
   }
}

void initialize() {
  pinMode(ENTRADA_D, INPUT);
   pinMode(ENTRADA_C, INPUT);
   pinMode(ENTRADA_B, INPUT);
   pinMode(ENTRADA_A, INPUT);
   pinMode(SALIDA_A, OUTPUT);
   pinMode(SALIDA_B, OUTPUT);
   pinMode(SALIDA_C, OUTPUT);
   pinMode(SALIDA_D, OUTPUT);
   digitalWrite(SALIDA_A, LOW);
   digitalWrite(SALIDA_B, LOW);
   digitalWrite(SALIDA_C, LOW);
   digitalWrite(SALIDA_D, LOW);
   lcd.init();
   lcd.backlight();
   lcd.clear();
}

void welcomeMessage() {
  lcd.setCursor( 0, 0 );
  lcd.print("<< SIMON GAME >>");
  lcd.setCursor( 0, 1 );
  lcd.print("  BIENVENIDOS  ");
  delay(4000);
}

void generaSecuencia(){
   randomSeed(millis());
   for(int i = 0; i < NIVEL_MAX; i++){
      secuencia[i] = random(2,6);
   }
}

void muestraSecuencia(){
   digitalWrite(SALIDA_A, LOW);
   digitalWrite(SALIDA_B, LOW);
   digitalWrite(SALIDA_C, LOW);
   digitalWrite(SALIDA_D, LOW);

   for(int i = 0; i < nivelActual; i++){
      if( secuencia[i] == SALIDA_A ){
         tone(BUZZER, 200);
         delay(200);
         noTone(BUZZER);
      }
      if( secuencia[i] == SALIDA_B ){
         tone(BUZZER, 300);
         delay(200);
         noTone(BUZZER);
      }
      if( secuencia[i] == SALIDA_C ){
         tone(BUZZER, 400);
         delay(200);
         noTone(BUZZER);
      }
      if( secuencia[i] == SALIDA_D ){
         tone(BUZZER, 500);
         delay(200);
         noTone(BUZZER);
      }
      digitalWrite(secuencia[i], HIGH);
      delay(velocidad);
      digitalWrite(secuencia[i], LOW);
      delay(200);
   }
}


void leeSecuencia(){
   int flag = 0;
   for(int i = 0; i < nivelActual; i++){
      flag = 0;
      while(flag == 0){

         if(digitalRead(ENTRADA_D) == HIGH){
            digitalWrite(SALIDA_D, HIGH);
            tone(BUZZER, 500);
            delay(300);
            noTone(BUZZER);
            secuenciaUsuario[i] = SALIDA_D;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(SALIDA_D, LOW);
         }

         if(digitalRead(ENTRADA_C) == HIGH){
            digitalWrite(SALIDA_C, HIGH);
            tone(BUZZER, 400);
            delay(300);
            noTone(BUZZER);
            secuenciaUsuario[i] = SALIDA_C;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(SALIDA_C, LOW);
         }

         if(digitalRead(ENTRADA_B) == HIGH){
            digitalWrite(SALIDA_B, HIGH);
            tone(BUZZER, 300);
            delay(300);
            noTone(BUZZER);
            secuenciaUsuario[i] = SALIDA_B;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(SALIDA_B, LOW);
         }

         if(digitalRead(ENTRADA_A) == HIGH){
            digitalWrite(SALIDA_A, HIGH);
            tone(BUZZER, 200);
            delay(300);
            noTone(BUZZER);
            secuenciaUsuario[i] = SALIDA_A;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(SALIDA_A, LOW);
         }

      }
   }
   secuenciaCorrecta();
}






void melodiaError(){
   for(int i = 0; i < 8; i++){
      int duracionNota = 1000/duracionNotas[i];
      tone(BUZZER, melodia[i],duracionNotas);
      int pausaEntreNotas = duracionNota * 1.30;
      delay(pausaEntreNotas);
      noTone(BUZZER);
   }
}
void secuenciaError(){
  lcd.setCursor( 10, 1 );
  lcd.print("Error");
  melodiaError();
   digitalWrite(SALIDA_A, HIGH);
   digitalWrite(SALIDA_B, HIGH);
   digitalWrite(SALIDA_C, HIGH);
   digitalWrite(SALIDA_D, HIGH);
   delay(250);
   digitalWrite(SALIDA_A, LOW);
   digitalWrite(SALIDA_B, LOW);
   digitalWrite(SALIDA_C, LOW);
   digitalWrite(SALIDA_D, LOW);
   delay(250);
  lcd.setCursor( 0, 1 );
  lcd.print("  Fin Del Juego  ");
  delay(3000);
   nivelActual = 1;
   velocidad = 500;
}
void secuenciaCorrecta(){
  if(nivelActual < NIVEL_MAX) {nivelActual++;} 
  velocidad -= 50;
  lcd.setCursor( 10, 1 );
  lcd.print("<Bien>");
  delay(500);
  lcd.setCursor( 10, 1 );
  lcd.print("      ");
  lcd.setCursor( 7, 1 );
  lcd.print(nivelActual);
  delay(200);
}

