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

//Less sign overload for User
bool operator<(const User &left, const User &right)
{
    return left.activity < right.activity;
}

//Greater sign overload for User
bool operator>(const User &left, const User &right)
{
    return left.activity > right.activity;
}
//Default comparator
template <class T>
struct DefComp
{
    bool operator() (const T& l, const T& r)
    {
        return l > r;
    }
};
//Template class heap
template <class T, class Comp=DefComp<T>>
class Heap
{
public:
    //Constructor
    Heap(Comp comp=Comp())
    {
        buffer = new T[3];
        current_size = 0;
        capacity = 3;
        this->comp = comp;
    }
    //Destructor
    ~Heap()
    {
        delete[] buffer;
    }
    //Function to get the top element
    const T& Peek() const 
    {
        return buffer[0];
    }
    //Function to extract top element
    void Extract()
    {
        if (current_size <= 0)
        {
            return;
        }
        current_size--;
        buffer[0] = buffer[current_size];
        heapify();
    }
    //Function to add an element
    void Add(const T& value)
    {
        current_size++;
        if (current_size >= capacity)
        {
            grow();
        }
        buffer[current_size - 1] = value;
        sift_up(current_size - 1);
    }
private:
    T* buffer;
    int current_size;
    int capacity;
    Comp comp;
    void sift_up(int idx)
    {
    while(idx > 0) 
        {
            int parent = (idx - 1) / 2;
            if( comp(buffer[idx], buffer[parent]) )
            {
                return;
            }
            std::swap( buffer[idx], buffer[parent] );
            {
                idx = parent;
            }
        }
    }
    void sift_down(int idx)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;
        if (left < current_size && comp(buffer[largest], buffer[left]))
        {
            largest = left;
        }
        if (right < current_size && comp(buffer[largest], buffer[right]))
        {
            largest = right;
        }
        if (largest != idx) 
        {
            std::swap(buffer[idx], buffer[largest]);
            sift_down(largest);
        }
    }
    //restores the heap
    void heapify()
    {
        if (current_size == 0 || current_size == 1) 
        {
            return;
        }
        for(int i = (current_size / 2) - 1; i >= 0; i--)
        {
            sift_down(i);
        }
    }
    //Function to dynamically allocate memory
    void grow()
    {
        capacity *= 2;
        T* new_buffer = new T[capacity];
        for (int i = 0; i < (int)current_size; i++)
        {
            new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
    }
};

int main() 
{
    int N, K;
    //input N, K
    std::cin >> N >> K;
    if (N == 0 || K == 0)
    {
        return 0;
    }
    User *a = new User[N];
    for (int i = 0; i < N; i++)
    {
        std::cin >> a[i].id >> a[i].activity;
    }

    Heap<User> *pudge = new Heap<User>();

    for(int i = 0; i < N; i++)
    {
        if (i >= K)
        {
            pudge->Add(a[i]);
            pudge->Extract();
        } 
        else
        {
            pudge->Add(a[i]);
        }
    }
    if (K < N)
    {
        N = K;
    }
    for (int i = 0; i < N; i++)
    {
        std::cout << pudge->Peek().id << " ";
        pudge->Extract();
    }
    return 0;
}