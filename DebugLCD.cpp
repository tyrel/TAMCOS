/*
 * TAMCOS - Tyrel's Awesome Microcontroller Operating System
 * Copyright (C) 2013 Tyrel L. Haveman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "DebugLCD.h"

DebugLCD::DebugLCD()
	: lcd(12, 11, 10, 5, 4, 3, 2)
	, progress(0)
{
	lcd.begin(16, 2);
	lcd.clear();

	memset(message, ' ', sizeof(message));
}

void DebugLCD::refresh()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	int i = 0;
	for (; i < progress; i++)
	{
		lcd.print("X");
	}
	for (; i < 16; i++)
	{
		lcd.print(" ");
	}

	lcd.setCursor(0, 1);
	lcd.print(message);
}

void DebugLCD::setMessage(const char* format, ...)
{
	memset(message, ' ', sizeof(message));

	va_list args;
	va_start(args, format);
	vsnprintf(message, sizeof(message), format, args);

	refresh();
}

void DebugLCD::makeProgress()
{
	progress++;
	if (progress > 16)
	{
		progress = 0;
	}

	refresh();
}

DebugLCD debug;
