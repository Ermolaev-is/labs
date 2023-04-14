#pragma once
#include "Stack.h"
#include <iostream>
#include <exception>


template <class T>
class StackArray : public Stack<T>
{
public:
	StackArray(size_t size = 100) :
		size_(size),
		top_(0)
	{
		if (size < 1)
			throw WrongStackSize();
		array_ = new T[size + 1];
	}

	StackArray(const StackArray<T>& src) = delete;

	StackArray(StackArray<T>&& src)
	{
		this->swap(src);
		src.array_ = nullptr;
	}

	StackArray& operator=(const StackArray<T>& src) = delete;

	StackArray& operator=(StackArray<T>&& src)
	{
		if (this != &src)
		{
			delete[] array_;
			this->swap(src);
			src.array_ = nullptr;
		}
		return *this;
	}

	virtual ~StackArray()
	{
		delete[] array_;
	}

	void push(const T& e)
	{
		if (top_ == size_)
		{
			throw StackOverflow();
		}
		array_[++top_] = e;
	}

	T pop()
	{
		if (isEmpty())
		{
			throw StackUnderflow();
		}
		return array_[top_--];
	}

	bool isEmpty()
	{
		return top_ == 0;
	}

	size_t getTop()
	{
		return top_;
	}

	class StackOverflow : public std::exception
	{
	public:
		StackOverflow()
		{
			reason_ = "Stack overflow!";
		}
		const char* what() const
		{
			return reason_;
		}
	private:
		const char* reason_;
	};

	class StackUnderflow : public std::exception
	{
	public:
		StackUnderflow()
		{
			reason_ = "Stack underflow!";
		}
		const char* what() const
		{
			return reason_;
		}
	private:
		const char* reason_;
	};


	class WrongStackSize : public std::exception
	{
	public:
		WrongStackSize()
		{
			reason_ = "Wrong stack size!";
		}
		const char* what() const
		{
			return reason_;
		}
	private:
		const char* reason_;
	};

private:
	T* array_;
	size_t top_;
	size_t size_;
	void swap(StackArray<T>& src)
	{
		std::swap(array_, src.array_);
		std::swap(top_, src.top_);
		std::swap(size_, src.size_);
	}
};

