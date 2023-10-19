#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX_SIZE 10000
#define NUMBER_OF_SENTENCES 1000

char* space(char* str){
    char* res = calloc(TEXT_MAX_SIZE, sizeof(char));
    int start = 0;
    while (str[start] == '\t' || str[start] == ' '){
        start++;
    }
    for (int i = 0; i < strlen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[strlen(str) - start] = '\0';
    return res;
}

int isNot7(char* str){
    if (strstr(str, "7") == NULL){
        return 1;
    }
    return 0;
}

int main()
{
    char **dyn_strs = malloc(NUMBER_OF_SENTENCES * sizeof(char*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dyn_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(char));
    } 
    char* str = calloc(TEXT_MAX_SIZE, sizeof(char));
    int index = 0;
    int len = 0;
    int result = 0;
    while (1){
        char symbol = getchar();
        str[index++] = symbol;
        if (symbol == '.' || symbol == '?' || symbol == ';'){
            str[index] = '\0';
            dyn_strs[len++] = str;
            index = 0;
            str = calloc(TEXT_MAX_SIZE, sizeof(char));
        }
        if (strstr(str, "Dragon flew away!") != NULL){
            dyn_strs[len++] = "Dragon flew away!";
            break;
        }
    }

    for (int i = 0; i < len - 1; i++){
        char* res = space(dyn_strs[i]);
        if (isNot7(res)){
            result++;
            printf("%s\n", res);
        }
    }
    printf("%s\n", dyn_strs[len - 1]);
    printf("Количество предложений до %d и количество предложений после %d", len - 1, result);
    return 0;
}