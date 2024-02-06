#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char** text = malloc(sizeof(char*));
    text[0] = calloc(1, sizeof(char));
    int overflow_sent = 1;
    int overflow_symb = 1;
    char* sent = calloc(1, sizeof(char));
    int index = 0;
    char symbol;
    while (1){
        symbol = getchar();
        if (symbol == '\n'){
            overflow_sent++;
            text[overflow_sent - 2] = sent;
            sent = calloc(1, sizeof(char));
            index = 0;
            overflow_symb = 1;
            if (strlen(text[overflow_sent - 2]) >= 4 && text[overflow_sent - 2][0] == 'F' && text[overflow_sent - 2][1] == 'i' && text[overflow_sent - 2][2] == 'n' && text[overflow_sent - 2][3] == '.'){
                overflow_sent--;
                break;
            }
            text = realloc(text, (overflow_sent) * sizeof(char*));
            text[overflow_sent - 1] = calloc(1, sizeof(char));
            continue;
        }
        sent[index++] = symbol;
        overflow_symb++;
        sent = realloc(sent, (overflow_symb) * sizeof(wchar_t));
        text[overflow_sent - 1] = realloc(text[overflow_sent - 1], (overflow_symb) * sizeof(wchar_t));
        text[overflow_sent - 1][overflow_symb - 1] = '\0';
        sent[overflow_symb - 1] = '\0';
    }
    for (int i = 0; i < overflow_sent; i++){
        printf("{%s}\n", text[i]);
    }
}
