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

#include "Logger.h"

namespace TAMCOS
{

Timer* Timer::instance = NULL;

Timer::Timer()
	: ticks(0), handler(NULL)
{
	// turn off interrupts while we configure the timer
	cli();

	// set timer1 interrupt to 10 Hz
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 1562; // this is how high it will count. when it reaches, it'll trigger
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK1 = (1 << OCIE1A);

	// re-enable interrupts
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
	Logger::Log("Tick %d", ticks);
	Logger::Flush();
	if (handler != NULL)
	{
		return handler->HandleTimerInterrupt(stackPointer);
	}
	else
	{
		return stackPointer;
	}
}

uint64_t Timer::getTickCount() const
{
	return ticks;
}

ISR(TIMER1_COMPA_vect) {
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

	SP = (uint16_t)stackptr;

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

} // end namespace