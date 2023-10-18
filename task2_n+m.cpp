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
    int first_len;
    int second_len;
    std::cin >> first_len;
    std::cin >> second_len;

    //memory allocation
    int* ptr1 = (int*) malloc(first_len*sizeof(int));
    int* ptr2 = (int*) malloc(second_len*sizeof(int));

    //zero length failsafe
    if ((first_len == 0) || (second_len == 0)) {
        return 0;
    }

    //array input
    for (int i = 0; i < first_len; i++) {
        std::cin >> ptr1[i];
    }
    for (int i = 0; i < second_len; i++) {
        std::cin >> ptr2[i];
    }

    //counter init
    int run1 = 0;
    int run2 = 0;

    //main cycle, complexity O(m+n)
    do {
        if (ptr1[run1] == ptr2[run2]) {
            std::cout << ptr1[run1] << ' ';
            run1++;
            run2++;
        }
        else if (ptr1[run1] < ptr2[run2]) {
            run1++;
        }
        else {
            run2++;
        }
    } while ((run1 < first_len) && (run2 < second_len));

    //free memory
    free(ptr1);
    free(ptr2);
}