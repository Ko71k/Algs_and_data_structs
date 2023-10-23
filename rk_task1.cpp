#include <iostream>

int Binary_Search(int* array, int array_len, int value)
{
    int answer_counter = 0;
    int lower_index = 0;
    int upper_index = array_len - 1;
    int mid = 0;
    while (lower_index < upper_index) {
            mid = (lower_index + upper_index) / 2;
            if (array[mid] < value) {
                lower_index = mid + 1;
            }
            else {
                upper_index = mid;
            }
        }
    if (value > array[array_len-1])
    {
        lower_index++;
    }
    return lower_index;
}

int main()
{
    int len = 0;
    std::cin >> len;

    int* array_ptr = (int*) malloc(len*sizeof(int));

    for (int i = 0; i < len; i++)
    {
        std::cin >> array_ptr[i];
    }
    int num = 0;
    std::cin >> num;
    std::cout << Binary_Search(array_ptr, len, num); 
    free(array_ptr);
    return 0;
}

