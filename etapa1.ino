#include <ShiftDisplay.h>
int valorLido, valor = -1, atual=-1;

ShiftDisplay aledro(COMMON_CATHODE, 4);
 
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(13, INPUT);

  digitalWrite(A1, 1);
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
}
