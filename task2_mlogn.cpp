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

int Intersection_new(int* big_array_ptr, int big_len, int* small_array_ptr, int small_len, int* answer)
{
    //cannot split binary and exponential search into separate functions, because of
    //too many arguments
    int answer_counter = 0;
    int lower_index = 0;
    int upper_index = 0;
    int mid = 0;
    for (int i = 0; i < small_len; i++)
    {
        //exponential search
        int bound = 1;
        while ((upper_index + bound < big_len) && (big_array_ptr[upper_index + bound] < small_array_ptr[i]))
        {
            bound *= 2;
        }
        if (upper_index + bound > big_len)
        {
            upper_index = big_len - 1;
        }
        else 
        {
            upper_index += bound;
        }
        //binary search
        while (lower_index < upper_index) {
            mid = (lower_index + upper_index) / 2;
            if (big_array_ptr[mid] < small_array_ptr[i]) {
                lower_index = mid + 1;
            }
            else {
                upper_index = mid;
            }
        }
        //binary search done, lower_index is the result
        //checking if found element is equal (then add to answer) or greater (then ignore)
        if (small_array_ptr[i] == big_array_ptr[lower_index]) {
            answer[answer_counter] = small_array_ptr[i];
            answer_counter++;
        }
    }
    return answer_counter;
}

int Intersection(int* big_array_ptr, int big_len, int* small_array_ptr, int small_len, int* answer) {
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
            if (big_array_ptr[mid] < small_array_ptr[i]) {
                lower_index = mid + 1;
            }
            else {
                upper_index = mid;
            }
        }
        //binary search done, lower_index is the result
        if (small_array_ptr[i] == big_array_ptr[lower_index]) {
            answer[answer_counter] = small_array_ptr[i];
            answer_counter++;
        }
        upper_index = big_len - 1;
    }
    //return answer length
    return answer_counter;
}

int main() {
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
    for (int i = 0; i < first_len; i++) {
        std::cin >> first_array_ptr[i];
    }
    for (int i = 0; i < second_len; i++) {
        std::cin >> second_array_ptr[i];
    }

    //function call
    int answer_len = Intersection_new(first_array_ptr, first_len, second_array_ptr, second_len, answer);

    //output
    if (answer_len > 0) {
        std::cout << answer[0];
    }
    for (int i = 1; i < answer_len; i++) {
        std::cout << " " << answer[i];
    }
    //free memory
    free(first_array_ptr);
    free(second_array_ptr);
    free(answer);
}