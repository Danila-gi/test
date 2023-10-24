#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX_SIZE 10000
#define NUMBER_OF_SENTENCES 1000
#define END_OF_INPUT "Dragon flew away!"

char* space(char* str){
    char* res = calloc(strlen(str) + 1, sizeof(char));
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

int hasNoSeven(char* str){
    if (strstr(str, "7") == NULL){
        return 1;
    }
    return 0;
}

char** allocate_memory_for_text(){
    char **dyn_strs = malloc(NUMBER_OF_SENTENCES * sizeof(char*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dyn_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(char));
    } 
    return dyn_strs;
}

void reading_of_sentences(int* ptr_index, int* ptr_len, int* ptr_result, char** dyn_strs, char* str){
    int overflow_str = 1;
    int overflow_mas = 1;
    while (1){
        char symbol = getchar();
        str[(*ptr_index)++] = symbol;
        if (symbol == '.' || symbol == '?' || symbol == ';'){
            str[*ptr_index] = '\0';
            dyn_strs[(*ptr_len)++] = str;
            *ptr_index = 0;
            str = calloc(TEXT_MAX_SIZE, sizeof(char));
        }
        if (strstr(str, END_OF_INPUT) != NULL){
            dyn_strs[(*ptr_len)++] = END_OF_INPUT;
            break;
        }
        if (TEXT_MAX_SIZE * overflow_str <= (*ptr_index)){
            str = realloc(str, TEXT_MAX_SIZE * (++overflow_str) * sizeof(char));
            dyn_strs[(*ptr_len)] = realloc(dyn_strs[(*ptr_len)], TEXT_MAX_SIZE * overflow_str * sizeof(char));
        }
        if (NUMBER_OF_SENTENCES * overflow_mas <= (*ptr_len)){
            dyn_strs = realloc(dyn_strs, NUMBER_OF_SENTENCES * (++overflow_mas) * sizeof(char*));
        }
    }
}

void output_of_sentences(int* ptr_len, int* ptr_result, char** dyn_strs){
    for (int i = 0; i < (*ptr_len) - 1; i++){
        char* sentence = space(dyn_strs[i]);
        if (hasNoSeven(sentence)){
            (*ptr_result)++;
            printf("%s\n", sentence);
        }
        free(sentence);
    }
    printf("%s\n", dyn_strs[(*ptr_len) - 1]);
}

void free_memory(char** dyn_strs, int len){
    for (int i = 0; i < len - 1; i++){
        free(dyn_strs[i]);
    }
    free(dyn_strs);
}

int main()
{
    char **dyn_strs = allocate_memory_for_text();
    char* str = calloc(TEXT_MAX_SIZE, sizeof(char));
    int index = 0;
    int* ptr_index = &index;

    int len = 0;
    int* ptr_len = &len;

    int result = 0;
    int* ptr_result = &result;

    reading_of_sentences(ptr_index, ptr_len, ptr_result, dyn_strs, str);

    output_of_sentences(ptr_len, ptr_result, dyn_strs);

    free_memory(dyn_strs, len);

    printf("Количество предложений до %d и количество предложений после %d", len - 1, result);
    return 0;
}