#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Sentence{
    wchar_t* sentence;
    int len_of_sentence;
};

struct Text{
    int count_of_sentences;
    struct Sentence* list_of_sentences;
};

int func_1(struct Text text){
    int sum = 0; 
    int position, start, len;
    wchar_t* result;
    wchar_t* str;
    wchar_t* search = L" sec ";
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i].sentence;
        while (wcsstr(str, search) != NULL){
            result = wcsstr(str, search);
            position = result - str;
            start = position - 1;
            while (1)
            {
                if (iswdigit(str[start]))
                    start--;
                else{
                    start++;
                    break;
                }
            }
            if (start <= position - 1){
                char* number = calloc(position - start + 1, sizeof(char));
                for (int x = 0; x < (position - start); x++){
                    number[x] = str[start + x];
                }
                sum += atoi(number);
                free(number);
            }
            str = wcsstr(str, search) + 5;
        }
    }
    sum = sum / 60;
    return sum;
}