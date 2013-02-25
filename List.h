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

#ifndef _LIST_h
#define _LIST_h

template <class T>
class ListNode
{
 private:
	 ListNode<T>* pnext;
	 T pvalue;

 public:
	 T value() { return pvalue; }
	 void setNext(ListNode<T>* item) { pnext = item; }
	 ListNode(T value) : pvalue(value), pnext(0) {}
	 ListNode<T>* next() { return pnext; }
};

template <class T>
class List
{
private:
	ListNode<T>* nodes;

public:
	List() : nodes(0) {}

	void add(T value)
	{
		ListNode<T>* prev = 0;
		ListNode<T>* next = nodes;
		while (next != 0)
		{
			prev = next;
			next = prev->next();
		}

		if (prev == 0)
		{
			nodes = new ListNode<T>(value);
		}
		else
		{
			prev->setNext(new ListNode<T>(value));
		}
	}

	ListNode<T>* getFirst()
	{
		return nodes;
	}

	void remove(ListNode<T>* node)
	{
		ListNode<T>* prev = 0;
		ListNode<T>* next = nodes;
		while (next != 0 && next != node)
		{
			prev = next;
			next = prev->next();
		}

		if (next == node)
		{
			next->setNext(node->next());
			if (node == nodes)
			{
				nodes = node->next();
			}

			delete node;
		}
	}
};

#endif

