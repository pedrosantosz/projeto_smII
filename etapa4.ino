#include <ShiftDisplay.h>

ShiftDisplay display(COMMON_CATHODE, 4);

int contagem = 10;
unsigned long tConta = millis();

void setup() {

}

void loop() {
	if (millis() - tConta >= 1000 && contagem >= 0) {
		display.set(contagem);
		contagem--;
		tConta = millis();
	}
	display.show();
}
