#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"

int sum_before_and_after_negative(int arr[], int N){
    int sum_all = 0;
    for (int i = 0; i < N; i++){
        sum_all += abs(arr[i]);
    }
    return sum_all - sum_between_negative(arr, N);
}