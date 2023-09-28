#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define ARR_SIZE 100


int main(){
    int number_of_func;
    int arr[ARR_SIZE];
    char end;
    int len = 0;
    scanf("%d", &number_of_func);
    end = getchar();

    while (end != '\n')
    {
        scanf("%d", &arr[len++]);
        end = getchar();
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