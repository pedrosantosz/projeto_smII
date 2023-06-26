#include <ShiftRegister74HC595.h>

#define DATA 2
#define LATCH 3
#define CLOCK 4
#define SENSOR 12
#define BUZZER 13

ShiftRegister74HC595 aLEDro(1, DATA, CLOCK, LATCH);

int alarme = -1, leds = 0;
unsigned long tInicial = millis();
unsigned long tInicialAlarme = millis();


void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  
}

void loop() {
  if(digitalRead(SENSOR) == 0){
    alarme = 1;
  }

  if (alarme == 1) {
    if (millis() - tInicial >= 300) {
      leds = !leds;
      tInicial = millis();
    }
    
    if (leds == 1){
      aLEDro.setAllHigh();
      tone(BUZZER, 12800);
    } else {
      aLEDro.setAllLow();
      noTone(BUZZER); 
    }
  }
  
}
