#include <VirtualLCD.h>

void setup() {
	Serial.begin(115200);
	VirtualLCD.begin(Serial);
	VirtualLCD.setSize(128, 64);
	VirtualLCD.setBackground(40, 10, 0);
	VirtualLCD.setForeground(200, 80, 10);
}

void loop() {
	VirtualLCD.setPixel(rand() % 128, rand() % 64);	
	VirtualLCD.clearPixel(rand() % 128, rand() % 64);	

}
