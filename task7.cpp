#include <iostream>
using std::string;
const int k = 256;

void countingSort(string * str, int n, int * c, int byte){
    for(int i = 0; i < k; i++)
        c[i] = 0;
    for(int i = 0; i < n; i++)
        c[str[i][byte]]++;
    int sum = 0;
    for(int i = 0; i < k; i++){
        int tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }
    string * b = new string[n];
    for(int i = 0; i < n; i++){
        b[c[str[i][byte]]++] = str[i];
    }
    for(int i = 0; i < n; i++)
        str[i] = b[i];
    delete[] b;
}

void MSDSort(string * str, int n, int byte){
    if(n <= 1)
        return;
    int * c = new int[k + 1];
    c[k] = n - 1;
    countingSort(str, n, c, byte);
    for(int i = 1; i < k; i++)
        MSDSort(str + c[i], c[i + 1] - c[i], byte + 1);
    delete[] c;
}

int main()
{
    int n = 0;
    string * str = new string[100000];
    while(!std::cin.eof())
    {
        std::cin >> str[n];
        n++;
        //checking for \0
        if(str[n - 1].empty())
        {
            n--;
            break;
        }
    }
    MSDSort(str, n, 0);
    for(int i = 0; i < n; i++)
        std::cout << str[i] << '\n';
    delete[] str;
}
