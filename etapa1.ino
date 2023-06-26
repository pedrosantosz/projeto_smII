#include <ShiftDisplay.h>
int valorLido, on = -1, atual=-1;

ShiftDisplay display(COMMON_CATHODE, 4);
 
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(13, INPUT);

  digitalWrite(A1, 1);
}

void loop() {
  valorLido = analogRead(A3);

  if (on == 1) {
    atual = 1;
    display.set("on");
    digitalWrite(A1, 0);
    digitalWrite(A0, 1);    
  }else if (on == 0) {
    atual = 0;
    display.set("off");
    digitalWrite(A0, 0);
    digitalWrite(A1, 1);
  } else if (on == -1) {
    display.set("off");
  }

  if (valorLido >= 673 && valorLido <= 693) {
    on = 1;
    if (atual != 1) {
      tone(13, 12570);
      delay(350); 
      noTone(13);
    }
  }else if (valorLido >= 843 && valorLido <= 853) {
    on = 0;
    if (atual != 0) {
      tone(13, 12570);
      delay(350);
      noTone(13);
    }
  }

  display.show();
}
