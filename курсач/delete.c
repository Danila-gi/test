#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "delete.h"
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define END_OF_INPUT L"\n\n"

struct Sentence{
    wchar_t* sentence;
    int len_of_sentence;
};

struct Text{
    int count_of_sentences;
    struct Sentence* list_of_sentences;
};

wchar_t* space(wchar_t* str){
    wchar_t* res = calloc(wcslen(str) + 1, sizeof(wchar_t));
    int start = 0;
    while (str[start] == '\t' || str[start] == ' ' || str[start] == '\n'){
        start++;
    }
    for (int i = 0; i < wcslen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[wcslen(str) - start] = '\0';
    return res;
}

int equal_sentences(wchar_t* str1, wchar_t* str2){
    int ind1 = 0;
    int ind2 = 0;
    if (wcslen(str1) != wcslen(str2))
        return 1;
    while (str1[ind1] != L'\0' || str2[ind2] != L'\0'){
        if (towlower(str1[ind1]) != towlower(str2[ind2]))
            return 1;
        ind1++;
        ind2++;
    }
    return 0;
}

struct Text delete_sentences(struct Text text){
    struct Text text_res;
    struct Sentence str, str_low;
    struct Sentence str_0, str_0_low;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        int flag = 1;
        for (int x = 0; x < index; x++){
            str_0 = text.list_of_sentences[x];
            if (equal_sentences(str.sentence, str_0.sentence) == 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            text_res.list_of_sentences[index++] = str;
            text_res.list_of_sentences = realloc(text_res.list_of_sentences, (index + 1) * sizeof(struct Sentence));
        }
    }
    text_res.count_of_sentences = index;
    return text_res;
}
