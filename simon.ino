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
