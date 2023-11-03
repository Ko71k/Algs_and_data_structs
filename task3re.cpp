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
    Stack(int len);
    ~Stack();
    int current;
    void Grow();
    void Push(int data);
    int Pop();
    void Printer();
};

void Stack::Printer()
{
    std::cout << "capacity = " << capacity << " current " << current << std::endl;
    for (int i = 0; i < current; i++)
    {
        std::cout << "ptr[" << i << "] = " << ptr[i] << " ";
    }
    std::cout << std::endl;
}

Stack::Stack(int len)
{
    ptr = new int[len];
    current = 0;
    capacity = len;
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
    ptr[current] = value;
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
    return ptr[current];
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

    Queue(int len);
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

Queue::Queue(int len)
{
    input = new Stack(len);
    output = new Stack(len);
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
    if (output->current == 0)
    {
        Flip();
    }
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
    int n, deq = 0;
    std::cin >> n;
    Queue myqueue(n);
    int a,b = 0;
    bool yes = true;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        if (a == 3)
        {
            myqueue.Enqueue(b);
        }
        else if (a == 2)
        {
            deq = myqueue.Dequeue();
            if (deq != b)
            {
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