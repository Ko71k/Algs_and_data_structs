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
        return left < right;
    }
};

//class heap
template <class T, class Comp=DefaultComparator<T>>
class Heap
{
private:
    Comp comp;
    T* heap_pointer;
    int type_size;
    int current;
    int capacity;

    size_t Element(size_t addr)
    {
        return addr/type_size;
    }

    //sifts up the element heap_pointer[index]
    void SiftUp(size_t index)
    {
        if (!comp(heap_pointer[(index - 1) / 2], heap_pointer[index]))
        {
            Swap((index - 1) / 2, index);
            SiftUp((index - 1) / 2);
        }
        return;
    };

    //sifts down the element heap_pointer[index]
    void SiftDown(size_t index)
    {
        if (index * 2 >= current)
        {
            size_t better_child, worse_child;
            if (comp(heap_pointer[index * 2 + 1], heap_pointer[index * 2 + 1]))
            {
                better_child = index * 2 + 1;
                worse_child = index * 2 + 2;
            }
            else
            {
                better_child = index * 2 + 2;
                worse_child = index * 2 + 1;
            }

            if (!comp(heap_pointer[index], heap_pointer[better_child]))
            {
                Swap(index, better_child);
                SiftDown(better_child);
            }
            else if (!comp(heap_pointer[index], heap_pointer[worse_child]))
            {
                Swap(index, worse_child);
                SiftDown(worse_child);
            }
        }
        return;
    };

    void Swap(size_t first, size_t second)
    {
        T tmp = heap_pointer[first];
        heap_pointer[first] = heap_pointer[second];
        heap_pointer[second] = tmp;
    }
    
    void Grow()
    {
        T* new_heap = (T *) new T[current*2];
        for (int i = 0; i < current; i++)
        {
            new_heap[i] = heap_pointer[i];
        }
        T* tmp = heap_pointer;
        capacity *= 2;
        heap_pointer = new_heap;
        delete tmp;
    };
public:
    //Adds an element to the end, then sifts it up
    void Add(T element)
    {
        if (current + 1 > capacity)
        {
            Grow();
        }
        heap_pointer[current] = element;
        SiftUp(current);
        current++;
        return;
    };

    //Swaps the bottom with the top, sifts up the top, deletes the bottom
    //to do: shrinking if current <= capacity / 2
    T ExtractTop()
    {
        T tmp = heap_pointer[0];
        Swap(0, capacity);
        SiftDown(0);
        current--;
        return tmp;
    };

    //returns the current top element without extracting it
    T Peek()
    {
        return this->heap_pointer[0];
    };

    int Printer()
    {
        for (int i = 0; i < current; i++)
        {
            std::cout << heap_pointer[i] << std::endl;
        }
        return current;
    }
    int Printer2()
    {
        for (int i = 0; i < current; i++)
        {
            std::cout << heap_pointer[i].id << " ";
        }
        return current;
    }
    
    
    //to do
    T* Heapify()
    {

    };

    //constructor
    Heap(T a, Comp comp=DefaultComparator<T>())
    {
        heap_pointer = new T[1];
        heap_pointer[0] = a;
        capacity = 1;
        current = 1;
        type_size = sizeof(T);
    };

    ~Heap()
    {
        delete heap_pointer;
    }
    // ~Heap() 
    // {
    //     if (heap_pointer != nullptr)
    //     {
    //         delete
    //         //delete [] heap_pointer;
    //     }
    // }
};

// int main2()
// {
//     User myuser1(1,2), myuser2(2,3);
//     Heap <User>myheap(myuser1);
//     std::cout << myheap.Peek() << std::endl;
//     myheap.Add(myuser2);
//     std::cout << myheap.Peek() << std::endl;
//     // std::cout << "Printer: \n";
//     // myheap.Printer();
// }

int main()
{
    int N, K;
    std::cin >> N;
    std::cin >> K;
    int id, activity;
    User proto;
    Heap <User>pudge(proto);


    std::cout<< "The N: " << N << " The K: " << K << std::endl;


    for (int i = 0; i < N; i++)
    {
        std::cout<< "Waiting: ";
        std::cin >> id >> activity;
        User newcomer(id, activity);
        pudge.Add(newcomer);
    }
    pudge.ExtractTop();
    pudge.Printer2();
    pudge.~Heap();
}