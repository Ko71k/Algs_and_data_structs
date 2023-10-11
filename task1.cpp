/*
1.2 Вернуть значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K
*/
#include <iostream>

bool bit_finder(int number, int position) {
    return (number >> position) & 1;
}

int main() {
    unsigned int input = 0;
    unsigned int wanted = 0;
    std::cin >> input;
    std::cin >> wanted;
    std::cout << bit_finder(input, wanted);
    return 0;
}
