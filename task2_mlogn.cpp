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

int main() {
    //length input
    int big_len;
    int small_len;
    std::cin >> big_len;
    std::cin >> small_len;
    //memory allocation
    int* big_array_ptr = (int*) malloc(big_len*sizeof(int));
    int* small_array_ptr = (int*) malloc(small_len*sizeof(int));
    //zero length failsafe
    if ((big_len == 0) || (small_len == 0)) {
        return 0;
    }
    //array input
    for (int i = 0; i < big_len; i++) {
        std::cin >> big_array_ptr[i];
    }
    for (int i = 0; i < small_len; i++) {
        std::cin >> small_array_ptr[i];
    }
    //counter init
    int lower_index = 0;
    int upper_index = big_len - 1;
    int mid = 0;
    //main cycle
    for (int i = 0; i < small_len; i++) {
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
            if (i>0) {
                std::cout << " ";
            }
            std::cout << small_array_ptr[i];
        }
        upper_index = big_len - 1;
    }
    //free memory
    free(small_array_ptr);
    free(big_array_ptr);
}