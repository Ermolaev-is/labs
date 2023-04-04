#pragma once
#include <iostream>
#include "Queue.h"
#include <exception>

template <class T>
class QueueArray : public Queue<T>
{
public:

    QueueArray(size_t size = 100)
    {
        if (size > 100 || size < 0)
            throw WrongQueueSize();
        max_size = size;
        front_index = 0;
        rear_index = -1;
        num_items = 0;
        array_ = new T[max_size];
    }

    QueueArray(const QueueArray<T>& src) = delete;

    QueueArray(QueueArray<T>&& src)
    {
        array_ = src.array_;
        front_index = src.front_index;
        rear_index = src.rear_index;
        max_size = src.max_size;
        num_items = src.num_items;
        src.array_ = nullptr;
    }


    QueueArray<T>& operator=(const QueueArray<T>& src) = delete;

    QueueArray<T>& operator=(QueueArray<T>&& src)
    {
        if (this != &src)
        {
            delete[] array_;
            array_ = src.array_;
            front_index = src.front_index;
            rear_index = src.rear_index;
            max_size = src.max_size;
            num_items = src.num_items;
            src.array_ = nullptr;
        }
        return *this;
    }

    virtual ~QueueArray()
    {
        delete[] array_;
    }

    void enQueue(const T& e)
    {
        if (num_items == max_size)
        {
            throw QueueOverflow();
        }
        rear_index = (rear_index + 1) % max_size;
        array_[rear_index] = e;
        num_items++;
    }

    T deQueue()
    {
        if (isEmpty())
        {
            throw QueueUnderflow();
        }
        T front_item = array_[front_index];
        front_index = (front_index + 1) % max_size;
        num_items--;
        return front_item;
    }

    bool isEmpty()
    {
        return (num_items == 0);
    }

    class QueueOverflow : public std::exception
    {
    public:
        QueueOverflow()
        {
            reason_ = "Queue overflow!";
        }
        const char* what() const
        {
            return reason_;
        }
    private:
        const char* reason_;
    };

    class QueueUnderflow : public std::exception
    {
    public:
        QueueUnderflow()
        {
            reason_ = "Queue underflow!";
        }
        const char* what() const
        {
            return reason_;
        }
    private:
        const char* reason_;
    };

    class WrongQueueSize : public std::exception
    {
    public:
        WrongQueueSize()
        {
            reason_ = "Wrong queue size!";
        }
        const char* what() const
        {
            return reason_;
        }
    private:
        const char* reason_;
    };


private:
    size_t max_size;
    size_t front_index;
    size_t rear_index;
    size_t num_items;
    T* array_;
};





