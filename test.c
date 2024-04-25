#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 2;
    int arr[size][size];
    arr[0][1] = 69420;
    printf("%p", arr[0][1]);
    void getValue (size_t x, size_t y, int arr[x][y]) {
        printf("%p", arr[0][1]);
        /*
        (*arr)[1][0] = 420;
        printf("%d", arr[1][0]);
        */
    }
    getValue(2,2, arr);
    return 0;
}
