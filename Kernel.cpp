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

#include "Kernel.h"
#include "Scheduler.h"
#include "Thread.h"
#include "Logger.h"

class Blinky : public Thread
{
public:
	Blinky()
		: Thread("blinky")
	{
		pinMode(13, OUTPUT);
	}

protected:
	virtual void Run()
	{
		bool on = false;
		unsigned long last = 0;
		while (1)
		{
			Logger::Flush();

			unsigned long current = Timer::getInstance().getTickCount();

			if (last != current && current % 1000 == 0)
			{
				if (on)
				{
					digitalWrite(13, HIGH);
				}
				else
				{
					digitalWrite(13, LOW);
				}
				on = !on;
				last = current;
			}
		}
	}
};

Kernel::Kernel()
{
	Scheduler& scheduler = Scheduler::getInstance();

	Blinky blinky;

	Logger::Log("Starting the scheduler");

	Logger::Flush();

	//scheduler.enable();

	while (true)
	{
		Logger::Flush();
	}
}
