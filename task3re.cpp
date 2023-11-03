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
};

Stack::Stack()
{
    //std::cout << "constr\n";
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
    //std::cout << " started pushing " << value << std::endl;
    if (current + 1 >= capacity)
    {
        //std::cout << "Growing\n";
        Grow();
        //std::cout << "Grew\n";
    }
    //std::cout << begin << " " << current << " " << capacity << " " << std::endl;
    ptr[(begin + current) % capacity] = value;
    //std::cout << begin << " " << current << " " << capacity << " " << ptr[(begin + current) % capacity] << std::endl;
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
};

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
    if (output->current == 0)
    {
        Flip();
    }
    return output->Pop();
}

void Queue::Flip()
{
    for (int i = 0; i++; i < input->current)
    {
        output->Push(input->Pop());
    }
}

int main()
{
    Queue za_chlenami;
    int n = 0;
    std::cin >> n;
    int a,b = 0;
    bool yes = true;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a >> b;
        if (a == 3)
        {
            za_chlenami.Enqueue(b);
        }
        else if (a == 2)
        {
            if (za_chlenami.Dequeue() != b)
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