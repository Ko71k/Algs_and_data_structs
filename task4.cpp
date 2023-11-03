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

    //Greater sign overload for User
    bool operator>(const User &left, const User &right)
    {
        return left.activity > right.activity;
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

    template <class T>
    struct ForMaxHeap
    {
        bool operator()(const T& left, const T& right) const
        {
            return left > right;
        }
    };

    //class heap
    template <class T, class Comp=DefaultComparator<T>>
    class Heap
    {
    private:
        Comp comp;
        T* heap_pointer;
        int current;
        int capacity;

        //sifts the index element to the top (or till it stops climbing)
        void SiftUp(int index)
        {
            int parent = 0;
            while (index > 0)
            {
                parent = (index - 1) / 2;
                if (comp(heap_pointer[index], heap_pointer[parent]))
                {
                    Swap(parent, index);
                    index = parent;
                }
                else 
                {
                    break;
                }
            }
            
        }

        //sifts down the element heap_pointer[index]
        void SiftDown(int index)
        {
            int l_child = index * 2 + 1;
            int r_child = index * 2 + 2;
            int best = index;
            if (comp(heap_pointer[l_child], heap_pointer[best]) && (l_child < current))
            {
                best = l_child;
            }
            if (comp(heap_pointer[r_child], heap_pointer[best]) && (r_child < current))
            {
                best = r_child;
            }
            if (best != index)
            {
                Swap(index, best);
                SiftDown(best);
            }
        }

        void Swap(int first, int second)
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
            if (current == capacity)
            {
                Grow();
            }
            heap_pointer[current] = element;
            if (current != 0)
            {
                SiftUp(current);
            }
            current++;
            return;
        };

        //Swaps the bottom with the top, sifts up the top, deletes the bottom
        //to do: shrinking if current <= capacity / 2
        T ExtractTop()
        {
            T tmp = heap_pointer[0];
            Swap(0, current - 1);
            current--;
            SiftDown(0);
            return tmp;
        };

        //returns the current top element without extracting it
        T Peek()
        {
            return this->heap_pointer[0];
        };

        void Printer()
        {
            
            std::cout << "Current is: " << current << " Capacity is: " << capacity << std::endl;
            for (int i = 0; i < current; i++)
            {
                std::cout << "The " << i << " element is: " << heap_pointer[i] << std::endl;
            }
            return;
        }

        void Printer_Tree()
        {
            std::cout << "Current is: " << current << " Capacity is: " << capacity << std::endl;
            switch (current)
            {
            case 7 ... 14:
            {
                for (int i = 7; i < 14; i++)
                {
                    std::cout << heap_pointer[i] << "   ";
                }
                std::cout << std::endl;
            }
            case 3 ... 6:
            {
                for (int i = 3; i < current; i++)
                {
                    std::cout << heap_pointer[i] << "   ";
                }
                std::cout << std::endl;
            }
            case 1 ... 2:
            {
                std::cout << "      ";
                for (int i = 1; i < 3; i++)
                {
                    std::cout << heap_pointer[i] << "   ";
                }
                std::cout << std::endl;
            }
            default:
                std::cout << "       HEAD: " << heap_pointer[0];
                std::cout << std::endl;
                break;
            }
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
        };

        ~Heap()
        {
            delete[] heap_pointer;
        }
    };

    int main()
    {
        int N, K;
        //N and K
        std::cin >> N;
        std::cin >> K;
        int id, activity;
        std::cin >> id >> activity;
        User proto(id, activity);
        Heap<User, ForMaxHeap<User>>pudge(proto, ForMaxHeap<User>());

        for (int i = 1; i < N; i++)
        {
            std::cin >> id >> activity;
            User newcomer(id, activity);
            pudge.Add(newcomer);
        }

        Heap<User>pudge2(pudge.ExtractTop());    

        if (N < K)
        {
            K = N;
        };

        for (int i = 1; i < K; i++)
        {
            pudge2.Add(pudge.ExtractTop());
        }

        for (int i = 0; i < K; i++)
        {
            std::cout << pudge2.ExtractTop().id << " ";
        }


        return 0;

    }