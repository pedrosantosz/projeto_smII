#include <ShiftRegister74HC595.h>

#define DATA 2
#define LATCH 3
#define CLOCK 4
#define SENSOR 12
#define BUZZER 13

ShiftRegister74HC595 leds(1, DATA, CLOCK, LATCH);

int alarme = -1, stateLeds = 0;
unsigned long tInicial = millis();

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
      stateLeds = !stateLeds;
      tInicial = millis();
    }
    
    if (stateLeds == 1){
      leds.setAllHigh();
      tone(BUZZER, 12800);
    } else {
      leds.setAllLow();
      noTone(BUZZER); 
    }
  }
  
}
