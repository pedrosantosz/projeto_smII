#include <ShiftDisplay.h>

#define RED
#define GREEN
#define BUZZER

int valorLido, on = -1, armado=-1;

ShiftDisplay display(COMMON_CATHODE, 4);
 
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(BUZZER, INPUT);

  digitalWrite(A1, 1);
}

void loop() {
  valorLido = analogRead(A3);

  if (on == 1) {
    armado = 1;
    display.set("on");
    digitalWrite(RED, 1);  
    digitalWrite(GREEN, 0);
  }else if (on == 0) {
    armado = 0;
    display.set("off");
    digitalWrite(RED, 0);
    digitalWrite(GREEN, 1);
  } else if (on == -1) {
    display.set("off");
  }

  if (valorLido >= 673 && valorLido <= 693) {
    on = 1;
    if (armado != 1) {
      tone(BUZZER, 12570);
      delay(350); 
      noTone(BUZZER);
    }
  }else if (valorLido >= 843 && valorLido <= 853) {
    on = 0;
    if (armado != 0) {
      tone(BUZZER, 12570);
      delay(350);
      noTone(BUZZER);
    }
  }
  display.show();
}
