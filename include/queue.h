#pragma once
#include <cstdint>
#include <stdexcept>
#include <iostream>

template <class T>
class Queue {
  private:
    T *data;              // Pointer to the dynamically allocated array
    int32_t current_size; // How many items are currently in the queue
    int32_t capacity;     // Max items allowed
    int32_t front_index;  // Index of the front element (where we dequeue)
    int32_t back_index;   // Index of the back element (where we enqueue)

  public:
    Queue() = delete;
    Queue(int32_t new_capacity);
    Queue(const Queue& other);
    Queue(Queue&& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    bool isFull();
    bool isEmpty();
    bool enqueue(T value); // Add to the back
    bool dequeue();        // Remove from the front
    T front();             // Look at the front item

    int32_t size();
    int32_t getCapacity();
    void display(const std::string& prefix = "");
};

// Constructor
template <class T>
Queue<T>::Queue(int32_t new_capacity) 
    : current_size(0), capacity(new_capacity), front_index(0), back_index(-1) 
{
    data = new T[capacity];
}

// Destructor
template <class T>
Queue<T>::~Queue() {
    delete[] data;
}

// Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& other) 
    : current_size(other.current_size), capacity(other.capacity), 
      front_index(other.front_index), back_index(other.back_index) 
{
    data = new T[capacity];
    for (int32_t i = 0; i < capacity; i++) {
        data[i] = other.data[i];
    }
}

// Move Constructor
template <class T>
Queue<T>::Queue(Queue&& other) 
    : current_size(other.current_size), capacity(other.capacity), 
      front_index(other.front_index), back_index(other.back_index), data(other.data) 
{
    other.data = nullptr;
    other.current_size = 0;
    other.capacity = 0;
}

// Assignment Operator
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        delete[] data;
        current_size = other.current_size;
        capacity = other.capacity;
        front_index = other.front_index;
        back_index = other.back_index;
        data = new T[capacity];
        for (int32_t i = 0; i < capacity; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <class T>
bool Queue<T>::isFull() {
    return current_size == capacity;
}

template <class T>
bool Queue<T>::isEmpty() {
    return current_size == 0;
}

// Enqueue: Add to the back
template <class T>
bool Queue<T>::enqueue(T value) {
    if (isFull()) return false;

    // Move back_index forward circularly
    back_index = (back_index + 1) % capacity;
    data[back_index] = value;
    current_size++;
    return true;
}

// Dequeue: Remove from the front
template <class T>
bool Queue<T>::dequeue() {
    if (isEmpty()) return false;

    // Move front_index forward circularly
    front_index = (front_index + 1) % capacity;
    current_size--;
    return true;
}

template <class T>
T Queue<T>::front() {
    if (isEmpty()) throw std::runtime_error("Queue is empty.");
    return data[front_index];
}

template <class T>
int32_t Queue<T>::size() {
    return current_size;
}

template <class T>
int32_t Queue<T>::getCapacity() {
    return capacity;
}

template <class T>
void Queue<T>::display(const std::string& prefix) {
    if (!prefix.empty()) std::cout << prefix << std::endl;
    if (isEmpty()) {
        std::cout << "[Empty Queue]" << std::endl;
        return;
    }

    std::cout << "Queue (Front to Back):" << std::endl;
    for (int32_t i = 0; i < current_size; i++) {
        int32_t index = (front_index + i) % capacity;
        std::cout << "  [" << index << "]: " << data[index];
        if (index == front_index) std::cout << " <- FRONT";
        if (index == back_index) std::cout << " <- BACK";
        std::cout << std::endl;
    }
}
