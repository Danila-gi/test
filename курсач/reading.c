#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define END_OF_INPUT L"\n\n"

wchar_t** reading_of_sentences(int* ptr_index, int* ptr_len, wchar_t** dyn_strs){
    setlocale(LC_ALL, "");
    int overflow_str = 0;
    int overflow_mas = 0;

    wchar_t *str = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
    wchar_t symbol;

    size_t flag = 0;

    while (1){
        symbol = getwchar();

        if (symbol == L'\n'){
            if (flag == 1)
                break;
            flag = 1;
        }
        else{
            flag = 0;
        }
        str[(*ptr_index)++] = symbol;

        if ((TEXT_MAX_SIZE + overflow_str) <= (*ptr_index)){
            overflow_str++;
            str = realloc(str, (TEXT_MAX_SIZE + overflow_str) * sizeof(wchar_t));
        }

        if (symbol == L'.'){
            str[*ptr_index] = L'\0';
            dyn_strs[(*ptr_len)++] = str;
            overflow_str = 0;
            (*ptr_index) = 0;
            str = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
        }
        if ((NUMBER_OF_SENTENCES + overflow_mas) <= (*ptr_len)){
            overflow_mas++;
            dyn_strs = realloc(dyn_strs, (NUMBER_OF_SENTENCES + overflow_mas) * sizeof(wchar_t*));
            dyn_strs[NUMBER_OF_SENTENCES + overflow_mas - 1] = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
        }
    }

    free(str);
    return dyn_strs;
}