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

struct Text func_4(struct Text text){
    const wchar_t* latters_rus = L"бвгджзйклмнпрстфхцчшщъьБВГДЖЗЙКЛМНПРСТФХЦЧШЩЪЬ";
    const wchar_t* latters_eng = L"bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    struct Text text_res;
    struct Sentence str;
    struct Sentence str_0;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    int flag, len, start;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        flag = 1;
        len = wcslen(str.sentence);
        start = len - 1;
        while (str.sentence[start] == ' ' || str.sentence[start] == ',' || str.sentence[start] == '.')
            start--;
        if (!((wcschr(latters_rus, str.sentence[start]) != NULL || wcschr(latters_eng, str.sentence[start]) != NULL)  && 
        (wcschr(latters_rus, str.sentence[start - 1]) != NULL || wcschr(latters_eng, str.sentence[start - 1]) != NULL) && 
        (wcschr(latters_rus, str.sentence[start - 2]) != NULL || wcschr(latters_eng, str.sentence[start - 2]) != NULL))){
            text_res.list_of_sentences[index++] = str;
            text_res.list_of_sentences = realloc(text_res.list_of_sentences, (index + 1) * sizeof(struct Sentence));
        }
    }
    text_res.count_of_sentences = index;
    return text_res;
}
