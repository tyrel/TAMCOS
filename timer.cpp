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

#include "Timer.h"

Timer* Timer::instance = NULL;

Timer::Timer()
{
	ticks = 0;

	handler = NULL;

	cli();

	// set timer0 interrupt to 2 kHz
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
	OCR0A = 124;
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS11) | (1 << CS10);
	TIMSK0 |= (1 << OCIE0A);

	sei();
}

Timer& Timer::getInstance()
{
	// TODO: synchronize this
	if (instance == NULL)
	{
		instance = new Timer();
	}

	return *instance;
}

void Timer::setInterruptHandler(TimerInterruptHandler* handler)
{
	this->handler = handler;
}

void* Timer::interrupt(void* stackPointer)
{
	ticks++;
	if (handler != NULL)
	{
		return handler->HandleTimerInterrupt(stackPointer);
	}
	else
	{
		return stackPointer;
	}
}

unsigned long Timer::getTickCount() const
{
	return ticks;
}

ISR(TIMER0_COMPA_vect) {
	// We want to store off the registers that the vector itself does not.
	asm volatile (
		"push r2"		"\n\t"
		"push r3"		"\n\t"
		"push r4"		"\n\t"
		"push r5"		"\n\t"
		"push r6"		"\n\t"
		"push r7"		"\n\t"
		"push r8"		"\n\t"
		"push r9"		"\n\t"
		"push r10"		"\n\t"
		"push r11"		"\n\t"
		"push r12"		"\n\t"
		"push r13"		"\n\t"
		"push r14"		"\n\t"
		"push r15"		"\n\t"
		"push r28"		"\n\t"
		"push r29"		"\n\t"
		:/*outputs*/:/*inputs*/:/*clobber*/);

	// now the current stack is what we'd want to save as a thread's stack
	uint8_t* stackptr = *(uint8_t**)(SP);

	stackptr = (uint8_t*)Timer::getInstance().interrupt(stackptr);

	asm volatile (
		"pop r29"		"\n\t"
		"pop r28"		"\n\t"
		"pop r15"		"\n\t"
		"pop r14"		"\n\t"
		"pop r13"		"\n\t"
		"pop r12"		"\n\t"
		"pop r11"		"\n\t"
		"pop r10"		"\n\t"
		"pop r9"		"\n\t"
		"pop r8"		"\n\t"
		"pop r7"		"\n\t"
		"pop r6"		"\n\t"
		"pop r5"		"\n\t"
		"pop r4"		"\n\t"
		"pop r3"		"\n\t"
		"pop r2"		"\n\t"
		:/*outputs*/:/*inputs*/:/*clobber*/);
}
