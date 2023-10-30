/*
4.2 Топ K пользователей из лога 
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/
#include <iostream>

//structure User, got id and times user log on
struct User
{
    User(int id, int activity)
    :id(id), activity(activity)
    {
        this->id = id;
        this->activity = activity;
    }
    User()
    :id(0), activity(0)
    {
    }
    int id;
    int activity;
};

// >> overload for User
std::istream& operator>>(std::istream &input, User &user)
{
    input >> user.id >> user.activity;
    return input;
}

// << overload for User
std::ostream& operator<<(std::ostream &output, const User &user)
{
    output << " " << user.id << " " << user.activity << " ";
    return output;
}

//Less sign overload for User
bool operator<(const User &left, const User &right)
{
    return left.activity < right.activity;
}


//default comparator
template <class T>
struct DefaultComparator
{
    bool operator()(const T& left, const T& right) const
    {
        return right < left;
    }
};

//class heap
template <class T, class Comp=DefaultComparator<T>>
class Heap
{
private:
    T* buf;
    size_t size;
    size_t capacity;

    void SiftUp();
    void SiftDown();
    void Grow();
public:
    void Add(T element);
    T ExtractTop();
    T Peek();

    Heap();
    ~Heap();
};


template <class T, class Comp=DefaultComparator>
Heap(Comp comp=DefaultComparator>()) -> <Heap, Comp> 
{
    comp();
    this.buf = NULL;
    this.size = NULL;
    this.capacity = NULL;
}
/*
template <class T, class Comp=DefaultComparator<T>>
Heap(Comp comp=DefaultComparator<T>())
{
    comp();
    this.buf = NULL;
    this.size = NULL;
    this.capacity = NULL;
}
*/

template <class T>
Heap<T>::~Heap()
{
    if (buf != NULL)
    {
        delete [] buf;
    }
}

template <class T>
void SiftUp()
{

}

template <class T>
void SiftDown()
{

}

template <class T>
void Add(T element)
{

}
template <class T>
T ExtractTop()
{

}
template <class T>
T Peek()
{

}

int main()
{
    User a;
    User b(3, 5);
    std::cin >> a;
    if (a<b)
    {
        std::cout << "1";
    }
    else
    {
        std::cout << "2";
    }

    std::cout << a << b;
}