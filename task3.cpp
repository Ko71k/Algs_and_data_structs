/*
Реализовать очередь с помощью двух стеков.
Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
*/
#include <iostream>

struct Node
{
    Node(int data)
    : data(data), next(nullptr)
    {
    }
    int data;
    Node *next;
};

class Stack
{
private:
    Node *top;
public:
    Stack();
    ~Stack();

    void Push(int data);
    int Pop();
    bool IsEmpty();
};

Stack::Stack(): top(nullptr)
{
}

Stack::~Stack()
{
}

bool Stack::IsEmpty()
{
    return top == nullptr;
}

void Stack::Push(int data)
{
    Node *node = new Node(data);
    if (IsEmpty())
    {
        top = node;
        return;
    }
    node->next = top;
    top = node;
}

int Stack::Pop()
{
    if (IsEmpty())
    {
        return -1;
    }
    int tmpData = top->data;
    Node *tmpNode = top;
    top = top->next;
    delete tmpNode;
    return tmpData;
}


class Queue
{
private:
    Node *PopReciever;
    Node *PushReciever;
public:
    Queue();
    ~Queue();
};

Queue::Queue(/* args */)
{
}

Queue::~Queue()
{
}
