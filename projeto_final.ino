#include <ShiftDisplay.h>
#include <ShiftRegister74HC595.h>

#define DATA 2
#define LATCH 3
#define CLOCK 4

#define RED A0
#define GREEN A1
#define BUZZER 13
#define SENSOR 12

int valorLido, on = -1, armado = -1, pos = 0, alarme = -1, contagem = 10, estado = 0, stateLeds = 0;
unsigned long tinicial = millis(), tConta = millis(),  tInicial = millis();

ShiftDisplay display(COMMON_CATHODE, 4);
ShiftRegister74HC595 leds(1, DATA, CLOCK, LATCH);
 
void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(SENSOR, INPUT);
  pinMode(A3, INPUT);

  digitalWrite(A1, 1);
  leds.setAllLow();
}

void loop() {
  valorLido = analogRead(A3);

  if (on == 1) {
    armado = 1;

    if (millis() - tConta >= 1000 && contagem >= -1) {
    display.set(contagem);
    contagem--;
    tConta = millis();

    digitalWrite(RED, estado);
    estado = !estado;
  }
  //display.show();

  if (contagem < -1) {
    display.set("on");
    if (digitalRead(SENSOR) == 0) {
      alarme = 1;
    }

    if (alarme == 1) {
      if (millis() - tInicial >= 300) {
        stateLeds = !stateLeds;
        tInicial = millis();
      }

      if (stateLeds == 1) {
        leds.setAllHigh();
        tone(BUZZER, 2300);
      } else {
        leds.setAllLow();
        noTone(BUZZER);
      }
    }
  } 
    digitalWrite(GREEN, 0);

    if (alarme != 1) {
        if (millis() - tinicial >= 200) {
        if (pos == 8)
          pos = 0;

        leds.setAllLow();
        leds.set(pos, 1);
        pos++;
        tinicial = millis();
      }
    }
  }else if (on == 0) {
    armado = 0;
    contagem = 10;
    alarme = 0;

    display.set("off");
    
    digitalWrite(RED, 0);
    digitalWrite(GREEN, 1);

    leds.setAllLow();
    pos = 0;
  } else if (on == -1) {
    display.set("off");
  }

  if (valorLido >= 673 && valorLido <= 693) {
    on = 1;
    if (armado != 1) {
      tone(BUZZER, 2300);
      delay(350); 
      noTone(BUZZER);
    }
  }else if (valorLido >= 843 && valorLido <= 853) {
    on = 0;
    if (armado != 0) {
      tone(BUZZER, 2300);
      delay(350);
      noTone(BUZZER);
    }
  }
  display.show();
}
