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

int cmp(const void *a, const void *b){
    const struct Sentence *f = (const struct Sentence *)a;
    const struct Sentence *s = (const struct Sentence *)b;
    int sum_f = 0;
    int sum_s = 0;

    for (int i = 0; i < wcslen((*f).sentence); i++){
        if ((*f).sentence[i] == ' ' || (*f).sentence[i] == ',' || (*f).sentence[i] == '.')
            break;
        sum_f += (int)(*f).sentence[i];
    }
    for (int i = 0; i < wcslen((*s).sentence); i++){
        if ((*s).sentence[i] == ' ' || (*s).sentence[i] == ',' || (*s).sentence[i] == '.')
            break;
        sum_s += (int)(*s).sentence[i];
    }
    
    if (sum_f > sum_s)
        return 1;
    if (sum_f < sum_s)
        return -1;
    else
        return 0;
    
}