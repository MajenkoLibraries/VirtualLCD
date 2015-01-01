/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
