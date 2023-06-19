#include <ShiftRegister74HC595.h>
#define DATA 2
#define LATCH 3
#define CLOCK 4

ShiftRegister74HC595 aLEDro(1, DATA, CLOCK, LATCH);

int valorLido, armado = -1, pos = 128;
unsigned long tinicial = millis();

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  aLEDro.setAllLow();
}

void loop() {
  valorLido = analogRead(A3);
  if (valorLido >= 673 && valorLido <= 693)
    valor = 1;
  else if (valorLido >= 843 && valorLido <= 853)
    valor = 0;

  if (valor == 1) {
    shiftOut(DATA, CLOCK, LSBFIRST, pos);
    
    if (millis() - tinicial >= 200) {
      pos = pos / 2;
      tinicial = millis();
    }
    
    digitalWrite(LATCH, 1);  
    digitalWrite(LATCH, 0);
    
    if (pos == 0)
        pos = 128;
  } else if (valor == 0) {
    aLEDro.setAllLow();
    pos = 0;
  }
}
