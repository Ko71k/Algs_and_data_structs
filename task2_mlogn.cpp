/*
2_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n >> m.
Найдите их пересечение.
Требования: Время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.. 
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. 
Внимание! 
В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером 
порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/

#include <iostream>
#include <cassert>

int Minimal(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Intersection(int* big_array_ptr, int big_len, int* small_array_ptr, int small_len, int* answer)
{
    //counter init
    int answer_counter = 0;
    int lower_index = 0;
    int upper_index = big_len - 1;
    int mid = 0;
    //main cycle
    for (int i = 0; i < small_len; i++) 
    {
        //binary search, 
        //lower_index is 0 or last step's result
        //upper_index is big_len - 1
        while (lower_index < upper_index) {
            mid = (lower_index + upper_index) / 2;
            if (big_array_ptr[mid] < small_array_ptr[i]) 
            {
                lower_index = mid + 1;
            }
            else
            {
                upper_index = mid;
            }
        }
        //binary search done, lower_index is the result
        if (small_array_ptr[i] == big_array_ptr[lower_index])
        {
            answer[answer_counter] = small_array_ptr[i];
            answer_counter++;
        }
        upper_index = big_len - 1;
    }
    //return answer length
    return answer_counter;
    //down there it is broken down to functions and optimized with exponential search
}

int Binary_search(int* array_ptr, int value, int lower_index, int upper_index)
{
    int mid = 0;
    while (lower_index < upper_index)
    {
        mid = (lower_index + upper_index) / 2;
        if (array_ptr[mid] < value) 
        {
            lower_index = mid + 1;
        }
        else
        {
            upper_index = mid;
        }
    }
    return lower_index;
}

int Exponential_search(int * array_ptr, int array_len, int value, int starting_point)
{   
    int slider1 = 1;
    int slider = starting_point + slider;
    while ((slider < array_len - 1) && (array_ptr[slider] < value))
    {
        slider1 *=2;
        slider = starting_point + slider;
    }
    return Binary_search(array_ptr, value, slider/2, Minimal(array_len - 1, slider + 1));
}

int Intersection_With_Exp(int* big_array_ptr, int big_len, int* small_array_ptr, int small_len, int* answer) 
{
    //counter init
    int answer_counter = 0;
    int lower_index = 0;
    int mid = 0;
    //main cycle
    for (int i = 0; i < small_len; i++) 
    {
       lower_index = Exponential_search(big_array_ptr, big_len, small_array_ptr[i], lower_index + 1);
        //binary search done, lower_index is the result
        if (small_array_ptr[i] == big_array_ptr[lower_index]) 
        {
            answer[answer_counter] = small_array_ptr[i];
            answer_counter++;
        }
    }
    //return answer length
    return answer_counter;
}

int main() 
{
    //length input
    int first_len;
    int second_len;
    std::cin >> first_len;
    std::cin >> second_len;
    //zero length assertion
    assert(!(first_len == 0) || (second_len == 0));

    //memory allocation
    int* first_array_ptr = (int*) malloc(first_len*sizeof(int));
    int* second_array_ptr = (int*) malloc(second_len*sizeof(int));
    int* answer = (int*) malloc(second_len*sizeof(int));

    //arrays input
    for (int i = 0; i < first_len; i++) 
    {
        std::cin >> first_array_ptr[i];
    }
    for (int i = 0; i < second_len; i++) 
    {
        std::cin >> second_array_ptr[i];
    }

    //function call
    int answer_len = Intersection_With_Exp(first_array_ptr, first_len, second_array_ptr, second_len, answer);

    //output
    if (answer_len > 0)
    {
        std::cout << answer[0];
    }
    for (int i = 1; i < answer_len; i++) 
    {
        std::cout << " " << answer[i];
    }
    //free memory
    free(first_array_ptr);
    free(second_array_ptr);
    free(answer);
}