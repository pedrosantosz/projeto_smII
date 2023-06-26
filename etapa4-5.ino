#include <ShiftDisplay.h>

#define RED A0

ShiftDisplay aledro(COMMON_CATHODE, 4);

int contagem = 10, estado = 0;
unsigned long tConta = millis();

void setup() {
	pinMode(RED, OUTPUT);
}

void loop() {
	if (millis() - tConta >= 1000 && contagem >= 0) {
		aledro.set(contagem);
		contagem--;
		tConta = millis();

		digitalWrite(RED, estado);
    		estado = !estado;
	}
	aledro.show();
}
