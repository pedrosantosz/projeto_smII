#include <ShiftDisplay.h>
#include <ShiftRegister74HC595.h>

#define DATA 2
#define LATCH 3
#define CLOCK 4

int valorLido, valor = -1, atual=-1, armado = -1, pos = 128;
unsigned long tinicial = millis();

ShiftDisplay aledro(COMMON_CATHODE, 4);
ShiftRegister74HC595 aLEDro(1, DATA, CLOCK, LATCH);
 
void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(13, INPUT);

  digitalWrite(A1, 1);
  aLEDro.setAllLow();
}

void loop() {
  valorLido = analogRead(A3);

  if (valor == 1) {
    atual = 1;
    aledro.set("on");
    digitalWrite(A1, 0);
    digitalWrite(A0, 1);    
  }else if (valor == 0) {
    atual = 0;
    aledro.set("off");
    digitalWrite(A0, 0);
    digitalWrite(A1, 1);
  } else if (valor == -1) {
    aledro.set("off");
  }

  if (valorLido >= 673 && valorLido <= 693) {
    valor = 1;
    if (atual != 1) {
      tone(13, 12570);
      delay(350); 
      noTone(13);
    }
  }else if (valorLido >= 843 && valorLido <= 853) {
    valor = 0;
    if (atual != 0) {
      tone(13, 12570);
      delay(350);
      noTone(13);
    }
  }

  aledro.show();

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
