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

#include <LiquidCrystal.h>
#include "DebugLCD.h"
#include "Logger.h"
#include "List.h"
#include "Thread.h"
#include "Kernel.h"
#include "Scheduler.h"
#include "timer.h"

void setup()
{
	TAMCOS::Timer::getInstance(); // cause new timer to be created
}

void loop()
{
	TAMCOS::Logger logger;
	TAMCOS::Kernel kernel(logger);

	while(1); // we don't ever want to return
}
