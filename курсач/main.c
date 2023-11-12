#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "reading.h"
#include "delete.h"
#include "memory.h"
#include "function_1.h"
#include "function_2.h"

struct Sentence{
    wchar_t* sentence;
    int len_of_sentence;
};

struct Text{
    int count_of_sentences;
    struct Sentence* list_of_sentences;
};

void output(struct Text text){
    for (int i = 0; i < text.count_of_sentences; i++){
        wprintf(L"%ls\n", text.list_of_sentences[i].sentence);
    }
}

int main()
{
    wprintf(L"Course work for option 5.14, created by Danila Ivanov.\n");
    int num_of_func;
    scanf("%d\n", &num_of_func);
    if (num_of_func == 5){
        wprintf(L"0 - вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности)\n");
        wprintf(L"1 - вызов функции под номером 1 из списка задания\n");
        wprintf(L"2 - вызов функции под номером 2 из списка задания\n");
        wprintf(L"3 - вызов функции под номером 3 из списка задания\n");
        wprintf(L"4 - вызов функции под номером 4 из списка задания\n");
        wprintf(L"5 - вывод справки о функциях, которые реализует программа.\n");
    }
    else {
        wchar_t **dyn_strs = allocate_memory_for_text();
        setlocale(LC_CTYPE, "");
        int index = 0;
        int* ptr_index = &index;

        int len = 0;
        int* ptr_len = &len;

        dyn_strs = reading_of_sentences(ptr_index, ptr_len, dyn_strs);

        struct Text text = {0, malloc((*ptr_len) * sizeof(struct Sentence))};
        text.count_of_sentences = (*ptr_len);
        for (int i = 0; i < (*ptr_len); i++){
            struct Sentence sen;
            sen.sentence = space(dyn_strs[i]);
            sen.len_of_sentence = wcslen(dyn_strs[i]);
            (text.list_of_sentences)[i] = sen;
        }
        text.count_of_sentences = (*ptr_len);

        text = delete_sentences(text);

        if (num_of_func == 0){
            output(text);
        }
        if (num_of_func == 1){
            wprintf(L"%d\n", func_1(text));
        }
        if (num_of_func == 2){
            qsort(text.list_of_sentences, text.count_of_sentences, sizeof(struct Sentence), cmp);
            output(text);
        }

        free_memory(dyn_strs, len);
        return 0;
    }
}