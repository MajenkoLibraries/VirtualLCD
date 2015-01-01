#include <VirtualLCD.h>

int px0;
int py0;
int px1;
int py1;
int dx0 = 1;
int dy0 = 1;
int dx1 = 1;
int dy1 = 1;

void setup() {
	Serial.begin(115200);
	VirtualLCD.begin(Serial);
	VirtualLCD.setSize(128, 64);
	VirtualLCD.setBackground(40, 10, 0);
	VirtualLCD.setForeground(200, 80, 10);
	px0 = rand() % 128;
	px1 = rand() % 128;
	py0 = rand() % 64;
	py1 = rand() % 64;
}

void loop() {
	VirtualLCD.drawLine(px0, py0, px1, py1, false);
	px0 += dx0;
	px1 += dx1;
	py0 += dy0;
	py1 += dy1;

	if (px0 == 0) { dx0 = 1; }

	if (px0 == 127) { dx0 = -1; }

	if (px1 == 0) { dx1 = 1; }

	if (px1 == 127) { dx1 = -1; }

	if (py0 == 0) { dy0 = 1; }

	if (py0 == 63) { dy0 = -1; }

	if (py1 == 0) { dy1 = 1; }

	if (py1 == 63) { dy1 = -1; }

	VirtualLCD.drawLine(px0, py0, px1, py1, true);
	delay(50);
}
