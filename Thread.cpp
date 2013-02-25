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

#include "Thread.h"
#include "Scheduler.h"
#include "Logger.h"

#define STACK_SIZE 4096
#define STACK_CHECK "STACKCHK"

Thread::Thread(const char* name)
	: name(strdup(name))
{
	stack = (uint8_t*)malloc(STACK_SIZE);
	memset(stack, 0, STACK_SIZE);
	strcpy((char*)stack, STACK_CHECK);
	stackPointer = (Registers*)(stack + sizeof(Registers));

	uint16_t thisPointer = (uint16_t)this;
	stackPointer->r25 = (uint8_t)((thisPointer >> 8) & 0x00FF);
	stackPointer->r26 = (uint8_t)(thisPointer & 0x00FF);

	stackPointer->ip = (void*)(&Thread::startThread);

	Scheduler::getInstance().addThread(this);
}

Thread::~Thread()
{
	//Scheduler::getInstance().removeThread(this);
}

Registers* Thread::getStackPointer() const
{
	return stackPointer;
}

void Thread::startThread(Thread* which)
{
	char msg[100];
	sprintf(msg, "Starting thread %s", which->getName());
	Logger::Log(msg);
	which->Run();
}

const char* Thread::getName() const
{
	return name;
}
