// Created by Emre Ozen on 11/15/2024.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>


template <class T>
class Vector
{
private:

    T* data;
    size_t size;
    size_t capacity;

    void increase_capacity()
    {
        if(capacity <= size)
        {
            capacity *= 2;
            T* temp = new T[capacity];

            for (size_t i = 0; i < size; i++)
            {
                temp[i] = data[i];
            }

            delete[] data;
            data = temp;
        }

    }

    void shrink_to_fit()
    {
        if(capacity > size)
        {

            int power = 1;

            while (power < size)
            {
                power *= 2;
            }
            capacity = power;

            T* temp = new T[capacity];
            for (size_t i = 0; i < size; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
    }

public:

    Vector() // Default constructer
    {
        size = 0;
        capacity = 2;
        data = new T[capacity];
    }

    Vector(size_t size, const T& value)
    {
        this->size = size;
        capacity = 2;
        increase_capacity();
        data = new T[capacity];

        for(int i = 0; i < size; i++)
        {
            data[i] = value;
        }
    }

    ~Vector()
    {
        delete[] data;
    }

    size_t GetSize()const
    {
        return size;
    }

    size_t GetCapacity()const
    {
        return capacity;
    }

    bool IsEmpty()const
    {
        return size == 0;
    }

    T& operator[](int index)
    {
        if (index >= size || index < 0 || IsEmpty())
        {
            throw std::out_of_range("index out of range");
        }

        return data[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size || index < 0 || IsEmpty())
        {
            throw std::out_of_range("index out of range");
        }

        return data[index];
    }

    T& front()
    {
        return data[0];
    }

    T& back()
    {
        return data[size-1];
    }

    T& at(size_t index)
    {
        return data[index];
    }

    const T& at(size_t index) const
    {
        return data[index];
    }

    T* Begin()
    {
        return data;
    }

    T* End()
    {
        return data + size;
    }

    void insert(size_t position, const T& value)
    {
        if(position > size)
            throw std::out_of_range("position out of range");

        size++;

        increase_capacity();

        for(int i = size-1; i > position; i--)
        {
            data[i] = data[i-1];
        }

        data[position] = value;
    }

    void push_back(const T& value)
    {
        insert(size, value);
    }

    void erase(size_t position)
    {
        if(position > size)
           throw std::out_of_range("position out of range");

        for(size_t i = position; i < size; i++)
        {
            data[i] = data[i+1];
        }

        size--;
        shrink_to_fit();

    }

    void pop_back()
    {
        erase(size-1);
    }

    void clear()
    {
        delete[] data;
        size = 0;
        capacity = 2;
    }

    void resize(size_t newSize, const T& value)
    {
        if(newSize > capacity)
        {
            while(newSize > capacity)
            {
                capacity *= 2;
            }

            T* temp = new T[capacity];

            for(size_t i = 0; i < size && i< newSize; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }

        for(size_t i = size; i < newSize; i++)
        {
            data[i] = value;
        }

        size = newSize;

    }

    void PrintVector()const
    {
        for (size_t i = 0; i < size; i++)
        {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
    }


    class iterator
    {
    public:
        iterator() : data(nullptr), index(0) {}

        iterator(T* ptr, size_t idx = 0) : data(ptr), index(idx) {}

        ~iterator() = default;

        iterator& operator++() // Prefix increment
        {
            ++data;
            ++index;
            return *this;
        }

        iterator operator++(int) // Postfix increment
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() // Prefix decrement
        {
            --data;
            --index;
            return *this;
        }

        iterator operator--(int) // Postfix decrement
        {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        T& operator*()
        {
            return *data;
        }

        bool operator==(const iterator& other) const
        {
            return data == other.data;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

    private:
        T* data;
        size_t index;
    };


};

#endif //VECTOR_H