#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1200
#define ARR_SIZE 100

int index_first_negative(int arr[], int N){
    for (int i = 0; i < N; i++){
        if (arr[i] < 0){
            return i;
        }
    }
}

int index_last_negative(int arr[], int N){
    for (int j = N - 1; j >= 0; j--){
        if (arr[j] < 0){
            return j;
        }
    }
}

int sum_between_negative(int arr[], int N){
    int sum = 0;
    for (int i = index_first_negative(arr, N); i < index_last_negative(arr, N); i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after_negative(int arr[], int N){
    int sum_all = 0;
    for (int i = 0; i < N; i++){
        sum_all += abs(arr[i]);
    }
    return sum_all - sum_between_negative(arr, N);
}

int main(){
    int number_of_func;
    char str[SIZE];
    int arr[ARR_SIZE];
    fgets(str,SIZE,stdin);

    char *str0 = strtok(str, " ");
    sscanf(str0, "%d", &number_of_func);
    str0 = strtok(NULL, " ");
    int len = 0;

    while (str0 != NULL)
    {
        sscanf(str0, "%d", &arr[len++]);
        str0 = strtok(NULL, " ");
    }

    switch (number_of_func){
        case 0:
            printf("%d\n", index_first_negative(arr, len));
            break;

        case 1:
            printf("%d\n", index_last_negative(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr, len));
            break;

        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, len));
            break;
        
        default:
            printf("Данные некорректны");
            break;
    }

    return 0;
}
