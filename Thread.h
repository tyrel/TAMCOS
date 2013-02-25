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

#ifndef _THREAD_h
#define _THREAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Registers
{
public:
	uint8_t sreg;
	uint8_t r29;
	uint8_t r28;
	uint8_t r15;
	uint8_t r14;
	uint8_t r13;
	uint8_t r12;
	uint8_t r11;
	uint8_t r10;
	uint8_t r9;
	uint8_t r8;
	uint8_t r7;
	uint8_t r6;
	uint8_t r5;
	uint8_t r4;
	uint8_t r3;
	uint8_t r2;
	uint8_t r31;
	uint8_t r30;
	uint8_t r27;
	uint8_t r26;
	uint8_t r25;
	uint8_t r24;
	uint8_t r23;
	uint8_t r22;
	uint8_t r21;
	uint8_t r20;
	uint8_t r19;
	uint8_t r18;
	uint8_t r17;
	uint8_t r16;
	uint8_t r0;
	uint8_t r1;
	void* ip;
};

class Thread
{
 private:
	 uint8_t* stack;
	 Registers* stackPointer;
	 char* name;
	 static void startThread(Thread* which);

protected:
	 virtual void Run() = 0;

public:
	 Thread(const char* name);
	 virtual ~Thread();

	 Registers* getStackPointer() const;

	 const char* getName() const;
};

#endif

