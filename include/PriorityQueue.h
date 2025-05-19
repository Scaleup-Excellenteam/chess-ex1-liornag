#pragma once

#include <list>
#include <stdexcept>



template<typename T>
struct MyComparator {
    int operator()(const T &a, const T &b) const {
        return a - b;
    }
};

template<typename T>
class PriorityQueue {
private:
    std::list<T> elements;
    MyComparator<T> comparator;
    size_t _maxSize;

public:
    PriorityQueue(size_t maxSize = 5) : _maxSize(maxSize) {
    }

    void push(const T& value) {
        auto it = elements.begin();
        for (; it != elements.end(); ++it) {
            if (comparator(value, *it) > 0) {
                break;
            }
        }
        elements.insert(it, value);

        if (_maxSize > 0 && elements.size() > _maxSize) {
            elements.pop_back();
        }
    }



    T poll() {
        if (elements.empty())
            throw std::runtime_error("Priority queue is empty");

        auto it = elements.begin();
        T value = *it;
        elements.erase(it);
        return value;
    }


    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    const T &peek() const {
        if (elements.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return elements.front();
    }

    typename std::list<T>::const_iterator begin() const {
        return elements.begin();
    }

    typename std::list<T>::const_iterator end() const {
        return elements.end();
    }
};
