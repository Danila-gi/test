#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10

wchar_t** allocate_memory_for_text(){
    wchar_t **dyn_strs = malloc(NUMBER_OF_SENTENCES * sizeof(wchar_t*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dyn_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
    } 
    return dyn_strs;
}

void free_memory(wchar_t** dyn_strs, int len){
    for (int i = 0; i < len - 1; i++){
        free(dyn_strs[i]);
    }
    free(dyn_strs);
}