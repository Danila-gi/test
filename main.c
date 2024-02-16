#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

long long sum(char* str){
    long long res = 0;
    char* istr = strtok(str, " ");
    while (istr != NULL)
    {
        res += atoi(istr);
        istr = strtok (NULL, " ");
    }
    return res;
}

long long pr(char* str){
    long long res = 1;
    char* istr = strtok(str, " ");
    while (istr != NULL)
    {
        res *= atoi(istr);
        istr = strtok (NULL, " ");
    }
    return res;
}

long long list_dir(const char *dirPath, long long result)
{
    DIR *dir = opendir(dirPath);
    if(dir) {
        struct  dirent *de = readdir(dir);
        while (de) {
            char file_path[256];
            char* new_dir = calloc(strlen(dirPath) + 4, sizeof(char));
            char* file_dir;
            char* line = calloc(100, sizeof(char));
            FILE *file;
            sprintf(file_path, "%s/%s", dirPath, de->d_name);
            if (strstr(de->d_name, "add") != NULL){
                sprintf(new_dir, "%s/%s", dirPath, de->d_name);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += list_dir(new_dir, 0);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= list_dir(new_dir, 0);
                }
            }
            if (strstr(de->d_name, "mul") != NULL){
                sprintf(new_dir, "%s/%s", dirPath, de->d_name);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += list_dir(new_dir, 1);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= list_dir(new_dir, 1);
                }
            }
            if (strlen(de->d_name) > 4 && (de->d_name)[strlen(de->d_name) - 4] == '.' && (de->d_name)[strlen(de->d_name) - 3] == 't' && (de->d_name)[strlen(de->d_name) - 2] == 'x' && (de->d_name)[strlen(de->d_name) - 1] == 't'){
                file_dir = calloc(strlen(dirPath) + strlen(de->d_name) + 3, sizeof(char));
                sprintf(file_dir, "%s/%s", dirPath, de->d_name);
                file = fopen(file_dir, "r");
                fgets(line, 100, file);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += sum(line);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= pr(line);
                }
            }
            file = fopen(file_path, "r");
            de = readdir(dir);
        }
    }
    closedir(dir);
    return result;
}

int main(){
    DIR *dir = opendir("./tmp");
    struct  dirent *de = readdir(dir);
    long long result = 0;
    while (de){
        if (strstr(de->d_name, "add") != NULL){
            result = list_dir("./tmp/add", 0);
            break;
        }
        if (strstr(de->d_name, "mul") != NULL){
            result = list_dir("./tmp/mul", 1);
            break;
        }
        de = readdir(dir);
    }
    char * filename = "result.txt";
    FILE *fp = fopen(filename, "w");
    if(fp)
    {
        char result_str[128];
        sprintf(result_str, "%lld", result);
        fputs(result_str, fp);
        fclose(fp);
    }
}
