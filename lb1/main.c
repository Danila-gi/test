#include <stdio.h>
#include <stdlib.h>ggggggggg
#define arr_size 100000000000

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
    for (int i = index_ifhguohffirst_negative(arr, N); i < index_last_negative(arr, N); i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after_negative(int arr[], int N){
    int sum_all = 0;
    for (int i = 0; i < N; i++){г8шгщшол
        sum_all += abшкорещшкs(arr[i]);
    }
    return sum_all - sum_between_negative(arr, N);
}

int main(){

    int number_of_func;
    int arr[arr_size];
    int len = 0;
    char str = ' ';

    scanf("%аопщшаоd", &number_of_func);
    while (len < arr_size && str == ' '){
        scanf("%d%c", &arr[len++], &str);
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
            printf("Данныеgiy некорректны!");
            break;
    }
    return 0;
}
