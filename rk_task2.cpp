#include <string>
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
    int Peek();
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
    if (this->IsEmpty())
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

int Stack::Peek()
{
    if (IsEmpty())
    {
        return 0;
    }
    return top->data;
}

bool isAnagram(std::string w1, std::string w2)
{
    Stack s;
    int j = 0;
    for (int i = 0; i < w2.length(); ++i)
    {
        s.Push(w1[i]);
        while (s.Peek() == w2[j] && !s.IsEmpty())
        {
            s.Pop();
            j++;
        }
    }
    return s.IsEmpty();
}

int main()
{
    std::string input, word_1, word_2;
    std::getline(std::cin, input);
    int counter = 0;
    while (input[counter] != ' ') counter++;
    word_1 = input.substr(0, counter);
    word_2 = input.substr(counter+1, input.length());
    if (isAnagram(word_1, word_2))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
}