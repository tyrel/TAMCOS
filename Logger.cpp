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

#include "Logger.h"

Logger* Logger::instance = new Logger();

Logger::Logger()
	: lock(true)
{
	instance = this;
	Serial.begin(9600);

	lock = false;
}

void Logger::Flush()
{
	if (instance == NULL) return;

	// TODO: lock better
	while (instance->lock) ;
	instance->lock = true;
	ListNode<char*>* node = instance->messages.getFirst();

	while (node != NULL)
	{
		Serial.println(node->value());
		ListNode<char*>* next = node->next();
		instance->messages.remove(node);
		node = next;
	}

	instance->lock = false;
}

void Logger::Log(const char* message)
{
	if (instance == NULL) return;

	// TODO: lock better
	while (instance->lock) ;
	instance->lock = true;

	instance->messages.add(strdup(message));

	instance->lock = false;
}
