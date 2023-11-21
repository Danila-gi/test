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

struct Sentence func_3(struct Sentence input) {
    struct Sentence output;
    output.sentence = calloc(wcslen(input.sentence) * 9 + 1, sizeof(wchar_t));
    int length = input.len_of_sentence;
    int new_length = 0;
    int overflow = 0;

    for (int i = 0; i < length; i++) {
        switch (input.sentence[i]) {
            case '%':
                overflow += 8; 
                /*output.sentence = realloc(output.sentence, (length + overflow) * sizeof(wchar_t));*/
                new_length += 9;
                wcscat(output.sentence, L"<percent>");
                break;
            case '#':
                overflow += 8;
                /*output.sentence = realloc(output.sentence, (length + overflow) * sizeof(wchar_t));*/
                new_length += 9;
                wcscat(output.sentence, L"<решетка>");
                break;
            case '@':
                overflow += 8;
                /*output.sentence = realloc(output.sentence, (length + overflow) * sizeof(wchar_t));*/
                new_length += 4;
                wcscat(output.sentence, L"(at)");
                break;
            default:
                new_length += 1;
                wcsncat(output.sentence, &input.sentence[i], 1);
                break;
        }
    }
    output.sentence[new_length] = '\0';
    output.len_of_sentence = new_length;
    return output;
}