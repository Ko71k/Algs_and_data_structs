// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка [Li, Ri].
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
// N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 10^9].

#include <cmath>
#include <iostream>

struct Point
{
    int left;
    int right;
    Point()
    {
    }
};
 //Less sign overload for Point
bool operator<(const Point &left, const Point &right)
{
    return left.left < right.left;
};

//Default comparator
template<class T>
struct CmpDefault   
{
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};

template<class T, class Comparator = CmpDefault<T>>
void Merge(T* array, const int& left, const int& middle, const int& right, T* result, Comparator cmp = CmpDefault<T>()) 
{
    int size = right - left + 1;
    int leftIndex = left;
    int rightIndex = middle;
    for (int k = 0; k < size; ++k) 
    {
        if (leftIndex < middle && rightIndex <= right) 
        {
            if (cmp(array[leftIndex], array[rightIndex])) 
            {
                result[k] = array[leftIndex];
                ++leftIndex;
            }
            else 
            {
                result[k] = array[rightIndex];
                ++rightIndex;
            }
        } else if (leftIndex < middle) 
        {
            result[k] = array[leftIndex];
            ++leftIndex;
        } 
        else
        {
            result[k] = array[rightIndex];
            ++rightIndex;
        }
    }
}

template<class T, class Comparator = CmpDefault<T>>
void MergeSort(T* array, const int& left, const int& right, Comparator cmp = CmpDefault<T>()) 
{
    if (right - left < 1) 
    {
        return;
    }
    int middle = ceil(float(left + right) / 2.);
    MergeSort(array, left, middle - 1);
    MergeSort(array, middle, right);
    int size = right - left + 1;
    auto* result = new Point[size];
    Merge(array, left, middle, right, result);
    std::copy(result, result + size, array + left);
    delete[] result;
}

int Summing(Point* array, int array_len)
{
    int answer = 0;
    int current_location = 0;
    for (int i = 0; i < array_len; i++)
    {
        if (array[i].left < current_location && array[i].right > current_location)
        {
            answer += array[i].right - current_location;
            current_location = array[i].right;
        }
        else if (array[i].right > current_location)
        {
            answer += array[i].right - array[i].left;
            current_location = array[i].right;
        }
    }
    return answer;
}

int main() 
{
    int points_amount = 0;
    std::cin >> points_amount;
    Point *points_array = new Point[points_amount];
    for (int i = 0; i < points_amount; i++)
    {
        std::cin >> points_array[i].left >> points_array[i].right;
    }
    MergeSort(points_array, 0, points_amount - 1);
    std::cout << Summing(points_array, points_amount);
    //delete[] points_array;
    return 0;
}