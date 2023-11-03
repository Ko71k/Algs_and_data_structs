/*
Реализовать очередь с помощью двух стеков.
Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
*/
#include <iostream>

class Stack
{
private:
    int * ptr;
    int capacity;
    int begin;
public:
    Stack();
    ~Stack();
    int current;
    void Grow();
    void Push(int data);
    int Pop();
    void Printer();
};

void Stack::Printer()
{
    std::cout << "capacity = " << capacity << " begin = " << begin << " current " << current << std::endl;
    for (int i = 0; i < current; i++)
    {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}

Stack::Stack()
{
    ptr = new int[16];
    current = 0;
    capacity = 16;
    begin = 0;
}

Stack::~Stack()
{
    delete[] ptr;
}

void Stack::Push(int value)
{
    if (current + 1 >= capacity)
    {
        Grow();
    }
    ptr[(begin + current) % capacity] = value;
    current++;
}

void Stack::Grow()
{
    int new_ptr[capacity*2];
    for (int i = 0; i < capacity; i++)
    {
        new_ptr[i] = ptr[i];
    }
    delete [] ptr;
}

int Stack::Pop()
{
    if (current == 0)
    {
        return -1;
    }
    current--;
    return ptr[begin + current];
}

class Queue
{
private:
    Stack *input;
    Stack *output;
public:
    void Enqueue(int data);
    int Dequeue();
    void Flip();

    Queue();
    ~Queue();
    void Printer();
};

void Queue::Printer()
{
    std::cout << "Input: " << std::endl;
    input->Printer();
    std::cout << "Output: " << std::endl;
    output->Printer();
}

Queue::Queue()
{
    input = new Stack();
    output = new Stack();
}

Queue::~Queue()
{
    input->~Stack();
    output->~Stack();
}

void Queue::Enqueue(int data)
{
    input->Push(data);
}

int Queue::Dequeue()
{
    //std::cout << "Dequeue: output->current = " << output->current << std::endl;
    //std::cout << "Dequeue: input->current = " << input->current << std::endl;
    if (output->current == 0)
    {
        Flip();
    }
    //std::cout << "Dequeue: output->current = " << output->current << std::endl;
    //std::cout << "Dequeue: input->current = " << input->current << std::endl;
    return output->Pop();
}

void Queue::Flip()
{
    int counter = input->current;
    for (int i = 0; i < counter; i++)
    {
        output->Push(input->Pop());
    }
}

int main()
{
    Queue za_chlenami;
    int n, deq = 0;
    std::cin >> n;
    int a,b = 0;
    bool yes = true;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        if (a == 3)
        {
            za_chlenami.Enqueue(b);
            za_chlenami.Printer();
        }
        else if (a == 2)
        {
            deq = za_chlenami.Dequeue();
            //if (za_chlenami.Dequeue() != b)
            if (deq != b)
            {
                std::cout << deq << " != " << b << std::endl;
                yes = false;
            }
        }
    }
    if (yes)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
}