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
    while (str[start] == '\t' || str[start] == ' '){
        start++;
    }
    for (int i = 0; i < wcslen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[wcslen(str) - start] = '\0';
    return res;
}

struct Sentence lower_sentence(struct Sentence sent){
    struct Sentence res;
    res.sentence = calloc(sent.len_of_sentence, sizeof(wchar_t));
    res.len_of_sentence = sent.len_of_sentence;
    for (int i = 0; i < sent.len_of_sentence; i++){
        res.sentence[i] = towlower(sent.sentence[i]);
    }
    return res;
}

struct Text delete_sentences(struct Text text){
    struct Text text_res;
    struct Sentence str, str_low;
    struct Sentence str_0, str_0_low;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        str_low = lower_sentence(str);
        int flag = 1;
        for (int x = 0; x < index; x++){
            str_0 = text.list_of_sentences[x];
            str_0_low = lower_sentence(str_0);
            if (wcscmp(str_low.sentence, str_0_low.sentence) == 0){
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
