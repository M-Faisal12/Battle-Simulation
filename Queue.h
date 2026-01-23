#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
class Queue {
private:
    T* data;
    int front;
    int rear;
    int capacity;
    int count;

public:
    Queue(int size = 100)
        : capacity(size), front(0), rear(-1), count(0) {
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    // Add element
    void enqueue(T value) {
        if (isFull())
            throw std::overflow_error("Queue is full");

        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }

    // Remove element
    T dequeue() {
        if (isEmpty())
            throw std::underflow_error("Queue is empty");

        T value = data[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    // Get front element
    T peek() const {
        if (isEmpty())
            throw std::underflow_error("Queue is empty");

        return data[front];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int size() const {
        return count;
    }
};

#endif
