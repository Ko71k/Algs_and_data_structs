#include <iostream>
/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль
Требования: к дополнительной памяти: O(n). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция Partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.
Реализуйте стратегию выбора опорного элемента “медиана трёх”.
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

template<typename T, typename Comparator = std::greater<T>>
int median(T * a, int p, int r, Comparator comp = Comparator())
{
    int mid = (p + r) / 2;

    //if (a[p] > a[r])
    if (comp(a[p], a[r]))
    {
        //if (a[r] > a[mid])
        if (comp(a[r], a[mid]))
        {
            return r;
        }
        else
        {
            return mid;
        }
    }
    else
    {
        //if (a[p] > a[mid])
        if (comp(a[p], a[mid]))
        {
            return p;
        }
        else
        {
            return mid;
        }
    }
}

//Default comparator

template<typename T, typename Comparator = std::less<T>>
int Partition(T * array, int left, int right, Comparator comp = Comparator())
{
    std::swap(array[right], array[median(array, left, right)]);
    int j = left;
    for(int i = left; i < right; i++)
        if(comp(array[i], array[right]))
        {
            std::swap(array[i], array[j]);
            j++;
        }
    std::swap(array[j], array[right]);
    return j;
}

template<typename T, typename Comparator = std::less<T>>
int KStatistics(T * array, int n, int k, Comparator comp = Comparator())
{
    int left = 0;
    int right = n - 1;
    int q = Partition(array, left, right, comp);
    while(q != k)
    {
        if(k < q)
            right = q - 1;
        else
            left = q + 1;
        q = Partition(array, left, right, comp);
    }
    return array[q];
}

int main()
{
    int n;
    std::cin >> n;

    int * array = new int[n];
    for(int i = 0; i < n; i++)
        std::cin >> array[i];
    //KStatistics for 10%
    std::cout << KStatistics(array, n, n/10) << std::endl;
    //KStatistics for median
    std::cout << KStatistics(array, n, n/2) << std::endl;
    //KStatistics for 90%
    std::cout << KStatistics(array, n, n - n/10) << std::endl;
    delete[] array;
    return 0;
}