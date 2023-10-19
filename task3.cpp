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
    while (!IsEmpty())
    {
        Pop();
    }
    
}

bool Stack::IsEmpty()
{
    return (top == nullptr);
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
    Stack *Reciever;
    Stack *Giver;
public:
    Queue(Stack first, Stack Second);
    Queue();
    ~Queue();

    void Enqueue(int data);
    int Dequeue();
    void Flip();
};

Queue::Queue()
{
    Stack Reciever_Base, Giver_Base;
    Reciever = &Reciever_Base;
    Giver = &Giver_Base;
}

Queue::Queue(Stack first, Stack Second) 
{
    Reciever = &first;
    Giver = &Second;
}

Queue::~Queue()
{
    while (!(Reciever->IsEmpty() && Giver->IsEmpty()))
    {
        Dequeue();
    }
    
}

void Queue::Enqueue(int data)
{
    Reciever->Push(data);
}

int Queue::Dequeue()
{
    if (!Giver->IsEmpty())
    {
        return Giver->Pop();
    }
    else
    {
        if (!Reciever->IsEmpty())
        {
            Flip();
            return Giver->Pop();
        } 
    }
    return -1;  
}

void Queue::Flip()
{
    while (!Reciever->IsEmpty())
    {
        Giver->Push(Reciever->Pop());
    }    
}

int main()
{
    int n = 0;
    std::cin >> n;
    int a, b = 0;
    bool answer = true;

    Stack first, second;

    //Queue myqueue;
    Queue myqueue(first, second);

    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        std::cin >> b;
        switch (a)
        {
        case 2:
            if (myqueue.Dequeue() != b)
            {
                answer = false;
            }
            break;
        case 3:
            myqueue.Enqueue(b);
            break;
        default:
            break;
        }
    }
    if (answer)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    myqueue.~Queue();
    first.~Stack();
    second.~Stack();
}