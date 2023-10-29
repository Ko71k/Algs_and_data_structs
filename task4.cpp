/*
4.2 Топ K пользователей из лога 
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/
#include <iostream>

template <typename T>
struct User
{
    User(int id, int activity)
    :id(id), activity(activity)
    {
    }
    User()
    :id(0), activity(0)
    {
    }
    int id;
    int activity;
};
template <typename Comparator>
bool Minimal(int a, int b)
{
    return (a < b);
}

template <typename T, typename Comparator>
class Heap
{
private:
    int SiftUp();
    int SiftDown();
    Comparator cmp;
public:
    int Add();
    int ExtractTop();
    int Peek();
    Heap();
    ~Heap();
};

int SiftUp()
{

}

int SiftDown()
{

}

int Add()
{

}

int ExtractTop()
{

}

int Peek()
{

}

Heap::Heap(): User, Minimal()
{
}

Heap::~Heap()
{
}

int main()
{

}