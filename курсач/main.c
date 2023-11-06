#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define END_OF_INPUT L"\n\n"

struct Sentence{
    wchar_t* sentence;
    int len_of_sentence;
};

struct Text{
    int len_of_Text;
    int count_of_sentences;
    struct Sentence* list_of_sentences;
};

wchar_t** allocate_memory_for_text(){
    wchar_t **dyn_strs = malloc(NUMBER_OF_SENTENCES * sizeof(wchar_t*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dyn_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
    } 
    return dyn_strs;
}

wchar_t** reading_of_sentences(int* ptr_index, int* ptr_len, wchar_t** dyn_strs){
    int overflow_str = 0;
    int overflow_mas = 0;

    wchar_t *str = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));

    while (1){
        wchar_t symbol = getwchar();

        str[(*ptr_index)++] = symbol;

        if ((TEXT_MAX_SIZE + overflow_str) <= (*ptr_index)){
            overflow_str++;
            str = realloc(str, (TEXT_MAX_SIZE + overflow_str) * sizeof(wchar_t));
        }

        if (wcsstr(str, END_OF_INPUT) != NULL){
            break;
        }

        if (symbol == L'.'){
            str[*ptr_index] = '\0';
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

void free_memory(wchar_t** dyn_strs, int len){
    for (int i = 0; i < len - 1; i++){
        free(dyn_strs[i]);
    }
    free(dyn_strs);
}

int main()
{
    wchar_t **dyn_strs = allocate_memory_for_text();
    setlocale(LC_CTYPE, "");
    int index = 0;
    int* ptr_index = &index;

    int len = 0;
    int* ptr_len = &len;

    dyn_strs = reading_of_sentences(ptr_index, ptr_len, dyn_strs);

    struct Text text = {0, 0, malloc((*ptr_len) * sizeof(struct Sentence))};
    text.count_of_sentences = (*ptr_len);
    int count_symbols_of_text = 0;
    for (int i = 0; i < (*ptr_len); i++){
        struct Sentence sen;
        sen.sentence = dyn_strs[i];
        sen.len_of_sentence = wcslen(dyn_strs[i]);
        count_symbols_of_text += wcslen(dyn_strs[i]);
        (text.list_of_sentences)[i] = sen;
    }
    text.count_of_sentences = (*ptr_len);
    text.len_of_Text = count_symbols_of_text;

    for (int i = 0; i < text.count_of_sentences; i++){
        wprintf(L"%ls-%d\n", text.list_of_sentences[i].sentence, text.list_of_sentences[i].len_of_sentence);
    }

    wprintf(L"Info of text: %d ---- %d", text.count_of_sentences, text.len_of_Text);

    free_memory(dyn_strs, len);
    return 0;
}